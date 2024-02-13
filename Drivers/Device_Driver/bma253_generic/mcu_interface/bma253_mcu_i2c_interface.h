#ifndef __BMA253_MCU_I2C_INTERFACE
#define __BMA253_MCU_I2C_INTERFACE

#include <stdint.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c/i2c_hcl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
// Please REPLACE struct mcu_i2c_interface by your own i2c struct
// typedef struct mcu_i2c_interface i2c_interface_t;
typedef I2C_HandleTypeDef i2c_interface_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BMA253_I2C_DEVICE_ADDRESS_SHIFT     1
#define BMA253_REG_SIZE                     1
#define BMA253_TIMEOUT                      1000
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
// Please IMPLEMENT your own i2c interface function
// static inline void BMA253_I2C_Read_Reg(i2c_interface_t* i2c_interface, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {}
static inline void BMA253_I2C_Read_Reg(i2c_interface_t* i2c_interface, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t read_length) {
	HCL_I2C_Mem_Read(i2c_interface, 
			dev_addr << BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
			reg_addr, BMA253_REG_SIZE, 
			p_data, 
			read_length,
			BMA253_TIMEOUT);
}

// static inline void BMA253_I2C_Write_Reg(i2c_interface_t* i2c_interface, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {}
static inline void BMA253_I2C_Write_Reg(i2c_interface_t* i2c_interface, uint8_t dev_addr, uint8_t reg_addr, uint8_t* p_data, uint16_t write_length) {
    HCL_I2C_Mem_Write(i2c_interface, 
                dev_addr << BMA253_I2C_DEVICE_ADDRESS_SHIFT, 
                reg_addr, BMA253_REG_SIZE, 
                p_data, 
                write_length, 
                BMA253_TIMEOUT);
}

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

#endif