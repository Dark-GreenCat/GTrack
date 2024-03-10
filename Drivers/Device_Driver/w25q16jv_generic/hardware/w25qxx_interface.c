#include "w25qxx_interface.h"

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
    W25Q_CS_SetLow(w25q->gpio_interface);
    W25Q_SPI_Transmit(w25q->spi_interface, p_data, size);
    W25Q_CS_SetHigh(w25q->gpio_interface);
}

void W25Q_ITF_Receive(w25q_t* w25q, uint8_t* p_data, uint16_t size) {
    W25Q_CS_SetLow(w25q->gpio_interface);
    W25Q_SPI_Receive(w25q->spi_interface, p_data, size);
    W25Q_CS_SetHigh(w25q->gpio_interface);
}

void W25Q_ITF_Reset(w25q_t* w25q) {
    uint8_t tx_data;
	
	tx_data = W25QXX_COMMAND_ENABLE_RESET;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);

    tx_data = W25QXX_COMMAND_RESET_DEVICE;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);

    W25Q_Delay(100);
}

uint32_t W25Q_ITF_ReadID(w25q_t* w25q) {
    uint8_t tx_data = W25QXX_COMMAND_JEDEC_ID;
    uint8_t rx_data[3];

    W25Q_CS_SetLow(w25q->gpio_interface);
    W25Q_SPI_Transmit(w25q->spi_interface, &tx_data, 1);
    W25Q_SPI_Receive(w25q->spi_interface, rx_data, 3);
    W25Q_CS_SetHigh(w25q->gpio_interface);

    return PACK_24_BITS(rx_data[0], rx_data[1], rx_data[2]);
}

void W25Q_ITF_Read(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t read_size, uint8_t* p_data) {
    uint8_t tx_data[4];
    uint32_t mem_addr = (page_index * W25QXX_PAGE_SIZE) + address_offset;
    W25Q_SetInstruction(tx_data, W25QXX_COMMAND_READ_DATA, mem_addr);

    W25Q_CS_SetLow(w25q->gpio_interface);
    W25Q_SPI_Transmit(w25q->spi_interface, tx_data, 4);
    W25Q_SPI_Receive(w25q->spi_interface, p_data, read_size);
    W25Q_CS_SetHigh(w25q->gpio_interface);
}

void W25Q_ITF_EnableWrite(w25q_t* w25q) {
    uint8_t tx_data = W25QXX_COMMAND_WRITE_ENABLE;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);
    W25Q_Delay(5);
}

void W25Q_ITF_DisableWrite(w25q_t* w25q) {
    uint8_t tx_data = W25QXX_COMMAND_WRITE_DISABLE;
    W25Q_ITF_Transmit(w25q, &tx_data, 1);
    W25Q_Delay(5);   
}

void W25Q_ITF_EraseSector(w25q_t* w25q, uint16_t sector_index) {
    uint8_t tx_data[4];
    uint32_t mem_addr = sector_index * W25QXX_PAGES_PER_SECTOR * W25QXX_PAGE_SIZE;
    W25Q_SetInstruction(tx_data, W25QXX_COMMAND_SECTOR_ERASE_4K, mem_addr);

    W25Q_ITF_EnableWrite(w25q);
    W25Q_ITF_Transmit(w25q, tx_data, 4);
    W25Q_Delay(450);
    W25Q_ITF_DisableWrite(w25q);
}

void W25Q_ITF_WritePage(w25q_t* w25q, uint16_t page_index, uint8_t address_offset, uint16_t write_size, uint8_t* p_data) {
    uint16_t page_start = page_index,
             page_end = page_index + (address_offset + write_size - 1) / W25QXX_PAGE_SIZE;
    
    uint16_t sector_start = page_start / W25QXX_PAGES_PER_SECTOR,
             sector_end = page_end / W25QXX_PAGES_PER_SECTOR;
    
    for (uint8_t sector_index = sector_start; sector_index <= sector_end; sector_index++) 
        W25Q_ITF_EraseSector(w25q, sector_index);

    for (uint16_t page_number = page_start; page_number <= page_end; page_number++) {
        uint8_t tx_data[4];
        uint32_t mem_addr;

        uint16_t bytes_send = 0;
        
        if (page_number == page_start) {
            mem_addr = (page_number * W25QXX_PAGE_SIZE) + address_offset;

            if (address_offset + write_size > 256) {
                bytes_send = 256 - address_offset;
            }
            else {
                bytes_send = write_size;
            }
        }
        else {
            mem_addr = page_number * W25QXX_PAGE_SIZE;

            if (write_size > 256) {
                bytes_send = 256;
            }
            else {
                bytes_send = write_size;
            }
        }

        W25Q_SetInstruction(tx_data, W25QXX_COMMAND_PAGE_PROGRAM, mem_addr);
        W25Q_ITF_EnableWrite(w25q);
        W25Q_CS_SetLow(w25q->gpio_interface);
        W25Q_SPI_Transmit(w25q->spi_interface, tx_data, 4);
        W25Q_SPI_Transmit(w25q->spi_interface, p_data, bytes_send);
        W25Q_CS_SetHigh(w25q->gpio_interface);
        W25Q_Delay(5);
        W25Q_ITF_DisableWrite(w25q);

        p_data += bytes_send;
    }
}