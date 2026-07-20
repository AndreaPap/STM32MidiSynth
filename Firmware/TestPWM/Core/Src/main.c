/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stdint.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "AudioEngine.h"
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
TIM_HandleTypeDef htim11;

/* USER CODE BEGIN PV */
float Sine[ 128 ] = { 0.5f, 0.5245338f, 0.5490086f, 0.5733652f, 0.5975452f, 0.6214901f, 0.6451423f, 0.6684449f, 0.6913417f, 0.7137775f, 0.7356984f, 0.7570514f, 0.7777851f, 0.7978497f, 0.8171966f, 0.8357795f, 0.8535534f, 0.8704756f, 0.8865052f, 0.9016038f, 0.9157348f, 0.9288643f, 0.9409606f, 0.9519946f, 0.9619398f, 0.970772f, 0.9784702f, 0.9850156f, 0.9903926f, 0.9945883f, 0.9975924f, 0.9993977f, 1.0f, 0.9993977f, 0.9975924f, 0.9945883f, 0.9903926f, 0.9850156f, 0.9784702f, 0.970772f, 0.9619398f, 0.9519946f, 0.9409606f, 0.9288643f, 0.9157348f, 0.9016038f, 0.8865052f, 0.8704756f, 0.8535534f, 0.8357795f, 0.8171966f, 0.7978497f, 0.7777851f, 0.7570514f, 0.7356984f, 0.7137775f, 0.6913417f, 0.6684449f, 0.6451423f, 0.6214901f, 0.5975452f, 0.5733652f, 0.5490086f, 0.5245338f, 0.5f, 0.4754662f, 0.4509914f, 0.4266348f, 0.4024548f, 0.3785099f, 0.3548577f, 0.3315551f, 0.3086583f, 0.2862225f, 0.2643016f, 0.2429486f, 0.2222149f, 0.2021503f, 0.1828034f, 0.1642205f, 0.1464466f, 0.1295244f, 0.1134948f, 0.0983962f, 0.0842652f, 0.0711357f, 0.0590394f, 0.0480054f, 0.0380602f, 0.029228f, 0.0215298f, 0.0149844f, 0.0096074f, 0.0054117f, 0.0024076f, 0.0006023f, 0.0f, 0.0006023f, 0.0024076f, 0.0054117f, 0.0096074f, 0.0149844f, 0.0215298f, 0.029228f, 0.0380602f, 0.0480054f, 0.0590394f, 0.0711357f, 0.0842652f, 0.0983962f, 0.1134948f, 0.1295244f, 0.1464466f, 0.1642205f, 0.1828034f, 0.2021503f, 0.2222149f, 0.2429486f, 0.2643016f, 0.2862225f, 0.3086583f, 0.3315551f, 0.3548577f, 0.3785099f, 0.4024548f, 0.4266348f, 0.4509914f, 0.4754662f };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM11_Init(void);
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
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
  //TIM11->ARR 	= 	65535;
  //TIM11->CCR1 	= 	16384;
  // PER INIZIALIZZARE CORRETTAMENTE GUARDA IL REFERENCE MANUAL SOTTO LA SEZIONE PWM
  // TIENI APERTA UNA SCHEDA SULLA DESCRIZIONE CHE SPIEGA QUALI REGISTRI INIZIALIZZARE E IN QUALE ORDINE
  // NELL'ALTRA SCHEDA APRI I SINGOLI REGISTRI E CONFIGURA
  TIM11->ARR 	=	255;
  TIM11->CCR1	= 	0;
  TIM11->CCMR1 	|= 	0x68;
  TIM11->CR1 	|= 	0x80;
  TIM11->EGR 	|= 	0x01;
  TIM11->CCER 	|= 	0x01;
  TIM11->CR1 	|=	0x01;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  AudioEngine_TypeState AudioEngine;
  AudioEngine.Sample = Sine;
  AudioEngine.SampleSize = 128;
  AudioEngine.PhaseIncrement = 0.05632f; // Time / Periodo = Index / SampleSize ->  ( Frequenza / SampleRate ) * SampleSize = Delta fase
  AudioEngine.Phase = 0;
  while (1)
  {

	  TIM11->CCR1 = ( uint32_t )( AudioEngine_Sample( &AudioEngine ) * 255 );
	  //HAL_GPIO_TogglePin( LED_GPIO_Port, LED_Pin );
	  //TIM11->CCR1 = TIM11->CCR1 == 255 ? 0 : TIM11->CCR1 + 1;
	  //HAL_Delay( 10 );
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 0;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 255;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */
  HAL_TIM_MspPostInit(&htim11);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
