#include "bma253_driver.h"

void BMA253_DRV_Init(bma253_t* bma253, u8 bma253_dev_address, i2c_interface_t* i2c_interface) {
    bma253->i2c_interface = i2c_interface;
    bma253->dev_addr = bma253_dev_address;

    BMA253_HWI_Init(bma253);
}

s16 BMA253_DRV_Accel_Process_Raw_Data(u16 accel_data_u16, u8 range_u8) {
    s16 accel_value = accel_data_u16;
    accel_value >>= BMA253_SHIFT_FOUR_BITS;
    
    float multiplier = 0;
    switch (range_u8)
    {
    case BMA253_RANGE_2G:
        multiplier = 0.98;
        break;

    case BMA253_RANGE_4G:
        multiplier = 1.95;
        break;

    case BMA253_RANGE_8G:
        multiplier = 3.91;
        break;

    case BMA253_RANGE_16G:
        multiplier = 7.81;
        break;
    
    default:
        break;
    }

    accel_value *= multiplier;
    return accel_value;
}

s16 BMA253_DRV_Get_Accel_X(bma253_t* bma253) {
    u16 data_u16 = BMA253_HWI_get_accd_x_msb_lsb(bma253);
    u8 range_u8 = BMA253_HWI_get_range(bma253);
    return BMA253_DRV_Accel_Process_Raw_Data(data_u16, range_u8);
}

s16 BMA253_DRV_Get_Accel_Y(bma253_t* bma253) {
    u16 data_u16 = BMA253_HWI_get_accd_y_msb_lsb(bma253);
    u8 range_u8 = BMA253_HWI_get_range(bma253);
    return BMA253_DRV_Accel_Process_Raw_Data(data_u16, range_u8);
}

s16 BMA253_DRV_Get_Accel_Z(bma253_t* bma253) {
    u16 data_u16 = BMA253_HWI_get_accd_z_msb_lsb(bma253);
    u8 range_u8 = BMA253_HWI_get_range(bma253);
    return BMA253_DRV_Accel_Process_Raw_Data(data_u16, range_u8);
}

void BMA253_DRV_Get_Accel_XYZ(bma253_t* bma253, bma253_accel_data_t* bma253_accel_data) {
    bma253_accel_data->x = BMA253_DRV_Get_Accel_X(bma253);
    bma253_accel_data->y = BMA253_DRV_Get_Accel_Y(bma253);
    bma253_accel_data->z = BMA253_DRV_Get_Accel_Z(bma253);
}

void BMA253_DRV_Get_Accel_XYZ_SameTimestamp(bma253_t* bma253, bma253_accel_data_t* bma253_accel_data) {
    u16 fifo_data_readout_u16[] = {
        BMA253_INIT_VALUE, BMA253_INIT_VALUE, BMA253_INIT_VALUE
    };
    u8 range_u8 = BMA253_INIT_VALUE;
    u8 fifo_data_select_u8 = BMA253_INIT_VALUE;

    BMA253_HWI_get_fifo_data_1frame(bma253, (u8*) fifo_data_readout_u16);
    range_u8 = BMA253_HWI_get_range(bma253);
    fifo_data_select_u8 = BMA253_HWI_get_fifo_data_select(bma253);

    bma253_accel_data->x = bma253_accel_data->y = bma253_accel_data->z = BMA253_INIT_VALUE;
    switch (fifo_data_select_u8)
    {
    case BMA253_FIFO_XYZ_DATA_ENABLED:
        bma253_accel_data->x = BMA253_DRV_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        bma253_accel_data->y = BMA253_DRV_Accel_Process_Raw_Data(fifo_data_readout_u16[1], range_u8);
        bma253_accel_data->z = BMA253_DRV_Accel_Process_Raw_Data(fifo_data_readout_u16[2], range_u8);
        break;
    
    case BMA253_FIFO_X_DATA_ENABLED:
        bma253_accel_data->x = BMA253_DRV_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        break;
    
    case BMA253_FIFO_Y_DATA_ENABLED:
        bma253_accel_data->y = BMA253_DRV_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        break;
    
    case BMA253_FIFO_Z_DATA_ENABLED:
        bma253_accel_data->z = BMA253_DRV_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        break;
    
    default:
        break;
    }
}
