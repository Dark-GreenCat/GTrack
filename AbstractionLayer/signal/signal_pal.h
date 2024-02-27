#ifndef __SIGNAL_PAL_H
#define __SIGNAL_PAL_H

#include "main.h"
#include <stdbool.h>

void PAL_SIGNAL_PWR_SetState(bool state);
void PAL_SIGNAL_LED_SetState(bool state);
void PAL_SIGNAL_LED_Toggle();

void PAL_SIGNAL_LED_BlinkTimer(TIM_HandleTypeDef* htim);

#endif