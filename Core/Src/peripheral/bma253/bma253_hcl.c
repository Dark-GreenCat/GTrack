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
    HCL_BMA253_Read_Reg(bma253, BMA253_FIFO_CONFIG_1_REG, &config_data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    bma253->fifo_config = config_data_u8;
}

void HCL_BMA253_Read_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    bma253->__read(bma253->hi2c, bma253->dev_addr, reg_addr, p_data, read_length);
}

void HCL_BMA253_Write_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    bma253->__write(bma253->hi2c, bma253->dev_addr, reg_addr, p_data, write_length);
}

uint8_t HCL_BMA253_get_shadow_dis(bma253_t* bma253) {
    uint8_t data_u8;

    HCL_BMA253_Read_Reg(bma253, BMA253_ACCD_HBW_SHADOW_DIS_BITS_REG, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    data_u8 = BMA253_GET_BITSLICE(data_u8, BMA253_ACCD_HBW_SHADOW_DIS_BITS);
    
    return data_u8;
}

void HCL_BMA253_set_shadow_dis(bma253_t* bma253, uint8_t shadow_dis_u8) {
    uint8_t data_u8 = BMA253_INIT_VALUE;
    
    HCL_BMA253_Read_Reg(bma253, BMA253_ACCD_HBW_SHADOW_DIS_BITS_REG, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
    data_u8 = BMA253_SET_BITSLICE(data_u8, BMA253_ACCD_HBW_SHADOW_DIS_BITS, shadow_dis_u8);
    HCL_BMA253_Write_Reg(bma253, BMA253_ACCD_HBW_SHADOW_DIS_BITS_REG, &data_u8, BMA253_GEN_READ_WRITE_LENGTH);
}


