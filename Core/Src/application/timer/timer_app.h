#ifndef __TIMER_APP
#define __TIMER_APP

#include "tim.h"
#include "stm32f0xx_hal.h"

extern TIM_HandleTypeDef* htim_app;

void APP_TIMER_Init(TIM_HandleTypeDef* htim);
void APP_TIMER_Start(void);

#endif
