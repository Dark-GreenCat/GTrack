#ifndef __GNSS_H
#define __GNSS_H

#include <stdbool.h>
#include "../mc60_core/mc60_core.h"
#include "../Ultilities/string_util.h"

/* 2.1.1. AT+QGNSSC Control Power Supply of GNSS Module */
void MC60_GNSS_Power_On(bool PowerState);
void MC60_GNSS_Power_GetStatus();

/* 2.1.2. AT+QGNSSRD Read GNSS Navigation Information */
void MC60_GNSS_Set_NavigationInfo_Protocol(const char* protocol);
void MC60_GNSS_Get_NavigationInfo(void);

/* 2.1.3. AT+QGNSSCMD Send Commands to GNSS Module */
void MC60_GNSS_Send_NMEACmd(const char* cmdString);

/* 2.1.4. AT+QGNSSTS Get Time Synchronization Status for GNSS Module */
void MC60_GNSS_Get_TimeSyncStatus(void);

/* 2.1.5. AT+QGNSSEPO Enable/Disable EPOTM Function */
void MC60_GNSS_EPO_GetInfo(void);
void MC60_GNSS_EPO_SetEnable(bool EnableState);

/* 2.1.6. AT+QGREFLOC Set Reference Location Information for QuecFastFix Online */
void MC60_GNSS_ReferenceLocation_Read(void);
void MC60_GNSS_ReferenceLocation_Set(const char* ref_latitude, const char* ref_longtitude);

/* 2.1.7. AT+QGEPOAID Trigger EPOTM Function */
void MC60_GNSS_EPO_Trigger(void);

/* 2.1.8. AT+QGEPOF EPOTM File Operation */
void MC60_GNSS_EPOFileOperation_Set(const char* mode, const char* index);

#endif
