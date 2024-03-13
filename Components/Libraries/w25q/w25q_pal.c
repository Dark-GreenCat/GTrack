#include "w25q_pal.h"

w25q_queue_t flash;

void PAL_W25Q_Queue_Init(w25q_queue_t* w25q_queue, w25q_t* w25q) {
    w25q_queue->w25q = w25q;

    w25q_queue->PageIndexPut = 0;
    w25q_queue->PageIndexGet = 0;
    w25q_queue->Count = 0;
    w25q_queue->Size = W25Q_PAGES_PER_SECTOR * W25Q_SECTORS_PER_BLOCK * W25Q_BLOCKS_PER_CHIP;
}

bool PAL_W25Q_Queue_IsEmpty(const w25q_queue_t* w25q_queue) {
    return (w25q_queue->PageIndexPut == w25q_queue->PageIndexGet);
}

bool PAL_W25Q_Queue_IsFull(const w25q_queue_t* w25q_queue) {
    return ((w25q_queue->PageIndexPut + 1) % w25q_queue->Size == w25q_queue->PageIndexGet);
}

void PAL_W25Q_Queue_Enqueue(w25q_queue_t* w25q_queue, const char* data, uint16_t data_size) {
    // Check if the current page is the start of a sector
    if (w25q_queue->PageIndexPut % W25Q_PAGES_PER_SECTOR == 0) {
        // Erase the sector
        uint16_t sector_index;
        W25Q_ITF_EraseSector(w25q_queue->w25q, (uint16_t) (w25q_queue->PageIndexPut / W25Q_PAGES_PER_SECTOR));
    }

    // Write the data to the page
    W25Q_ITF_WritePage(w25q_queue->w25q, w25q_queue->PageIndexPut, 0, data_size, (uint8_t*) data);

    w25q_queue->PageIndexPut = (w25q_queue->PageIndexPut + 1) % w25q_queue->Size;
    w25q_queue->Count++;
}

void PAL_W25Q_Queue_Dequeue(w25q_queue_t* w25q_queue, char* data, uint16_t data_size) {
    if (PAL_W25Q_Queue_IsEmpty(w25q_queue)) {
        // Queue is empty, handle the error or return a default value
        data[0] = '\0';
        return;
    }

    // Read the data from the page
    W25Q_ITF_ReadPage(w25q_queue->w25q, w25q_queue->PageIndexGet, 0, data_size, (uint8_t*) data);

    w25q_queue->PageIndexGet = (w25q_queue->PageIndexGet + 1) % w25q_queue->Size;
    w25q_queue->Count--;
}