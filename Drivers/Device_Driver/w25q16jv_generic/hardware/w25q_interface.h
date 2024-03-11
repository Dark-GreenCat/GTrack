#ifndef __W25QXX_INTERFACE_H
#define __W25QXX_INTERFACE_H

#include "w25q_def.h"
#include "../mcu_interface/w25q_mcu_spi_interface.h"

#include <stdint.h>

/************************************************************************************************************
**************    Public Definitions
************************************************************************************************************/

#define W25Q_PageToSector(PageNumber)      ((PageNumber) / W25Q_PAGES_PER_SECTOR)
#define W25Q_PageToBlock(PageNumber)       ((PageNumber) / (W25Q_PAGES_PER_SECTOR * W25Q_SECTORS_PER_BLOCK))
#define W25Q_SectorToBlock(SectorNumber)   ((SectorNumber) / W25Q_SECTORS_PER_BLOCK)
#define W25Q_SectorToPage(SectorNumber)    ((SectorNumber) * W25Q_PAGES_PER_SECTOR)
#define W25Q_BlockToPage(BlockNumber)      ((BlockNumber) * (W25Q_PAGES_PER_SECTOR * W25Q_SECTORS_PER_BLOCK))
#define W25Q_PageToAddress(PageNumber)     ((PageNumber) * W25Q_PAGE_SIZE)
#define W25Q_SectorToAddress(SectorNumber) ((SectorNumber) * (W25Q_PAGES_PER_SECTOR * W25Q_PAGE_SIZE))
#define W25Q_BlockToAddress(BlockNumber)   ((BlockNumber) * (W25Q_SECTORS_PER_BLOCK * W25Q_PAGES_PER_SECTOR * W25Q_PAGE_SIZE))
#define W25Q_AddressToPage(Address)        ((Address) / W25Q_PAGE_SIZE)
#define W25Q_AddressToSector(Address)      ((Address) / (W25Q_PAGES_PER_SECTOR * W25Q_PAGE_SIZE))
#define W25Q_AddressToBlock(Address)       ((Address) / (W25Q_SECTORS_PER_BLOCK * W25Q_PAGES_PER_SECTOR * W25Q_PAGE_SIZE))

#define PACK_24_BITS(b1, b2, b3) (((uint32_t)(b1) << 16) | ((uint32_t)(b2) << 8) | (uint32_t)(b3))

/************************************************************************************************************
**************    Public struct/enum
************************************************************************************************************/

typedef struct {
    spi_interface_t* spi_interface;
    gpio_interface_t* gpio_interface;
} w25q_t;

/************************************************************************************************************
**************    Private Functions
************************************************************************************************************/

void W25Q_SetInstruction(uint8_t* destination, uint8_t cmd, uint32_t mem_addr);

void W25Q_ITF_Transmit(w25q_t* w25q, uint8_t* p_data, uint16_t size);
void W25Q_ITF_Receive(w25q_t* w25q, uint8_t* p_data, uint16_t size);
void W25Q_ITF_TransmitReceive(w25q_t* w25q, uint8_t* tx_data, uint16_t tx_size, uint8_t* rx_data, uint16_t rx_size);

void W25Q_ITF_EnableWrite(w25q_t* w25q);
void W25Q_ITF_DisableWrite(w25q_t* w25q);

void W25Q_ITF_ReadFn(w25q_t* w25q, uint32_t address, uint16_t rx_size, uint8_t* p_data);
void W25Q_ITF_WriteFn(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t write_size, uint8_t* p_data);

/************************************************************************************************************
**************    Public Functions
************************************************************************************************************/

void W25Q_ITF_Init(w25q_t* w25q, spi_interface_t* spi_interface, gpio_interface_t* gpio_interface);
void W25Q_ITF_Reset(w25q_t* w25q);

void W25Q_ITF_EraseChip(w25q_t* w25q);
void W25Q_ITF_EraseSector(w25q_t* w25q, uint16_t sector_index);
void W25Q_ITF_EraseBlock(w25q_t* w25q, uint16_t block_index);

void W25Q_ITF_WriteAddress(w25q_t* w25q, uint32_t address, uint16_t size, uint8_t* p_data);
void W25Q_ITF_WritePage(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t size, uint8_t* p_data);
void W25Q_ITF_WriteSector(w25q_t* w25q, uint16_t sector_index, uint32_t address_offset, uint16_t size, uint8_t* p_data);
void W25Q_ITF_WriteBlock(w25q_t* w25q, uint16_t block_index, uint32_t address_offset, uint16_t size, uint8_t* p_data);

void W25Q_ITF_ReadAddress(w25q_t* w25q, uint32_t address, uint16_t size, uint8_t* p_data);
void W25Q_ITF_ReadPage(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t size, uint8_t* p_data);
void W25Q_ITF_ReadSector(w25q_t* w25q, uint16_t sector_index, uint32_t address_offset, uint16_t size, uint8_t* p_data);
void W25Q_ITF_ReadBlock(w25q_t* w25q, uint16_t block_index, uint32_t address_offset, uint16_t size, uint8_t* p_data);

uint32_t W25Q_ITF_ReadID(w25q_t* w25q);

#endif