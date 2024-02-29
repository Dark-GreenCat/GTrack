#ifndef __ADC_PAL_H
#define __ADC_PAL_H

#include "adc/adc_hcl.h"

#define PAL_ADC_TIMEOUT     1

float PAL_ADC_GetVoltage(ADC_HandleTypeDef* hadc, uint8_t channel_number);

#endif