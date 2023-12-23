#ifndef __BMA253_PCL_H
#define __BMA253_PCL_H


#include "HCL/driver/bma253/bma253_hcl.h"
#include "HCL/i2c/i2c_hcl.h"


#define PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT     1
#define PCL_BMA253_REG_SIZE                     1
#define PCL_BMA253_TIMEOUT                      1000


typedef bma253_t BMA253_TypeDef;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} BMA253_Accel_Data_t;

static void __PCL_BMA253_Read_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
static void __PCL_BMA253_Write_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);

void PCL_BMA253_Init(BMA253_TypeDef* pcl_bma253, I2C_HandleTypeDef* hcl_i2c);

void PCL_BMA253_Mem_Read(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
void PCL_BMA253_Mem_Write(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);



int16_t PCL_BMA253_Accel_Process_Raw_Data(uint16_t accel_data_u16, uint8_t range_u8);
int16_t PCL_BMA253_Get_Accel_X(BMA253_TypeDef* pcl_bma253);
int16_t PCL_BMA253_Get_Accel_Y(BMA253_TypeDef* pcl_bma253);
int16_t PCL_BMA253_Get_Accel_Z(BMA253_TypeDef* pcl_bma253);
void PCL_BMA253_Get_Accel_XYZ(BMA253_TypeDef* pcl_bma253, BMA253_Accel_Data_t* pcl_bma253_accel_data);
void PCL_BMA253_Get_Accel_XYZ_FIFO(BMA253_TypeDef* pcl_bma253, BMA253_Accel_Data_t* pcl_bma253_accel_data);

#endif