#ifndef __W25Q_PAL_H
#define __W25Q_PAL_H

#include "hardware//w25q_interface.h"

typedef struct {
    w25q_t* w25q;
    uint16_t PageIndexPut;
    uint16_t PageIndexGet;
    uint16_t Count;
    uint16_t Size;
} w25q_queue_t;

extern w25q_queue_t flash;

// Initialize the W25Q queue
void PAL_W25Q_Queue_Init(w25q_queue_t* w25q_queue, w25q_t* w25q);

// Check if the W25Q queue is empty
bool PAL_W25Q_Queue_IsEmpty(const w25q_queue_t* w25q_queue);

// Check if the W25Q queue is full
bool PAL_W25Q_Queue_IsFull(const w25q_queue_t* w25q_queue);

// Enqueue data into the W25Q queue
void PAL_W25Q_Queue_Enqueue(w25q_queue_t* w25q_queue, const char* data, uint16_t data_size);

// Dequeue data from the W25Q queue
void PAL_W25Q_Queue_Dequeue(w25q_queue_t* w25q_queue, char* data, uint16_t data_size);

#endif