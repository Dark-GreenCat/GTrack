#include "bma253_pcl.h"

static I2C_HandleTypeDef* pcl_bma253_i2c;

void __PCL_BMA253_Read_Reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HCL_I2C_Mem_Read(pcl_bma253_i2c, 
                    dev_addr << PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                    reg_addr, PCL_BMA253_REG_SIZE, 
                    p_data, 
                    read_length, 
                    PCL_BMA253_TIMEOUT);
}

void __PCL_BMA253_Write_Reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_I2C_Mem_Write(pcl_bma253_i2c, 
                dev_addr << PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, PCL_BMA253_REG_SIZE, 
                p_data, 
                write_length, 
                PCL_BMA253_TIMEOUT);
}

void PCL_BMA253_Init(BMA253_TypeDef* pcl_bma253, I2C_HandleTypeDef* hcl_i2c) {
    pcl_bma253->hi2c = hcl_i2c;
    pcl_bma253->bma253.dev_addr = BMA2x2_I2C_ADDR1;
    pcl_bma253_i2c = pcl_bma253->hi2c;

    pcl_bma253->bma253.write = __PCL_BMA253_Write_Reg;
    pcl_bma253->bma253.read = __PCL_BMA253_Read_Reg;
    HCL_BMA253_Init(&pcl_bma253->bma253);
}

void PCL_BMA253_Mem_Read(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    I2C_HandleTypeDef* pcl_bma253_i2c_current = pcl_bma253_i2c;
    pcl_bma253_i2c = pcl_bma253->hi2c;

    __PCL_BMA253_Read_Reg(pcl_bma253->bma253.dev_addr, reg_addr, p_data, read_length);
    pcl_bma253_i2c = pcl_bma253_i2c_current;
}

void PCL_BMA253_Mem_Write(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    I2C_HandleTypeDef* pcl_bma253_i2c_current = pcl_bma253_i2c;
    pcl_bma253_i2c = pcl_bma253->hi2c;

    __PCL_BMA253_Write_Reg(pcl_bma253->bma253.dev_addr, reg_addr, p_data, write_length);
    pcl_bma253_i2c = pcl_bma253_i2c_current;
}

int16_t PCL_BMA253_Get_Accel(BMA253_TypeDef* pcl_bma253, uint8_t BMA2x2_ACCEL_12BIT_LSB_REG) {
    uint8_t data_u8[BMA2x2_ACCEL_DATA_SIZE] = {
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE
    };

    PCL_BMA253_Mem_Read(pcl_bma253, BMA2x2_ACCEL_12BIT_LSB_REG, data_u8, BMA2x2_LSB_MSB_READ_LENGTH);

    int16_t accel_value = ((((int16_t) data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]) << BMA2x2_SHIFT_EIGHT_BITS) | data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB]);
    accel_value >>= BMA2x2_SHIFT_FOUR_BITS;

    return accel_value;
}

int16_t PCL_BMA253_Get_Accel_X(BMA253_TypeDef* pcl_bma253) {
    return PCL_BMA253_Get_Accel(pcl_bma253, BMA2x2_ACCEL_X12_LSB_REG);
}

int16_t PCL_BMA253_Get_Accel_Y(BMA253_TypeDef* pcl_bma253) {
    return PCL_BMA253_Get_Accel(pcl_bma253, BMA2x2_ACCEL_Y12_LSB_REG);
}

int16_t PCL_BMA253_Get_Accel_Z(BMA253_TypeDef* pcl_bma253) {
    return PCL_BMA253_Get_Accel(pcl_bma253, BMA2x2_ACCEL_Z12_LSB_REG);
}
