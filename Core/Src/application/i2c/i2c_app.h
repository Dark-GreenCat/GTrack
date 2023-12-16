#ifndef __I2C_APP_H
#define __I2C_APP_H

#include "stm32f0xx_hal.h"
#include "i2c.h"

#define HCL_I2C_TIMEOUT         1000

/* Hardware Communication Layer - HCL*/
extern I2C_HandleTypeDef* hi2c_accelemeter;

void HCL_I2C_Mem_Read(I2C_HandleTypeDef* hi2c, uint16_t dev_addr, uint16_t reg_addr, uint8_t* p_data, uint16_t read_length);

#endif