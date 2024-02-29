#ifndef __SUPPLIER_PAL_H
#define __SUPPLIER_PAL_H

#include "adc/adc_pal.h"

#define PAL_SUPPLIER_CHANNEL_BATTERY        1
#define PAL_SUPPLIER_CHANNEL_CHARGER        2

float PAL_SUPPLIER_GetBatteryVoltage();
float PAL_SUPPLIER_GetChargerVoltage();

#endif
