#ifndef __BOARD_H
#define __BOARD_H

#define RED_LED_TOGGLE(arg)  HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
#define RED_LED_ON(arg)      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 1);
#define RED_LED_OFF(arg)     HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 0);


void boardInit(void);


#endif