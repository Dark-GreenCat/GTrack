#include "bma253_hcl.h"

void HCL_BMA253_Init(bma253_t* bma253, 
                     void (*read)(I2C_HandleTypeDef*, uint8_t, uint8_t, uint8_t*, uint16_t), 
                     void (*write)(I2C_HandleTypeDef*, uint8_t, uint8_t, uint8_t*, uint16_t)
                     ) 
{
    uint8_t data_u8 = BMA253_INIT_VALUE;
    uint8_t config_data_u8 = BMA253_INIT_VALUE;

    /* Initialize BMA253 struct */
    bma253->__read = read;
    bma253->__write = write;

    /* Read ChipID */
    HCL_BMA253_Read_Reg(bma253, BMA253_BGW_CHIPID_REG, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    bma253->chip_id = data_u8;

    /* Read Fifo Config Register */
    HCL_BMA253_Read_Reg(bma253, BMA253_FIFO_CONFIG_1_FIFO_MODE_REG, &config_data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    bma253->fifo_config = config_data_u8;
}

void HCL_BMA253_Read_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    bma253->__read(bma253->hi2c, bma253->dev_addr, reg_addr, p_data, read_length);
}

void HCL_BMA253_Write_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    bma253->__write(bma253->hi2c, bma253->dev_addr, reg_addr, p_data, write_length);
}

uint8_t HCL_BMA253_get_bits(bma253_t* bma253, uint8_t reg_addr, uint8_t bits_pos, uint8_t bits_msk, uint16_t length) {
    uint8_t data_u8;

    HCL_BMA253_Read_Reg(bma253, reg_addr, &data_u8, length);
    data_u8 = ((data_u8 & bits_msk) >> bits_pos);
    
    return data_u8;
}

void HCL_BMA253_set_bits(bma253_t* bma253, uint8_t reg_addr, uint8_t bits_pos, uint8_t bits_msk, uint8_t val) {
    uint8_t data_u8 = BMA253_INIT_VALUE;
    
    HCL_BMA253_Read_Reg(bma253, reg_addr, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    data_u8 = (data_u8 & ~bits_msk) | ((val << bits_pos) & bits_msk);

    HCL_BMA253_Write_Reg(bma253, reg_addr, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
}

uint8_t HCL_BMA253_get_shadow_dis(bma253_t* bma253) {
    return
    HCL_BMA253_get_bits(bma253, BMA253_ACCD_HBW_SHADOW_DIS_BITS_REG,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_POS,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_MSK,
                                BMA253_GEN_READ_WRITE_LENGTH);
}

void HCL_BMA253_set_shadow_dis(bma253_t* bma253, uint8_t shadow_dis_u8) {
    HCL_BMA253_set_bits(bma253, BMA253_ACCD_HBW_SHADOW_DIS_BITS_REG,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_POS,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_MSK,                                
                                shadow_dis_u8);
}

uint8_t HCL_BMA253_get_data_high_bw(bma253_t* bma253) {
    return 
    HCL_BMA253_get_bits(bma253, BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_REG,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_POS,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_MSK,
                                BMA253_GEN_READ_WRITE_LENGTH);
}

void HCL_BMA253_set_data_high_bw(bma253_t* bma253, uint8_t data_high_bw_u8) {
    HCL_BMA253_set_bits(bma253, BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_REG,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_POS,
                                BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_MSK,
                                data_high_bw_u8);
}

uint8_t HCL_BMA253_get_bw(bma253_t* bma253) {
    return
    HCL_BMA253_get_bits(bma253, BMA253_PMU_BW_BW_BITS_REG,
                                BMA253_PMU_BW_BW_BITS_POS,
                                BMA253_PMU_BW_BW_BITS_MSK,
                                BMA253_GEN_READ_WRITE_LENGTH);
}

void HCL_BMA253_set_bw(bma253_t* bma253, uint8_t bw_u8) {
    HCL_BMA253_set_bits(bma253, BMA253_PMU_BW_BW_BITS_REG,
                                BMA253_PMU_BW_BW_BITS_POS,
                                BMA253_PMU_BW_BW_BITS_MSK,
                                bw_u8);
}

uint8_t HCL_BMA253_get_range(bma253_t* bma253) {
    return
    HCL_BMA253_get_bits(bma253,
                        BMA253_PMU_RANGE_RANGE_REG,
                        BMA253_PMU_RANGE_RANGE_POS,
                        BMA253_PMU_RANGE_RANGE_MSK,
                        BMA253_GEN_READ_WRITE_LENGTH);
}

void HCL_BMA253_set_fifo_mode(bma253_t* bma253, uint8_t fifo_mode_u8) {
    HCL_BMA253_set_bits(bma253,
                        BMA253_FIFO_CONFIG_1_FIFO_MODE_REG,
                        BMA253_FIFO_CONFIG_1_FIFO_MODE_POS,
                        BMA253_FIFO_CONFIG_1_FIFO_MODE_MSK,
                        fifo_mode_u8);
}

uint8_t HCL_BMA253_get_fifo_mode(bma253_t* bma253) {
    return
    HCL_BMA253_get_bits(bma253,
                        BMA253_FIFO_CONFIG_1_FIFO_MODE_REG,
                        BMA253_FIFO_CONFIG_1_FIFO_MODE_POS,
                        BMA253_FIFO_CONFIG_1_FIFO_MODE_MSK,
                        BMA253_GEN_READ_WRITE_LENGTH);
}

void HCL_BMA253_set_fifo_data_select(bma253_t* bma253, uint8_t fifo_data_select_u8) {
    HCL_BMA253_set_bits(bma253,
                        BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_REG,
                        BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_POS,
                        BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_MSK,
                        fifo_data_select_u8);
}

uint8_t HCL_BMA253_get_fifo_data_select(bma253_t* bma253) {
    return
    HCL_BMA253_get_bits(bma253,
                        BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_REG,
                        BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_POS,
                        BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_MSK,
                        BMA253_GEN_READ_WRITE_LENGTH);    
}

uint8_t HCL_BMA253_get_fifo_frame_counter(bma253_t* bma253) {
    return
    HCL_BMA253_get_bits(bma253,
                        BMA253_FIFO_STATUS_FIFO_FRAME_COUNTER_REG,
                        BMA253_FIFO_STATUS_FIFO_FRAME_COUNTER_POS,
                        BMA253_FIFO_STATUS_FIFO_FRAME_COUNTER_MSK,
                        BMA253_GEN_READ_WRITE_LENGTH);
}

void HCL_BMA253_read_fifo_data(bma253_t* bma253, bma253_fifo_config_t* bma253_fifo_data) {
    uint8_t fifo_data_select = HCL_BMA253_get_fifo_data_select(bma253);
    uint8_t fifo_frame_count = HCL_BMA253_get_fifo_frame_counter(bma253);

    uint8_t fifo_data_length;
    if(fifo_data_select == BMA253_FIFO_XYZ_DATA_ENABLED)
        fifo_data_length = fifo_frame_count * BMA253_FIFO_XYZ_AXES_FRAME_SIZE;
    else
        fifo_data_length = fifo_frame_count * BMA253_FIFO_SINGLE_AXIS_FRAME_SIZE;

    bma253_fifo_data->fifo_length = fifo_data_length;
    HCL_BMA253_Read_Reg(bma253, BMA253_FIFO_DATA_REG, bma253_fifo_data->fifo_data, bma253_fifo_data->fifo_length);
}

void HCL_BMA253_get_fifo_data_1frame(bma253_t* bma253, uint8_t* fifo_data_u8) {
    uint8_t fifo_data_select = HCL_BMA253_get_fifo_data_select(bma253);

    uint8_t fifo_data_length;
    if(fifo_data_select == BMA253_FIFO_XYZ_DATA_ENABLED)
        fifo_data_length = BMA253_FIFO_XYZ_AXES_FRAME_SIZE;
    else
        fifo_data_length = BMA253_FIFO_SINGLE_AXIS_FRAME_SIZE;
    
    HCL_BMA253_Read_Reg(bma253, BMA253_FIFO_DATA_REG, fifo_data_u8, fifo_data_length);
}

void HCL_BMA253_set_range(bma253_t* bma253, uint8_t range_u8) {
    HCL_BMA253_set_bits(bma253,
                        BMA253_PMU_RANGE_RANGE_REG,
                        BMA253_PMU_RANGE_RANGE_POS,
                        BMA253_PMU_RANGE_RANGE_MSK,
                        range_u8);
}


uint16_t HCL_BMA253_get_accd_x_msb_lsb(bma253_t* bma253) {
    uint16_t data_u16;
    HCL_BMA253_Read_Reg(bma253, BMA253_ACCEL_X12_LSB_REG, (uint8_t*) &data_u16, BMA253_LSB_MSB_READ_LENGTH);
    return data_u16;
}

uint16_t HCL_BMA253_get_accd_y_msb_lsb(bma253_t* bma253) {
    uint16_t data_u16;
    HCL_BMA253_Read_Reg(bma253, BMA253_ACCEL_Y12_LSB_REG, (uint8_t*) &data_u16, BMA253_LSB_MSB_READ_LENGTH);
    return data_u16;
}

uint16_t HCL_BMA253_get_accd_z_msb_lsb(bma253_t* bma253) {
    uint16_t data_u16;
    HCL_BMA253_Read_Reg(bma253, BMA253_ACCEL_Z12_LSB_REG, (uint8_t*) &data_u16, BMA253_LSB_MSB_READ_LENGTH);
    return data_u16;
}


