#ifndef __MC60_GNSS_H
#define __MC60_GNSS_H

#include "mc60_gnss_data_retrieval.h"

static inline void MC60_GNSS_PowerOn(mc60_t* mc60) {
    MC60_ITF_SendCmd(mc60, "AT+QGNSSC=1");
}

static inline void MC60_GNSS_PowerOff(mc60_t* mc60) {
    MC60_ITF_SendCmd(mc60, "AT+QGNSSC=0");
}

#endif