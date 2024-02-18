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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>

#include "string_util.h"
#include "signal/signal_pal.h"
#include "timer/timer_hcl.h"
#include "usart/usart_hcl.h"
#include "interface/mc60_interface.h"
#include "gnss/mc60_gnss.h"
#include "network/mqtt/mc60_mqtt.h"
#include "BMA253/bma253_pal.h"
#include "gpio/gpio_hcl.h"
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
  /* USER CODE BEGIN 2 */
  HCL_GPIO_Init();
  HCL_UART_Init(huart_terminal, 64);
  HCL_UART_Init(huart_mc60, 512);
  HCL_TIMER_Init(&htim3);

  mc60_t mc60;
  MC60_ITF_Init(&mc60, huart_mc60, &hgpio_mc60_pwrkey, &hgpio_mc60_gnss_en, &hgpio_mc60_vdd_ext);
  HCL_GPIO_WritePin(&hgpio_mc60_gsm_en, GPIO_PIN_RESET);
  //test_main_bma253();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HCL_UART_StartReceive(huart_terminal);
  HCL_UART_StartReceive(huart_mc60);


  bool mc60_state = false;
  PAL_UART_OutString(huart_terminal, "\nCheck MC60 Status: ");
  mc60_state = MC60_ITF_IsRunning(&mc60);
  PAL_UART_OutNumber(huart_terminal, mc60_state);

  PAL_UART_OutString(huart_terminal, "\n-------- Power on MC60 --------\n");
  MC60_ITF_PowerOn(&mc60);
  PAL_UART_OutString(huart_terminal, "\n------ Check MC60 status ------");
  PAL_UART_OutString(huart_terminal, "\n\t>> Running command: AT\n");
  MC60_ITF_SendCmd(&mc60, "AT");
  HAL_Delay(6000);
  PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);
  PAL_UART_OutString(huart_terminal, "\nCheck MC60 Status: ");
  mc60_state = MC60_ITF_IsRunning(&mc60);
  PAL_UART_OutNumber(huart_terminal, mc60_state);
  

//  PAL_UART_OutString(huart_terminal, "\n-------- Power on GNSS --------\n");
//  MC60_ITF_GNSS_PowerOn(&mc60);
//  HAL_Delay(3000);
 PAL_UART_FlushToUART_String(huart_mc60, huart_terminal);

  // // HCL_TIMER_Start();
  uint32_t pre = HAL_GetTick();
  uint32_t cur = pre;
//  bool lastState = mc60_state;
  char buffer[256];
  nmea_data GPSData;
  bool isMQTTOpen = false;
  bool isMQTTConnect = false;
  while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    cur = HAL_GetTick();
    PAL_UART_FlushToUART_Char(huart_terminal, huart_mc60);
    PAL_UART_FlushToUART_Char(huart_mc60, huart_terminal);

    if (cur - pre >= 5000) {
      if (!isMQTTOpen) {
        isMQTTConnect = false;
        int8_t result = MC60_MQTT_Open(&mc60, MC60_MQTT_TCP_CONNECT_ID_0, "demo.thingsboard.io", 1883, 3000);
        PAL_UART_OutString(huart_terminal, "\n*** Opening MQTT connection... ");
        PAL_UART_OutString(huart_terminal, "\nStatus code: ");
        PAL_UART_OutNumber_Signed(huart_terminal, result);
        if (result == 0 || result == 2) {
          isMQTTOpen = true;
          PAL_UART_OutString(huart_terminal, "\nMQTT connection openned!\n");
        }
      }

      if(!isMQTTConnect) {
        int8_t result = MC60_MQTT_Connect(&mc60, MC60_MQTT_TCP_CONNECT_ID_0, "demo.thingsboard.io", "3QcnES9LsYKtGIIXxNXU", "", 3000); 
        PAL_UART_OutString(huart_terminal, "\n*** Connecting MQTT broker... ");
        PAL_UART_OutString(huart_terminal, "\nStatus code: ");
        PAL_UART_OutNumber_Signed(huart_terminal, result);
        if(result == 0 || result == 1) {
          isMQTTConnect = true;
          PAL_UART_OutString(huart_terminal, "\nMQTT broker connected!\n");
        }
      }
      
      // if (result == 0 || result == 2) {
      //   MC60_MQTT_Connect(mc60, MC60_MQTT_TCP_CONNECT_ID_0, )
      // }
      // PAL_UART_OutString(huart_terminal, "\nConnecting GNSS...\n");
      // if (MC60_GNSS_Get_Navigation_Info(&mc60, &GPSData, 3000)) {
      //   NMEA_Parser_changeTimezone(&GPSData, 7);
      //   char temp[30];
      //   sprintf(buffer, "\n----- CAPTURING GNSS DATA -----\n");
      //   sprintf(buffer + strlen(buffer), "Time: %02d:%02d:%02d\n", GPSData.Time.hours, GPSData.Time.minutes, GPSData.Time.seconds);
      //   sprintf(buffer + strlen(buffer), "Date: %02d/%02d/%04d\n", GPSData.Date.day, GPSData.Date.month, 2000 + GPSData.Date.year);
      //   sprintf(buffer + strlen(buffer), "Latitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.latitude, temp));
      //   sprintf(buffer + strlen(buffer), "Longitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.longitude, temp));
      //   sprintf(buffer + strlen(buffer), "Speed: %s knots\n", NMEA_Parser_nmeafloattostr(GPSData.Speed.speed_knot, temp));
      //   sprintf(buffer + strlen(buffer), "Course: %s degrees\n", NMEA_Parser_nmeafloattostr(GPSData.Course.course_degree, temp));
      //   sprintf(buffer + strlen(buffer), "HDOP: %s\n", NMEA_Parser_nmeafloattostr(GPSData.HDOP.hdop, temp));
      //   sprintf(buffer + strlen(buffer), "Altitude: %s m\n", NMEA_Parser_nmeafloattostr(GPSData.Altitude.altitude_meter, temp));
      //   sprintf(buffer + strlen(buffer), "\n");

      //   PAL_UART_OutString(huart_terminal, buffer);
      // }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
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
