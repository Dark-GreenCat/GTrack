#ifndef __MC60_GNSS_DATA_RETRIEVAL_H
#define __MC60_GNSS_DATA_RETRIEVAL_H

#include "../interface/mc60_interface.h"

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

static inline void MC60_GNSS_Get_NMEA_Sentence(mc60_t* mc60, NMEASentenceType nmea_type, char* sentence) {
    
}

#endif