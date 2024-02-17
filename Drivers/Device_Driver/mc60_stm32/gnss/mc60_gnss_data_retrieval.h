#ifndef __MC60_GNSS_DATA_RETRIEVAL_H
#define __MC60_GNSS_DATA_RETRIEVAL_H

#include "../interface/mc60_interface.h"

#include "parser/NMEAParser-0.1.2/nmea_parser.h"

#define NMEA_RMC_PARAM "NMEA/RMC"
#define NMEA_VTG_PARAM "NMEA/VTG"
#define NMEA_GGA_PARAM "NMEA/GGA"
#define NMEA_GSA_PARAM "NMEA/GSA"
#define NMEA_GSV_PARAM "NMEA/GSV"
#define NMEA_GLL_PARAM "NMEA/GLL"

enum NMEASentenceType {
    NMEA_RMC = (1 << 0),
    NMEA_VTG = (1 << 1),
    NMEA_GGA = (1 << 2),
    NMEA_GSA = (1 << 3),
    NMEA_GSV = (1 << 4),
    NMEA_GLL = (1 << 5)
};

static inline bool MC60_GNSS_Get_Navigation_Info(mc60_t* mc60, nmea_data* gnss_data, uint32_t timeout) {
    MC60_ITF_SendCmd(mc60, "AT+QGNSSRD?");
    bool isSuccess = false;

    uint8_t numberOfLineNeedProcess = 2;
    uint32_t last = MC60_MCU_Uptime();

    uint16_t current_index = 0;
    while (last + timeout > MC60_MCU_Uptime()) {
        char c = MC60_ITF_ReceiveChar(mc60, timeout);
        if (c == 0) continue;
        last = MC60_MCU_Uptime();

        if (isSuccess && MC60_ITF_DetectResponse(c, MC60_RESPONSE_OK_STRING, MC60_RESPONSE_OK_LENGTH, &current_index)) break;
        if (!(NMEA_Parser_Process(gnss_data, c))) continue;
        isSuccess = (--numberOfLineNeedProcess == 0);
    }

    return isSuccess;
}

#endif