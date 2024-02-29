#include "adc_pal.h"

float PAL_ADC_GetVoltage(ADC_HandleTypeDef* hadc, uint8_t channel_number) {
    HCL_ADC_ClearUpdate();
    HCL_ADC_SelectChannel(channel_number);
    HCL_ADC_StartSample(hadc);

    uint32_t start_time = HAL_GetTick();
    while(HAL_GetTick() - start_time < PAL_ADC_TIMEOUT) {
        if (HCL_ADC_IsUpdate()) 
            return HCL_ADC_GetVoltage();
    }

    return -1.0;
}