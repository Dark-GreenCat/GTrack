#include "power_app.h"

void STM32_LowPowerMode_Init() {
  __HAL_RCC_PWR_CLK_ENABLE();
}

void STM32_EnterSTANDBYMode() {
  /* Clear the WU FLAG */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  HAL_PWR_EnterSTANDBYMode();
}

void STM32_EnterSLEEPMode() {
  HAL_SuspendTick();
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}