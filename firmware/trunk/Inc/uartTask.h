#ifndef _UART_TASK_H_
#define _UART_TASK_H_

void floatToString(float f1, char *str);
char *fts(float f1);
void sendAck(void);
void checkUart(void);

#endif