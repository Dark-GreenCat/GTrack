#include "bma253_hcl.h"

void HCL_BMA253_Init(bma253_t* bma253, void (*read)(uint8_t, uint8_t, uint8_t*, uint16_t), void (*write)(uint8_t, uint8_t, uint8_t*, uint16_t)) {
    uint8_t data_u8 = BMA2x2_INIT_VALUE;
    uint8_t config_data_u8 = BMA2x2_INIT_VALUE;
    
    /* Initialize BMA253 struct */
    bma253->__read = read;
    bma253->__write = write;

    /* Read ChipID */
    HCL_BMA253_Read_Reg(bma253, BMA2x2_CHIP_ID_REG, &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    bma253->chip_id = data_u8;

    /* Read Fifo Config Register */
    HCL_BMA253_Read_Reg(bma253, BMA2x2_FIFO_MODE_REG, &config_data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    bma253->fifo_config = config_data_u8;
}

void HCL_BMA253_Read_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    bma253->__read(bma253->dev_addr, reg_addr, p_data, read_length);
}

void HCL_BMA253_Write_Reg(bma253_t* bma253, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    bma253->__write(bma253->dev_addr, reg_addr, p_data, write_length);
}
