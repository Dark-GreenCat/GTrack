#ifndef __POWER_H
#define __POWER_H

#include "stm32f0xx_hal.h"

void STM32_LowPowerMode_Init(void);
void STM32_EnterSTANDBYMode(void);
void STM32_EnterSLEEPMode(void);

#endif