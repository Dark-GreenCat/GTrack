#ifndef __TIMER_HCL_H
#define __TIMER_HCL_H

#include "tim.h"
#include "stm32f0xx_hal.h"

extern TIM_HandleTypeDef* htim_led;

void HCL_TIMER_Init(TIM_HandleTypeDef* htim);
void HCL_TIMER_Start(TIM_HandleTypeDef* htim);
void HCL_TIMER_Stop(TIM_HandleTypeDef* htim);

#endif
