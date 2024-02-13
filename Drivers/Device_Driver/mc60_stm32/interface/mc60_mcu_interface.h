#ifndef __MC60_MCU_INTERFACE_H
#define __MC60_MCU_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart/usart_pal.h"
#include "gpio/gpio_hcl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
// Please REPLACE struct mcu_uart_interface by your own i2c struct
// typedef struct mcu_uart_interface mc60_uart_interface_t;
typedef UART_HandleTypeDef mc60_uart_interface_t;
// typedef struct mcu_gpio_interface mc60_gpio_interface_t;
typedef GPIO_HandleTypeDef mc60_gpio_interface_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
// Please IMPLEMENT your own uart interface function
// static inline void MC60_UART_Send(mc60_uart_interface_t* mc60_uart_interface, char* cmd) {}
static inline void MC60_UART_Send(mc60_uart_interface_t* mc60_uart_interface, const char* content) {
    PCL_UART_OutString(mc60_uart_interface, content);
}

// static inline bool MC60_UART_IsAvailable(mc60_uart_interface_t* mc60_uart_interface) {}
static inline bool MC60_UART_IsAvailable(mc60_uart_interface_t* mc60_uart_interface) {
    if (mc60_uart_interface != huart_mc60) return false;
    return HCL_UART_IsAvailable(mc60_uart_interface);
}

// static inline void MC60_UART_Receive(mc60_uart_interface_t* mc60_uart_interface, char* response, uint16_t maxLength, uint32_t timeout) {}
static inline void MC60_UART_Receive(mc60_uart_interface_t* mc60_uart_interface, char* response, uint16_t max_length, uint32_t timeout) {
    uint32_t lastReceived = HAL_GetTick();
    uint16_t length = 0;
    while ((length < max_length) && (lastReceived + timeout < HAL_GetTick())) {
        if (MC60_UART_IsAvailable(mc60_uart_interface)) {
            *response++ = HCL_UART_InChar(mc60_uart_interface);
            length++;
            lastReceived = HAL_GetTick();
        }
    }

    *response = '\0';
}

// Please IMPLEMENT your own gpio interface function
// static inline void MC60_GPIO_Set(mc60_gpio_interface_t* mc60_gpio_interface) {}
static inline void MC60_GPIO_Set(mc60_gpio_interface_t* mc60_gpio_interface) {
    HCL_GPIO_WritePin(mc60_gpio_interface, GPIO_PIN_RESET);
}

// static inline void MC60_GPIO_Reset(mc60_gpio_interface_t* mc60_gpio_interface) {}
static inline void MC60_GPIO_Reset(mc60_gpio_interface_t* mc60_gpio_interface) {
    HCL_GPIO_WritePin(mc60_gpio_interface, GPIO_PIN_SET);
}


static inline bool MC60_GPIO_Read(mc60_gpio_interface_t* mc60_gpio_interface) {
    return (bool) HCL_GPIO_ReadPin(mc60_gpio_interface);
}

// static inline void MC60_Delay(uint32_t delay_ms) {}
static inline void MC60_Delay(uint32_t delay_ms) {
    HAL_Delay(delay_ms);
}

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

#endif