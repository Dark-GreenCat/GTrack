#include "supplier_pal.h"

float PAL_SUPPLIER_GetBatteryVoltage() {
    return PAL_ADC_GetVoltage(&hadc, PAL_SUPPLIER_CHANNEL_BATTERY);
}

float PAL_SUPPLIER_GetChargerVoltage() {
    return PAL_ADC_GetVoltage(&hadc, PAL_SUPPLIER_CHANNEL_CHARGER);
}