#ifndef __W25QXX_MCU_SPI_INTERFACE
#define __W25QXX_MCU_SPI_INTERFACE

#include <stdint.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi/spi_hcl.h"
#include "gpio/gpio_hcl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
// Please REPLACE struct mcu_spi_interface by your own spi struct
// typedef struct mcu_spi_interface spi_interface_t;
typedef SPI_HandleTypeDef spi_interface_t;
typedef GPIO_HandleTypeDef gpio_interface_t;
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
// Please IMPLEMENT your own spi interface function
// static inline void W25Q_SPI_Transmit(spi_interface_t* spi_interface, uint8_t* p_data, uint16_t length) {}
static inline void W25Q_SPI_Transmit(spi_interface_t* spi_interface, uint8_t* p_data, uint16_t length) {
    HCL_SPI_Transmit(spi_interface, p_data, length);
}

// static inline void W25Q_SPI_Receive(spi_interface_t* spi_interface, uint8_t* p_data, uint16_t length) {}
static inline void W25Q_SPI_Receive(spi_interface_t* spi_interface, uint8_t* p_data, uint16_t length) {
    HCL_SPI_Receive(spi_interface, p_data, length);
}

static inline void W25Q_CS_Select(gpio_interface_t* gpio_interface, bool select) {
    HCL_GPIO_WritePin(&hgpio_stm32_spi1_nss, (GPIO_PinState) select);
}

static inline void W25Q_Delay(uint32_t ms) {
    HAL_Delay(ms);
}

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

#endif