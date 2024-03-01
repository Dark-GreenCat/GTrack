#ifndef __BMA253_HARDWARE_INTERFACE_H
#define __BMA253_HARDWARE_INTERFACE_H

#include "bma253_def.h"
#include "../mcu_interface/bma253_mcu_i2c_interface.h"

typedef struct {
	u8 power_mode_u8;																			//save current bma253 operation mode
	u8 chip_id; 																						//chip_id of bma2x2
	u8 ctrl_mode_reg;																					//the value of power mode register 0x11
	u8 low_mode_reg;																					//the value of power mode register 0x12
	u8 dev_addr;																						//initializes bma2x2's I2C device address
	u8 fifo_config;																					//store the fifo configuration register
	i2c_interface_t* i2c_interface;
    void (*__read) (i2c_interface_t* i2c_interface, u8 dev_addr, u8 reg_addr, u8* p_data, u16 read_length);				//function pointer to the SPI/I2C read function
    void (*__write) (i2c_interface_t* i2c_interface, u8 dev_addr, u8 reg_addr, u8* p_data, u16 write_length);			//function pointer to the SPI/I2C write function
} bma253_t;

typedef struct {
	/*! Data buffer of user defined length is to be mapped here */
	u8 fifo_data[192];
	/*! Index of accel data stored in FIFO buffer */
	u8 accel_byte_start_index;
	/*! No of bytes to be read in FIFO as specified by the user */
	u8 fifo_length;
} bma253_fifo_config_t;

void BMA253_HWI_Init(bma253_t* bma253);

static inline void BMA253_HWI_Read_Reg(bma253_t* bma253, u8 reg_addr, u8* p_data, u16 read_length) {
	bma253->__read(bma253->i2c_interface, bma253->dev_addr, reg_addr, p_data, read_length);
}

static inline void BMA253_HWI_Write_Reg(bma253_t* bma253, u8 reg_addr, u8* p_data, u16 write_length) {
    bma253->__write(bma253->i2c_interface, bma253->dev_addr, reg_addr, p_data, write_length);
}

static inline u8 BMA253_HWI_get_bits(bma253_t* bma253, u8 reg_addr, u8 bits_pos, u8 bits_msk, u16 length) {
	u8 data_u8;
    BMA253_HWI_Read_Reg(bma253, reg_addr, &data_u8, length);
    data_u8 = ((data_u8 & bits_msk) >> bits_pos);
    return data_u8;
}

static inline void BMA253_HWI_set_bits(bma253_t* bma253, u8 reg_addr, u8 bits_pos, u8 bits_msk, u8 val) {
    u8 data_u8 = BMA253_INIT_VALUE;
    BMA253_HWI_Read_Reg(bma253, reg_addr, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    data_u8 = (data_u8 & ~bits_msk) | ((val << bits_pos) & bits_msk);
    BMA253_HWI_Write_Reg(bma253, reg_addr, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
}


#define BMA253_GET_BITS(bma253, bitname, len)\
(BMA253_HWI_get_bits((bma253), (bitname##_REG), (bitname##_POS), (bitname##_MSK), (len)))

#define BMA253_SET_BITS(bma253, bitname, val)\
(BMA253_HWI_set_bits((bma253), (bitname##_REG), (bitname##_POS), (bitname##_MSK), (val)))


u8 BMA253_HWI_get_shadow_dis(bma253_t* bma253);
void BMA253_HWI_set_shadow_dis(bma253_t* bma253, u8 shadow_dis_u8);

u8 BMA253_HWI_get_data_high_bw(bma253_t* bma253);
void BMA253_HWI_set_data_high_bw(bma253_t* bma253, u8 data_high_bw_u8);

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
u8 BMA253_HWI_get_bw(bma253_t* bma253);
void BMA253_HWI_set_bw(bma253_t* bma253, u8 bw_u8);

/*!
 *	range_u8 : The value of range
 *		  range_u8 |   result
 *       ----------------- | --------------
 *              0x03       | BMA253_PMU_RANGE_RANGE_2G
 *              0x05       | BMA253_PMU_RANGE_RANGE_4G
 *              0x08       | BMA253_PMU_RANGE_RANGE_8G
 *              0x0C       | BMA253_PMU_RANGE_RANGE_16G
 */
u8 BMA253_HWI_get_range(bma253_t* bma253);
void BMA253_HWI_set_range(bma253_t* bma253, u8 range_u8);


/*!
 *	fifo_mode_u8 : The value of fifo_mode
 *		  fifo_mode_u8 |   result
 *       ----------------- | --------------
 *              0x00       | BMA253_FIFO_CONFIG_1_FIFO_MODE_BYPASS
 *              0x01       | BMA253_FIFO_CONFIG_1_FIFO_MODE_FIFO
 *              0x02       | BMA253_FIFO_CONFIG_1_FIFO_MODE_STREAM
 */
u8 BMA253_HWI_get_fifo_mode(bma253_t* bma253);
void BMA253_HWI_set_fifo_mode(bma253_t* bma253, u8 fifo_mode_u8);

/*!
 *  fifo_data_select_u8 : The value of FIFO axis data select
 *   fifo_data_select_u8    |    result
 *  ------------------------- |------------------
 *        0x00                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_XYZ
 *        0x01                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_X
 *        0x02                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_Y
 *        0x03                |   BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_Z
 */
u8 BMA253_HWI_get_fifo_data_select(bma253_t* bma253);
void BMA253_HWI_set_fifo_data_select(bma253_t* bma253, u8 fifo_data_select_u8);

u8 BMA253_HWI_get_fifo_frame_counter(bma253_t* bma253);

void BMA253_HWI_read_fifo_data(bma253_t* bma253, bma253_fifo_config_t* bma253_fifo_data);
void BMA253_HWI_get_fifo_data_1frame(bma253_t* bma253, u8* fifo_data_u8);

u16 BMA253_HWI_get_accd_x_msb_lsb(bma253_t* bma253);
u16 BMA253_HWI_get_accd_y_msb_lsb(bma253_t* bma253);
u16 BMA253_HWI_get_accd_z_msb_lsb(bma253_t* bma253);

u8 BMA253_HWI_get_latch_int(bma253_t* bma253);
void BMA253_HWI_set_latch_int(bma253_t* bam253, u8 latch_int_u8);

u8 BMA253_HWI_get_source(bma253_t* bma253, u8 channel_u8);
void BMA253_HWI_set_source(bma253_t* bma253, u8 channel_u8, u8 int_src_u8);

u8 BMA253_HWI_get_int_map(bma253_t* bma253, u8 channel_u8, u8 int_number_u8);
void BMA253_HWI_set_int_map(bma253_t* bma253, u8 channel_u8, u8 int_number_u8, u8 int_map_u8);

u8 BMA253_HWI_get_intr_level(bma253_t* bma253, u8 channel_u8);
void BMA253_HWI_set_intr_level(bma253_t* bma253, u8 channel_u8, u8 intr_level_u8);

u8 BMA253_HWI_get_intr_output_type(bma253_t* bma253, u8 channel_u8);
void BMA253_HWI_set_intr_output_type(bma253_t* bma253, u8 channel_u8, u8 intr_output_type_u8);

u8 BMA253_HWI_get_slope_th(bma253_t* bma253);
void BMA253_HWI_set_slope_th(bma253_t* bma253, u8 slope_th_u8);

u8 BMA253_HWI_get_slope_dur(bma253_t* bma253);
void BMA253_HWI_set_slope_dur(bma253_t* bma253, u8 slope_dur_u8);

u8 BMA253_HWI_get_slope_en(bma253_t* bma253, u8 slope_axis_u8);
void BMA253_HWI_set_slope_en(bma253_t* bma253, u8 slope_axis_u8, u8 slope_en_axis_u8);

#endif