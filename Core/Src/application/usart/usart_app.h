#ifndef __USART_APP_H
#define __USART_APP_H

#include <stdbool.h>
#include "stm32f0xx_hal.h"
#include "usart.h"
#include "fifo_app.h"

#define APP_CHAR_LF     0x0A

extern UART_HandleTypeDef* huart_terminal;
extern UART_HandleTypeDef* huart_mc60;

/* Kết nối UART với UART của STM32 -> Đặt kích thước FIFO*/
void APP_UART_Init(UART_HandleTypeDef* huart, uint32_t size);
/* Bật Interrupt khi nhận dữ liệu */
void APP_UART_StartReceive(UART_HandleTypeDef* huart);
/* Busy-wait đợi FIFO có dữ liệu -> Trả về kí tự */
char APP_UART_InChar(UART_HandleTypeDef* huart);

/* Truyền 1 ký tự */
void APP_UART_OutChar(UART_HandleTypeDef* huart, char data);
/* Truyền từng ký tự của xâu */
void APP_UART_OutString(UART_HandleTypeDef* huart, const char* str);
/* Truyền toàn bộ ký tự trong FIFO */
void APP_UART_FIFO_Flush(UART_HandleTypeDef* huart);

/* Kiểm tra con trỏ Get và Put, nếu bằng nhau thì FIFO trống */
bool APP_UART_FIFO_isEmpty(UART_HandleTypeDef* huart);

#endif