#include "stm32f4xx_hal.h"
#include "xprintf.h"
#include "stdlib.h"
#include "board.h"
#include "controlTask.h"
#include "pwm.h"
#include "libUART.h"
#include "uartTask.h"
#include <stdbool.h>

/* Makra i definicje */
#define dt 0.0001 // 100 us
#define ADC_REF 3000ULL
#define MAX_12_BIT 4096ULL

// Maksymalne wartości dla 3 V na pinie analogowym
// ADC: 4095 -> 3V -> 30 A
#define MAX_CURRENT 30000 //mA
#define MAX_SPEED 1400 //obr/min

/* --- Zmienne globalne --- */
uint32_t adcResult[2] = {0};         //ADC DMA buffer, 0 - current, 1 - speed
bool newMotorState = false;

/* --- Zmienne globalne --- */
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;

/* --- Funkcje statyczne --- */
static void motorControl(void);
static void stopMotor(void);
static void startMotor(void);

/* --- Definicja obiektu silnika --- */
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
  adcBuffer[currPos++] = adcResult[0];
  currPos = currPos % ADC_BUFFER_SIZE;
}

void startADC(void)
{
  HAL_ADC_Start_DMA(&hadc1, adcResult, 2);
}

void stopADC(void)
{
  HAL_ADC_Stop_DMA(&hadc1);
}

static float getMotorCurrentRaw(void)
{
  uint32_t current = 0;
  uint32_t adcCpy = adcResult[0];
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

speedType_t getMotorSpeed(void)
{
  speedType_t speedRaw = 0;
  uint32_t adcCpy = adcResult[1];
  speedRaw = (uint32_t)((MAX_SPEED * adcCpy) / MAX_12_BIT);
  return speedRaw;
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
#define TH_VAL_CURR 1
#define INT_THRESHOLD_MAX_CURR TH_VAL_CURR
#define INT_THRESHOLD_MIN_CURR -TH_VAL_CURR

static float integral_PI = 0;
static float PI(float Kp, float Ti, float varRef, float var, float limit)
{
  float error, out;

  error = varRef - var;
  integral_PI += Kp * error / Ti;

  if (integral_PI > INT_THRESHOLD_MAX_CURR)
    integral_PI = INT_THRESHOLD_MAX_CURR;
  else if (integral_PI < INT_THRESHOLD_MIN_CURR)
    integral_PI = INT_THRESHOLD_MIN_CURR;

  out = Kp * error + integral_PI;

  return limitVar(out, limit);
}

#define TH_VAL_SPEED 30
#define INT_THRESHOLD_MAX_SPEED TH_VAL_SPEED
#define INT_THRESHOLD_MIN_SPEED -TH_VAL_SPEED

static float errorPrev_PID = 0, integral_PID = 0;
static float PID(float Kp, float Ti, float Td, float varRef, float var, float limit)
{
  float error, out, derivative;

  error = varRef - var;
  integral_PID += Kp * error / Ti;
  derivative = Kp * Td * (error - errorPrev_PID) / dt;
  errorPrev_PID = error;

  if (integral_PID > INT_THRESHOLD_MAX_SPEED)
    integral_PID = INT_THRESHOLD_MAX_SPEED;
  else if (integral_PID < INT_THRESHOLD_MIN_SPEED)
    integral_PID = INT_THRESHOLD_MIN_SPEED;

  out = Kp * error + integral_PID + derivative;

  return limitVar(out, limit);
}

static void motorControl(void)
{
  static float gamma = 0;

  switch (motor.state)
    {
    case STOP_MOTOR:
      break;

    case SPEED_CONTROL:
      motor.speed = getMotorSpeed();
      motor.currentPID.ref = PID(motor.speedPID.kp, motor.speedPID.ki, motor.speedPID.kd, motor.speedPID.ref, motor.speed, motor.currentLimit);
      motor.current = getMotorCurrentRaw();
      gamma = PI(motor.currentPID.kp, motor.currentPID.ki, motor.currentPID.ref, motor.current, 1);
      setDutyCycle(gamma);
      break;

    case TORQUE_CONTROL:
      motor.current = getMotorCurrentRaw();
      gamma = PI(motor.currentPID.kp, motor.currentPID.ki, motor.currentPID.ref, motor.current, 1);
      setDutyCycle(gamma);
      break;

    default:
      break;
    }
}

// Motor control interrupt
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
  setDutyCycle(motor.dutyCycle);
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
      xprintf("Kp: %s\n", fts04(motor.currentPID.kp));
      xprintf("Ki: %s\n", fts04(motor.currentPID.ki));
      xprintf("Czestotliwosc modulacji: %d Hz\n", motor.frequency);
      xprintf("Regulacja momentu\n");
      motor.start();
      break;

    case SPEED_CONTROL:
      xprintf("***************************************\n");
      xprintf("Odebrane dane:\n");
      xprintf("Predkosc zadana: %d obr/min\n", (uint16_t)(motor.speedPID.ref));
      xprintf("Kp pradu: %s\n", fts04(motor.currentPID.kp));
      xprintf("Ki pradu: %s\n", fts04(motor.currentPID.ki));
      xprintf("Kp predkosci: %s\n", fts04(motor.speedPID.kp));
      xprintf("Ki predkosci: %s\n", fts04(motor.speedPID.ki));
      xprintf("Kd predkosci: %s\n", fts04(motor.speedPID.kd));
      xprintf("Czestotliwosc modulacji: %d Hz\n", motor.frequency);
      xprintf("Ograniczenie pradu: %d A\n", (uint16_t)(motor.currentLimit));
      xprintf("Regulacja predkosci\n");
      motor.start();
      break;

    case PWM_CONTROL:
      xprintf("***************************************\n");
      xprintf("Odebrane dane:\n");
      xprintf("Czestotliwosc modulacji: %d Hz\n", motor.frequency);
      xprintf("Wspolczynnik wypelnienia: %d %%\n", (uint32_t)(motor.dutyCycle * 100));
      xprintf("Sterowanie PWM\n");
      motor.start();
      break;

    default:
      break;
    }
}
