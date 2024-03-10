/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>

#include "signal/signal_pal.h"
#include "timer/timer_hcl.h"
#include "usart/usart_hcl.h"
#include "gnss/mc60_gnss.h"
#include "bma253/bma253_pal.h"
#include "gpio/gpio_hcl.h"
#include "mc60/mc60_pal.h"
#include "gtrack_nal.h"
#include "gtrack_ual.h"
#include "display/display_pal.h"
#include "supplier/supplier_pal.h"
#include "hardware/w25qxx_interface.h"
////#include "test_bma253.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
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
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  PAL_DISPLAY_Show("\nEXT INTTERUPT DETECTED!\n");
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_ADC_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  
  HCL_GPIO_Init();
  HCL_UART_Init(huart_terminal);
  HCL_UART_Init(huart_mc60);
  HCL_TIMER_Init(&htim3);

  PAL_BMA253_Init();
  UAL_GTRACK_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HCL_UART_StartReceive(huart_terminal);
  HCL_UART_StartReceive(huart_mc60);
  //UAL_GTRACK_GeoTrack_Enable();

  uint32_t pre = HAL_GetTick();
  uint32_t cur = pre;
  bool isRunning = true;
  char data = 0;
  bool mc60LastState = false, mc60CurState = false;
  uint8_t TxData[] = "MS830 - Hello World! My name is Barry Allen";
  uint8_t RxData[51];

  w25q_t w25q;
  W25Q_ITF_Init(&w25q, &hspi1, &hgpio_stm32_spi1_nss);
  W25Q_ITF_Reset(&w25q);
  //W25Q_ITF_WritePage(&w25q, 0, 0, 43, TxData);
  while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	continue;
    uint32_t ID = W25Q_ITF_ReadID(&w25q);
    PAL_DISPLAY_ShowNumber(ID);
    PAL_DISPLAY_Show("\n");

    W25Q_ITF_Read(&w25q, 0, 0, 50, RxData);
	RxData[50] = '\0';
	PAL_DISPLAY_Show((char*) RxData);
    //W25Q_ITF_WritePage(&w25q, 0, 0, 43, TxData);
//    W25Q_ITF_Read(&w25q, 0, 0, 50, RxData);
//	RxData[50] = '\0';
//	PAL_DISPLAY_Show((char*) RxData);
    
    HAL_Delay(2000);
    continue;
    PAL_DISPLAY_Show("\nRead data\n");
    PAL_DISPLAY_ShowNumber(BMA253_HWI_get_slope_en(&pal_bma253, BMA253_SLOPE_X_INTR));
    BMA253_HWI_set_slope_en(&pal_bma253, BMA253_SLOPE_X_INTR, BMA253_INTR_ENABLE);
    PAL_DISPLAY_Show("\n");
    PAL_DISPLAY_ShowNumber(BMA253_HWI_get_slope_en(&pal_bma253, BMA253_SLOPE_X_INTR));

    HAL_Delay(2000);
    
    continue;
    cur = HAL_GetTick();
    mc60CurState = MC60_ITF_IsRunning(&pal_mc60.core);

    if (HCL_UART_IsAvailable(huart_terminal)) {
      data = HCL_UART_InChar(huart_terminal);
      HCL_UART_OutChar(huart_mc60, data);
    }
    PAL_UART_FlushToUART_Char(huart_mc60, huart_terminal);
    
    if (data == '#') {
      data = 0;
      PAL_DISPLAY_ShowNumber(MC60_ITF_GNSS_checkPower(&pal_mc60.core));
      isRunning = !isRunning;
      if (isRunning == false) {
        PAL_DISPLAY_Show("\nPAUSE RUNNING");
        PAL_MC60_PowerOn(MC60_POWER_OFF);
      }
      else  {
        PAL_DISPLAY_Show("\nCONTINUE RUNNING");
      }
    }

    if (!isTimerRunning)
      PAL_SIGNAL_LED_SetState(!mc60CurState);

    if (!isRunning) {
      continue;
    }

    continue;

    if (!mc60CurState) {
      UAL_GTRACK_GeoTrack_Enable();
    }

    if (cur - pre > 15000) {
      // HCL_UART_OutChar(huart_mc60, '.');
      UAL_GTRACK_GeoTrack_GetMetric();
      pre = cur;
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
