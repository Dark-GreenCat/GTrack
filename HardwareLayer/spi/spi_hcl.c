#include "spi_hcl.h"

void HCL_SPI_Transmit(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size) {
    HAL_SPI_Transmit(hspi, pData, Size, SPI_TIMEOUT);
}

void HCL_SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size) {
    HAL_SPI_Receive(hspi, pData, Size, SPI_TIMEOUT);
}
