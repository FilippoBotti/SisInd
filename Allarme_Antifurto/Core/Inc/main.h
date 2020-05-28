/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define R1_Pin GPIO_PIN_0
#define R1_GPIO_Port GPIOC
#define R2_Pin GPIO_PIN_1
#define R2_GPIO_Port GPIOC
#define PIR_Pin GPIO_PIN_3
#define PIR_GPIO_Port GPIOC
#define PIR_EXTI_IRQn EXTI3_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define R4_Pin GPIO_PIN_4
#define R4_GPIO_Port GPIOA
#define C1_Pin GPIO_PIN_5
#define C1_GPIO_Port GPIOA
#define C1_EXTI_IRQn EXTI9_5_IRQn
#define WHITE_LED_Pin GPIO_PIN_6
#define WHITE_LED_GPIO_Port GPIOA
#define PIN_D7_Pin GPIO_PIN_5
#define PIN_D7_GPIO_Port GPIOC
#define R3_Pin GPIO_PIN_0
#define R3_GPIO_Port GPIOB
#define RED_LED_Pin GPIO_PIN_10
#define RED_LED_GPIO_Port GPIOB
#define PIN_D4_Pin GPIO_PIN_12
#define PIN_D4_GPIO_Port GPIOB
#define PIN_EN_Pin GPIO_PIN_6
#define PIN_EN_GPIO_Port GPIOC
#define C3_Pin GPIO_PIN_7
#define C3_GPIO_Port GPIOC
#define C3_EXTI_IRQn EXTI9_5_IRQn
#define PIN_RS_Pin GPIO_PIN_8
#define PIN_RS_GPIO_Port GPIOC
#define C4_Pin GPIO_PIN_9
#define C4_GPIO_Port GPIOA
#define C4_EXTI_IRQn EXTI9_5_IRQn
#define PIN_D5_Pin GPIO_PIN_11
#define PIN_D5_GPIO_Port GPIOA
#define PIN_D6_Pin GPIO_PIN_12
#define PIN_D6_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define C2_Pin GPIO_PIN_6
#define C2_GPIO_Port GPIOB
#define C2_EXTI_IRQn EXTI9_5_IRQn
#define GREEN_LED_Pin GPIO_PIN_8
#define GREEN_LED_GPIO_Port GPIOB
#define YELLOW_LED_Pin GPIO_PIN_9
#define YELLOW_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
