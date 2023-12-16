#include "../peripheral/bma253/bma253_hcl.h"
#include "../Src/HCL/i2c/i2c_hcl.h"

#define PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT     1
#define PCL_BMA253_REG_SIZE                     1
#define PCL_BMA253_TIMEOUT                      1000

typedef struct {
    bma253_t bma253;
    I2C_HandleTypeDef* hi2c;
} BMA253_TypeDef;


static void __PCL_BMA253_Read_Reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
static void __PCL_BMA253_Write_Reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);
void PCL_BMA253_Init(BMA253_TypeDef* pcl_bma253, I2C_HandleTypeDef* hcl_i2c);

void PCL_BMA253_Mem_Read(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
void PCL_BMA253_Mem_Write(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);


/*
Value range of BMA2x2_ACCEL_12BIT_LSB_REG:
    BMA2x2_ACCEL_X12_LSB_REG
    BMA2x2_ACCEL_Y12_LSB_REG
    BMA2x2_ACCEL_Z12_LSB_REG
*/
int16_t PCL_BMA253_Get_Accel(BMA253_TypeDef* pcl_bma253, uint8_t BMA2x2_ACCEL_12BIT_LSB_REG);
int16_t PCL_BMA253_Get_Accel_X(BMA253_TypeDef* pcl_bma253);
int16_t PCL_BMA253_Get_Accel_Y(BMA253_TypeDef* pcl_bma253);
int16_t PCL_BMA253_Get_Accel_Z(BMA253_TypeDef* pcl_bma253);