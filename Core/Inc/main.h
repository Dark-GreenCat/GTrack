/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "display/display_pal.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define DEBUG_ENABLE


#ifdef DEBUG_ENABLE
#define DEBUG(...) PAL_DISPLAY_Debug(__VA_ARGS__);
#else
#define DEBUG(...)
#endif
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define STM32_SPI1_NSS_Pin GPIO_PIN_4
#define STM32_SPI1_NSS_GPIO_Port GPIOA
#define GSM_EN_Pin GPIO_PIN_12
#define GSM_EN_GPIO_Port GPIOB
#define GNSS_EN_Pin GPIO_PIN_13
#define GNSS_EN_GPIO_Port GPIOB
#define MC60_PWRKEY_Pin GPIO_PIN_14
#define MC60_PWRKEY_GPIO_Port GPIOB
#define MC60_VDD_EXT_Pin GPIO_PIN_15
#define MC60_VDD_EXT_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_11
#define LED_GREEN_GPIO_Port GPIOA
#define LED_PWR_Pin GPIO_PIN_12
#define LED_PWR_GPIO_Port GPIOA
#define ACCE_INT1_Pin GPIO_PIN_3
#define ACCE_INT1_GPIO_Port GPIOB
#define ACCE_INT1_EXTI_IRQn EXTI2_3_IRQn
#define STM32_I2C1_SCL_Pin GPIO_PIN_6
#define STM32_I2C1_SCL_GPIO_Port GPIOB
#define STM32_I2C1_SDA_Pin GPIO_PIN_7
#define STM32_I2C1_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
