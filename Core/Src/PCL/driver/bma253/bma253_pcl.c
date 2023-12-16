#include "bma253_pcl.h"

void PCL_BMA253_Init(BMA253_TypeDef* pcl_bma253, I2C_HandleTypeDef* hcl_i2c) {
    pcl_bma253->hi2c = hcl_i2c;
    pcl_bma253->bma253.dev_addr = BMA2x2_I2C_ADDR1;

    HCL_BMA253_Init(&pcl_bma253->bma253);
}

void PCL_BMA253_Mem_Read(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HCL_BMA253_Read_Reg(pcl_bma253->hi2c, pcl_bma253->bma253.dev_addr, reg_addr, p_data, read_length);
}

void PCL_BMA253_Mem_Write(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_BMA253_Write_Reg(pcl_bma253->hi2c, pcl_bma253->bma253.dev_addr, reg_addr, p_data, write_length);
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

void PCL_BMA253_Get_Accel_XYZ(BMA253_TypeDef* pcl_bma253, BMA253_Accel_Data_t* pcl_bma253_accel_data) {
    pcl_bma253_accel_data->x = PCL_BMA253_Get_Accel_X(pcl_bma253);
    pcl_bma253_accel_data->y = PCL_BMA253_Get_Accel_Y(pcl_bma253);
    pcl_bma253_accel_data->z = PCL_BMA253_Get_Accel_Z(pcl_bma253);
}
