#ifndef __MC60_CORE_H
#define __MC60_CORE_H

#include <stdbool.h>

#include "stm32f0xx_hal.h"
#include "PCL/usart/usart_pcl.h"

#define MC60_VBAT_GPIO_Port   GSM_EN_GPIO_Port
#define MC60_VBAT_Pin         GSM_EN_Pin

/* Khởi tạo chân UART cho MC60 */
void MC60_Init(UART_HandleTypeDef* huart);
/* Đưa MC60_PWRKEY lên 1 trong 100ms -> MC_PWRKEY về 0 trong 1200ms */
void MC60_PowerOn(void);
/* MC60_PWRKEY về 0 trong 900ms */
void MC60_PowerOff(void);

/* Truyền UART nguyên chuỗi str */
void MC60_ATCommand_Send(const char* str);
/* Truyền UART chuỗi str + "=?\r\n" */
void MC60_ATCommand_Test(const char* str);
/* Truyền UART chuỗi str + "?\r\n" */
void MC60_ATCommand_Read(const char* str);
/* Truyền UART chuỗi str + "=<parameter>\r\n" */
void MC60_ATCommand_Write(const char* str, const char* parameter);
/* Truyền UART chuỗi str + "=<parameter1>,<parameter2>\r\n" */
void MC60_ATCommand_Write_2Parameter(const char* str, const char* parameter1, const char* parameter2);
/* Truyền UART chuỗi str + "\r\n" */
void MC60_ATCommand_Execute(const char* str);

#endif
