#ifndef __FIFO_HCL_H
#define __FIFO_HCL_H


// FiFo.h
// Runs on STM32F103C8T6
// Provide functions that implement the Software FiFo Buffer
// Last Modified: 1/2/2023
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
#include <stdint.h>

#define FIFO_SIZE_MAX 512

// Declare state variables for FiFo
//        size, buffer, put and get indexes
typedef struct {
    uint32_t PutI;  // index to put new
    uint32_t GetI;  // index of oldest
    uint32_t Size;
    uint8_t* Fifo;
} Fifo_t;

void Fifo_Init(Fifo_t* Fifo, uint8_t* allocated_buffer, uint32_t buffer_size);
uint8_t Fifo_Put(Fifo_t* Fifo, char data);
uint8_t Fifo_Get(Fifo_t* Fifo);

uint8_t Fifo_isEmpty(Fifo_t* Fifo);
uint8_t Fifo_isFull(Fifo_t* Fifo);

#endif