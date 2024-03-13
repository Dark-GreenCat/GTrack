#include "usart_pal.h"

void PAL_UART_OutString(UART_HandleTypeDef* huart, const char* str) {
    while (*str != '\0')
        HCL_UART_OutChar(huart, (uint8_t)*str++);
}

void PAL_UART_OutNumber(UART_HandleTypeDef* huart, uint32_t number) {
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

void PAL_UART_OutNumber_Signed(UART_HandleTypeDef* huart, int32_t number) {
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

void PAL_UART_OutNumber_Double(UART_HandleTypeDef* huart, double number, uint8_t precision) {
    if (number < 0) {
        HCL_UART_OutChar(huart, '-');
        number = -number;
    }
    
    // Convert the double to an integer
    uint32_t integer = (uint32_t)number;

    // Output the integer part
    PAL_UART_OutNumber(huart, integer);

    // Output the decimal point
    HCL_UART_OutChar(huart, '.');

    // Calculate the fractional part
    double fractional = number - integer;

    // Output the fractional part with the desired precision
    for (uint8_t i = 0; i < precision; i++) {
        fractional *= 10; // Shift the decimal point to the right
        uint32_t digit = (uint32_t)fractional;
        PAL_UART_OutNumber(huart, digit);
        fractional -= digit;
    }
}

void PAL_UART_OutBinary_8BIT(UART_HandleTypeDef* huart, uint8_t data) {
    uint8_t bit;
	uint8_t i = 8;
    while(i--) {
        bit = (data & (1 << i)) ? 1 : 0;
        HCL_UART_OutChar(huart, bit + '0');
    }
}

void PAL_UART_OutBinary_16BIT(UART_HandleTypeDef* huart, uint16_t data) {
    uint8_t bit;
	uint8_t i = 16;
    while(i--) {
        bit = (data & (1 << i)) ? 1 : 0;
        HCL_UART_OutChar(huart, bit + '0');
    }
}


void PAL_UART_FlushToUART_Char(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive) {
	if (HCL_UART_IsAvailable(huart_transmit)) {
		if(huart_transmit == huart_mc60) {
			huart_transmit = huart_mc60;
		}
        char data = HCL_UART_InChar(huart_transmit);
        HCL_UART_OutChar(huart_receive, data);
    }
}

void PAL_UART_FlushToUART_String(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive) {
    while (HCL_UART_IsAvailable(huart_transmit)) {
        PAL_UART_FlushToUART_Char(huart_transmit, huart_receive);
    }
}


