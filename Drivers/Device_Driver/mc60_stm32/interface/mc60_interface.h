#ifndef __MC60_ITF_INTERFACE_H
#define __MC60_ITF_INTERFACE_H

#include "mc60_mcu_interface.h"
#include "../Core/Src/GTrack/PCL/driver/mc60/mc60_core/mc60_core_pcl.h"

typedef struct {
    mc60_uart_interface_t* uart_interface;
    mc60_gpio_interface_t* gpio_pwrkey_interface;
    mc60_gpio_interface_t* gpio_vdd_ext_interface;
} mc60_t;

/* Khởi tạo chân UART cho MC60 */
static inline void MC60_ITF_Init(mc60_t* mc60, mc60_uart_interface_t* uart_interface, 
                             mc60_gpio_interface_t* gpio_pwrkey_interface, 
                             mc60_gpio_interface_t* gpio_vdd_ext_interface) {
    mc60->uart_interface = uart_interface;
    mc60->gpio_pwrkey_interface = gpio_pwrkey_interface;
    mc60->gpio_vdd_ext_interface = gpio_vdd_ext_interface;

    MC60_GPIO_Reset(gpio_pwrkey_interface);
    MC60_Init(uart_interface);
}
/* Đưa MC60_ITF_PWRKEY lên 1 trong 100ms -> MC_PWRKEY về 0 trong 1200ms */
static inline void MC60_ITF_PowerOn(mc60_t* mc60) {
    MC60_GPIO_Set(mc60->gpio_pwrkey_interface);
    MC60_Delay(100);
    MC60_GPIO_Reset(mc60->gpio_pwrkey_interface);
    MC60_Delay(1200);
    MC60_GPIO_Set(mc60->gpio_pwrkey_interface);
    MC60_Delay(1200);
}

/* MC60_ITF_PWRKEY về 0 trong 900ms */
static inline void MC60_ITF_PowerOff(mc60_t* mc60) {
    MC60_GPIO_Reset(mc60->gpio_pwrkey_interface);
    MC60_Delay(850);
    MC60_GPIO_Set(mc60->gpio_pwrkey_interface);
}

static inline bool MC60_ITF_IsReady(mc60_t* mc60) {
    return MC60_GPIO_Read(mc60->gpio_vdd_ext_interface);
}

static inline void MC60_ITF_SendCmd(mc60_t* mc60, const char* cmd) {
    MC60_UART_Send(mc60->uart_interface, cmd);
    MC60_UART_Send(mc60->uart_interface, "\r\n");
}

static inline void MC60_ITF_SendCmdWithParam(mc60_t* mc60, const char* cmd, const char* param) {
    MC60_UART_Send(mc60->uart_interface, cmd);
    MC60_UART_Send(mc60->uart_interface, "=");
    MC60_UART_Send(mc60->uart_interface, param);
    MC60_UART_Send(mc60->uart_interface, "\r\n");
}

static inline void MC60_ITF_ReceiveResponse(mc60_t* mc60, char *res, uint16_t max_length, uint32_t timeout) {
    MC60_UART_Receive(mc60->uart_interface, res, max_length, timeout);
}

// /* Truyền UART nguyên chuỗi str */
// void MC60_ITF_ATCommand_Send(const char* str);
// /* Truyền UART chuỗi str + "=?\r\n" */
// void MC60_ITF_ATCommand_Test(const char* str);
// /* Truyền UART chuỗi str + "?\r\n" */
// void MC60_ITF_ATCommand_Read(const char* str);
// /* Truyền UART chuỗi str + "=<parameter>\r\n" */
// void MC60_ITF_ATCommand_Write(const char* str, const char* parameter);
// /* Truyền UART chuỗi str + "=<parameter1>,<parameter2>\r\n" */
// void MC60_ITF_ATCommand_Write_2Parameter(const char* str, const char* parameter1, const char* parameter2);
// /* Truyền UART chuỗi str + "\r\n" */
// void MC60_ITF_ATCommand_Execute(const char* str);

#endif
