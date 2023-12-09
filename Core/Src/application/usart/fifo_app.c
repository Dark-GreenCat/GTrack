// FiFo.c
// Runs on STM32F103C8T6
// Provide functions that implement the Software FiFo Buffer
// Last Modified: 1/2/2023
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
#include "fifo_app.h"

// *********** FiFo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
void Fifo_Init(Fifo_t* Fifo, uint32_t size) {
  Fifo->PutI = Fifo->GetI = 0;  // empty
  Fifo->Size = size;
}

// *********** FiFo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint8_t Fifo_Put(Fifo_t* Fifo, char data) {
  if (Fifo_isFull(Fifo)) return 0; // fail if full
  Fifo->Fifo[Fifo->PutI] = data;         // save in Fifo
  Fifo->PutI = (Fifo->PutI + 1) % Fifo->Size; // next place to put
  return 1;
}

// *********** Fifo_Get**********
// Gets an element from the FIFO
// Input: none
// Output: If the FIFO is empty return 0
//         If the FIFO has data, remove it, and return it
uint8_t Fifo_Get(Fifo_t* Fifo) {
  if (Fifo_isEmpty(Fifo)) return 0; // fail if empty
  uint32_t dataIndex = Fifo->GetI;
  Fifo->GetI = (Fifo->GetI + 1) % Fifo->Size; // next place to get
  return Fifo->Fifo[dataIndex];
}

uint8_t Fifo_isEmpty(Fifo_t* Fifo) {
  return (Fifo->PutI == Fifo->GetI);
}

uint8_t Fifo_isFull(Fifo_t* Fifo) {
  return (((Fifo->PutI + 1) % Fifo->Size) == Fifo->GetI);
}