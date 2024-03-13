#ifndef __SPI_HCL_H
#define __SPI_HCL_H

#include "spi.h"

#define SPI_TIMEOUT 500

static inline void HCL_SPI_Transmit(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size) {
    HAL_SPI_Transmit(hspi, pData, Size, SPI_TIMEOUT);
}

static inline void HCL_SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size) {
    HAL_SPI_Receive(hspi, pData, Size, SPI_TIMEOUT);
}

#endif