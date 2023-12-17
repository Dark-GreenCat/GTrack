#include "bma253_pcl.h"

void __PCL_BMA253_Read_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HCL_I2C_Mem_Read(hi2c, 
                dev_addr << PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, PCL_BMA253_REG_SIZE, 
                p_data, 
                read_length, 
                PCL_BMA253_TIMEOUT);
}

void __PCL_BMA253_Write_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_I2C_Mem_Write(hi2c, 
                dev_addr << PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, PCL_BMA253_REG_SIZE, 
                p_data, 
                write_length, 
                PCL_BMA253_TIMEOUT);
}

void PCL_BMA253_Init(BMA253_TypeDef* pcl_bma253, I2C_HandleTypeDef* hi2c) {
    pcl_bma253->hi2c = hi2c;
    pcl_bma253->dev_addr = BMA253_I2C_ADDR1;

    HCL_BMA253_Init(pcl_bma253, __PCL_BMA253_Read_Reg, __PCL_BMA253_Write_Reg);

    /* Make sure the accurate of accel data */
    HCL_BMA253_set_shadow_dis(pcl_bma253, !BMA253_ACCD_HBW_SHADOW_DIS_BITS_VAL);
    /* Filter accel data */
    HCL_BMA253_set_data_high_bw(pcl_bma253, !BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_VAL);
}

void PCL_BMA253_Mem_Read(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HCL_BMA253_Read_Reg(pcl_bma253, reg_addr, p_data, read_length);
}

void PCL_BMA253_Mem_Write(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_BMA253_Write_Reg(pcl_bma253, reg_addr, p_data, write_length);
}



int16_t PCL_BMA253_Get_Accel_X(BMA253_TypeDef* pcl_bma253) {
    return HCL_BMA253_get_accel_x(pcl_bma253);
}

int16_t PCL_BMA253_Get_Accel_Y(BMA253_TypeDef* pcl_bma253) {
    return HCL_BMA253_get_accel_y(pcl_bma253);
}

int16_t PCL_BMA253_Get_Accel_Z(BMA253_TypeDef* pcl_bma253) {
    return HCL_BMA253_get_accel_z(pcl_bma253);
}

void PCL_BMA253_Get_Accel_XYZ(BMA253_TypeDef* pcl_bma253, BMA253_Accel_Data_t* pcl_bma253_accel_data) {
    pcl_bma253_accel_data->x = PCL_BMA253_Get_Accel_X(pcl_bma253);
    pcl_bma253_accel_data->y = PCL_BMA253_Get_Accel_Y(pcl_bma253);
    pcl_bma253_accel_data->z = PCL_BMA253_Get_Accel_Z(pcl_bma253);
}
