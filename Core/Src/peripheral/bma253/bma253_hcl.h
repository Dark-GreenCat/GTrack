#include "bma2x2.h"
#include "stdint.h"

/*!
 *	@brief bma2x2 initialization struct
 *	struct bma2x2_t is used for assigning the following parameters.
 *
 *	Bus write function pointer: BMA2x2_WR_FUNC_PTR
 *	Bus read function pointer: BMA2x2_RD_FUNC_PTR
 *	Burst read function pointer: BMA2x2_BRD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *	Chip id of the sensor: chip_id
 */
typedef struct {
	/*! save current bma253 operation mode */
	uint8_t power_mode_u8;
	/*! chip_id of bma2x2 */
	uint8_t chip_id;
	/*! the value of power mode register 0x11*/
	uint8_t ctrl_mode_reg;
	/*! the value of power mode register 0x12*/
	uint8_t low_mode_reg;
	/*! initializes bma2x2's I2C device address*/
	uint8_t dev_addr;
	/*! store the fifo configuration register*/
	uint8_t fifo_config;
	/*! function pointer to the SPI/I2C write function */
    void (*write) (uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length);
	/*! function pointer to the SPI/I2C read function */
    void (*read) (uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length);
} bma253_t;



void HCL_BMA253_Init(bma253_t* bma253);
void HCL_BMA253_Read_Reg(uint8_t reg_addr, uint8_t *data_u8, uint8_t len_u8);
void HCL_BMA253_Write_Reg(uint8_t reg_addr, uint8_t *data_u8, uint8_t len_u8);