#include "bma253_pcl.h"

void __PCL_BMA253_Read_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HCL_I2C_Mem_Read(hi2c, 
                dev_addr << PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, PCL_BMA253_REG_SIZE, 
                p_data, 
                read_length, 
                PCL_BMA253_TIMEOUT);
}

void __PCL_BMA253_Write_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_I2C_Mem_Write(hi2c, 
                dev_addr << PCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, PCL_BMA253_REG_SIZE, 
                p_data, 
                write_length, 
                PCL_BMA253_TIMEOUT);
}

void PCL_BMA253_Init(BMA253_TypeDef* pcl_bma253, I2C_HandleTypeDef* hi2c) {
    pcl_bma253->hi2c = hi2c;
    pcl_bma253->dev_addr = BMA253_I2C_ADDR1;

    HCL_BMA253_Init(pcl_bma253, __PCL_BMA253_Read_Reg, __PCL_BMA253_Write_Reg);

    /* Make sure the accurate of accel data */
    HCL_BMA253_set_shadow_dis(pcl_bma253, !BMA253_ACCD_HBW_SHADOW_DIS_BITS_VAL);
    /* Filter accel data */
    HCL_BMA253_set_data_high_bw(pcl_bma253, !BMA253_ACCD_HBW_DATA_HIGH_BW_BITS_VAL);
    /* Set data aquision bandwidth */
    HCL_BMA253_set_bw(pcl_bma253, BMA253_PMU_BW_BW_BITS_7_81HZ);
    /* Set measurement range */
    HCL_BMA253_set_range(pcl_bma253, BMA253_PMU_RANGE_RANGE_2G);

    /* Set FIFO to store current accel value */
    HCL_BMA253_set_fifo_mode(pcl_bma253, BMA253_FIFO_CONFIG_1_FIFO_MODE_BYPASS);    
    /* Set Accel axis to be stored in FIFO */
    HCL_BMA253_set_fifo_data_select(pcl_bma253, BMA253_FIFO_CONFIG_1_FIFO_DATA_SELECT_XYZ);
}

void PCL_BMA253_Mem_Read(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HCL_BMA253_Read_Reg(pcl_bma253, reg_addr, p_data, read_length);
}

void PCL_BMA253_Mem_Write(BMA253_TypeDef* pcl_bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_BMA253_Write_Reg(pcl_bma253, reg_addr, p_data, write_length);
}



int16_t PCL_BMA253_Accel_Process_Raw_Data(uint16_t accel_data_u16, uint8_t range_u8) {
    int16_t accel_value = accel_data_u16;
    accel_value >>= BMA253_SHIFT_FOUR_BITS;
    
    float multiplier = 0;
    switch (range_u8)
    {
    case BMA253_PMU_RANGE_RANGE_2G:
        multiplier = 0.98;
        break;

    case BMA253_PMU_RANGE_RANGE_4G:
        multiplier = 1.95;
        break;

    case BMA253_PMU_RANGE_RANGE_8G:
        multiplier = 3.91;
        break;

    case BMA253_PMU_RANGE_RANGE_16G:
        multiplier = 7.81;
        break;
    
    default:
        break;
    }

    accel_value *= multiplier;
    return accel_value;
}

int16_t PCL_BMA253_Get_Accel_X(BMA253_TypeDef* pcl_bma253) {
    uint16_t data_u16 = HCL_BMA253_get_accd_x_msb_lsb(pcl_bma253);
    uint8_t range_u8 = HCL_BMA253_get_range(pcl_bma253);
    return PCL_BMA253_Accel_Process_Raw_Data(data_u16, range_u8);
}

int16_t PCL_BMA253_Get_Accel_Y(BMA253_TypeDef* pcl_bma253) {
    uint16_t data_u16 = HCL_BMA253_get_accd_y_msb_lsb(pcl_bma253);
    uint8_t range_u8 = HCL_BMA253_get_range(pcl_bma253);
    return PCL_BMA253_Accel_Process_Raw_Data(data_u16, range_u8);
}

int16_t PCL_BMA253_Get_Accel_Z(BMA253_TypeDef* pcl_bma253) {
    uint16_t data_u16 = HCL_BMA253_get_accd_z_msb_lsb(pcl_bma253);
    uint8_t range_u8 = HCL_BMA253_get_range(pcl_bma253);
    return PCL_BMA253_Accel_Process_Raw_Data(data_u16, range_u8);
}

void PCL_BMA253_Get_Accel_XYZ(BMA253_TypeDef* pcl_bma253, BMA253_Accel_Data_t* pcl_bma253_accel_data) {
    pcl_bma253_accel_data->x = PCL_BMA253_Get_Accel_X(pcl_bma253);
    pcl_bma253_accel_data->y = PCL_BMA253_Get_Accel_Y(pcl_bma253);
    pcl_bma253_accel_data->z = PCL_BMA253_Get_Accel_Z(pcl_bma253);
}

void PCL_BMA253_Get_Accel_XYZ_FIFO(BMA253_TypeDef* pcl_bma253, BMA253_Accel_Data_t* pcl_bma253_accel_data) {
    uint16_t fifo_data_readout_u16[] = {
        BMA253_INIT_VALUE, BMA253_INIT_VALUE, BMA253_INIT_VALUE
    };
    uint8_t range_u8 = BMA253_INIT_VALUE;
    uint8_t fifo_data_select_u8 = BMA253_INIT_VALUE;

    HCL_BMA253_get_fifo_data_1frame(pcl_bma253, (uint8_t*) fifo_data_readout_u16);
    range_u8 = HCL_BMA253_get_range(pcl_bma253);
    fifo_data_select_u8 = HCL_BMA253_get_fifo_data_select(pcl_bma253);

    pcl_bma253_accel_data->x = pcl_bma253_accel_data->y = pcl_bma253_accel_data->z = BMA253_INIT_VALUE;
    switch (fifo_data_select_u8)
    {
    case BMA253_FIFO_XYZ_DATA_ENABLED:
        pcl_bma253_accel_data->x = PCL_BMA253_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        pcl_bma253_accel_data->y = PCL_BMA253_Accel_Process_Raw_Data(fifo_data_readout_u16[1], range_u8);
        pcl_bma253_accel_data->z = PCL_BMA253_Accel_Process_Raw_Data(fifo_data_readout_u16[2], range_u8);
        break;
    
    case BMA253_FIFO_X_DATA_ENABLED:
        pcl_bma253_accel_data->x = PCL_BMA253_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        break;
    
    case BMA253_FIFO_Y_DATA_ENABLED:
        pcl_bma253_accel_data->y = PCL_BMA253_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        break;
    
    case BMA253_FIFO_Z_DATA_ENABLED:
        pcl_bma253_accel_data->z = PCL_BMA253_Accel_Process_Raw_Data(fifo_data_readout_u16[0], range_u8);
        break;
    
    default:
        break;
    }
}
