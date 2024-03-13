#include "timer_hcl.h"
#include "gpio/gpio_hcl.h"

TIM_HandleTypeDef* htim_led;
TIM_HandleTypeDef* htim_pwr;
bool isTimerRunning;

void HCL_TIMER_Init(TIM_HandleTypeDef* htim) {
    if (htim == &htim3) htim_led = htim;
    if (htim == &htim6) htim_pwr = htim;
}

void HCL_TIMER_Start(TIM_HandleTypeDef* htim) {
  // __HAL_TIM_CLEAR_FLAG(htim_led, TIM_SR_UIF);   // Prevent interrupt triggered immediately after calling HAL_TIM_Base_Start_IT()
  HAL_TIM_Base_Start_IT(htim);
  if (htim == htim_led) isTimerRunning = true;
}

void HCL_TIMER_Stop(TIM_HandleTypeDef* htim) {
  HAL_TIM_Base_Stop_IT(htim);
  isTimerRunning = false;
}
