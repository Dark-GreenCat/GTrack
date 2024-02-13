#ifndef __BMA253_PCL_H
#define __BMA253_PCL_H

#include "hardware/bma253_hardware_interface.h"

#define BMA253_ACCD_HBW_SHADOW_DIS_BITS_VAL     		((u8) 1)
#define BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_VAL			((u8) 1)

#define BMA253_FIFO_MODE_BYPASS			((u8) 0x00)
#define BMA253_FIFO_MODE_FIFO			((u8) 0x01)
#define BMA253_FIFO_MODE_STREAM			((u8) 0x02)

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} bma253_accel_data_t;

void BMA253_DRV_Init(bma253_t* bma253, u8 bma253_dev_address, i2c_interface_t* i2c_interface);

s16 BMA253_DRV_Accel_Process_Raw_Data(u16 accel_data_u16, u8 range_u8);
s16 BMA253_DRV_Get_Accel_X(bma253_t* bma253);
s16 BMA253_DRV_Get_Accel_Y(bma253_t* bma253);
s16 BMA253_DRV_Get_Accel_Z(bma253_t* bma253);
void BMA253_DRV_Get_Accel_XYZ(bma253_t* bma253, bma253_accel_data_t* bma253_accel_data);
void BMA253_DRV_Get_Accel_XYZ_SameTimestamp(bma253_t* bma253, bma253_accel_data_t* bma253_accel_data);

#endif