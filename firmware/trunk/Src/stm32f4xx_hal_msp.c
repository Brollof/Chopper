#include "stm32f4xx_hal.h"

extern DMA_HandleTypeDef hdma_adc1;

void HAL_MspInit(void)
{
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if (huart->Instance == USART1)
    {
      __USART1_CLK_ENABLE();

      /**USART1 GPIO Configuration
      PA9     ------> USART1_TX
      PA10     ------> USART1_RX
      */
      GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_PULLUP;
      GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }

}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if (huart->Instance == UART4)
    {
      __UART4_CLK_DISABLE();

      /**UART4 GPIO Configuration
      PA0/WKUP     ------> UART4_TX
      PA1     ------> UART4_RX
      */
      HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

      /* Peripheral DMA DeInit*/
      HAL_DMA_DeInit(huart->hdmatx);

      /* Peripheral interrupt DeInit*/
      HAL_NVIC_DisableIRQ(UART4_IRQn);
    }
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef* hwwdg)
{

  if (hwwdg->Instance == WWDG)
    {
      __WWDG_CLK_ENABLE();
    }

}

void HAL_WWDG_MspDeInit(WWDG_HandleTypeDef* hwwdg)
{
  if (hwwdg->Instance == WWDG)
    {
      __WWDG_CLK_DISABLE();
    }
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if (hadc->Instance == ADC1)
    {
      /* USER CODE BEGIN ADC1_MspInit 0 */

      /* USER CODE END ADC1_MspInit 0 */
      /* Peripheral clock enable */
      __HAL_RCC_ADC1_CLK_ENABLE();
      /**ADC1 GPIO Configuration
      PC1     ------> ADC1_IN11
      */
      GPIO_InitStruct.Pin = GPIO_PIN_1;
      GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

      /* Peripheral DMA init*/

      hdma_adc1.Instance = DMA2_Stream0;
      hdma_adc1.Init.Channel = DMA_CHANNEL_0;
      hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
      hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
      hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
      hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
      hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
      hdma_adc1.Init.Mode = DMA_CIRCULAR;
      hdma_adc1.Init.Priority = DMA_PRIORITY_VERY_HIGH;
      hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
      HAL_DMA_Init(&hdma_adc1);

      __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc1);

      /* USER CODE BEGIN ADC1_MspInit 1 */

      /* USER CODE END ADC1_MspInit 1 */
    }

}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

  if (hadc->Instance == ADC1)
    {
      /* USER CODE BEGIN ADC1_MspDeInit 0 */

      /* USER CODE END ADC1_MspDeInit 0 */
      /* Peripheral clock disable */
      __HAL_RCC_ADC1_CLK_DISABLE();

      /**ADC1 GPIO Configuration
      PC1     ------> ADC1_IN11
      */
      HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1);

    }
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if (htim_base->Instance == TIM5)
    {
      /* USER CODE BEGIN TIM5_MspInit 0 */

      /* USER CODE END TIM5_MspInit 0 */
      /* Peripheral clock enable */
      __HAL_RCC_TIM5_CLK_ENABLE();
      /* USER CODE BEGIN TIM5_MspInit 1 */

      /* USER CODE END TIM5_MspInit 1 */
    }
  else if (htim_base->Instance == TIM4)
    {
      /* USER CODE BEGIN TIM4_MspInit 0 */

      /* USER CODE END TIM4_MspInit 0 */
      /* Peripheral clock enable */
      __HAL_RCC_TIM4_CLK_ENABLE();
      /* USER CODE BEGIN TIM4_MspInit 1 */

      /* USER CODE END TIM4_MspInit 1 */
    }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if (htim->Instance == TIM5)
    {
      /* USER CODE BEGIN TIM5_MspPostInit 0 */

      /* USER CODE END TIM5_MspPostInit 0 */

      /**TIM5 GPIO Configuration
      PA0     ------> TIM5_CH1
      */
      GPIO_InitStruct.Pin = GPIO_PIN_0;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      /* USER CODE BEGIN TIM5_MspPostInit 1 */

      /* USER CODE END TIM5_MspPostInit 1 */
    }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if (htim_base->Instance == TIM5)
    {
      /* USER CODE BEGIN TIM5_MspDeInit 0 */

      /* USER CODE END TIM5_MspDeInit 0 */
      /* Peripheral clock disable */
      __HAL_RCC_TIM5_CLK_DISABLE();
      /* USER CODE BEGIN TIM5_MspDeInit 1 */

      /* USER CODE END TIM5_MspDeInit 1 */
    }
  else if (htim_base->Instance == TIM4)
    {
      /* USER CODE BEGIN TIM4_MspDeInit 0 */

      /* USER CODE END TIM4_MspDeInit 0 */
      /* Peripheral clock disable */
      __HAL_RCC_TIM4_CLK_DISABLE();

      /* Peripheral interrupt DeInit*/
      HAL_NVIC_DisableIRQ(TIM4_IRQn);

      /* USER CODE BEGIN TIM4_MspDeInit 1 */

      /* USER CODE END TIM4_MspDeInit 1 */
    }

}
