#ifndef __GPIO_HCL_H
#define __GPIO_HCL_H

#include "gpio.h"

typedef struct {
    GPIO_TypeDef* Port;
    uint16_t Pin;
} GPIO_HandleTypeDef;

extern GPIO_HandleTypeDef hgpio_mc60_pwrkey;
extern GPIO_HandleTypeDef hgpio_mc60_gnss_en;
extern GPIO_HandleTypeDef hgpio_mc60_gsm_en;
extern GPIO_HandleTypeDef hgpio_mc60_vdd_ext;


static inline void HCL_GPIO_Config(GPIO_HandleTypeDef* hgpio, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    hgpio->Port = GPIOx;
    hgpio->Pin = GPIO_Pin;
}

static inline void HCL_GPIO_Init() {
    HCL_GPIO_Config(&hgpio_mc60_gsm_en, GSM_EN_GPIO_Port, GSM_EN_Pin);
    HCL_GPIO_Config(&hgpio_mc60_pwrkey, MC60_PWRKEY_GPIO_Port, MC60_PWRKEY_Pin);
    HCL_GPIO_Config(&hgpio_mc60_gnss_en, GNSS_EN_GPIO_Port, GNSS_EN_Pin);
    HCL_GPIO_Config(&hgpio_mc60_vdd_ext, MC60_VDD_EXT_GPIO_Port, MC60_VDD_EXT_Pin);
}

static inline void HCL_GPIO_WritePin(GPIO_HandleTypeDef* hgpio, GPIO_PinState PinState) {
    HAL_GPIO_WritePin(hgpio->Port, hgpio->Pin, PinState);
}

static inline GPIO_PinState HCL_GPIO_ReadPin(GPIO_HandleTypeDef* hgpio) {
    return HAL_GPIO_ReadPin(hgpio->Port, hgpio->Pin);
}

#endif