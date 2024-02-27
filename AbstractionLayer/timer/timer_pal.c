#include "timer/timer_pal.h"
#include "signal/signal_pal.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  if(htim == &htim3) PAL_SIGNAL_LED_BlinkTimer(htim);
}