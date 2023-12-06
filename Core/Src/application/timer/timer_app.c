#include "timer_app.h"

TIM_HandleTypeDef* htim_app;

void APP_TIMER_Init(TIM_HandleTypeDef* htim) {
    htim_app = htim;
}

void APP_TIMER_Start(void) {
  __HAL_TIM_CLEAR_FLAG(htim_app, TIM_SR_UIF);   // Prevent interrupt triggered immediately after calling HAL_TIM_Base_Start_IT()
  HAL_TIM_Base_Start_IT(htim_app);
}
