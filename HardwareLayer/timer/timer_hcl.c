#include "timer_hcl.h"
#include "gpio/gpio_hcl.h"

TIM_HandleTypeDef* htim_led;
bool isTimerRunning;

void HCL_TIMER_Init(TIM_HandleTypeDef* htim) {
    htim_led = htim;
}

void HCL_TIMER_Start(TIM_HandleTypeDef* htim) {
  // __HAL_TIM_CLEAR_FLAG(htim_led, TIM_SR_UIF);   // Prevent interrupt triggered immediately after calling HAL_TIM_Base_Start_IT()
  HAL_TIM_Base_Start_IT(htim);
  isTimerRunning = true;
}

void HCL_TIMER_Stop(TIM_HandleTypeDef* htim) {
  HAL_TIM_Base_Stop_IT(htim);
  isTimerRunning = false;
}
