#ifndef __SPI_HCL_H
#define __SPI_HCL_H

#include "spi.h"

#define SPI_TIMEOUT 500

void HCL_SPI_Transmit(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size);
void HCL_SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size);

#endif