#include "usart_hcl.h"

UART_HandleTypeDef* huart_terminal = &huart1;
UART_HandleTypeDef* huart_mc60 = &huart3;

static uint8_t Rx_data;
static Fifo_t Fifo_1;
static Fifo_t Fifo_3;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart == huart_terminal) {
        Fifo_Put(&Fifo_1, Rx_data);
    }

    if (huart == huart_mc60) {
        Fifo_Put(&Fifo_3, Rx_data);
    }

    HAL_UART_Receive_IT(huart, &Rx_data, 1);
}


void HCL_UART_Init(UART_HandleTypeDef* huart, uint32_t size) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    Fifo_Init(Fifo_n, size);
}

void HCL_UART_StartReceive(UART_HandleTypeDef* huart) {
    HAL_UART_Receive_IT(huart, &Rx_data, 1);
}

char HCL_UART_InChar(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    if (Fifo_isEmpty(Fifo_n)) return -1;
    return Fifo_Get(Fifo_n);
}

void HCL_UART_OutChar(UART_HandleTypeDef* huart, char data) {
    HAL_UART_Transmit(huart, (uint8_t*)&data, 1, 1);
}

void HCL_UART_FIFO_Flush(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    uint8_t data;
    while (!Fifo_isEmpty(Fifo_n)) {
        data = Fifo_Get(Fifo_n);
        HCL_UART_OutChar(huart_terminal, data);
    }
}

bool HCL_UART_IsAvailable(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    return !Fifo_isEmpty(Fifo_n);
}


