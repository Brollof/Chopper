#include "main.h"
#include "WM.h"
#include "guiTask.h"

extern WM_HWIN WindowInit(void);

void guiInit(void)
{
  WM_SetCreateFlags(WM_CF_MEMDEV);
  // WM_MULTIBUF_Enable(1);
  GUI_Init();

  GUI_Clear();
  WindowInit();
}

static void touchScreenUpdate(void)
{
  GUI_PID_STATE TS_State;
  static TS_StateTypeDef prev_state;
  __IO TS_StateTypeDef  ts;
  uint16_t xDiff, yDiff;

  BSP_TS_GetState((TS_StateTypeDef *)&ts);

  TS_State.Pressed = ts.TouchDetected;

  xDiff = (prev_state.X > ts.X) ? (prev_state.X - ts.X) : (ts.X - prev_state.X);
  yDiff = (prev_state.Y > ts.Y) ? (prev_state.Y - ts.Y) : (ts.Y - prev_state.Y);

  if ((prev_state.TouchDetected != ts.TouchDetected ) ||
      (xDiff > 3 ) ||
      (yDiff > 3))
    {
      prev_state.TouchDetected = ts.TouchDetected;

      if ((ts.X != 0) &&  (ts.Y != 0))
        {
          prev_state.X = ts.X;
          prev_state.Y = ts.Y;
        }
// ?
      TS_State.Layer = 0;
      TS_State.x = prev_state.X;
      TS_State.y = prev_state.Y;

      GUI_TOUCH_StoreStateEx(&TS_State);
    }
}

void guiRefresh(void)
{
  touchScreenUpdate();
  GUI_Exec(); // Update widgets
}