#include "signal_app.h"

void APP_SIGNAL_PWR_SetState(bool state) {
    HAL_GPIO_WritePin(LED_PWR_GPIO_Port, LED_PWR_Pin, !state);
}

void APP_SIGNAL_LED_SetState(bool state) {
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, !state);
}

