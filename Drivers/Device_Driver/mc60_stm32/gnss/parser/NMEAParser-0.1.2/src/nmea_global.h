#ifndef __NMEA_GLOBAL_H
#define __NMEA_GLOBAL_H

#include "core/nmea_data.h"

// WARNING: Do not include this header directly. It is meant for internal use only.
// Including this header may lead to unexpected behavior and conflicts.

#define NMEA_FIELD_MESSAGE_ID       0

extern char Term[NMEA_MAX_FIELD_SIZE];
extern bool isFix;

#endif