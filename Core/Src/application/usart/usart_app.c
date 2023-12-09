#include "usart_app.h"

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
        // APP_UART_OutChar(huart, Rx_data);
    if(huart == huart_terminal) {
        HAL_ResumeTick();
        APP_SIGNAL_LED_SetState(1);
        APP_SIGNAL_PWR_SetState(1);
    }
    }

    if (huart == huart_mc60) {
        Fifo_Put(&Fifo_3, Rx_data);
        __HAL_TIM_SetCounter(&htim3, 0);
    }

    HAL_UART_Receive_IT(huart, &Rx_data, 1);
}


void APP_UART_Init(UART_HandleTypeDef* huart, uint32_t size) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    Fifo_Init(Fifo_n, size);
}

void APP_UART_StartReceive(UART_HandleTypeDef* huart) {
    HAL_UART_Receive_IT(huart, &Rx_data, 1);
}

char APP_UART_InChar(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    while (Fifo_isEmpty(Fifo_n));
    return Fifo_Get(Fifo_n);
}

void APP_UART_readStringUtil(UART_HandleTypeDef* huart, char terminatedChar, char* destination) {
    char data = APP_UART_InChar(huart);
    while (data != terminatedChar) {
        *destination++ = data;
        data = APP_UART_InChar(huart);
    }

    *destination = '\0';
}

 
void APP_UART_OutChar(UART_HandleTypeDef* huart, char data) {
    HAL_UART_Transmit(huart, (uint8_t*)&data, 1, 1);
}

void APP_UART_OutString(UART_HandleTypeDef* huart, const char* str) {
    while (*str != '\0')
        APP_UART_OutChar(huart, (uint8_t)*str++);
}

void APP_UART_OutNumber(UART_HandleTypeDef* huart, uint32_t number) {
    if(number == 0) APP_UART_OutChar(huart, '0');

    while (number != 0) {
        uint8_t last_digit = number % 10;
        number /= 10;

        APP_UART_OutChar(huart, last_digit + '0');
    }
}

void APP_UART_FIFO_Flush(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    uint8_t data;
    while (!Fifo_isEmpty(Fifo_n)) {
        data = Fifo_Get(Fifo_n);
        APP_UART_OutChar(huart_terminal, data);
    }
}
void APP_UART_FlushToUART_Char(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive) {
    if (!APP_UART_FIFO_isEmpty(huart_transmit)) {
        char data = APP_UART_InChar(huart_transmit);
        APP_UART_OutChar(huart_receive, data);
    }
}

void APP_UART_FlushToUART_String(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive) {
    while (!APP_UART_FIFO_isEmpty(huart_transmit)) {
        APP_UART_FlushToUART_Char(huart_transmit, huart_receive);
    }
}

bool APP_UART_FIFO_isEmpty(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    return Fifo_isEmpty(Fifo_n);
}


