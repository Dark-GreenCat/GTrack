#include "usart_pcl.h"

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


