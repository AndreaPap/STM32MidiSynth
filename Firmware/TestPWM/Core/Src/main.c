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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Engine.h"
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
TIM_HandleTypeDef htim10;
TIM_HandleTypeDef htim11;

/* USER CODE BEGIN PV */
float Sine[ 128 ] = { 0.5f, 0.5245338f, 0.5490086f, 0.5733652f, 0.5975452f, 0.6214901f, 0.6451423f, 0.6684449f, 0.6913417f, 0.7137775f, 0.7356984f, 0.7570514f, 0.7777851f, 0.7978497f, 0.8171966f, 0.8357795f, 0.8535534f, 0.8704756f, 0.8865052f, 0.9016038f, 0.9157348f, 0.9288643f, 0.9409606f, 0.9519946f, 0.9619398f, 0.970772f, 0.9784702f, 0.9850156f, 0.9903926f, 0.9945883f, 0.9975924f, 0.9993977f, 1.0f, 0.9993977f, 0.9975924f, 0.9945883f, 0.9903926f, 0.9850156f, 0.9784702f, 0.970772f, 0.9619398f, 0.9519946f, 0.9409606f, 0.9288643f, 0.9157348f, 0.9016038f, 0.8865052f, 0.8704756f, 0.8535534f, 0.8357795f, 0.8171966f, 0.7978497f, 0.7777851f, 0.7570514f, 0.7356984f, 0.7137775f, 0.6913417f, 0.6684449f, 0.6451423f, 0.6214901f, 0.5975452f, 0.5733652f, 0.5490086f, 0.5245338f, 0.5f, 0.4754662f, 0.4509914f, 0.4266348f, 0.4024548f, 0.3785099f, 0.3548577f, 0.3315551f, 0.3086583f, 0.2862225f, 0.2643016f, 0.2429486f, 0.2222149f, 0.2021503f, 0.1828034f, 0.1642205f, 0.1464466f, 0.1295244f, 0.1134948f, 0.0983962f, 0.0842652f, 0.0711357f, 0.0590394f, 0.0480054f, 0.0380602f, 0.029228f, 0.0215298f, 0.0149844f, 0.0096074f, 0.0054117f, 0.0024076f, 0.0006023f, 0.0f, 0.0006023f, 0.0024076f, 0.0054117f, 0.0096074f, 0.0149844f, 0.0215298f, 0.029228f, 0.0380602f, 0.0480054f, 0.0590394f, 0.0711357f, 0.0842652f, 0.0983962f, 0.1134948f, 0.1295244f, 0.1464466f, 0.1642205f, 0.1828034f, 0.2021503f, 0.2222149f, 0.2429486f, 0.2643016f, 0.2862225f, 0.3086583f, 0.3315551f, 0.3548577f, 0.3785099f, 0.4024548f, 0.4266348f, 0.4509914f, 0.4754662f };
float Saw[ 128 ] = { 0.0f, 0.015873f, 0.031746f, 0.047619f, 0.0634921f, 0.0793651f, 0.0952381f, 0.1111111f, 0.1269841f, 0.1428571f, 0.1587302f, 0.1746032f, 0.1904762f, 0.2063492f, 0.2222222f, 0.2380952f, 0.2539683f, 0.2698413f, 0.2857143f, 0.3015873f, 0.3174603f, 0.3333333f, 0.3492063f, 0.3650794f, 0.3809524f, 0.3968254f, 0.4126984f, 0.4285714f, 0.4444444f, 0.4603175f, 0.4761905f, 0.4920635f, 0.5079365f, 0.5238095f, 0.5396825f, 0.5555556f, 0.5714286f, 0.5873016f, 0.6031746f, 0.6190476f, 0.6349206f, 0.6507937f, 0.6666667f, 0.6825397f, 0.6984127f, 0.7142857f, 0.7301587f, 0.7460317f, 0.7619048f, 0.7777778f, 0.7936508f, 0.8095238f, 0.8253968f, 0.8412698f, 0.8571429f, 0.8730159f, 0.8888889f, 0.9047619f, 0.9206349f, 0.9365079f, 0.952381f, 0.968254f, 0.984127f, 1.0f, 0.9846154f, 0.9692308f, 0.9538462f, 0.9384615f, 0.9230769f, 0.9076923f, 0.8923077f, 0.8769231f, 0.8615385f, 0.8461538f, 0.8307692f, 0.8153846f, 0.8f, 0.7846154f, 0.7692308f, 0.7538462f, 0.7384615f, 0.7230769f, 0.7076923f, 0.6923077f, 0.6769231f, 0.6615385f, 0.6461538f, 0.6307692f, 0.6153846f, 0.6f, 0.5846154f, 0.5692308f, 0.5538462f, 0.5384615f, 0.5230769f, 0.5076923f, 0.4923077f, 0.4769231f, 0.4615385f, 0.4461538f, 0.4307692f, 0.4153846f, 0.4f, 0.3846154f, 0.3692308f, 0.3538462f, 0.3384615f, 0.3230769f, 0.3076923f, 0.2923077f, 0.2769231f, 0.2615385f, 0.2461538f, 0.2307692f, 0.2153846f, 0.2f, 0.1846154f, 0.1692308f, 0.1538462f, 0.1384615f, 0.1230769f, 0.1076923f, 0.0923077f, 0.0769231f, 0.0615385f, 0.0461538f, 0.0307692f, 0.0153846f };
float Sawtooth[ 128 ] = { 0.0f, 0.007874f, 0.015748f, 0.023622f, 0.0314961f, 0.0393701f, 0.0472441f, 0.0551181f, 0.0629921f, 0.0708661f, 0.0787402f, 0.0866142f, 0.0944882f, 0.1023622f, 0.1102362f, 0.1181102f, 0.1259843f, 0.1338583f, 0.1417323f, 0.1496063f, 0.1574803f, 0.1653543f, 0.1732283f, 0.1811024f, 0.1889764f, 0.1968504f, 0.2047244f, 0.2125984f, 0.2204724f, 0.2283465f, 0.2362205f, 0.2440945f, 0.2519685f, 0.2598425f, 0.2677165f, 0.2755906f, 0.2834646f, 0.2913386f, 0.2992126f, 0.3070866f, 0.3149606f, 0.3228346f, 0.3307087f, 0.3385827f, 0.3464567f, 0.3543307f, 0.3622047f, 0.3700787f, 0.3779528f, 0.3858268f, 0.3937008f, 0.4015748f, 0.4094488f, 0.4173228f, 0.4251969f, 0.4330709f, 0.4409449f, 0.4488189f, 0.4566929f, 0.4645669f, 0.4724409f, 0.480315f, 0.488189f, 0.496063f, 0.503937f, 0.511811f, 0.519685f, 0.5275591f, 0.5354331f, 0.5433071f, 0.5511811f, 0.5590551f, 0.5669291f, 0.5748031f, 0.5826772f, 0.5905512f, 0.5984252f, 0.6062992f, 0.6141732f, 0.6220472f, 0.6299213f, 0.6377953f, 0.6456693f, 0.6535433f, 0.6614173f, 0.6692913f, 0.6771654f, 0.6850394f, 0.6929134f, 0.7007874f, 0.7086614f, 0.7165354f, 0.7244094f, 0.7322835f, 0.7401575f, 0.7480315f, 0.7559055f, 0.7637795f, 0.7716535f, 0.7795276f, 0.7874016f, 0.7952756f, 0.8031496f, 0.8110236f, 0.8188976f, 0.8267717f, 0.8346457f, 0.8425197f, 0.8503937f, 0.8582677f, 0.8661417f, 0.8740157f, 0.8818898f, 0.8897638f, 0.8976378f, 0.9055118f, 0.9133858f, 0.9212598f, 0.9291339f, 0.9370079f, 0.9448819f, 0.9527559f, 0.9606299f, 0.9685039f, 0.976378f, 0.984252f, 0.992126f, 1.0f };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM11_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */
Engine_TypeSampleState Engine1;
Engine_TypeSampleState Engine2;
Engine_TypeSampleState Engine3;
Engine_TypeSampleState Engine4;
Engine_TypeSampleState Engine5;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef* htim )
{
	float Sum = (
			Engine_SampleStep( &Engine1 ) +
			Engine_SampleStep( &Engine2 ) +
			Engine_SampleStep( &Engine3 ) +
			Engine_SampleStep( &Engine4 ) +
			Engine_SampleStep( &Engine5 )
			) / 5.0f;

	TIM11->CCR1 = ( uint32_t )( Sum * 255 );
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
  MX_TIM11_Init();
  MX_TIM10_Init();
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

  TIM10->CR1 	|=	0x01;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Engine_SampleInit( &Engine1, Saw, 		128, 220.0f, 0.10f,  48000.0f );
  Engine_SampleInit( &Engine2, Saw, 		128, 220.0f, 0.05f,  48000.0f );
  Engine_SampleInit( &Engine3, Sine, 		128, 220.0f, 0.00f,  48000.0f );
  Engine_SampleInit( &Engine4, Saw, 		128, 440.0f, 0.02f,  48000.0f );
  Engine_SampleInit( &Engine5, Saw, 		128, 440.0f, 0.12f,  48000.0f );

  HAL_TIM_Base_Start_IT( &htim10 );
  while (1)
  {

	  //
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
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 0;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 1749;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

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
