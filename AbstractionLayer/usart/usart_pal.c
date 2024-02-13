#include "usart_pal.h"

bool PCL_UART_ReadStringUntil(UART_HandleTypeDef *huart, char terminatedChar, char *destination) {
    static bool isFirstInit = true;
    static char* p_Destination = NULL;
    
    if(isFirstInit) p_Destination = destination;
    isFirstInit = false;
    bool isDone = false;
    if (HCL_UART_IsAvailable(huart)) {
      char data = HCL_UART_InChar(huart);
      while (data != terminatedChar) {
        *p_Destination++ = data;
        if (!HCL_UART_IsAvailable(huart)) break;
        data = HCL_UART_InChar(huart);
      }
      if(data == terminatedChar) isDone = true;
      if (isDone) {
        *p_Destination = '\0';
        p_Destination = destination;
      }
    }

    return isDone;
}

void PCL_UART_OutString(UART_HandleTypeDef* huart, const char* str) {
    while (*str != '\0')
        HCL_UART_OutChar(huart, (uint8_t)*str++);
}

void PCL_UART_OutNumber(UART_HandleTypeDef* huart, uint32_t number) {
    if(number == 0) {
        HCL_UART_OutChar(huart, '0');
        return;
    }

	char number_str[10];
	uint8_t index = 0;
    while (number != 0) {
        number_str[index++] = number % 10 + '0';
        number /= 10;
    }

    while(index--) HCL_UART_OutChar(huart, number_str[index]);
}

void PCL_UART_OutNumber_Signed(UART_HandleTypeDef* huart, int32_t number) {
    if(number == 0) {
		HCL_UART_OutChar(huart, '0');
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
	
    if(isSigned) HCL_UART_OutChar(huart, '-');
	while(index--) HCL_UART_OutChar(huart, number_str[index]);
}

void PCL_UART_OutBinary_8BIT(UART_HandleTypeDef* huart, uint8_t data) {
    uint8_t bit;
	uint8_t i = 8;
    while(i--) {
        bit = (data & (1 << i)) ? 1 : 0;
        HCL_UART_OutChar(huart, bit + '0');
    }
}

void PCL_UART_OutBinary_16BIT(UART_HandleTypeDef* huart, uint16_t data) {
    uint8_t bit;
	uint8_t i = 16;
    while(i--) {
        bit = (data & (1 << i)) ? 1 : 0;
        HCL_UART_OutChar(huart, bit + '0');
    }
}


void PCL_UART_FlushToUART_Char(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive) {
    if (HCL_UART_IsAvailable(huart_transmit)) {
        char data = HCL_UART_InChar(huart_transmit);
        HCL_UART_OutChar(huart_receive, data);
    }
}

void PCL_UART_FlushToUART_String(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive) {
    while (HCL_UART_IsAvailable(huart_transmit)) {
        PCL_UART_FlushToUART_Char(huart_transmit, huart_receive);
    }
}


