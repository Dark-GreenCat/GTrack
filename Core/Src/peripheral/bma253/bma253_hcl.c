#include "bma253_hcl.h"

static bma253_t* p_bma253;

void HCL_BMA253_Init(bma253_t* bma253) {
    uint8_t data_u8 = BMA2x2_INIT_VALUE;
    uint8_t config_data_u8 = BMA2x2_INIT_VALUE;
    
    p_bma253 = bma253;
    /* Read ChipID */
    p_bma253->read(p_bma253->dev_addr, BMA2x2_CHIP_ID_REG, &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    p_bma253->chip_id = data_u8;

    /* Read Fifo Config Register */
    p_bma253->read(p_bma253->dev_addr, BMA2x2_FIFO_MODE_REG, &config_data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    p_bma253->fifo_config = config_data_u8;
}

void HCL_BMA253_Read_Reg(uint8_t reg_addr, uint8_t* data_u8, uint8_t len_u8) {
    p_bma253->read(p_bma253->dev_addr, reg_addr, data_u8, len_u8);
}

void HCL_BMA253_Write_Reg(uint8_t reg_addr, uint8_t* data_u8, uint8_t len_u8) {
    p_bma253->write(p_bma253->dev_addr, reg_addr, data_u8, len_u8);
}
