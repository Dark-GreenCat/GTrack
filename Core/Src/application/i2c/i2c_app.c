#include "i2c_app.h"

void HCL_I2C_Mem_Read(I2C_HandleTypeDef* hi2c, uint16_t dev_addr, uint16_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HAL_I2C_Mem_Read(hi2c, (dev_addr << 1), reg_addr, 1, p_data, read_length, HCL_I2C_TIMEOUT);
}