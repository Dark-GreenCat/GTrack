#ifndef __BMA253_HCL_H
#define __BMA253_HCL_H

#include "bma2x2.h"
#include "../HCL/i2c/i2c_hcl.h"
#include <stdint.h>

#define BMA253_ACCD_HBW_SHADOW_DIS_BITS_VAL     ((uint8_t) 1)
#define BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_VAL	((uint8_t) 1)

/**** ADAPTER STRUCT AND FUNCTIONS FOR SPECIFIC IMPLEMENTATION *****/
/*
	Please rewrite these to adapt your implementation, according to the instruction:
		1. ADD YOUR NECESSARY MEMBER to bma253_t struct
		   You can remove these struct members EXCEPT dev_addr
		2. ADD YOUR NECESSARY PARAMETERS to bma253_t (*__read) and (*__write) prototype.
		   DO NOT REMOVE THE OTHER PARAMETERS: dev_addr, reg_addr, p_data, read/write_length
		3. REWRITE the DEFINITION of HCL_BMA253_Read/Write_Reg()
		   DO NOT MODIFY THE PROTOTYPE of HCL_BMA253_Read/Write_Reg()
		   Make sure HCL_BMA253_Read/Write_Reg() call the (*__read)/(*__write) member function of bma253 struct
		4. REWRITE the PROTOTYPE and DEFINITION of HCL_BMA253_Init()
		   Make sure HCL_BMA253_Init() receive YOUR READ/WRITE FUNCTION and assign them to (*__read)/(*__write) of bma253_t

typedef struct {
	uint8_t power_mode_u8; 																					//save current bma253 operation mode
	uint8_t chip_id; 																						//chip_id of bma2x2
	uint8_t ctrl_mode_reg;																					//the value of power mode register 0x11
	uint8_t low_mode_reg;																					//the value of power mode register 0x12
	uint8_t dev_addr;																						//initializes bma2x2's I2C device address
	uint8_t fifo_config;																					//store the fifo configuration register
    void (*__read) (uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);				//function pointer to the SPI/I2C read function
    void (*__write) (uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);			//function pointer to the SPI/I2C write function
} bma253_t;

void HCL_BMA253_Init(bma253_t* bma253, void (*read)(uint8_t, uint8_t, uint8_t*, uint16_t), void (*write)(uint8_t, uint8_t, uint8_t*, uint16_t));
void HCL_BMA253_Read_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
void HCL_BMA253_Write_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);
*/

typedef struct {
	uint8_t power_mode_u8; 																					//save current bma253 operation mode
	uint8_t chip_id; 																						//chip_id of bma2x2
	uint8_t ctrl_mode_reg;																					//the value of power mode register 0x11
	uint8_t low_mode_reg;																					//the value of power mode register 0x12
	uint8_t dev_addr;																						//initializes bma2x2's I2C device address
	uint8_t fifo_config;																					//store the fifo configuration register
	I2C_HandleTypeDef* hi2c;
    void (*__read) (I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);				//function pointer to the SPI/I2C read function
    void (*__write) (I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);			//function pointer to the SPI/I2C write function
} bma253_t;


void HCL_BMA253_Init(bma253_t* bma253, 
					 void (*read)(I2C_HandleTypeDef*, uint8_t, uint8_t, uint8_t*, uint16_t), 
					 void (*write)(I2C_HandleTypeDef*, uint8_t, uint8_t, uint8_t*, uint16_t)
					);
void HCL_BMA253_Read_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
void HCL_BMA253_Write_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);

uint8_t HCL_BMA253_get_bits(bma253_t* bma253, uint8_t reg_addr, uint8_t bits_pos, uint8_t bits_msk, uint16_t length);
void HCL_BMA253_set_bits(bma253_t* bma253, uint8_t reg_addr, uint8_t bits_pos, uint8_t bits_msk, uint8_t val);

uint8_t HCL_BMA253_get_shadow_dis(bma253_t* bma253);
void HCL_BMA253_set_shadow_dis(bma253_t* bma253, uint8_t shadow_dis_u8);

uint8_t HCL_BMA253_get_data_high_bw(bma253_t* bma253);
void HCL_BMA253_set_data_high_bw(bma253_t* bma253, uint8_t data_high_bw_u8);

/*
Value range of BMA253_ACCEL_AXIS_LSB_REG:
    BMA253_ACCEL_X12_LSB_REG
    BMA253_ACCEL_Y12_LSB_REG
    BMA253_ACCEL_Z12_LSB_REG
*/
int16_t HCL_BMA253_get_accel(bma253_t* bma253, uint8_t BMA253_ACCEL_AXIS_LSB_REG);
int16_t HCL_BMA253_get_accel_x(bma253_t* bma253);
int16_t HCL_BMA253_get_accel_y(bma253_t* bma253);
int16_t HCL_BMA253_get_accel_z(bma253_t* bma253);
#endif