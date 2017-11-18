#ifndef _PWM_H_
#define _PWM_H_

void setSwitchingFrequency(uint32_t freq);
void setDutyCycle(float gamma);
void startPWM(void);
void stopPWM(void);

#endif