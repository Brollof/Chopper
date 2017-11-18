#ifndef __LIB_UART_H
#define __LIB_UART_H

#define USART_BUFFER_SIZE 255

typedef struct
{
  uint8_t buffer[USART_BUFFER_SIZE];
  uint8_t pos;
  void (*clear)(void);
} uartBuffer_t;

void uartInit(void);
void printRxBuff(void);
uartBuffer_t *getUartRxData(void);

#endif