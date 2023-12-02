#include "gnss.h"

void MC60_GNSS_Power_On(bool PowerState) {
    MC60_ATCommand_Write("AT+QGNSSC", PowerState ? "1" : "0");
}

void MC60_GNSS_Power_GetStatus() {
    MC60_ATCommand_Read("AT+QGNSSC");
}

void MC60_GNSS_Set_NavigationInfo_Protocol(const char* protocol) {
    MC60_ATCommand_Write("AT+QGNSSRD", protocol);
}

void MC60_GNSS_Get_NavigationInfo(void) {
    MC60_ATCommand_Read("AT+QGNSSRD");
}

void MC60_GNSS_Send_NMEACmd(const char* cmdString) {
    MC60_ATCommand_Write_2Parameter("AT+QGNSSCMD", "0", cmdString);
}

void MC60_GNSS_Get_TimeSyncStatus(void) {
    MC60_ATCommand_Read("AT+QGNSSTS");
}

void MC60_GNSS_EPO_GetStatus(void) {
    MC60_ATCommand_Read("AT+QGNSSEPO");
}

void MC60_GNSS_EPO_GetInfo(void) {
    MC60_ATCommand_Read("AT+QGNSSEPO");
}

void MC60_GNSS_EPO_SetEnable(bool EnableState) {
    MC60_ATCommand_Write("AT+QGNSSEPO", EnableState ? "1" : "0");
}

void MC60_GNSS_ReferenceLocation_Read(void) {
    MC60_ATCommand_Read("AT+QGREFLOC");
}

void MC60_GNSS_ReferenceLocation_Set(const char* ref_latitude, const char* ref_longtitude) {
    MC60_ATCommand_Write_2Parameter("AT+QGREFLOC", ref_latitude, ref_longtitude);
}

void MC60_GNSS_EPO_Trigger(void) {
    MC60_ATCommand_Execute("AT+QGEPOAID");
}

void MC60_GNSS_EPOFileOperation_Set(const char* mode, const char* index) {
    MC60_ATCommand_Write_2Parameter("AT+QGEPOF", mode, index);
}
