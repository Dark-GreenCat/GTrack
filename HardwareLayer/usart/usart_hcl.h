#ifndef __USART_HCL_H
#define __USART_HCL_H

#include <stdbool.h>
#include "stm32f0xx_hal.h"
#include "usart.h"
#include "tim.h"
#include "fifo_hcl.h"
#include "signal/signal_pal.h"

extern UART_HandleTypeDef* huart_terminal;
extern UART_HandleTypeDef* huart_mc60;

/* Kết nối UART với UART của STM32 -> Đặt kích thước FIFO*/
void HCL_UART_Init(UART_HandleTypeDef* huart, uint32_t size);
/* Bật Interrupt khi nhận dữ liệu */
void HCL_UART_StartReceive(UART_HandleTypeDef* huart);
/* Busy-wait đợi FIFO có dữ liệu -> Trả về kí tự */
char HCL_UART_InChar(UART_HandleTypeDef* huart);

/* Truyền 1 ký tự */
void HCL_UART_OutChar(UART_HandleTypeDef* huart, char data);

/* Truyền toàn bộ ký tự trong FIFO */
void HCL_UART_FIFO_Flush(UART_HandleTypeDef* huart);
/* Kiểm tra con trỏ Get và Put, nếu bằng nhau thì FIFO trống */
bool HCL_UART_IsAvailable(UART_HandleTypeDef* huart);

#endif
