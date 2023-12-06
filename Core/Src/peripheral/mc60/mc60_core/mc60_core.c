#include "mc60_core.h"

static UART_HandleTypeDef* mc60_huart;

void MC60_Init(UART_HandleTypeDef* huart) {
    mc60_huart = huart;
}

void MC60_PowerOn(void) {
    HAL_GPIO_WritePin(MC60_VBAT_GPIO_Port, MC60_VBAT_Pin, 0);
    HAL_GPIO_WritePin(MC60_PWRKEY_GPIO_Port, MC60_PWRKEY_Pin, 0);
    HAL_Delay(100);
    HAL_GPIO_WritePin(MC60_PWRKEY_GPIO_Port, MC60_PWRKEY_Pin, 1);
    HAL_Delay(1200);
    HAL_GPIO_WritePin(MC60_PWRKEY_GPIO_Port, MC60_PWRKEY_Pin, 0);
    HAL_Delay(1200);
}

void MC60_PowerOff(void) {
    MC60_ATCommand_Write("AT+QPOWD", "1");
}

void MC60_ATCommand_Send(const char* str) {
    APP_UART_OutString(mc60_huart, str);
}

void MC60_ATCommand_Test(const char* str) {
    MC60_ATCommand_Send(str);
    MC60_ATCommand_Send("=?\r\n");
}

void MC60_ATCommand_Read(const char* str) {
    MC60_ATCommand_Send(str);
    MC60_ATCommand_Send("?\r\n");
}

void MC60_ATCommand_Write(const char* str, const char* parameter) {
    MC60_ATCommand_Send(str);
    MC60_ATCommand_Send("=");
    MC60_ATCommand_Send(parameter);
    MC60_ATCommand_Send("\r\n");
}

void MC60_ATCommand_Write_2Parameter(const char* str, const char* parameter1, const char* parameter2) {
    MC60_ATCommand_Send(str);
    MC60_ATCommand_Send("=");
    MC60_ATCommand_Send(parameter1);
    MC60_ATCommand_Send(",");
    MC60_ATCommand_Send(parameter2);
    MC60_ATCommand_Send("\r\n");
}

void MC60_ATCommand_Execute(const char* str) {
    MC60_ATCommand_Send(str);
    MC60_ATCommand_Send("\r\n");
}
