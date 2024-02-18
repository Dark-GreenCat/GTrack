#ifndef __USART_PCL_H
#define __USART_PCL_H

#include <stdbool.h>
#include "stm32f0xx_hal.h"
#include "usart/usart_hcl.h"

bool PAL_UART_ReadStringUntil(UART_HandleTypeDef* huart, char terminatedChar, char* destination);

/* Truyền từng ký tự của xâu */
void PAL_UART_OutString(UART_HandleTypeDef* huart, const char* str);
void PAL_UART_OutNumber(UART_HandleTypeDef* huart, uint32_t number);
void PAL_UART_OutNumber_Signed(UART_HandleTypeDef* huart, int32_t number);
void PAL_UART_OutBinary_8BIT(UART_HandleTypeDef* huart, uint8_t data);
void PAL_UART_OutBinary_16BIT(UART_HandleTypeDef* huart, uint16_t data);

void PAL_UART_FlushToUART_Char(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive);
void PAL_UART_FlushToUART_String(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive);


#endif
