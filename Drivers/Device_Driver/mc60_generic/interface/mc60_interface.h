#ifndef __MC60_INTERFACE_H
#define __MC60_INTERFACE_H

#include "mc60_mcu_interface.h"
#include "utils/mc60_util.h"

#define MC60_AT_COMMAND_MAX_SIZE            256
#define MC60_RESPONSE_OK_STRING "OK\r\n"
#define MC60_RESPONSE_OK_LENGTH 4

#define MC60_POWERON_READY_DELAY_MS         100
#define MC60_POWERON_PULSE_DELAY_MS         1200
#define MC60_POWERON_STABILIZED_DELAY_MS    1200

#define MC60_POWEROFF_PULSE_DELAY_MS        850


typedef struct {
    mc60_uart_interface_t* uart_interface;
    mc60_gpio_interface_t* gpio_pwrkey_interface;
    mc60_gpio_interface_t* gpio_gnss_vcc_en;
    mc60_gpio_interface_t* gpio_vdd_ext_interface;
} mc60_t;

/* Khởi tạo chân UART cho MC60 */
void MC60_ITF_Init(mc60_t* mc60, mc60_uart_interface_t* uart_interface, 
                             mc60_gpio_interface_t* gpio_pwrkey_interface,
                             mc60_gpio_interface_t* gpio_gnss_vcc_en, 
                             mc60_gpio_interface_t* gpio_vdd_ext_interface);

bool MC60_ITF_IsRunning(mc60_t* mc60);

/* Đưa MC60_ITF_PWRKEY lên 1 trong 100ms -> MC_PWRKEY về 0 trong 1200ms */
void MC60_ITF_PowerOn(mc60_t* mc60);

/* MC60_ITF_PWRKEY về 0 trong 900ms */
void MC60_ITF_PowerOff(mc60_t* mc60);

void MC60_ITF_Send(mc60_t* mc60, const char* str);

void MC60_ITF_SendCmd(mc60_t* mc60, const char* cmd);

void MC60_ITF_SendCmdWithParam(mc60_t* mc60, const char* cmd, const char* param);

char MC60_ITF_ReceiveChar(mc60_t* mc60, uint32_t timeout);

void MC60_ITF_ReceiveResponse(mc60_t* mc60, char *res, uint16_t max_length, uint32_t timeout);

bool MC60_ITF_DetectResponse(char c, const char* target, uint32_t target_length, uint32_t* current_index);

bool MC60_ITF_WaitForResponse(mc60_t* mc60, const char* response, uint32_t response_length, uint32_t timeout);

void MC60_ITF_GNSS_PowerOn(mc60_t* mc60);

#endif