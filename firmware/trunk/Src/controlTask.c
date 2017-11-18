#include "stm32f4xx_hal.h"
#include "xprintf.h"
#include "stdlib.h"
#include "board.h"
#include "controlTask.h"
#include "pwm.h"
#include "libUART.h"
#include "uartTask.h"
#include <stdbool.h>

/////////////////////////////////////////////////////
// 1. -----sprawdzic nowy PID_NEW
// 2. sprawdzic PID na podstawie wartosci chwilowej pradu (wywalic srednia)
// 3. sprawdzic PID z wyliczaniem czlonu integral bez czasu dt
// 4. ADC+DMA w trybie ciągłym

////////////// PYTANIA //////////////
// 1. jaki okres probkowania ?
// 2. wartosc srednia ?
// 3. dt w PI ?
// 4. prad czy wartosc adc ?

/* Macros and defines */
#define dt 0.0001 // 100 us
#define EPSILON 0.01
#define ADC_REF 3000ULL
#define MAX_12_BIT 4096ULL
#define MAX_CURRENT 15000 //mA

/* --- Global variables declaration --- */
volatile uint32_t adcResult = 0;         //ADC DMA buffer
bool newMotorState = false;

/* --- External variables --- */
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;

/* --- Static functions --- */
static void motorControl(void);
static void stopMotor(void);
static void startMotor(void);

/* --- Define motor object --- */
motorObject_t motor =
{
  .frequency = 0,
  .current = 0,
  .speed = 0,
  .state = STOP_MOTOR,
  .stop = stopMotor,
  .start = startMotor,
};

motorObject_t *getMotorObject(void)
{
  return &motor;
}

#define ADC_BUFFER_SIZE 512
uint32_t adcBuffer[ADC_BUFFER_SIZE] = {0};
int16_t currPos = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  adcBuffer[currPos++] = adcResult;
  currPos = currPos % ADC_BUFFER_SIZE;
}

void startADC(void)
{
  HAL_ADC_Start_DMA(&hadc1, &adcResult, 1);
}

void stopADC(void)
{
  HAL_ADC_Stop_DMA(&hadc1);
}

void getMotorLimits(currentType_t *current, speedType_t *speed)
{
  *current = motor.currentLimit;
  *speed = motor.speedLimit;
}

static float getMotorCurrent(void)
{
  uint32_t current = 0;
  uint32_t adcCpy = adcResult;
  current = (uint32_t)((MAX_CURRENT * adcCpy) / MAX_12_BIT);
  return ((float)current) / 1000;
}

float getMotorAverageCurrent(void)
{
  uint32_t current = 0, average = 0;
  uint32_t sum = 0;
  uint16_t i = 0;

  for (i = 0; i < ADC_BUFFER_SIZE; i++)
    sum += adcBuffer[i];

  average = sum >> 9;
  current = (uint32_t)((MAX_CURRENT * average) / MAX_12_BIT);
  return ((float)current) / 1000;
}

static float limitVar(float var, float limit) // returns value in range <0:limit>
{
  if (var > limit)
    var = limit;
  else if (var < 0)
    var = 0;

  return var;
}

#define ABS(x)  (((x) < 0) ? -(x) : (x))
#define TH_VAL 2
#define INT_THRESHOLD_MAX TH_VAL
#define INT_THRESHOLD_MIN -TH_VAL

static float integral_PI = 0;
static float PI(float Kp, float Ki, float varRef, float var, float limit)
{
  float error, out;

  error = varRef - var;
  // integral_PI += error * dt;
  integral_PI += error;

  // windup #1 - wylaczenie integratora
  // if (integral_PI > INT_THRESHOLD_MAX || integral_PI < INT_THRESHOLD_MIN)
  //   integral_PI = 0;

  // windup #2 - ograniczenie wartosci integratora
  if (integral_PI > INT_THRESHOLD_MAX)
    integral_PI = INT_THRESHOLD_MAX;
  else if (integral_PI < INT_THRESHOLD_MIN)
    integral_PI = INT_THRESHOLD_MIN;

  out = Kp * error + Ki * integral_PI;

  return limitVar(out, limit); // ograniczenie regulatora
}

static float PI_NEW(float Kp, float Ti, float varRef, float var, float limit)
{
  float error, out;

  error = varRef - var;
  integral_PI += Kp * error / Ti;

  out = Kp * error + integral_PI;

  return limitVar(out, limit);
}

static float errorPrev_PID = 0, integral_PID = 0;
static float PID(float Kp, float Ki, float Kd, float varRef, float var, float limit)
{
  float error, derivative, out;

  error = varRef - var;
  // if (abs(error) > EPSILON)
  integral_PID += error * dt;

  derivative = (error - errorPrev_PID) / dt;
  out = Kp * error + Ki * integral_PID + Kd * derivative;
  errorPrev_PID = error;

  return limitVar(out, limit);
}

/* Called from ADC Conv. Compl. Interrupt */
static void motorControl(void)
{
  static float gamma = 0;

  switch (motor.state)
    {
    case STOP_MOTOR:
      break;

    case SPEED_CONTROL:
      // iRef = PID(Kp_omega, Ki_omega, Kd_omega, omegaRef, omega, 1); //limit 1 w jw
      // i = getMotorCurrent();
      // gamma = PID(Kp_i, Ki_i, Kd_i, iRef, i, 1);
      // setDutyCycle(gamma);
      break;

    case TORQUE_CONTROL:
      motor.current = getMotorCurrent();
      gamma = PI(motor.currentPID.kp, motor.currentPID.ki, motor.currentPID.ref, motor.current, 0.9);
      setDutyCycle(gamma);
      break;

    default:
      break;
    }
}

// Control interrupt
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4) // 100 us
    {
      motorControl();
    }
}

void stopControlInterrupt(void)
{
  HAL_TIM_Base_Stop_IT(&htim4);
}

void startControlInterrupt(void)
{
  HAL_TIM_Base_Start_IT(&htim4);
}

static void stopMotor(void)
{
  xprintf("Silnik STOP\n");
  RED_LED_OFF();
  stopPWM();
  stopADC();
  stopControlInterrupt();
  integral_PI = 0; // przerobic
  integral_PID = 0;
  errorPrev_PID = 0;
}

static void startMotor(void)
{
  xprintf("Silnik START...\n");
  RED_LED_ON();
  setSwitchingFrequency(motor.frequency);
  setDutyCycle(0.5);
  startADC();
  startPWM();

  if (motor.state != PWM_CONTROL)
    startControlInterrupt();
}

void updateMotorState(void)
{
  newMotorState = true;
}

void motorCheck(void)
{
  if (!newMotorState)
    return;

  newMotorState = false;

  switch (motor.state)
    {
    case STOP_MOTOR:
      motor.stop();
      break;

    case TORQUE_CONTROL:
      xprintf("***************************************\n");
      xprintf("Odebrane dane:\n");
      xprintf("Prad zadany: %d A\n", (uint16_t)(motor.currentPID.ref));
      xprintf("Kp: %s\n", fts(motor.currentPID.kp));
      xprintf("Ki: %s\n", fts(motor.currentPID.ki));
      xprintf("Czestotliwosc modulacji: %d Hz\n", motor.frequency);
      xprintf("Ograniczenie pradu: %d\n", (uint16_t)(motor.currentLimit));
      xprintf("Ograniczenie predkosci: %d\n", motor.speedLimit);
      xprintf("Regulacja momentu\n");
      motor.start();
      break;

    case SPEED_CONTROL:
      xprintf("***************************************\n");
      xprintf("Odebrane dane:\n");
      xprintf("Predkosc zadana: %d obr/min\n", (uint16_t)(motor.speedPID.ref));
      xprintf("Kp pradu: %s\n", fts(motor.currentPID.kp));
      xprintf("Ki pradu: %s\n", fts(motor.currentPID.ki));
      xprintf("Kp predkosci: %s\n", fts(motor.speedPID.kp));
      xprintf("Ki predkosci: %s\n", fts(motor.speedPID.ki));
      xprintf("Kd predkosci: %s\n", fts(motor.speedPID.kd));
      xprintf("Czestotliwosc modulacji: %d Hz\n", motor.frequency);
      xprintf("Ograniczenie pradu: %d\n", (uint16_t)(motor.currentLimit));
      xprintf("Ograniczenie predkosci: %d\n", motor.speedLimit);
      xprintf("Regulacja predkosci\n");
      motor.start();
      break;

    case PWM_CONTROL:
      xprintf("***************************************\n");
      xprintf("Odebrane dane:\n");
      xprintf("Czestotliwosc modulacji: %d Hz\n", motor.frequency);
      xprintf("Sterowanie PWM\n");
      motor.start();
      break;

    default:
      break;
    }
}
