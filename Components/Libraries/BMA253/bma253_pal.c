#include "bma253_pal.h"

BMA253_TypeDef pal_bma253;

void PAL_BMA253_Init() {
    BMA253_DRV_Init(&pal_bma253, BMA253_I2C_ADDR1, &hi2c1);

    /* Make sure the accurate of accel data */
    BMA253_HWI_set_shadow_dis(&pal_bma253, !BMA253_ACCD_HBW_SHADOW_DIS_BITS_VAL);
    /* Filter accel data */
    BMA253_HWI_set_data_high_bw(&pal_bma253, !BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_VAL);
    /* Set data aquision bandwidth */
    BMA253_HWI_set_bw(&pal_bma253, BMA253_BW_7_81HZ);
    /* Set measurement range */
    BMA253_HWI_set_range(&pal_bma253, BMA253_RANGE_2G);

    /* Set FIFO to store current accel value */
    BMA253_HWI_set_fifo_mode(&pal_bma253, BMA253_FIFO_MODE_BYPASS);    
    /* Set Accel axis to be stored in FIFO */
    BMA253_HWI_set_fifo_data_select(&pal_bma253, BMA253_FIFO_XYZ_DATA_ENABLED);


    BMA253_HWI_set_slope_en(&pal_bma253, BMA253_SLOPE_X_INTR, BMA253_INTR_DISABLE);
    BMA253_HWI_set_slope_en(&pal_bma253, BMA253_SLOPE_Y_INTR, BMA253_INTR_DISABLE);
    BMA253_HWI_set_slope_en(&pal_bma253, BMA253_SLOPE_Z_INTR, BMA253_INTR_DISABLE);

    BMA253_HWI_set_latch_int(&pal_bma253, BMA253_LATCH_DURN_NON_LATCH);
    BMA253_HWI_set_source(&pal_bma253, BMA253_SOURCE_SLOPE, BMA253_INTR_ENABLE);
    BMA253_HWI_set_int_map(&pal_bma253, BMA253_INTR_PAD_SLOPE, BMA253_INTR1, BMA253_INTR_ENABLE);
    BMA253_HWI_set_intr_level(&pal_bma253, BMA253_INTR1_LEVEL, BMA253_ACTIVE_HIGH);
    BMA253_HWI_set_intr_output_type(&pal_bma253, BMA253_INTR1_OUTPUT, BMA253_PUSS_PULL);
    BMA253_HWI_set_slope_th(&pal_bma253, 0x03);
    BMA253_HWI_set_slope_dur(&pal_bma253, 0x03);

    BMA253_HWI_set_slope_en(&pal_bma253, BMA253_SLOPE_X_INTR, BMA253_INTR_ENABLE);
    BMA253_HWI_set_slope_en(&pal_bma253, BMA253_SLOPE_Y_INTR, BMA253_INTR_ENABLE);
    BMA253_HWI_set_slope_en(&pal_bma253, BMA253_SLOPE_Z_INTR, BMA253_INTR_ENABLE);
}

void PAL_BMA253_Get_Accel_XYZ(bma253_accel_data_t* bma253_accel_data) {
    BMA253_DRV_Get_Accel_XYZ_SameTimestamp(&pal_bma253, bma253_accel_data);
}
