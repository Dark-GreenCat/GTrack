#include "../peripheral/bma253/bma253_hcl.h"
#include "../Src/HCL/i2c/i2c_hcl.h"

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


/*
Value range of BMA253_ACCEL_12BIT_LSB_REG:
    BMA253_ACCEL_X12_LSB_REG
    BMA253_ACCEL_Y12_LSB_REG
    BMA253_ACCEL_Z12_LSB_REG
*/
int16_t PCL_BMA253_Get_Accel(BMA253_TypeDef* pcl_bma253, uint8_t BMA253_ACCEL_12BIT_LSB_REG);
int16_t PCL_BMA253_Get_Accel_X(BMA253_TypeDef* pcl_bma253);
int16_t PCL_BMA253_Get_Accel_Y(BMA253_TypeDef* pcl_bma253);
int16_t PCL_BMA253_Get_Accel_Z(BMA253_TypeDef* pcl_bma253);
void PCL_BMA253_Get_Accel_XYZ(BMA253_TypeDef* pcl_bma253, BMA253_Accel_Data_t* pcl_bma253_accel_data);