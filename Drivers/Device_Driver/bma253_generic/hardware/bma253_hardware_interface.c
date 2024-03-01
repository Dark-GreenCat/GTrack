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

u8 BMA253_HWI_get_latch_int(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_LATCH_INTR, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_latch_int(bma253_t* bma253, u8 latch_int_u8) {
    BMA253_SET_BITS(bma253, BMA253_LATCH_INTR, latch_int_u8);
}

u8 BMA253_HWI_get_source(bma253_t* bma253, u8 channel_u8) {
    u8 int_src_u8 = -1;

    switch (channel_u8) {
        case BMA253_SOURCE_LOW_G:
            int_src_u8 = BMA253_GET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_LOW_G, BMA253_GEN_READ_WRITE_LENGTH);
            break;

        case BMA253_SOURCE_HIGH_G:
            int_src_u8 = BMA253_GET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_HIGH_G, BMA253_GEN_READ_WRITE_LENGTH);
            break;

        case BMA253_SOURCE_SLOPE:
            int_src_u8 = BMA253_GET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_SLOPE, BMA253_GEN_READ_WRITE_LENGTH);
            break;

        case BMA253_SOURCE_SLOW_NO_MOTION:
            int_src_u8 = BMA253_GET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_SLOW_NO_MOTION, BMA253_GEN_READ_WRITE_LENGTH);
            break;

        case BMA253_SOURCE_TAP:
            int_src_u8 = BMA253_GET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_TAP, BMA253_GEN_READ_WRITE_LENGTH);
            break;

        case BMA253_SOURCE_DATA:
            int_src_u8 = BMA253_GET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_DATA, BMA253_GEN_READ_WRITE_LENGTH);
            break;

        default:
            break;
    }

    return int_src_u8;
}

void BMA253_HWI_set_source(bma253_t* bma253, u8 channel_u8, u8 int_src_u8) {
    switch (channel_u8) {
        case BMA253_SOURCE_LOW_G:
            BMA253_SET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_LOW_G, int_src_u8);
            break;

        case BMA253_SOURCE_HIGH_G:
            BMA253_SET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_HIGH_G, int_src_u8);
            break;

        case BMA253_SOURCE_SLOPE:
            BMA253_SET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_SLOPE, int_src_u8);
            break;

        case BMA253_SOURCE_SLOW_NO_MOTION:
            BMA253_SET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_SLOW_NO_MOTION, int_src_u8);
            break;

        case BMA253_SOURCE_TAP:
            BMA253_SET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_TAP, int_src_u8);
            break;

        case BMA253_SOURCE_DATA:
            BMA253_SET_BITS(bma253, BMA253_UNFILT_INTR_SOURCE_DATA, int_src_u8);
            break;

        default:
            break;
    }
}

u8 BMA253_HWI_get_int_map(bma253_t* bma253, u8 channel_u8, u8 int_number_u8) {
    switch (channel_u8) {
        case BMA253_INTR_PAD_LOW_G:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_LOW_G, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_LOW_G, BMA253_GEN_READ_WRITE_LENGTH));
            break;

        case BMA253_INTR_PAD_HIGH_G:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_HIGH_G, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_HIGH_G, BMA253_GEN_READ_WRITE_LENGTH));
            break;

        case BMA253_INTR_PAD_SLOPE:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_SLOPE, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_SLOPE, BMA253_GEN_READ_WRITE_LENGTH));
            break;

        case BMA253_INTR_PAD_SLOW_NO_MOTION:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_SLOW_NO_MOTION, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_SLOW_NO_MOTION, BMA253_GEN_READ_WRITE_LENGTH));
            break;

        case BMA253_INTR_PAD_DOUBLE_TAP:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_DOUBLE_TAP, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_DOUBLE_TAP, BMA253_GEN_READ_WRITE_LENGTH));
            break;

        case BMA253_INTR_PAD_SINGLE_TAP:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_SINGLE_TAP, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_SINGLE_TAP, BMA253_GEN_READ_WRITE_LENGTH));
            break;

        case BMA253_INTR_PAD_ORIENT:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_ORIENT, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_ORIENT, BMA253_GEN_READ_WRITE_LENGTH));
            break;
            
        case BMA253_INTR_PAD_FLAT:
            return (int_number_u8 == BMA253_INTR1 ? BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_FLAT, BMA253_GEN_READ_WRITE_LENGTH) :
                BMA253_GET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_FLAT, BMA253_GEN_READ_WRITE_LENGTH));
            break;

        default:
            return 0;
            break;
    }
}

void BMA253_HWI_set_int_map(bma253_t* bma253, u8 channel_u8, u8 int_number_u8, u8 int_map_u8) {
    switch (channel_u8) {
        case BMA253_INTR_PAD_LOW_G:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_LOW_G, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_LOW_G, int_map_u8));
            break;

        case BMA253_INTR_PAD_HIGH_G:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_HIGH_G, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_HIGH_G, int_map_u8));
            break;

        case BMA253_INTR_PAD_SLOPE:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_SLOPE, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_SLOPE, int_map_u8));
            break;

        case BMA253_INTR_PAD_SLOW_NO_MOTION:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_SLOW_NO_MOTION, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_SLOW_NO_MOTION, int_map_u8));
            break;

        case BMA253_INTR_PAD_DOUBLE_TAP:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_DOUBLE_TAP, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_DOUBLE_TAP, int_map_u8));
            break;

        case BMA253_INTR_PAD_SINGLE_TAP:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_SINGLE_TAP, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_SINGLE_TAP, int_map_u8));
            break;

        case BMA253_INTR_PAD_ORIENT:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_ORIENT, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_ORIENT, int_map_u8));
            break;
            
        case BMA253_INTR_PAD_FLAT:
            (int_number_u8 == BMA253_INTR1 ? BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR1_PAD_FLAT, int_map_u8) :
                BMA253_SET_BITS(bma253, BMA253_ENABLE_INTR2_PAD_FLAT, int_map_u8));
            break;

        default:
            break;
    }
}

u8 BMA253_HWI_get_intr_level(bma253_t* bma253, u8 channel_u8) {
    switch (channel_u8)
    {
    case BMA253_INTR1_LEVEL:
        return BMA253_GET_BITS(bma253, BMA253_INTR1_PAD_ACTIVE_LEVEL, BMA253_GEN_READ_WRITE_LENGTH);
        break;
    
    case BMA253_INTR2_LEVEL:
        return BMA253_GET_BITS(bma253, BMA253_INTR2_PAD_ACTIVE_LEVEL, BMA253_GEN_READ_WRITE_LENGTH);
        break;

    default:
        return -1;
        break;
    }
}

void BMA253_HWI_set_intr_level(bma253_t* bma253, u8 channel_u8, u8 intr_level_u8) {
    switch (channel_u8)
    {
    case BMA253_INTR1_LEVEL:
        BMA253_SET_BITS(bma253, BMA253_INTR1_PAD_ACTIVE_LEVEL, intr_level_u8);
        break;

    case BMA253_INTR2_LEVEL:
        BMA253_SET_BITS(bma253, BMA253_INTR2_PAD_ACTIVE_LEVEL, intr_level_u8);
        break;
    
    default:
        break;
    }
}

u8 BMA253_HWI_get_intr_output_type(bma253_t* bma253, u8 channel_u8) {
    switch (channel_u8)
    {
    case BMA253_INTR1_OUTPUT:
        return BMA253_GET_BITS(bma253, BMA253_INTR1_PAD_OUTPUT_TYPE, BMA253_GEN_READ_WRITE_LENGTH);
        break;
    
    case BMA253_INTR2_OUTPUT:
        return BMA253_GET_BITS(bma253, BMA253_INTR2_PAD_OUTPUT_TYPE, BMA253_GEN_READ_WRITE_LENGTH);
        break;

    default:
        return -1;
        break;
    }
}

void BMA253_HWI_set_intr_output_type(bma253_t* bma253, u8 channel_u8, u8 intr_output_type_u8) {
    switch (channel_u8)
    {
    case BMA253_INTR1_OUTPUT:
        BMA253_SET_BITS(bma253, BMA253_INTR1_PAD_OUTPUT_TYPE, intr_output_type_u8);
        break;

    case BMA253_INTR2_OUTPUT:
        BMA253_SET_BITS(bma253, BMA253_INTR2_PAD_OUTPUT_TYPE, intr_output_type_u8);
        break;
    
    default:
        break;
    }
}

u8 BMA253_HWI_get_slope_th(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_SLOPE_THRES, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_slope_th(bma253_t* bma253, u8 slope_th_u8) {
    BMA253_SET_BITS(bma253, BMA253_SLOPE_THRES, slope_th_u8);
}

u8 BMA253_HWI_get_slope_dur(bma253_t* bma253) {
    return BMA253_GET_BITS(bma253, BMA253_SLOPE_DURN, BMA253_GEN_READ_WRITE_LENGTH);
}

void BMA253_HWI_set_slope_dur(bma253_t* bma253, u8 slope_dur_u8) {
    if (slope_dur_u8 > 0x03) slope_dur_u8 = 0x03;
    BMA253_SET_BITS(bma253, BMA253_SLOPE_DURN, slope_dur_u8);
}

u8 BMA253_HWI_get_slope_en(bma253_t* bma253, u8 slope_axis_u8) {
    switch (slope_axis_u8)
    {
    case BMA253_SLOPE_X_INTR:
        return BMA253_GET_BITS(bma253, BMA253_ENABLE_SLOPE_X_INTR, BMA253_GEN_READ_WRITE_LENGTH);
        break;
    
    case BMA253_SLOPE_Y_INTR:
        return BMA253_GET_BITS(bma253, BMA253_ENABLE_SLOPE_Y_INTR, BMA253_GEN_READ_WRITE_LENGTH);
        break;
    
    case BMA253_SLOPE_Z_INTR:
        return BMA253_GET_BITS(bma253, BMA253_ENABLE_SLOPE_Z_INTR, BMA253_GEN_READ_WRITE_LENGTH);
        break;
    
    default:
        return -1;
        break;
    }
}

void BMA253_HWI_set_slope_en(bma253_t* bma253, u8 slope_axis_u8, u8 slope_en_axis_u8) {
    switch (slope_axis_u8)
    {
    case BMA253_SLOPE_X_INTR:
        BMA253_SET_BITS(bma253, BMA253_ENABLE_SLOPE_X_INTR, slope_en_axis_u8);
        break;
    
    case BMA253_SLOPE_Y_INTR:
        BMA253_SET_BITS(bma253, BMA253_ENABLE_SLOPE_Y_INTR, slope_en_axis_u8);
        break;
    
    case BMA253_SLOPE_Z_INTR:
        BMA253_SET_BITS(bma253, BMA253_ENABLE_SLOPE_Z_INTR, slope_en_axis_u8);
        break;
    
    default:
        break;
    }
}




