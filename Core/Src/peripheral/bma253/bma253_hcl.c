#include "bma253_hcl.h"

static bma253_t* p_bma253;

void HCL_BMA253_Init(bma253_t* bma253) {
    bma253->read = HCL_BMA253_Read_Reg;
    bma253->write = HCL_BMA253_Write_Reg;
    // uint8_t data_u8 = BMA2x2_INIT_VALUE;
    // uint8_t config_data_u8 = BMA2x2_INIT_VALUE;
    
    // /* Backup the global value */
    // bma253_t* p_bma253_current = p_bma253;

    // p_bma253 = bma253;
    // /* Read ChipID */
    // p_bma253->read(p_bma253->dev_addr, BMA2x2_CHIP_ID_REG, &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    // p_bma253->chip_id = data_u8;

    // /* Read Fifo Config Register */
    // p_bma253->read(p_bma253->dev_addr, BMA2x2_FIFO_MODE_REG, &config_data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    // p_bma253->fifo_config = config_data_u8;

    // /* Reassign the global value */
    // p_bma253 = p_bma253_current;
}

void HCL_BMA253_Read_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
    HCL_I2C_Mem_Read(hi2c, 
                dev_addr << HCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, HCL_BMA253_REG_SIZE, 
                p_data, 
                read_length, 
                HCL_BMA253_TIMEOUT);
}

void HCL_BMA253_Write_Reg(I2C_HandleTypeDef* hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_I2C_Mem_Write(hi2c, 
                dev_addr << HCL_BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, HCL_BMA253_REG_SIZE, 
                p_data, 
                write_length, 
                HCL_BMA253_TIMEOUT);
}
