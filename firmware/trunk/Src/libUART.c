#include "stm32f4xx_hal.h"
#include <xprintf.h>
#include "board.h"
#include "libUART.h"
#include <string.h>
#include "controlTask.h"
#include <stdbool.h>

static void clearRxBuffer(void);
volatile bool sem = false;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;
// extern osMessageQId uartTaskQueue;
// osSemaphoreId uartTxSemaphore;
uint8_t rxChar = 0;
uint8_t currentBuffPos = 0;

uartBuffer_t rxData =
{
  .buffer = {0},
  .pos = 0,
  .clear = clearRxBuffer,
};

uartBuffer_t *getUartRxData(void)
{
  return &rxData;
}

static void clearRxBuffer(void)
{
  memset(rxData.buffer, 0, USART_BUFFER_SIZE);
  rxData.pos = 0;
}

void printRxBuff(void)
{
  xprintf("RxBuff: %s\n", rxData.buffer);
}

static void sendConsole(char data)
{
  HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&data, sizeof(uint8_t));
  sem = true;
  while (sem);
  // osMessagePut(uartTaskQueue, (uint32_t)data, 10);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
    {
      HAL_UART_Receive_IT(&huart1, &rxChar, 1);
      rxData.buffer[rxData.pos++] = rxChar;
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
    {
      // osSemaphoreRelease(uartTxSemaphore);
      sem = false;
    }
}

void uartInit(void)
{
  __DMA2_CLK_ENABLE();

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

  // DMA Tx Initialization
  hdma_usart1_tx.Instance = DMA2_Stream7;
  hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
  hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_usart1_tx.Init.Mode = DMA_NORMAL;
  hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
  hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  HAL_DMA_Init(&hdma_usart1_tx);

  __HAL_LINKDMA(&huart1, hdmatx, hdma_usart1_tx);

  HAL_NVIC_SetPriority(USART1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);

  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

  HAL_UART_Receive_IT(&huart1, &rxChar, 1);

  xdev_out(sendConsole);
}
