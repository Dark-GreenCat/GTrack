#include "application/signal/signal_app.h"

int test_signal_app_main(void) {
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    APP_SIGNAL_PWR_SetState(0);
    APP_SIGNAL_LED_SetState(1);
    HAL_Delay(200);
    APP_SIGNAL_PWR_SetState(1);
    APP_SIGNAL_LED_SetState(0);
    HAL_Delay(800);   
  }
}