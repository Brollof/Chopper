#include "main.h"
#include <board.h>
#include <stdbool.h>
#include <xprintf.h>
#include <libUART.h>
#include <string.h>
#include "guiTask.h"
#include "controlTask.h"
#include "uartTask.h"

typedef enum
{
  LED_EVENT,
  GUI_EVENT,
  REFRESH_CURRENT_ON_GUI_EVENT,
  UART_EVENT,

  eventsNum,
} events_t;

typedef struct
{
  void (*callback)(void);
  uint32_t period;
  uint32_t lastExeTime;
} periodEvents_t;

static void changeLedState(void)
{
  HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
}

periodEvents_t periodEvents[eventsNum] =
{
  [LED_EVENT] = {changeLedState, 1000},
  [GUI_EVENT] = {guiRefresh, 50},
  [REFRESH_CURRENT_ON_GUI_EVENT] = {refreshMotorCurrentOnGUI, 500},
  [UART_EVENT] = {checkUart, 100},
};


static void doPeriodically(void)
{
  static uint32_t tick = 0;
  static uint8_t i;

  tick = HAL_GetTick();
  for (i = 0; i < eventsNum; i++)
    {
      if (tick - periodEvents[i].lastExeTime >= periodEvents[i].period)
        {
          periodEvents[i].callback();
          periodEvents[i].lastExeTime = tick;
        }
    }
}

int main(void)
{
  boardInit();
  guiInit();

  while (1)
    {
      motorCheck();
      doPeriodically();
    }
}
