#ifndef _CONTROL_TASK_H_
#define _CONTROL_TASK_H_

typedef float currentType_t;
typedef uint16_t speedType_t;
typedef enum
{
  STOP_MOTOR = 0,
  SPEED_CONTROL = 1,
  TORQUE_CONTROL = 2,
  PWM_CONTROL = 3,
} controlType_t;

typedef struct
{
  float Kp_i;
  float Ki_i;
  float Kp_omega;
  float Ki_omega;
  float Kd_omega;
  currentType_t iRef;
  currentType_t currentLimit;
  speedType_t speedLimit;
  speedType_t omegaRef;
  uint16_t freqRef;
  controlType_t type;
} controlData_t;

typedef struct
{
  float kp;
  float ki;
  float kd;
  float ref;
} PID_t;

typedef struct
{
  PID_t currentPID;
  PID_t speedPID;
  currentType_t current;
  currentType_t currentLimit;
  speedType_t speed;
  speedType_t speedLimit;
  uint16_t frequency;
  controlType_t state;
  void(*start)(void);
  void(*stop)(void);
} motorObject_t;

void stopControlInterrupt(void);
void startControlInterrupt(void);
void startADC(void);
void stopADC(void);
void getMotorLimits(currentType_t *current, speedType_t *speed);
void motorCheck(void);
motorObject_t *getMotorObject(void);
void updateMotorState(void);
float getMotorAverageCurrent(void);

#endif