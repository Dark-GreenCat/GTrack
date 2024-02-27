#include "timer_hcl.h"
#include "gpio/gpio_hcl.h"

TIM_HandleTypeDef* htim_led;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  static uint8_t blinkCount = 0;

  if (htim == &htim3) {
    if (blinkCount < 6) { // Blink 3 times (6 toggles)
      HCL_GPIO_TogglePin(&hgpio_ctrl_led_g);
      blinkCount++;
    }
    else {
      HAL_TIM_Base_Stop_IT(htim);
      blinkCount = 0;
    }
  }
}

void HCL_TIMER_Init(TIM_HandleTypeDef* htim) {
    htim_led = htim;
}

void HCL_TIMER_Start(TIM_HandleTypeDef* htim) {
  // __HAL_TIM_CLEAR_FLAG(htim_led, TIM_SR_UIF);   // Prevent interrupt triggered immediately after calling HAL_TIM_Base_Start_IT()
  HAL_TIM_Base_Start_IT(htim);
}

void HCL_TIMER_Stop(TIM_HandleTypeDef* htim) {
  HAL_TIM_Base_Stop_IT(htim);
}
