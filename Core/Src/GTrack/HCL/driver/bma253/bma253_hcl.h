#ifndef __BMA253_HCL_H
#define __BMA253_HCL_H

#include "bma2x2.h"
#include "HCL/i2c/i2c_hcl.h"
#include <stdint.h>

#define BMA253_ACCD_HBW_SHADOW_DIS_BITS_VAL     		((uint8_t) 1)
#define BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_VAL			((uint8_t) 1)

#define BMA253_FIFO_CONFIG_1_FIFO_MODE_BYPASS			((uint8_t) 0x00)
#define BMA253_FIFO_CONFIG_1_FIFO_MODE_FIFO				((uint8_t) 0x01)
#define BMA253_FIFO_CONFIG_1_FIFO_MODE_STREAM			((uint8_t) 0x02)

#define BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_XYZ		((uint8_t) 0x00)
#define BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_X			((uint8_t) 0x01)
#define BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_Y			((uint8_t) 0x02)
#define BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_Z			((uint8_t) 0x03)

#define BMA253_FIFO_DATA_REG							BMA253_FIFO_DATA_OUTPUT_ADDR

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

typedef struct {
	/*! Data buffer of user defined length is to be mapped here */
	uint8_t fifo_data[192];
	/*! Index of accel data stored in FIFO buffer */
	u8 accel_byte_start_index;
	/*! No of bytes to be read in FIFO as specified by the user */
	u8 fifo_length;
} bma253_fifo_config_t;

void HCL_BMA253_Init(bma253_t* bma253, 
					 void (*read)(I2C_HandleTypeDef*, uint8_t, uint8_t, uint8_t*, uint16_t), 
					 void (*write)(I2C_HandleTypeDef*, uint8_t, uint8_t, uint8_t*, uint16_t)
					);
void HCL_BMA253_Read_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
void HCL_BMA253_Write_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);


void HCL_BMA253_set_bits(bma253_t* bma253, uint8_t reg_addr, uint8_t bits_pos, uint8_t bits_msk, uint8_t val);
uint8_t HCL_BMA253_get_bits(bma253_t* bma253, uint8_t reg_addr, uint8_t bits_pos, uint8_t bits_msk, uint16_t length);

void HCL_BMA253_set_shadow_dis(bma253_t* bma253, uint8_t shadow_dis_u8);
uint8_t HCL_BMA253_get_shadow_dis(bma253_t* bma253);

void HCL_BMA253_set_data_high_bw(bma253_t* bma253, uint8_t data_high_bw_u8);
uint8_t HCL_BMA253_get_data_high_bw(bma253_t* bma253);

/*
 * 		  Value of bw_u8
 *		  bw_u8            |   result
 *       ----------------- | --------------
 *              0x08       | BMA253_PMU_BW_BW_BITS_7_81HZ
 *              0x09       | BMA253_PMU_BW_BW_BITS_15_63HZ
 *              0x0A       | BMA253_PMU_BW_BW_BITS_31_25HZ
 *              0x0B       | BMA253_PMU_BW_BW_BITS_62_50HZ
 *              0x0C       | BMA253_PMU_BW_BW_BITS_125HZ
 *              0x0D       | BMA253_PMU_BW_BW_BITS_250HZ
 *              0x0E       | BMA253_PMU_BW_BW_BITS_500HZ
 *              0x0F       | BMA253_PMU_BW_BW_BITS_1000HZ
*/
void HCL_BMA253_set_bw(bma253_t* bma253, uint8_t bw_u8);
uint8_t HCL_BMA253_get_bw(bma253_t* bma253);

/*!
 *	range_u8 : The value of range
 *		  range_u8 |   result
 *       ----------------- | --------------
 *              0x03       | BMA253_PMU_RANGE_RANGE_2G
 *              0x05       | BMA253_PMU_RANGE_RANGE_4G
 *              0x08       | BMA253_PMU_RANGE_RANGE_8G
 *              0x0C       | BMA253_PMU_RANGE_RANGE_16G
 */
void HCL_BMA253_set_range(bma253_t* bma253, uint8_t range_u8);
uint8_t HCL_BMA253_get_range(bma253_t* bma253);


/*!
 *	fifo_mode_u8 : The value of fifo_mode
 *		  fifo_mode_u8 |   result
 *       ----------------- | --------------
 *              0x00       | BMA253_FIFO_CONFIG_1_FIFO_MODE_BYPASS
 *              0x01       | BMA253_FIFO_CONFIG_1_FIFO_MODE_FIFO
 *              0x02       | BMA253_FIFO_CONFIG_1_FIFO_MODE_STREAM
 */
void HCL_BMA253_set_fifo_mode(bma253_t* bma253, uint8_t fifo_mode_u8);
uint8_t HCL_BMA253_get_fifo_mode(bma253_t* bma253);

/*!
 *  fifo_data_select_u8 : The value of FIFO axis data select
 *   fifo_data_select_u8    |    result
 *  ------------------------- |------------------
 *        0x00                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_XYZ
 *        0x01                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_X
 *        0x02                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_Y
 *        0x03                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_Z
 */
void HCL_BMA253_set_fifo_data_select(bma253_t* bma253, uint8_t fifo_data_select_u8);
uint8_t HCL_BMA253_get_fifo_data_select(bma253_t* bma253);

uint8_t HCL_BMA253_get_fifo_frame_counter(bma253_t* bma253);

void HCL_BMA253_read_fifo_data(bma253_t* bma253, bma253_fifo_config_t* bma253_fifo_data);
void HCL_BMA253_get_fifo_data_1frame(bma253_t* bma253, uint8_t* fifo_data_u8);


void HCL_BMA253_set_data_high_bw(bma253_t* bma253, uint8_t data_high_bw_u8);
uint8_t HCL_BMA253_get_data_high_bw(bma253_t* bma253);

/*
 * 		  Value of bw_u8
 *		  bw_u8            |   result
 *       ----------------- | --------------
 *              0x08       | BMA253_PMU_BW_BW_BITS_7_81HZ
 *              0x09       | BMA253_PMU_BW_BW_BITS_15_63HZ
 *              0x0A       | BMA253_PMU_BW_BW_BITS_31_25HZ
 *              0x0B       | BMA253_PMU_BW_BW_BITS_62_50HZ
 *              0x0C       | BMA253_PMU_BW_BW_BITS_125HZ
 *              0x0D       | BMA253_PMU_BW_BW_BITS_250HZ
 *              0x0E       | BMA253_PMU_BW_BW_BITS_500HZ
 *              0x0F       | BMA253_PMU_BW_BW_BITS_1000HZ
*/

void HCL_BMA253_set_bw(bma253_t* bma253, uint8_t bw_u8);
uint8_t HCL_BMA253_get_bw(bma253_t* bma253);

uint16_t HCL_BMA253_get_accd_x_msb_lsb(bma253_t* bma253);
uint16_t HCL_BMA253_get_accd_y_msb_lsb(bma253_t* bma253);
uint16_t HCL_BMA253_get_accd_z_msb_lsb(bma253_t* bma253);
#endif