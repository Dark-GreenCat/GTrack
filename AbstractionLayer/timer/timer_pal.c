#include "timer/timer_pal.h"
#include "signal/signal_pal.h"

extern bool UAL_MC60_isTurningOn;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  static uint8_t mc60TurnOnCount = 0;
  if (htim != &htim3) return;
  
  mc60TurnOnCount = (UAL_MC60_isTurningOn && mc60TurnOnCount < 10) ? mc60TurnOnCount + 1 : 0;
  
  if (mc60TurnOnCount == 1) PAL_SIGNAL_LED_Toggle();
}