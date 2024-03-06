#ifndef __W25QXX_INTERFACE_H
#define __W25QXX_INTERFACE_H

#include "w25qxx_def.h"
#include "../mcu_interface/w25qxx_mcu_spi_interface.h"

#include <stdint.h>

#define PACK_24_BITS(b1, b2, b3) (((uint32_t)(b1) << 16) | ((uint32_t)(b2) << 8) | (uint32_t)(b3))

typedef struct {
    spi_interface_t* spi_interface;
    gpio_interface_t* gpio_interface;
} w25q_t;

void W25Q_SetInstruction(uint8_t* destination, uint8_t cmd, uint32_t mem_addr);

void W25Q_ITF_Init(w25q_t* w25q, spi_interface_t* spi_interface, gpio_interface_t* gpio_interface);
void W25Q_ITF_Transmit(w25q_t* w25q, uint8_t* p_data, uint16_t size);
void W25Q_ITF_Receive(w25q_t* w25q, uint8_t* p_data, uint16_t size);

void W25Q_ITF_Reset(w25q_t* w25q);
uint32_t W25Q_ITF_ReadID(w25q_t* w25q);

/**
 * Read data from the W25Q flash memory.
 *
 * @param w25q               Pointer to the W25Q flash memory structure.
 * @param page_index        The page number to start reading from (0 to (W25QXX_BLOCKS_PER_CHIP * 256) - 1).
 * @param address_offset     The offset within the start page (0 to 255).
 * @param read_size          The amount of data to read (in bytes).
 * @param p_data             Pointer to the array where the received data will be stored.
 */
void W25Q_ITF_Read(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t read_size, uint8_t* p_data);

void W25Q_ITF_EnableWrite(w25q_t* w25q);
void W25Q_ITF_DisableWrite(w25q_t* w25q);
void W25Q_ITF_EraseSector(w25q_t* w25q, uint16_t sector_index);

/**
 * Write data to a page in the W25Q flash memory.
 *
 * @param w25q              Pointer to the W25Q flash memory structure.
 * @param page_index       The page number to write  (0 to (W25QXX_BLOCKS_PER_CHIP * 256) - 1).
 * @param address_offset    The offset within the page to start writing at (0 to 255).
 * @param write_size        The size of the data to be written (in bytes).
 * @param p_data            Pointer to the data to be written.
 */
void W25Q_ITF_WritePage(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t write_size, uint8_t* p_data);

#endif