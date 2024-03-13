#ifndef __POWER_HCL_H
#define __POWER_HCL_H

#include "main.h"
#include "stm32f0xx_hal.h"

extern bool IsSleep;
extern bool IsStop;
void HCL_POWER_EnterSleepMode();
void HCL_POWER_EnterStopMode();

#endif