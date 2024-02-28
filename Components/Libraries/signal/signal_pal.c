#include "signal_pal.h"
#include "gpio/gpio_hcl.h"
#include "timer/timer_hcl.h"

void PAL_SIGNAL_PWR_SetState(bool state) {
    HCL_GPIO_WritePin(&hgpio_ctrl_led_r, !state);
}

void PAL_SIGNAL_LED_SetState(bool state) {
    HCL_GPIO_WritePin(&hgpio_ctrl_led_g, !state);
}

void PAL_SIGNAL_LED_Toggle() {
    HCL_GPIO_TogglePin(&hgpio_ctrl_led_g);
}

void PAL_SIGNAL_LED_BlinkTimer(TIM_HandleTypeDef* htim) {
    static uint8_t blinkCount = 0;

    if (blinkCount < 6) { // Blink 3 times (6 toggles)
        PAL_SIGNAL_LED_Toggle();
        blinkCount++;
    }
    else {
        HAL_TIM_Base_Stop_IT(htim);
        blinkCount = 0;
    }
}
