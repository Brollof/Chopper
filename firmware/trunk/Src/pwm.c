#include "stm32f4xx_hal.h"
#include "pwm.h"

#define TIMER3_CLOCK 84000000

extern TIM_HandleTypeDef htim5;

void setSwitchingFrequency(uint32_t freq)
{
  uint32_t period = TIMER3_CLOCK / (freq * 84);
  htim5.Init.Prescaler = 84 - 1;
  htim5.Init.Period = period;
  HAL_TIM_Base_Init(&htim5);
}

void setDutyCycle(float gamma)
{
  TIM5->CCR1 = htim5.Init.Period * gamma;
}

void startPWM(void)
{
  HAL_TIM_Base_Start(&htim5);
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
}

void stopPWM(void)
{
  HAL_TIM_Base_Stop(&htim5);
  HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
}

