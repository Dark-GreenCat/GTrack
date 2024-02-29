#ifndef __ADC_HCL_H
#define __ADC_HCL_H

#include "adc.h"
#include <stdbool.h>

void HCL_ADC_SelectChannel(uint8_t channel_number);
void HCL_ADC_StartSample(ADC_HandleTypeDef* hadc);
bool HCL_ADC_IsUpdate();
void HCL_ADC_ClearUpdate();
float HCL_ADC_GetVoltage();

#endif