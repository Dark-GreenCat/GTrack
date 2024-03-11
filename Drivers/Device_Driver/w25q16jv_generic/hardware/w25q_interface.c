#include "w25q_interface.h"

void W25Q_SetInstruction(uint8_t* destination, uint8_t cmd, uint32_t mem_addr) {
    destination[0] = cmd;
    destination[1] = (mem_addr >> 16) & 0xFF;
    destination[2] = (mem_addr >> 8) & 0xFF;
    destination[3] = (mem_addr) & 0xFF;
}


void W25Q_ITF_Init(w25q_t* w25q, spi_interface_t* spi_interface, gpio_interface_t* gpio_interface) {
    w25q->spi_interface = spi_interface;
    w25q->gpio_interface = gpio_interface;
}

void W25Q_ITF_Transmit(w25q_t* w25q, uint8_t* p_data, uint16_t size) {
    W25Q_CS_Select(w25q->gpio_interface, false);
    W25Q_SPI_Transmit(w25q->spi_interface, p_data, size);
    W25Q_CS_Select(w25q->gpio_interface, true);
}

void W25Q_ITF_Receive(w25q_t* w25q, uint8_t* p_data, uint16_t size) {
    W25Q_CS_Select(w25q->gpio_interface, false);
    W25Q_SPI_Receive(w25q->spi_interface, p_data, size);
    W25Q_CS_Select(w25q->gpio_interface, true);
}

void W25Q_ITF_TransmitReceive(w25q_t* w25q, uint8_t* tx_data, uint16_t tx_size, uint8_t* rx_data, uint16_t rx_size) {
    W25Q_CS_Select(w25q->gpio_interface, false);
    W25Q_SPI_Transmit(w25q->spi_interface, tx_data, tx_size);
    W25Q_SPI_Receive(w25q->spi_interface, rx_data, rx_size);
    W25Q_CS_Select(w25q->gpio_interface, true);
}

void W25Q_ITF_Reset(w25q_t* w25q) {
    uint8_t tx_data;
	
	tx_data = W25Q_COMMAND_ENABLE_RESET;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);

    tx_data = W25Q_COMMAND_RESET_DEVICE;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);

    W25Q_Delay(100);
}

void W25Q_ITF_EraseChip(w25q_t* w25q) {
    uint8_t tx_data[1] = { W25Q_COMMAND_CHIP_ERASE };

    W25Q_ITF_EnableWrite(w25q);
    W25Q_ITF_Transmit(w25q, tx_data, 1);
    W25Q_ITF_DisableWrite(w25q);

    // Should wait for 25s to completely erase
}

uint32_t W25Q_ITF_ReadID(w25q_t* w25q) {
    uint8_t tx_data = W25Q_COMMAND_JEDEC_ID;
    uint8_t rx_data[3];

    W25Q_CS_Select(w25q->gpio_interface, false);
    W25Q_SPI_Transmit(w25q->spi_interface, &tx_data, 1);
    W25Q_SPI_Receive(w25q->spi_interface, rx_data, 3);
    W25Q_CS_Select(w25q->gpio_interface, true);

    return PACK_24_BITS(rx_data[0], rx_data[1], rx_data[2]);
}

void W25Q_ITF_EnableWrite(w25q_t* w25q) {
    uint8_t tx_data = W25Q_COMMAND_WRITE_ENABLE;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);
    W25Q_Delay(5);
}

void W25Q_ITF_DisableWrite(w25q_t* w25q) {
    uint8_t tx_data = W25Q_COMMAND_WRITE_DISABLE;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);
    W25Q_Delay(5);   
}

void W25Q_ITF_ReadFn(w25q_t* w25q, uint32_t address, uint16_t rx_size, uint8_t* p_data) {
    uint8_t tx_data[4];
    W25Q_SetInstruction(tx_data, W25Q_COMMAND_READ_DATA, address);

    W25Q_ITF_TransmitReceive(w25q, tx_data, 4, p_data, rx_size);
}

void W25Q_ITF_WriteFn(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t write_size, uint8_t* p_data) {
    uint8_t tx_data[4];
    W25Q_SetInstruction(tx_data, W25Q_COMMAND_PAGE_PROGRAM, W25Q_PageToAddress(page_index) + address_offset);

    uint16_t max_size = W25Q_PAGE_SIZE - address_offset;
    if(write_size > max_size) write_size = max_size;

    W25Q_ITF_EnableWrite(w25q);
    W25Q_CS_Select(w25q->gpio_interface, false);
    W25Q_SPI_Transmit(w25q->spi_interface, tx_data, 4);
    W25Q_SPI_Transmit(w25q->spi_interface, p_data, write_size);
    W25Q_CS_Select(w25q->gpio_interface, true);
    W25Q_ITF_DisableWrite(w25q);
}

void W25Q_ITF_EraseSector(w25q_t* w25q, uint16_t sector_index) {
    uint8_t tx_data[4];
    uint32_t mem_addr = W25Q_SectorToAddress(sector_index);
    W25Q_SetInstruction(tx_data, W25Q_COMMAND_SECTOR_ERASE_4K, mem_addr);

    W25Q_ITF_EnableWrite(w25q);
    W25Q_ITF_Transmit(w25q, tx_data, 4);
    W25Q_Delay(450);
    W25Q_ITF_DisableWrite(w25q);
}

void W25Q_ITF_EraseBlock(w25q_t* w25q, uint16_t block_index) {
    uint8_t tx_data[4];
    uint32_t mem_addr = W25Q_BlockToAddress(block_index);
    W25Q_SetInstruction(tx_data, W25Q_COMMAND_BLOCK_ERASE_64K, mem_addr);

    W25Q_ITF_EnableWrite(w25q);
    W25Q_ITF_Transmit(w25q, tx_data, 4);
    W25Q_Delay(2100);
    W25Q_ITF_DisableWrite(w25q);
}

void W25Q_ITF_WriteAddress(w25q_t* w25q, uint32_t address, uint16_t size, uint8_t* p_data) {
    uint16_t tx_length = 0;
    do {
        uint16_t page_index = W25Q_AddressToPage(address);
        uint8_t address_offset = address % W25Q_PAGE_SIZE;
        uint16_t max_size = W25Q_PAGE_SIZE - address_offset;

        if (size < max_size) tx_length = size;
        else tx_length = max_size;

        W25Q_ITF_WriteFn(w25q, page_index, address_offset, tx_length, p_data);

        address += tx_length;
        p_data += tx_length;
        size -= tx_length;
    } while (size > 0);
}

void W25Q_ITF_WritePage(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t size, uint8_t* p_data) {
    W25Q_ITF_WriteFn(w25q, page_index, address_offset, size, p_data);
}

void W25Q_ITF_WriteSector(w25q_t* w25q, uint16_t sector_index, uint32_t address_offset, uint16_t size, uint8_t* p_data) {
    uint32_t address = W25Q_SectorToAddress(sector_index) + address_offset;
    W25Q_ITF_WriteAddress(w25q, address, size, p_data);
}

void W25Q_ITF_WriteBlock(w25q_t* w25q, uint16_t block_index, uint32_t address_offset, uint16_t size, uint8_t* p_data) {
    uint32_t address = W25Q_BlockToAddress(block_index) + address_offset;
    W25Q_ITF_WriteAddress(w25q, address, size, p_data);
}

void W25Q_ITF_ReadAddress(w25q_t* w25q, uint32_t address, uint16_t size, uint8_t* p_data) {
    W25Q_ITF_ReadFn(w25q, address, size, p_data);
}

void W25Q_ITF_ReadPage(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t size, uint8_t* p_data) {
    uint32_t address = W25Q_PageToAddress(page_index) + address_offset;
    W25Q_ITF_ReadFn(w25q, address, size, p_data);
}

void W25Q_ITF_ReadSector(w25q_t* w25q, uint16_t sector_index, uint32_t address_offset, uint16_t size, uint8_t* p_data) {
    uint32_t address = W25Q_SectorToAddress(sector_index) + address_offset;
    W25Q_ITF_ReadFn(w25q, address, size, p_data);
}

void W25Q_ITF_ReadBlock(w25q_t* w25q, uint16_t block_index, uint32_t address_offset, uint16_t size, uint8_t* p_data) {
    uint32_t address = W25Q_BlockToAddress(block_index) + address_offset;
    W25Q_ITF_ReadFn(w25q, address, size, p_data);
}
