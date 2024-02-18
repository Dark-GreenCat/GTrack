#ifndef __MC60_ITF_INTERFACE_H
#define __MC60_ITF_INTERFACE_H

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
static inline void MC60_ITF_Init(mc60_t* mc60, mc60_uart_interface_t* uart_interface, 
                             mc60_gpio_interface_t* gpio_pwrkey_interface,
                             mc60_gpio_interface_t* gpio_gnss_vcc_en, 
                             mc60_gpio_interface_t* gpio_vdd_ext_interface) {
    mc60->uart_interface = uart_interface;
    mc60->gpio_pwrkey_interface = gpio_pwrkey_interface;
    mc60->gpio_gnss_vcc_en = gpio_gnss_vcc_en;
    mc60->gpio_vdd_ext_interface = gpio_vdd_ext_interface;

    MC60_GPIO_Reset(gpio_pwrkey_interface);
    MC60_GPIO_Reset(gpio_gnss_vcc_en);
}
							 
static inline bool MC60_ITF_IsRunning(mc60_t* mc60) {
    return MC60_GPIO_Read(mc60->gpio_vdd_ext_interface);
}

/* Đưa MC60_ITF_PWRKEY lên 1 trong 100ms -> MC_PWRKEY về 0 trong 1200ms */
static inline void MC60_ITF_PowerOn(mc60_t* mc60) {
    if(MC60_ITF_IsRunning(mc60)) return;

    MC60_GPIO_Set(mc60->gpio_pwrkey_interface);
    MC60_Delay(MC60_POWERON_READY_DELAY_MS);
    MC60_GPIO_Reset(mc60->gpio_pwrkey_interface);
    MC60_Delay(MC60_POWERON_PULSE_DELAY_MS);
    MC60_GPIO_Set(mc60->gpio_pwrkey_interface);
    MC60_Delay(MC60_POWERON_STABILIZED_DELAY_MS);
}

/* MC60_ITF_PWRKEY về 0 trong 900ms */
static inline void MC60_ITF_PowerOff(mc60_t* mc60) {
    if(!MC60_ITF_IsRunning(mc60)) return;
    
    MC60_GPIO_Reset(mc60->gpio_pwrkey_interface);
    MC60_Delay(MC60_POWEROFF_PULSE_DELAY_MS);
    MC60_GPIO_Set(mc60->gpio_pwrkey_interface);
}

static inline void MC60_ITF_Send(mc60_t* mc60, const char* str) {
    MC60_UART_Send(mc60->uart_interface, str);
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

static inline char MC60_ITF_ReceiveChar(mc60_t* mc60, uint32_t timeout) {
    return MC60_UART_ReceiveChar(mc60->uart_interface, timeout);
}

static inline void MC60_ITF_ReceiveResponse(mc60_t* mc60, char *res, uint16_t max_length, uint32_t timeout) {
    MC60_UART_Receive(mc60->uart_interface, res, max_length, timeout);
}

static inline bool MC60_ITF_DetectResponse(char c, const char* target, uint32_t target_length, uint32_t* current_index) {
    if (c == target[*current_index]) {
        (*current_index)++;
        if (*current_index == target_length) {
            // Reached the end of the target string
            *current_index = 0;
            return true;
        }
    } else {
        // Reset index if the characters do not match
        *current_index = 0;
    }
    
    return false;
}

static inline bool MC60_ITF_WaitForResponse(mc60_t* mc60, const char* response, uint32_t response_length, uint32_t timeout) {
    uint32_t last = MC60_MCU_Uptime();
    
	uint32_t current_index = 0; 
    while (MC60_MCU_Uptime() - last < timeout) {
        char c = MC60_ITF_ReceiveChar(mc60, timeout);
        if (c == 0) continue;
        
        last = MC60_MCU_Uptime();
        if(MC60_ITF_DetectResponse(c, response, response_length, &current_index)) return true;
    }

    return false;
}

static inline void MC60_ITF_GNSS_PowerOn(mc60_t* mc60) {
    MC60_ITF_SendCmd(mc60, "AT+QGNSSC=1");
    MC60_GPIO_Set(mc60->gpio_gnss_vcc_en);
}

#endif
