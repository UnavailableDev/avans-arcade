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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM3_Init(void);
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
  MX_SPI1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  // correct byte for led control
  uint16_t pos_x = 310; //0b0000 0001 0011 0110
  uint16_t pos_y = 210;

  uint8_t left = 0;
  uint8_t right = 0;
  uint8_t up = 0;
  uint8_t down = 0;

  uint8_t tileMap[30][40] =
  {
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 },
		  {1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1,1,1 }



  };

  uint8_t pos_x_bit[2];
  uint8_t pos_y_bit[2];
  uint8_t data_send[3];

  int tileX;
  int tileY;





  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

		//shift int into 2 8bit u_int
		pos_x_bit[1] = pos_x & 0xff;
		pos_x_bit[0] = (pos_x >> 8);

		pos_y_bit[1] = pos_y & 0xff;
		pos_y_bit[0] = (pos_y >> 8);

		// simplify coor for tilemap
		tileX = pos_x / 20;
		tileY = pos_y / 16;


		//read buttons 4 times
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
		{
			left++;
		}
		else
		{
			left = 0;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 1)
		 {
			right++;
		 }
		else
		{
			right = 0;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 1)
		{
			up++;
		}
		else
		{
			up = 0;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == 1)
		{
			down++;
		}
		else
		{
			down = 0;
		}
		// compare position x/y with tilemap for collision
		if(left > 10)
		{
			if(tileMap[tileY][tileX] == 1)
			{
				left = 0;
			}
			else
			{
				pos_x--;
			}
			left = 0;
		}
		if(right > 10)
		{
			if(tileMap[tileY][tileX+1] == 1)
			{
				right = 0;
			}
			else
			{
				pos_x++;
			}
			right = 0;
		}
		if(up > 10)
		{
			if(tileMap[tileY+1][tileX] == 1)
			{
				up = 0;
			}
			else
			{
				pos_y++;
			}
		up = 0;
		}
		if(down > 10)
		{
			if( tileMap[tileY][tileX] == 1)
			{
				down = 0;
			}
			else
			{
				pos_y--;
			}
			down = 0;
		}
		// send data via SPI
		data_send[0] = 0b00000000; // first byte is address
		data_send[1] = pos_y_bit[0] ;
		data_send[2] = pos_y_bit[1];
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi1, data_send, 3, HAL_MAX_DELAY); //3*8 bit
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		data_send[0] = 0b01000000; // first byte is address
		data_send[1] = pos_x_bit[0] ;
		data_send[2] = pos_x_bit[1];
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi1, data_send, 3, HAL_MAX_DELAY); //3*8 bit
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);


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
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);

  /*Configure GPIO pin : PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 PB6 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
