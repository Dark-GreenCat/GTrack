#include "adc_hcl.h"

#include <stdbool.h>

static uint16_t ADCValue = 0;
static float Voltage = 0;
static bool IsADCUpdate = false;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    ADCValue = HAL_ADC_GetValue(hadc);
    Voltage = (float) ADCValue / 4095 * 3.3;

    IsADCUpdate = true;
}

void HCL_ADC_SelectChannel(uint8_t channel_number) {
    ADC1->CHSELR = (1UL << channel_number);
}

void HCL_ADC_StartSample(ADC_HandleTypeDef* hadc) {
    HAL_ADC_Start_IT(hadc);
}

bool HCL_ADC_IsUpdate() {
    return IsADCUpdate;
}

void HCL_ADC_ClearUpdate() {
    IsADCUpdate = false;
}

float HCL_ADC_GetVoltage() {
    IsADCUpdate = false;
    return Voltage;
}
