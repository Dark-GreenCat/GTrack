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
    }

    if (huart == huart_mc60) {
        Fifo_Put(&Fifo_3, Rx_data);
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

    if (Fifo_isEmpty(Fifo_n)) return -1;
    return Fifo_Get(Fifo_n);
}

bool APP_UART_ReadStringUntil(UART_HandleTypeDef *huart, char terminatedChar, char *destination) {
    static bool isFirstInit = true;
    static char* p_Destination = NULL;
    
    if(isFirstInit) p_Destination = destination;
    isFirstInit = false;
    bool isDone = false;
    if (APP_UART_IsAvailable(huart)) {
      char data = APP_UART_InChar(huart);
      while (data != terminatedChar) {
        *p_Destination++ = data;
        if (!APP_UART_IsAvailable(huart)) break;
        data = APP_UART_InChar(huart);
      }
      if(data == terminatedChar) isDone = true;
      if (isDone) {
        *p_Destination = '\0';
        p_Destination = destination;
      }
    }

    return isDone;
}

void APP_UART_OutChar(UART_HandleTypeDef* huart, char data) {
    HAL_UART_Transmit(huart, (uint8_t*)&data, 1, 1);
}

void APP_UART_OutString(UART_HandleTypeDef* huart, const char* str) {
    while (*str != '\0')
        APP_UART_OutChar(huart, (uint8_t)*str++);
}

void APP_UART_OutNumber(UART_HandleTypeDef* huart, uint32_t number) {
    if(number == 0) {
        APP_UART_OutChar(huart, '0');
        return;
    }

	char number_str[10];
	uint8_t index = 0;
    while (number != 0) {
        number_str[index++] = number % 10 + '0';
        number /= 10;
    }

    while(index--) APP_UART_OutChar(huart, number_str[index]);
}

void APP_UART_OutNumber_Signed(UART_HandleTypeDef* huart, int32_t number) {
    if(number == 0) {
		APP_UART_OutChar(huart, '0');
		return;
	}

    bool isSigned = (number < 0);
	if(isSigned) number = -number;

	char number_str[10];
	uint8_t index = 0;
    while (number != 0) {
        number_str[index++] = number % 10 + '0';
        number /= 10;
    }
	
    if(isSigned) APP_UART_OutChar(huart, '-');
	while(index--) APP_UART_OutChar(huart, number_str[index]);
}

void APP_UART_OutBinary_8BIT(UART_HandleTypeDef* huart, uint8_t data) {
    uint8_t bit;
	uint8_t i = 8;
    while(i--) {
        bit = (data & (1 << i)) ? 1 : 0;
        APP_UART_OutChar(huart, bit + '0');
    }
}

void APP_UART_OutBinary_16BIT(UART_HandleTypeDef* huart, uint16_t data) {
    uint8_t bit;
	uint8_t i = 16;
    while(i--) {
        bit = (data & (1 << i)) ? 1 : 0;
        APP_UART_OutChar(huart, bit + '0');
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
    if (APP_UART_IsAvailable(huart_transmit)) {
        char data = APP_UART_InChar(huart_transmit);
        APP_UART_OutChar(huart_receive, data);
    }
}

void APP_UART_FlushToUART_String(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive) {
    while (APP_UART_IsAvailable(huart_transmit)) {
        APP_UART_FlushToUART_Char(huart_transmit, huart_receive);
    }
}

bool APP_UART_IsAvailable(UART_HandleTypeDef* huart) {
    Fifo_t* Fifo_n = NULL;
    if (huart == huart_terminal) Fifo_n = &Fifo_1;
    if (huart == huart_mc60) Fifo_n = &Fifo_3;

    return !Fifo_isEmpty(Fifo_n);
}


