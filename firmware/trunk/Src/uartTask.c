#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <xprintf.h>
#include "uartTask.h"
#include "libUART.h"
#include "controlTask.h"
#include "board.h"

extern UART_HandleTypeDef huart1;
static void setMotorData(uint8_t paraNum, char *parameter);

typedef enum
{
  CMD_SEND_ACK,
  CMD_CONTROL_DATA,
  cmdNum,
} cmdType_t;

typedef struct
{
  char prefix;
  void (*prepareData)(uint8_t paramNum, char *parameter);
  void (*executeCommand)(void);
} cmd_t;

const cmd_t commandsFromPC[cmdNum] =
{
  [CMD_SEND_ACK] = {'s', NULL, sendAck},
  [CMD_CONTROL_DATA] = {'c', setMotorData, updateMotorState},
};

static uint8_t searchForCommand(char prefix)
{
  int cmd = 0;
  for (cmd = 0; cmd < cmdNum; cmd++)
    {
      if (prefix == commandsFromPC[cmd].prefix)
        break;
    }

  return cmd;
}

void floatToString(float f1, char *str)
{
  int d1 = f1;
  float f2 = f1 - d1;
  int d2 = (int)(f2 * 100);
  xsprintf (str, "%d.%02d", d1, d2);
}

char *fts(float f1)
{
  static char str[10];
  int d1 = f1;
  float f2 = f1 - d1;
  int d2 = (int)(f2 * 100);
  xsprintf (str, "%d.%02d", d1, d2);
  return str;
}

static uint8_t parseParameter(char *buff, char *out)
{
  static uint8_t i = 0;
  uint8_t j = 0;

  while (buff[i] != 'n')
    {
      if (buff[i] == 'e') //end of transmission detected
        {
          i = 0;
          return 0;
        }

      out[j] = buff[i];
      j++;
      i++;
    }

  i++; // to ommit 'n' character in next iteration
  return 1;
}

static void setMotorData(uint8_t paraNum, char *parameter)
{
  motorObject_t *motor = getMotorObject();

  switch (paraNum)
    {
    case 0:
      motor->currentPID.kp = atof(parameter);
      break;

    case 1:
      motor->currentPID.ki = atof(parameter);
      break;

    case 2:
      motor->speedPID.kp = atof(parameter);
      break;

    case 3:
      motor->speedPID.ki = atof(parameter);
      break;

    case 4:
      motor->speedPID.kd = atof(parameter);
      break;

    case 5:
      motor->state = atoi(parameter);
      break;

    case 6:
      motor->frequency = atoi(parameter);
      break;

    case 7:
      motor->currentPID.ref = atof(parameter);
      break;

    case 8:
      motor->speedPID.ref = atoi(parameter);
      break;

    case 9:
      motor->currentLimit = atof(parameter);
      break;

    case 10:
      motor->speedLimit = atoi(parameter);
      break;

    default:
      break;
    }
}

void sendAck(void)
{
  xprintf("ack");
}

static void prepareCommandData(cmdType_t cmd, char *parameter, uint8_t *paraNum)
{
  if (commandsFromPC[cmd].prepareData != NULL && cmd < cmdNum)
    commandsFromPC[cmd].prepareData((*paraNum)++, parameter);
}

static void executeCommand(cmdType_t cmd)
{
  if (commandsFromPC[cmd].executeCommand !=  NULL && cmd < cmdNum)
    commandsFromPC[cmd].executeCommand();
}

static cmdType_t parseRxBuffer(void)
{
  uartBuffer_t *rxData = getUartRxData();
  uint8_t *rxBuff = rxData->buffer;
  char parameter[12] = {0};
  uint8_t status = 1, paraNum = 0;
  cmdType_t cmd = searchForCommand(rxBuff[0]);

  rxBuff++; // ommit prefix
  while (status)
    {
      status = parseParameter((char *)rxBuff, parameter);
      prepareCommandData(cmd, parameter, &paraNum);
      memset(parameter, 0, sizeof(parameter));
    }

  rxData->clear(); //clear rx buffer - data is no longer needed
  return cmd;
}

static uint8_t checkRxBuff(void)
{
  uartBuffer_t *rxData = getUartRxData();
  uint8_t *rxBuff = rxData->buffer;
  while (*rxBuff != 0)
    {
      if (*rxBuff == 'e') // rx buff is not empty - parsing needed
        return 1;

      rxBuff++;
    }
  return 0;
}

void checkUart(void)
{
  if (checkRxBuff())
    {
      cmdType_t cmd = parseRxBuffer();
      executeCommand(cmd);
    }
}