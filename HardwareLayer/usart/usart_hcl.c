#include "usart_hcl.h"

UART_HandleTypeDef* huart_terminal = &huart1;
UART_HandleTypeDef* huart_mc60 = &huart3;

static uint8_t Rx_data;

static uint8_t buffer_terminal[FIFO_TERMINAL_SIZE];
static uint8_t buffer_mc60[FIFO_MC60_SIZE];
static Fifo_t Fifo_terminal;
static Fifo_t Fifo_mc60;

static Fifo_t* HCL_UART_GetFifo(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_temp = NULL;
    if (huart == huart_terminal) Fifo_temp = &Fifo_terminal;
    if (huart == huart_mc60) Fifo_temp = &Fifo_mc60;

    return Fifo_temp;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart == huart_terminal) {
        Fifo_Put(&Fifo_terminal, Rx_data);
    }

    if (huart == huart_mc60) {
        Fifo_Put(&Fifo_mc60, Rx_data);
    }

    HAL_UART_Receive_IT(huart, &Rx_data, 1);
}


void HCL_UART_Init(UART_HandleTypeDef* huart) {
    if (huart == huart_terminal) Fifo_Init(&Fifo_terminal, buffer_terminal, FIFO_TERMINAL_SIZE);
    if (huart == huart_mc60) Fifo_Init(&Fifo_mc60, buffer_mc60, FIFO_MC60_SIZE);
}

void HCL_UART_StartReceive(UART_HandleTypeDef* huart) {
    HAL_UART_Receive_IT(huart, &Rx_data, 1);
}

char HCL_UART_InChar(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_temp = HCL_UART_GetFifo(huart);

    if (Fifo_isEmpty(Fifo_temp)) return -1;
    return Fifo_Get(Fifo_temp);
}

void HCL_UART_OutChar(UART_HandleTypeDef* huart, char data) {
    HAL_UART_Transmit(huart, (uint8_t*)&data, 1, 1);
}

void HCL_UART_FIFO_Flush(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_temp = HCL_UART_GetFifo(huart);

    uint8_t data;
    while (!Fifo_isEmpty(Fifo_temp)) {
        data = Fifo_Get(Fifo_temp);
        HCL_UART_OutChar(huart_terminal, data);
    }
}

bool HCL_UART_IsAvailable(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_temp = HCL_UART_GetFifo(huart);

    return !Fifo_isEmpty(Fifo_temp);
}


