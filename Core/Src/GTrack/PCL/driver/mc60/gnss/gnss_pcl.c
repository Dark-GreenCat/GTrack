#include "gnss_pcl.h"
#include <stdint.h>

void MC60_GNSS_Power_On(bool PowerState) {
  MC60_ATCommand_Write("AT+QGNSSC", PowerState ? "1" : "0");
  HAL_GPIO_WritePin(GNSS_EN_GPIO_Port, GNSS_EN_Pin, PowerState);
}

void MC60_GNSS_Power_GetStatus() { MC60_ATCommand_Read("AT+QGNSSC"); }

void MC60_GNSS_Set_NavigationInfo_Protocol(const char *protocol) {
  MC60_ATCommand_Write("AT+QGNSSRD", protocol);
}

void MC60_GNSS_Get_NavigationInfo() {
  MC60_ATCommand_Read("AT+QGNSSRD");
  static char SerialLine[128];

  uint32_t TimeOut_Pre = HAL_GetTick();
  uint32_t TimeOut_Cur = TimeOut_Pre;
  while (1) {
    TimeOut_Cur = HAL_GetTick();
    if (TimeOut_Cur - TimeOut_Pre >= MC60_GNSS_TIMEOUT)
      return;

    bool isDone = PCL_UART_ReadStringUntil(huart_mc60, '\n', SerialLine);
    if (isDone) {
      if (UTIL_STRING_isStartWith(SerialLine, "OK"))
        return;
      if (UTIL_STRING_isStartWith(SerialLine, "\r"))
        continue;
      if (UTIL_STRING_isStartWith(SerialLine, "AT+")) {
        PCL_UART_OutString(
            huart_terminal,
            "\n\n\n------ GETTING NAVIGATION INFORMATION ------");
        continue;
      }

      PCL_UART_OutString(huart_terminal, "\nRead: ");
      PCL_UART_OutString(huart_terminal, SerialLine);
      char *p_SerialLine = SerialLine;
      UTIL_STRING_getSubStringAfterChar(p_SerialLine, ' ', p_SerialLine);
      UTIL_STRING_getSubStringBeforeChar(p_SerialLine, '\r', p_SerialLine);

      char GNGLL_Data[50];
      uint32_t index = -1;
      do {
        p_SerialLine += index + 1;
        UTIL_STRING_getSubStringBeforeChar(p_SerialLine, ',', GNGLL_Data);
        PCL_UART_OutString(huart_terminal, "\n    Data: ");
        PCL_UART_OutString(huart_terminal, GNGLL_Data);
        index = (uint32_t)UTIL_STRING_indexOf(p_SerialLine, ',');
      } while (index != (uint32_t)-1);
    }
  }
}

void MC60_GNSS_Send_NMEACmd(const char *cmdString) {
  MC60_ATCommand_Write_2Parameter("AT+QGNSSCMD", "0", cmdString);
}

void MC60_GNSS_Get_TimeSyncStatus(void) { MC60_ATCommand_Read("AT+QGNSSTS"); }

void MC60_GNSS_EPO_GetStatus(void) { MC60_ATCommand_Read("AT+QGNSSEPO"); }

void MC60_GNSS_EPO_GetInfo(void) { MC60_ATCommand_Read("AT+QGNSSEPO"); }

void MC60_GNSS_EPO_SetEnable(bool EnableState) {
  MC60_ATCommand_Write("AT+QGNSSEPO", EnableState ? "1" : "0");
}

void MC60_GNSS_ReferenceLocation_Read(void) {
  MC60_ATCommand_Read("AT+QGREFLOC");
}

void MC60_GNSS_ReferenceLocation_Set(const char *ref_latitude,
                                     const char *ref_longtitude) {
  MC60_ATCommand_Write_2Parameter("AT+QGREFLOC", ref_latitude, ref_longtitude);
}

void MC60_GNSS_EPO_Trigger(void) { MC60_ATCommand_Execute("AT+QGEPOAID"); }

void MC60_GNSS_EPOFileOperation_Set(const char *mode, const char *index) {
  MC60_ATCommand_Write_2Parameter("AT+QGEPOF", mode, index);
}
