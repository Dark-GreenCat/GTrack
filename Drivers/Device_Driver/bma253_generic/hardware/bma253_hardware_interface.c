#include "bma253_hardware_interface.h"

void BMA253_HWI_Init(bma253_t* bma253) 
{
    u8 data_u8 = BMA253_INIT_VALUE;
    u8 config_data_u8 = BMA253_INIT_VALUE;

    /* Initialize BMA253 struct */
    bma253->__read = BMA253_I2C_Read_Reg;
    bma253->__write = BMA253_I2C_Write_Reg;

    /* Read ChipID */
    bma253->__read(bma253->i2c_interface, bma253->dev_addr, BMA253_CHIP_ID_REG, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    bma253->chip_id = data_u8;

    /* Read Fifo Config Register */
    bma253->__read(bma253->i2c_interface, bma253->dev_addr, BMA253_FIFO_MODE_REG, &config_data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    bma253->fifo_config = config_data_u8;
}


u8 BMA253_HWI_get_shadow_dis(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_DIS_SHADOW_PROC, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_shadow_dis(bma253_t* bma253, u8 shadow_dis_u8) {
    BMA253_SET_BITS(bma253, BMA253_DIS_SHADOW_PROC, shadow_dis_u8);
}

u8 BMA253_HWI_get_data_high_bw(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_ENABLE_DATA_HIGH_BW, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_data_high_bw(bma253_t* bma253, u8 data_high_bw_u8) {
    BMA253_SET_BITS(bma253, BMA253_ENABLE_DATA_HIGH_BW, data_high_bw_u8);
}

u8 BMA253_HWI_get_bw(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_BW, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_bw(bma253_t* bma253, u8 bw_u8) {
    BMA253_SET_BITS(bma253, BMA253_BW, BMA253_GEN_READ_WRITE_LENGTH);
}

u8 BMA253_HWI_get_range(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_RANGE_SELECT, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_range(bma253_t* bma253, u8 range_u8) {
    BMA253_SET_BITS(bma253, BMA253_RANGE_SELECT, range_u8);
}

u8 BMA253_HWI_get_fifo_mode(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_FIFO_MODE, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_fifo_mode(bma253_t* bma253, u8 fifo_mode_u8) {
    BMA253_SET_BITS(bma253, BMA253_FIFO_MODE, fifo_mode_u8);
}

u8 BMA253_HWI_get_fifo_data_select(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_FIFO_DATA_SELECT, BMA253_GEN_READ_WRITE_LENGTH); 
}

void BMA253_HWI_set_fifo_data_select(bma253_t* bma253, u8 fifo_data_select_u8) {
    BMA253_SET_BITS(bma253, BMA253_FIFO_DATA_SELECT, fifo_data_select_u8);
}


u8 BMA253_HWI_get_fifo_frame_counter(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_FIFO_FRAME_COUNT_STAT, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_read_fifo_data(bma253_t* bma253, bma253_fifo_config_t* bma253_fifo_data) {
    u8 fifo_data_select = BMA253_HWI_get_fifo_data_select(bma253);
    u8 fifo_frame_count = BMA253_HWI_get_fifo_frame_counter(bma253);

    u8 fifo_data_length;
    if(fifo_data_select == BMA253_FIFO_XYZ_DATA_ENABLED)
        fifo_data_length = fifo_frame_count * BMA253_FIFO_XYZ_AXES_FRAME_SIZE;
    else
        fifo_data_length = fifo_frame_count * BMA253_FIFO_SINGLE_AXIS_FRAME_SIZE;

    bma253_fifo_data->fifo_length = fifo_data_length;
    BMA253_HWI_Read_Reg(bma253, BMA253_FIFO_DATA_OUTPUT_ADDR, bma253_fifo_data->fifo_data, bma253_fifo_data->fifo_length);
}

void BMA253_HWI_get_fifo_data_1frame(bma253_t* bma253, u8* fifo_data_u8) {
    u8 fifo_data_select = BMA253_HWI_get_fifo_data_select(bma253);

    u8 fifo_data_length;
    if(fifo_data_select == BMA253_FIFO_XYZ_DATA_ENABLED)
        fifo_data_length = BMA253_FIFO_XYZ_AXES_FRAME_SIZE;
    else
        fifo_data_length = BMA253_FIFO_SINGLE_AXIS_FRAME_SIZE;
    
    BMA253_HWI_Read_Reg(bma253, BMA253_FIFO_DATA_OUTPUT_ADDR, fifo_data_u8, fifo_data_length);
}


uint16_t BMA253_HWI_get_accd_x_msb_lsb(bma253_t* bma253) {
    uint16_t data_u16;
    BMA253_HWI_Read_Reg(bma253, BMA253_ACCEL_X12_LSB_REG, (u8*) &data_u16, BMA253_LSB_MSB_READ_LENGTH);
    return data_u16;
}

uint16_t BMA253_HWI_get_accd_y_msb_lsb(bma253_t* bma253) {
    uint16_t data_u16;
    BMA253_HWI_Read_Reg(bma253, BMA253_ACCEL_Y12_LSB_REG, (u8*) &data_u16, BMA253_LSB_MSB_READ_LENGTH);
    return data_u16;
}

uint16_t BMA253_HWI_get_accd_z_msb_lsb(bma253_t* bma253) {
    uint16_t data_u16;
    BMA253_HWI_Read_Reg(bma253, BMA253_ACCEL_Z12_LSB_REG, (u8*) &data_u16, BMA253_LSB_MSB_READ_LENGTH);
    return data_u16;
}


