#ifndef __TIMER_HCL_H
#define __TIMER_HCL_H

#include "tim.h"
#include "stm32f0xx_hal.h"

extern TIM_HandleTypeDef* htim_app;

void HCL_TIMER_Init(TIM_HandleTypeDef* htim);
void HCL_TIMER_Start(void);

#endif
