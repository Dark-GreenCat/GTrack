#ifndef __USART_APP_H
#define __USART_APP_H

#include <stdbool.h>
#include "stm32f0xx_hal.h"
#include "usart.h"
#include "tim.h"
#include "fifo_app.h"
#include "../signal/signal_app.h"

#define APP_CHAR_LF     0x0A

extern UART_HandleTypeDef* huart_terminal;
extern UART_HandleTypeDef* huart_mc60;

/* Kết nối UART với UART của STM32 -> Đặt kích thước FIFO*/
void APP_UART_Init(UART_HandleTypeDef* huart, uint32_t size);
/* Bật Interrupt khi nhận dữ liệu */
void APP_UART_StartReceive(UART_HandleTypeDef* huart);
/* Busy-wait đợi FIFO có dữ liệu -> Trả về kí tự */
char APP_UART_InChar(UART_HandleTypeDef* huart);
bool APP_UART_ReadStringUntil(UART_HandleTypeDef* huart, char terminatedChar, char* destination);

/* Truyền 1 ký tự */
void APP_UART_OutChar(UART_HandleTypeDef* huart, char data);
/* Truyền từng ký tự của xâu */
void APP_UART_OutString(UART_HandleTypeDef* huart, const char* str);
void APP_UART_OutNumber(UART_HandleTypeDef* huart, uint32_t number);
void APP_UART_OutNumber_Signed(UART_HandleTypeDef* huart, int32_t number);
void APP_UART_OutBinary_8BIT(UART_HandleTypeDef* huart, uint8_t data);
void APP_UART_OutBinary_16BIT(UART_HandleTypeDef* huart, uint16_t data);

/* Truyền toàn bộ ký tự trong FIFO */
void APP_UART_FIFO_Flush(UART_HandleTypeDef* huart);
void APP_UART_FlushToUART_Char(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive);
void APP_UART_FlushToUART_String(UART_HandleTypeDef* huart_transmit, UART_HandleTypeDef* huart_receive);

/* Kiểm tra con trỏ Get và Put, nếu bằng nhau thì FIFO trống */
bool APP_UART_IsAvailable(UART_HandleTypeDef* huart);

#endif
