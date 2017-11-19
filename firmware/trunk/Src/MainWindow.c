#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "controlTask.h"
#include "uartTask.h"
#include "xprintf.h"
#include "DIALOG.h"
#include "guiTask.h"

#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_MULTIPAGE_0 (GUI_ID_USER + 0x01)
#define ID_EDIT_KP_CURRENT (GUI_ID_USER + 0x02)
#define ID_BUTTON_0 (GUI_ID_USER + 0x03)
#define ID_BUTTON_1 (GUI_ID_USER + 0x04)
#define ID_BUTTON_2 (GUI_ID_USER + 0x05)
#define ID_BUTTON_3 (GUI_ID_USER + 0x06)
#define ID_BUTTON_4 (GUI_ID_USER + 0x07)
#define ID_BUTTON_5 (GUI_ID_USER + 0x08)
#define ID_BUTTON_6 (GUI_ID_USER + 0x09)
#define ID_BUTTON_7 (GUI_ID_USER + 0x0A)
#define ID_BUTTON_8 (GUI_ID_USER + 0x0B)
#define ID_BUTTON_9 (GUI_ID_USER + 0x0C)
#define ID_BUTTON_BACKSPACE_CURRENT (GUI_ID_USER + 0x0D)
#define ID_CLEAR_ALL_CURRENT (GUI_ID_USER + 0x0E)
#define ID_TEXT_KP_CURRENT (GUI_ID_USER + 0x0F)
#define ID_TEXT_KI_CURRENT (GUI_ID_USER + 0x10)
#define ID_EDIT_KI_CURRENT (GUI_ID_USER + 0x12)
#define ID_FREQ_EDIT (GUI_ID_USER + 0x14)
#define ID_BUTTON_DOT_CURRENT (GUI_ID_USER + 0x16)
#define ID_CURRENT_REF_EDIT (GUI_ID_USER + 0x17)
#define ID_TEXT_CURRENT_REF (GUI_ID_USER + 0x18)
#define ID_CURRENT_MEAS_TXT (GUI_ID_USER + 0x19)
#define ID_CURRENT_MEAS (GUI_ID_USER + 0x1A)
#define ID_DROPDOWN_FREQ (GUI_ID_USER + 0x11)
#define ID_TEXT_ERROR1 (GUI_ID_USER + 0x13)
#define ID_TEXT_ERROR2 (GUI_ID_USER + 0x15)

#define ID_BUTTON_10 (GUI_ID_USER + 0x1B)
#define ID_BUTTON_11 (GUI_ID_USER + 0x1C)
#define ID_BUTTON_12 (GUI_ID_USER + 0x1D)
#define ID_BUTTON_13 (GUI_ID_USER + 0x1F)
#define ID_BUTTON_14 (GUI_ID_USER + 0x20)
#define ID_BUTTON_15 (GUI_ID_USER + 0x21)
#define ID_BUTTON_16 (GUI_ID_USER + 0x22)
#define ID_BUTTON_17 (GUI_ID_USER + 0x23)
#define ID_BUTTON_18 (GUI_ID_USER + 0x24)
#define ID_BUTTON_19 (GUI_ID_USER + 0x25)
#define ID_BUTTON_DOT_SPEED (GUI_ID_USER + 0x26)
#define ID_BUTTON_BACKSPACE_SPEED (GUI_ID_USER + 0x27)
#define ID_CLEAR_ALL_SPEED (GUI_ID_USER + 0x28)
#define ID_SPEED_REF_EDIT (GUI_ID_USER + 0x29)
#define ID_TEXT_SPEED_REF (GUI_ID_USER + 0x2A)
#define ID_TEXT_KP_SPEED (GUI_ID_USER + 0x2B)
#define ID_TEXT_KI_SPEED (GUI_ID_USER + 0x2C)
#define ID_TEXT_KD_SPEED (GUI_ID_USER + 0x2D)
#define ID_EDIT_KP_SPEED (GUI_ID_USER + 0x2E)
#define ID_EDIT_KI_SPEED (GUI_ID_USER + 0x2F)
#define ID_EDIT_KD_SPEED (GUI_ID_USER + 0x30)

#define ID_TEXT_CURRENT_LIMIT (GUI_ID_USER + 0x3E)
#define ID_EDIT_CURRENT_LIMIT (GUI_ID_USER + 0x40)

/* Main window */
#define ID_DROPDOWN_DUTY_CYCLE (GUI_ID_USER + 0x41)
#define ID_TEXT_FREQ (GUI_ID_USER + 0x42)
#define ID_TEXT_DUTY_CYCLE (GUI_ID_USER + 0x43)
#define ID_SPEED_MEAS_TXT (GUI_ID_USER + 0x44)
#define ID_SPEED_MEAS (GUI_ID_USER + 0x45)

#define MAX_EDIT_FIELD_LENGTH 6

/*********************************************************************/

/* Keypad Y pos */
#define ROW_3_HEIGHT 245-10
#define ROW_2_HEIGHT 200-10
#define ROW_1_HEIGHT 155-10
#define ROW_0_HEIGHT 110-10

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_CurrentReg[] =
{
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 240, 320, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "7", ID_BUTTON_7, 4, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "8", ID_BUTTON_8, 62, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "9", ID_BUTTON_9, 119, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "ClrAll", ID_CLEAR_ALL_CURRENT, 177, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "4", ID_BUTTON_4, 4, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "5", ID_BUTTON_5, 62, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "6", ID_BUTTON_6, 119, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "0", ID_BUTTON_0, 177, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "1", ID_BUTTON_1, 4, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "2", ID_BUTTON_2, 62, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "3", ID_BUTTON_3, 119, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Usun", ID_BUTTON_BACKSPACE_CURRENT, 177, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, ".", ID_BUTTON_DOT_CURRENT, 177, ROW_0_HEIGHT, 55, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Kp", ID_TEXT_KP_CURRENT, 15, 5, 31, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Ti", ID_TEXT_KI_CURRENT, 70, 5, 23, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "kpEditCurrent", ID_EDIT_KP_CURRENT, 15, 20, 45, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "kiEditCurrent", ID_EDIT_KI_CURRENT, 70, 20, 45, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Prad zadany [A]:", ID_TEXT_CURRENT_REF, 15, 45, 90, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "currentRefEdit", ID_CURRENT_REF_EDIT, 15, 60, 80, 20, 0, 0x64, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_SpeedReg[] =
{
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 240, 320, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "7", ID_BUTTON_17, 4, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "8", ID_BUTTON_18, 62, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "9", ID_BUTTON_19, 119, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "ClrAll", ID_CLEAR_ALL_SPEED, 177, ROW_3_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "4", ID_BUTTON_14, 4, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "5", ID_BUTTON_15, 62, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "6", ID_BUTTON_16, 119, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "0", ID_BUTTON_10, 177, ROW_2_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "1", ID_BUTTON_11, 4, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "2", ID_BUTTON_12, 62, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "3", ID_BUTTON_13, 119, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Usun", ID_BUTTON_BACKSPACE_SPEED, 177, ROW_1_HEIGHT, 55, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, ".", ID_BUTTON_DOT_SPEED, 177, ROW_0_HEIGHT, 55, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Kp", ID_TEXT_KP_SPEED, 15, 5, 25, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Ti", ID_TEXT_KI_SPEED, 70, 5, 25, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Td", ID_TEXT_KD_SPEED, 70 + 55, 5, 25, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "kpEditSpeed", ID_EDIT_KP_SPEED, 15, 20, 45, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "kiEditSpeed", ID_EDIT_KI_SPEED, 70, 20, 45, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "kdEditSpeed", ID_EDIT_KD_SPEED, 70 + 55, 20, 45, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Predkosc zadana [obr/min]:", ID_TEXT_SPEED_REF, 15, 45, 150, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "speedRefEdit", ID_SPEED_REF_EDIT, 15, 60, 80, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Ograniczenie pradu [A]:", ID_TEXT_CURRENT_LIMIT, 15, 85, 150, 20, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "currentLimitEdit", ID_EDIT_CURRENT_LIMIT, 15, 100, 60, 20, 0, 0x64, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Control[] =
{
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 240, 320, 0, 0x0, 0 },
  { RADIO_CreateIndirect, "Radio", GUI_ID_RADIO0, 6, 9, 181, 90, 0, 0x1e03, 0 },
  { BUTTON_CreateIndirect, "START", GUI_ID_BUTTON0, 140, 10, 83, 33, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "STOP", GUI_ID_BUTTON1, 140, 60, 83, 33, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Czestotliwosc [Hz]:", ID_TEXT_FREQ, 10, 100, 150, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Wypelnienie [%]:", ID_TEXT_DUTY_CYCLE, 125, 100, 150, 20, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "dropdownFreq", ID_DROPDOWN_FREQ, 10, 115, 100, 18, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "dropdownDutyCycle", ID_DROPDOWN_DUTY_CYCLE, 125, 115, 100, 18, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Prad [A]:", ID_CURRENT_MEAS_TXT, 10, 155, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "0.00", ID_CURRENT_MEAS, 10, 170, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Predkosc [obr/min]:", ID_SPEED_MEAS_TXT, 125, 155, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "0", ID_SPEED_MEAS, 125, 170, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "", ID_TEXT_ERROR1, 10, 210, 200, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "", ID_TEXT_ERROR2, 10, 230, 220, 20, 0, 0x0, 0 },

};

#define PAGES_NUM 3
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
typedef enum
{
  EDIT_KP_CURRENT,
  EDIT_KI_CURRENT,
  EDIT_KP_SPEED,
  EDIT_KI_SPEED,
  EDIT_KD_SPEED,
  EDIT_CURRENT_REF,
  EDIT_SPEED_REF,
  EDIT_CURRENT_LIMIT,
  EDIT_ERROR1,
  EDIT_ERROR2,
  editFieldsNum,
} editField_t;

WM_HWIN hStopButton;
WM_HWIN hStartButton;
WM_HWIN hRadio;
WM_HWIN hDialogControl;
WM_HWIN hDialogCurrentReg;
WM_HWIN hDialogSpeedReg;
WM_HWIN hMultiPage;
WM_HWIN hDropDownFreq;
WM_HWIN hDropDownDutyCycle;

editField_t activeEditField = EDIT_KP_CURRENT;
char currentlyEditedField[10] = "";
static uint8_t radioButtonSelectIndex = 0;

#define ENABLE_START_BTN(arg) WM_EnableWindow(hStartButton)
#define DISABLE_START_BTN(arg) WM_DisableWindow(hStartButton)
#define ENABLE_STOP_BTN(arg) WM_EnableWindow(hStopButton)
#define DISABLE_STOP_BTN(arg) WM_DisableWindow(hStopButton)

static void onStartClick(WM_MESSAGE *pMsg);
static inline void enableAllPages(void);

static const char buttonsCurrent[ID_BUTTON_9 + 1][2] =
{
  [ID_BUTTON_0] = "0",
  [ID_BUTTON_1] = "1",
  [ID_BUTTON_2] = "2",
  [ID_BUTTON_3] = "3",
  [ID_BUTTON_4] = "4",
  [ID_BUTTON_5] = "5",
  [ID_BUTTON_6] = "6",
  [ID_BUTTON_7] = "7",
  [ID_BUTTON_8] = "8",
  [ID_BUTTON_9] = "9",
};

static const char buttonsSpeed[ID_BUTTON_19 + 1][2] =
{
  [ID_BUTTON_10] = "0",
  [ID_BUTTON_11] = "1",
  [ID_BUTTON_12] = "2",
  [ID_BUTTON_13] = "3",
  [ID_BUTTON_14] = "4",
  [ID_BUTTON_15] = "5",
  [ID_BUTTON_16] = "6",
  [ID_BUTTON_17] = "7",
  [ID_BUTTON_18] = "8",
  [ID_BUTTON_19] = "9",
};

static const uint8_t radioMap[] =
{
  [0] = TORQUE_CONTROL,
  [1] = SPEED_CONTROL,
  [2] = PWM_CONTROL,
};

static WM_HWIN editHandles[editFieldsNum];

static void _controlWindowCallback(WM_MESSAGE * pMsg)
{
  int     NCode;
  int     Id;

  switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
      editHandles[EDIT_ERROR1] = WM_GetDialogItem(pMsg->hWin, ID_TEXT_ERROR1);
      editHandles[EDIT_ERROR2] = WM_GetDialogItem(pMsg->hWin, ID_TEXT_ERROR2);

      hStartButton = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON0);
      hStopButton = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON1);
      WM_DisableWindow(hStopButton);

      hRadio = WM_GetDialogItem(pMsg->hWin, GUI_ID_RADIO0);
      RADIO_SetText(hRadio, "Regulacja pradu", 0);
      RADIO_SetText(hRadio, "Regulacja predkosci", 1);
      RADIO_SetText(hRadio, "PWM", 2);

      hDropDownFreq = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_FREQ);
      DROPDOWN_SetFont(hDropDownFreq, GUI_FONT_24_1);
      DROPDOWN_SetListHeight(hDropDownFreq, 135); // dlugosc listy
      DROPDOWN_AddString(hDropDownFreq, "500");
      DROPDOWN_AddString(hDropDownFreq, "1000");
      DROPDOWN_AddString(hDropDownFreq, "1500");
      DROPDOWN_AddString(hDropDownFreq, "2000");
      DROPDOWN_AddString(hDropDownFreq, "2500");
      DROPDOWN_AddString(hDropDownFreq, "3000");
      DROPDOWN_AddString(hDropDownFreq, "3500");
      DROPDOWN_AddString(hDropDownFreq, "4000");
      DROPDOWN_AddString(hDropDownFreq, "4500");
      DROPDOWN_AddString(hDropDownFreq, "5000");
      DROPDOWN_AddString(hDropDownFreq, "5500");
      DROPDOWN_AddString(hDropDownFreq, "6000");
      DROPDOWN_AddString(hDropDownFreq, "6500");
      DROPDOWN_AddString(hDropDownFreq, "7000");
      DROPDOWN_AddString(hDropDownFreq, "7500");
      DROPDOWN_AddString(hDropDownFreq, "8000");
      DROPDOWN_AddString(hDropDownFreq, "8500");
      DROPDOWN_AddString(hDropDownFreq, "9000");
      DROPDOWN_AddString(hDropDownFreq, "9500");
      DROPDOWN_AddString(hDropDownFreq, "10000");
      DROPDOWN_SetAutoScroll(hDropDownFreq, 1);
      DROPDOWN_SetScrollbarWidth(hDropDownFreq, 30); // szerokosc scrollbara
      DROPDOWN_SetSel(hDropDownFreq, 9); // 50 % PWM domyslnie

      hDropDownDutyCycle = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_DUTY_CYCLE);
      DROPDOWN_SetFont(hDropDownDutyCycle, GUI_FONT_24_1);
      DROPDOWN_SetListHeight(hDropDownDutyCycle, 135); // dlugosc listy
      DROPDOWN_AddString(hDropDownDutyCycle, "10");
      DROPDOWN_AddString(hDropDownDutyCycle, "20");
      DROPDOWN_AddString(hDropDownDutyCycle, "30");
      DROPDOWN_AddString(hDropDownDutyCycle, "40");
      DROPDOWN_AddString(hDropDownDutyCycle, "50");
      DROPDOWN_AddString(hDropDownDutyCycle, "60");
      DROPDOWN_AddString(hDropDownDutyCycle, "70");
      DROPDOWN_AddString(hDropDownDutyCycle, "80");
      DROPDOWN_AddString(hDropDownDutyCycle, "90");
      DROPDOWN_AddString(hDropDownDutyCycle, "100");
      DROPDOWN_SetAutoScroll(hDropDownDutyCycle, 1);
      DROPDOWN_SetScrollbarWidth(hDropDownDutyCycle, 30); // szerokosc scrollbara
      DROPDOWN_SetSel(hDropDownDutyCycle, 4); // 50 % PWM domyslnie
      WM_DisableWindow(hDropDownDutyCycle);
      break;

    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch (Id)
        {
        case ID_MULTIPAGE_0: // Notifications sent by 'Multipage'
          switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
              break;
            case WM_NOTIFICATION_RELEASED:
              break;
            case WM_NOTIFICATION_MOVED_OUT:
              break;
            case WM_NOTIFICATION_VALUE_CHANGED:
              break;
            }
          break;

        case GUI_ID_RADIO0: // Notifications sent by 'Radio'
          switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
              break;
            case WM_NOTIFICATION_RELEASED:
              break;
            case WM_NOTIFICATION_VALUE_CHANGED:
              hRadio = WM_GetDialogItem(pMsg->hWin, GUI_ID_RADIO0);
              radioButtonSelectIndex = RADIO_GetValue(hRadio);

              if (radioMap[radioButtonSelectIndex] == PWM_CONTROL)
                WM_EnableWindow(hDropDownDutyCycle);
              else
                WM_DisableWindow(hDropDownDutyCycle);
              break;
            }
          break;

        case GUI_ID_BUTTON0: // Notifications sent by 'START'
          switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
              onStartClick(pMsg);
              break;
            case WM_NOTIFICATION_RELEASED:
              break;
            }
          break;

        case GUI_ID_BUTTON1: // Notifications sent by 'STOP'
          switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
            {
              DISABLE_STOP_BTN();
              ENABLE_START_BTN();
              TEXT_SetText(editHandles[EDIT_ERROR1], "");
              enableAllPages();
              WM_EnableWindow(hRadio);
              WM_EnableWindow(hDropDownFreq);

              if (radioMap[radioButtonSelectIndex] == PWM_CONTROL)
                WM_EnableWindow(hDropDownDutyCycle);
              else
                WM_DisableWindow(hDropDownDutyCycle);

              motorObject_t *motor = getMotorObject();
              motor->state = STOP_MOTOR;
              updateMotorState();
            }
            break;
            case WM_NOTIFICATION_RELEASED:
              break;
            }
          break;
        }
      break;

    default:
      WM_DefaultProc(pMsg);
      break;

    }
}

static void _currentRegWindowCallback(WM_MESSAGE * pMsg)
{
  int NCode;
  int Id;

  switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
      editHandles[EDIT_KP_CURRENT] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_KP_CURRENT);
      editHandles[EDIT_KI_CURRENT] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_KI_CURRENT);
      editHandles[EDIT_CURRENT_REF] = WM_GetDialogItem(pMsg->hWin, ID_CURRENT_REF_EDIT);
      break;

    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch (Id)
        {
        case ID_BUTTON_0 ... ID_BUTTON_9:
          switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
              EDIT_GetText(editHandles[activeEditField], currentlyEditedField, 10);
              if (strlen(currentlyEditedField) < MAX_EDIT_FIELD_LENGTH)
                {
                  strcat(currentlyEditedField, buttonsCurrent[Id]);
                  EDIT_SetText(editHandles[activeEditField], currentlyEditedField);
                }
              break;
            }
          break;

        case ID_BUTTON_BACKSPACE_CURRENT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            {
              EDIT_GetText(editHandles[activeEditField], currentlyEditedField, 10);
              uint8_t length = strlen(currentlyEditedField);
              if (length < 1)
                break;
              currentlyEditedField[length - 1] = '\0';
              EDIT_SetText(editHandles[activeEditField], currentlyEditedField);
            }
          break;

        case ID_CLEAR_ALL_CURRENT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            {
              memset(currentlyEditedField, 0, sizeof(currentlyEditedField));
              EDIT_SetText(editHandles[EDIT_KP_CURRENT], currentlyEditedField);
              EDIT_SetText(editHandles[EDIT_KI_CURRENT], currentlyEditedField);
              EDIT_SetText(editHandles[EDIT_CURRENT_REF], currentlyEditedField);

            }
          break;

        case ID_BUTTON_DOT_CURRENT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            {
              if (activeEditField == EDIT_CURRENT_REF)
                break;

              EDIT_GetText(editHandles[activeEditField], currentlyEditedField, 10);
              if (strlen(currentlyEditedField) < MAX_EDIT_FIELD_LENGTH)
                {
                  strcat(currentlyEditedField, ".");
                  EDIT_SetText(editHandles[activeEditField], currentlyEditedField);
                }
            }
          break;

        case ID_EDIT_KP_CURRENT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_KP_CURRENT;
          break;

        case ID_EDIT_KI_CURRENT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_KI_CURRENT;
          break;

        case ID_CURRENT_REF_EDIT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_CURRENT_REF;
          break;
        }
      break;
    default:
      WM_DefaultProc(pMsg);
      break;
    }
}

static void _speedRegWindowCallback(WM_MESSAGE * pMsg)
{
  int NCode;
  int Id;

  switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
      editHandles[EDIT_KP_SPEED] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_KP_SPEED);
      editHandles[EDIT_KI_SPEED] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_KI_SPEED);
      editHandles[EDIT_KD_SPEED] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_KD_SPEED);
      editHandles[EDIT_SPEED_REF] = WM_GetDialogItem(pMsg->hWin, ID_SPEED_REF_EDIT);
      editHandles[EDIT_CURRENT_LIMIT] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_CURRENT_LIMIT);
      break;

    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch (Id)
        {
        case ID_BUTTON_10 ... ID_BUTTON_19:
          switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
              EDIT_GetText(editHandles[activeEditField], currentlyEditedField, 10);
              if (strlen(currentlyEditedField) < MAX_EDIT_FIELD_LENGTH)
                {
                  strcat(currentlyEditedField, buttonsSpeed[Id]);
                  EDIT_SetText(editHandles[activeEditField], currentlyEditedField);
                }
              break;
            }
          break;

        case ID_BUTTON_BACKSPACE_SPEED:
          if (NCode == WM_NOTIFICATION_CLICKED)
            {
              EDIT_GetText(editHandles[activeEditField], currentlyEditedField, 10);
              uint8_t length = strlen(currentlyEditedField);
              if (length < 1)
                break;
              currentlyEditedField[length - 1] = '\0';
              EDIT_SetText(editHandles[activeEditField], currentlyEditedField);
            }
          break;

        case ID_CLEAR_ALL_SPEED:
          if (NCode == WM_NOTIFICATION_CLICKED)
            {
              memset(currentlyEditedField, 0, sizeof(currentlyEditedField));

              EDIT_SetText(editHandles[EDIT_KP_SPEED], currentlyEditedField);
              EDIT_SetText(editHandles[EDIT_KI_SPEED], currentlyEditedField);
              EDIT_SetText(editHandles[EDIT_KD_SPEED], currentlyEditedField);
              EDIT_SetText(editHandles[EDIT_SPEED_REF], currentlyEditedField);
              EDIT_SetText(editHandles[EDIT_CURRENT_LIMIT], currentlyEditedField);
            }
          break;

        case ID_BUTTON_DOT_SPEED:
          if (NCode == WM_NOTIFICATION_CLICKED)
            {
              if (activeEditField == EDIT_SPEED_REF)
                break;

              EDIT_GetText(editHandles[activeEditField], currentlyEditedField, 10);
              if (strlen(currentlyEditedField) < MAX_EDIT_FIELD_LENGTH)
                {
                  strcat(currentlyEditedField, ".");
                  EDIT_SetText(editHandles[activeEditField], currentlyEditedField);
                }
            }
          break;

        case ID_EDIT_KP_SPEED:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_KP_SPEED;
          break;

        case ID_EDIT_KI_SPEED:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_KI_SPEED;
          break;

        case ID_EDIT_KD_SPEED:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_KD_SPEED;
          break;

        case ID_SPEED_REF_EDIT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_SPEED_REF;
          break;

        case ID_EDIT_CURRENT_LIMIT:
          if (NCode == WM_NOTIFICATION_CLICKED)
            activeEditField = EDIT_CURRENT_LIMIT;
          break;
        }
      break;
    default:
      WM_DefaultProc(pMsg);
      break;
    }
}

static void setInitialValues(void)
{
  EDIT_SetText(editHandles[EDIT_KP_CURRENT], "0.5");
  EDIT_SetText(editHandles[EDIT_KI_CURRENT], "3");
  EDIT_SetText(editHandles[EDIT_KP_SPEED], "5");
  EDIT_SetText(editHandles[EDIT_KI_SPEED], "0.4");
  EDIT_SetText(editHandles[EDIT_KD_SPEED], "0.0001");
  EDIT_SetText(editHandles[EDIT_CURRENT_LIMIT], "15");
}

WM_HWIN WindowInit(void);
WM_HWIN WindowInit(void)
{
  WM_HWIN hWin = 0;
  WM_HWIN hFrameWin;

  hFrameWin = FRAMEWIN_Create("Chopper", NULL, WM_CF_SHOW, -10, 0, 260, 325);
  FRAMEWIN_SetBorderSize(hFrameWin, 0);
  FRAMEWIN_SetTitleVis(hFrameWin, 0);

  hMultiPage = MULTIPAGE_CreateEx(7, 6, 235, 310, WM_GetClientWindow(hFrameWin), WM_CF_SHOW, 0, 0);
  MULTIPAGE_SetFont(hMultiPage, GUI_FONT_24_1);

  hDialogControl = GUI_CreateDialogBox(_aDialogCreate_Control, GUI_COUNTOF(_aDialogCreate_Control), _controlWindowCallback, WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialogControl, "Sterowanie");
  hDialogCurrentReg = GUI_CreateDialogBox(_aDialogCreate_CurrentReg, GUI_COUNTOF(_aDialogCreate_CurrentReg), _currentRegWindowCallback, WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialogCurrentReg, "Reg. pradu");
  hDialogSpeedReg = GUI_CreateDialogBox(_aDialogCreate_SpeedReg, GUI_COUNTOF(_aDialogCreate_SpeedReg), _speedRegWindowCallback, WM_UNATTACHED, 0, 0);
  MULTIPAGE_AddPage(hMultiPage, hDialogSpeedReg, "Reg. predkosci");

  MULTIPAGE_SelectPage(hMultiPage, 0);
  setInitialValues();

  return hWin;
}

static void startMotorFromGUI(WM_MESSAGE *pMsg)
{
  motorObject_t *motor = getMotorObject();
  char buff[10] = {0};

  /* Regulator pradu */
  EDIT_GetText(editHandles[EDIT_KP_CURRENT], currentlyEditedField, 10);
  motor->currentPID.kp = atof(currentlyEditedField);

  EDIT_GetText(editHandles[EDIT_KI_CURRENT], currentlyEditedField, 10);
  motor->currentPID.ki = atof(currentlyEditedField);

  EDIT_GetText(editHandles[EDIT_CURRENT_REF], currentlyEditedField, 10);
  motor->currentPID.ref = atof(currentlyEditedField);

  /* Regulator predkosci */
  EDIT_GetText(editHandles[EDIT_KP_SPEED], currentlyEditedField, 10);
  motor->speedPID.kp = atof(currentlyEditedField);

  EDIT_GetText(editHandles[EDIT_KI_SPEED], currentlyEditedField, 10);
  motor->speedPID.ki = atof(currentlyEditedField);

  EDIT_GetText(editHandles[EDIT_KD_SPEED], currentlyEditedField, 10);
  motor->speedPID.kd = atof(currentlyEditedField);

  EDIT_GetText(editHandles[EDIT_SPEED_REF], currentlyEditedField, 10);
  motor->speedPID.ref = atof(currentlyEditedField);

  /* Ograniczenie pradu */
  EDIT_GetText(editHandles[EDIT_CURRENT_LIMIT], currentlyEditedField, 10);
  motor->currentLimit = atof(currentlyEditedField);

  WM_HWIN hDropDown = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_FREQ);
  int sel = DROPDOWN_GetSel(hDropDown);
  DROPDOWN_GetItemText(hDropDown, sel, buff, sizeof(buff));
  motor->frequency = atoi(buff);

  hDropDown = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_DUTY_CYCLE);
  sel = DROPDOWN_GetSel(hDropDown);
  DROPDOWN_GetItemText(hDropDown, sel, buff, sizeof(buff));
  motor->dutyCycle = atof(buff);
  motor->dutyCycle /= 100;

  motor->state = radioMap[radioButtonSelectIndex];
  updateMotorState();
}

#define COEFF_MIN 0.0001
#define COEFF_MAX 100.000
#define CURRENT_MIN 1
#define CURRENT_MAX 100
#define SPEED_MIN 1
#define SPEED_MAX 3000
static bool checkField(editField_t field, float min, float max)
{
  float temp;
  char buff[10] = {0};

  EDIT_GetText(editHandles[field], buff, sizeof(buff));
  temp = atof(buff);

  if (temp >= min && temp <= max)
    return true;
  else
    return false;
}

static const char wrongValue[] = "Nieprawidlowa wartosc";
#define ERROR_MESSAGE(str) strcpy(error, str)
#define IS_FIELD_VALID(field, min, max, msg) \
{  if (!checkField(field, min, max)){ \
    ERROR_MESSAGE(msg); \
  return false;}}

static bool isMotorStartPossible(char *error)
{
  switch (radioMap[radioButtonSelectIndex])
    {
    case TORQUE_CONTROL:
      IS_FIELD_VALID(EDIT_KP_CURRENT, COEFF_MIN, COEFF_MAX, "nastawy Kp regulatora pradu.");
      IS_FIELD_VALID(EDIT_KI_CURRENT, COEFF_MIN, COEFF_MAX, "nastawy Ti regulatora pradu.");
      IS_FIELD_VALID(EDIT_CURRENT_REF, CURRENT_MIN, CURRENT_MAX, "pradu zadanego.");
      break;

    case SPEED_CONTROL:
      IS_FIELD_VALID(EDIT_KP_CURRENT, COEFF_MIN, COEFF_MAX, "nastawy Kp regulatora pradu.");
      IS_FIELD_VALID(EDIT_KI_CURRENT, COEFF_MIN, COEFF_MAX, "nastawy Ti regulatora pradu.");
      IS_FIELD_VALID(EDIT_KP_SPEED, COEFF_MIN, COEFF_MAX, "nastawy Kp regulatora predkosci.");
      IS_FIELD_VALID(EDIT_KI_SPEED, COEFF_MIN, COEFF_MAX, "nastawy Ti regulatora predkosci.");
      IS_FIELD_VALID(EDIT_KD_SPEED, COEFF_MIN, COEFF_MAX, "nastawy Td regulatora predkosci.");
      IS_FIELD_VALID(EDIT_SPEED_REF, SPEED_MIN, SPEED_MAX, "predkosci zadanej.");
      IS_FIELD_VALID(EDIT_CURRENT_LIMIT, CURRENT_MIN, CURRENT_MAX, "ograniczenia pradu.");
      break;

    case PWM_CONTROL:
      break;

    default:
      break;
    }

  return true;
}

static inline void disableAllPages(void)
{
  uint8_t i = 0;
  for (i = 0; i < PAGES_NUM; i++)
    MULTIPAGE_DisablePage(hMultiPage, i);
}

static inline void enableAllPages(void)
{
  uint8_t i = 0;
  for (i = 0; i < PAGES_NUM; i++)
    MULTIPAGE_EnablePage(hMultiPage, i);
}

static void onStartClick(WM_MESSAGE *pMsg)
{
  bool startPossible = false;
  char errorMessage[50] = {0};

  startPossible = isMotorStartPossible(errorMessage);

  if (startPossible)
    {
      TEXT_SetFont(editHandles[EDIT_ERROR1], GUI_FONT_16B_1);
      TEXT_SetTextColor(editHandles[EDIT_ERROR1], GUI_GREEN);
      TEXT_SetText(editHandles[EDIT_ERROR1], "OK !");
      TEXT_SetText(editHandles[EDIT_ERROR2], "");
      DISABLE_START_BTN();
      ENABLE_STOP_BTN();

      /*Disable all controls - only STOP is active */
      disableAllPages();
      WM_DisableWindow(hRadio);
      WM_DisableWindow(hDropDownFreq);
      WM_DisableWindow(hDropDownDutyCycle);
      startMotorFromGUI(pMsg);
    }
  else
    {
      TEXT_SetFont(editHandles[EDIT_ERROR1], GUI_FONT_16B_1);
      TEXT_SetFont(editHandles[EDIT_ERROR2], GUI_FONT_16B_1);
      TEXT_SetTextColor(editHandles[EDIT_ERROR1], GUI_RED);
      TEXT_SetTextColor(editHandles[EDIT_ERROR2], GUI_RED);
      TEXT_SetText(editHandles[EDIT_ERROR1], wrongValue);
      TEXT_SetText(editHandles[EDIT_ERROR2], errorMessage);
    }
}

void refreshMotorCurrentOnGUI(void)
{
  static float motorCurrent = 0;
  static speedType_t motorSpeed = 0;
  static char currentStr[6];
  static char speedStr[6];
  static WM_HWIN hDlg, hText;

  motorObject_t *motor = getMotorObject();
  if (motor->state == STOP_MOTOR)
    {
      motorCurrent = 0;
      motorSpeed = 0;
    }
  else
    {
      motorCurrent = getMotorAverageCurrent();
      motorSpeed = getMotorSpeed();
    }

  floatToString(motorCurrent, currentStr); // float to str
  xsprintf(speedStr, "%d", motorSpeed); // int to str

  if (WM_IsVisible(hDialogControl))
    {
      hDlg = WM_GetClientWindow(hDialogControl);
      hText = WM_GetDialogItem(hDlg, ID_CURRENT_MEAS);
      TEXT_SetText(hText, currentStr);

      hText = WM_GetDialogItem(hDlg, ID_SPEED_MEAS);
      TEXT_SetText(hText, speedStr);
    }

  char data[20];
  xsprintf(data, "$%s$", currentStr);
  xprintf("%s", data);

  xsprintf(data, "^%d^", motorSpeed);
  xprintf("%s", data);
}
