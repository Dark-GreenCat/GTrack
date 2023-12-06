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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "application/usart/usart_app.h"
#include "application/signal/signal_app.h"
#include "application/timer/timer_app.h"
#include "peripheral/mc60/gnss/gnss.h"
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
bool MC60_PowerOff_Request = 0;
bool MC60_PowerOff_Status = 0;

bool STM32_SLEEP_Request = 0;
bool STM32_SLEEP_Status = 0;
bool STM32_WAKEUP_Request = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
//   MC60_PowerOff_Request = 1;
//   if(STM32_SLEEP_Status) {
//     STM32_WAKEUP_Request = 1;
//     HAL_ResumeTick();
//   }
//   else {
//     STM32_SLEEP_Request = 1;
//   }
// }

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
  APP_UART_Init(huart_terminal, 63);
  APP_UART_Init(huart_mc60, 300);
  APP_TIMER_Init(&htim3);

  MC60_Init(huart_mc60);
	
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  APP_UART_StartReceive(huart_terminal);
  APP_UART_StartReceive(huart_mc60);

  APP_UART_OutString(huart_terminal, "\n-------- Power on MC60 --------\n");
  MC60_PowerOn();
  APP_UART_OutString(huart_terminal, "\n------ Check MC60 status ------\n");
  APP_UART_OutString(huart_terminal, "\n\t>> Running command: AT\n");
  MC60_ATCommand_Execute("AT");
  HAL_Delay(6000);
  APP_UART_FlushToUART_String(huart_terminal, huart_mc60);
  // MC60_PowerOff_Status = 0;
  
  APP_UART_OutString(huart_terminal, "\n-------- Power on GNSS --------\n");
  MC60_GNSS_Power_On(1);

  APP_TIMER_Start();
  while (1) {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
    /* Receive command from Terminal and send to MC60 */
    if (!APP_UART_FIFO_isEmpty(huart_terminal)) {
      char data = APP_UART_InChar(huart_terminal);
      switch (data) {
      case '!':
        APP_UART_OutString(huart_terminal, "------ Power On ------\n");
        __HAL_TIM_SetCounter(&htim3, 0);
        MC60_PowerOn();
        MC60_ATCommand_Execute("AT");
        MC60_PowerOff_Status = 0;
        break;

      case '@':
        HAL_GPIO_WritePin(MC60_PWRKEY_GPIO_Port, MC60_PWRKEY_Pin, 0);
        break;

      case '#':
        HAL_GPIO_WritePin(MC60_PWRKEY_GPIO_Port, MC60_PWRKEY_Pin, 1);
        break;

      case '^':
        APP_UART_OutString(huart_terminal, "------ Power Off ------\n");
        MC60_PowerOff();
        break;

      case '*':
        NVIC_SystemReset();
        break;
      
      case '~':
        APP_UART_OutString(huart_terminal, "------ Go to bed ------\n");
        APP_SIGNAL_LED_SetState(0);
        APP_SIGNAL_PWR_SetState(0);
        HAL_SuspendTick();
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); 
        break;

      default:
        APP_UART_OutChar(huart_mc60, data);
        break;
      }
    }

    /* Display response to Terminal */
    APP_UART_FlushToUART_Char(huart_mc60, huart_terminal);

    /* Turn off MC60 if MC60 is not used for a specific time */
    // if (MC60_PowerOff_Request) {
    //   MC60_PowerOff_Request = 0;
    //   if(!MC60_PowerOff_Status) {
    //     MC60_PowerOff_Status = 1;
    //     APP_UART_OutString(huart_terminal, "------ Time out! Turning off MC60 ------\n");
    //     MC60_PowerOff();
    //   }

    //   if(STM32_SLEEP_Request) {
    //      STM32_SLEEP_Request = 0;
    //      STM32_SLEEP_Status = 1;
    //      APP_SIGNAL_LED_SetState(0);
    //      APP_SIGNAL_PWR_SetState(0);
    //      HAL_SuspendTick();
    //      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); 
    //   }

    //   if(STM32_WAKEUP_Request) {
    //     STM32_WAKEUP_Request = 0;
    //     STM32_SLEEP_Status = 0;
    //     APP_SIGNAL_PWR_SetState(1);
    //     APP_SIGNAL_LED_SetState(1);
    //   }
    // }
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
