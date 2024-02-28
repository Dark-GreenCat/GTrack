#ifndef __TIMER_PAL_H
#define __TIMER_PAL_H

#include "timer/timer_hcl.h"

#define PAL_TIM_GETSCALE(htim, ms) ((ms) / ((htim)->Init.Period))

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim);

#endif