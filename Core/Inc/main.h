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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern const uint16_t silenceData[10];
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Button_2_Pin GPIO_PIN_2
#define Button_2_GPIO_Port GPIOE
#define Button_2_EXTI_IRQn EXTI2_IRQn
#define Button_3_Pin GPIO_PIN_3
#define Button_3_GPIO_Port GPIOE
#define Button_3_EXTI_IRQn EXTI3_IRQn
#define Button_6_Pin GPIO_PIN_6
#define Button_6_GPIO_Port GPIOE
#define Button_6_EXTI_IRQn EXTI9_5_IRQn
#define Button_0_Pin GPIO_PIN_0
#define Button_0_GPIO_Port GPIOC
#define Button_0_EXTI_IRQn EXTI0_IRQn
#define Button_1_Pin GPIO_PIN_1
#define Button_1_GPIO_Port GPIOA
#define Button_1_EXTI_IRQn EXTI1_IRQn
#define Rot_BTN_Pin GPIO_PIN_5
#define Rot_BTN_GPIO_Port GPIOA
#define Button_7_Pin GPIO_PIN_7
#define Button_7_GPIO_Port GPIOE
#define Button_7_EXTI_IRQn EXTI9_5_IRQn
#define SPI_SD_CS_Pin GPIO_PIN_15
#define SPI_SD_CS_GPIO_Port GPIOE
#define Button_8_Pin GPIO_PIN_8
#define Button_8_GPIO_Port GPIOD
#define Button_8_EXTI_IRQn EXTI9_5_IRQn
#define Button_9_Pin GPIO_PIN_9
#define Button_9_GPIO_Port GPIOD
#define Button_9_EXTI_IRQn EXTI9_5_IRQn
#define Button_10_Pin GPIO_PIN_10
#define Button_10_GPIO_Port GPIOD
#define Button_10_EXTI_IRQn EXTI15_10_IRQn
#define Button_11_Pin GPIO_PIN_11
#define Button_11_GPIO_Port GPIOD
#define Button_11_EXTI_IRQn EXTI15_10_IRQn
#define Button_12_Pin GPIO_PIN_12
#define Button_12_GPIO_Port GPIOD
#define Button_12_EXTI_IRQn EXTI15_10_IRQn
#define Button_13_Pin GPIO_PIN_13
#define Button_13_GPIO_Port GPIOD
#define Button_13_EXTI_IRQn EXTI15_10_IRQn
#define Button_14_Pin GPIO_PIN_14
#define Button_14_GPIO_Port GPIOD
#define Button_14_EXTI_IRQn EXTI15_10_IRQn
#define Button_15_Pin GPIO_PIN_15
#define Button_15_GPIO_Port GPIOD
#define Button_15_EXTI_IRQn EXTI15_10_IRQn
#define Button_LED_6_Pin GPIO_PIN_6
#define Button_LED_6_GPIO_Port GPIOC
#define Button_LED_15_Pin GPIO_PIN_8
#define Button_LED_15_GPIO_Port GPIOC
#define Button_LED_14_Pin GPIO_PIN_9
#define Button_LED_14_GPIO_Port GPIOC
#define Button_LED_3_Pin GPIO_PIN_8
#define Button_LED_3_GPIO_Port GPIOA
#define Button_LED_4_Pin GPIO_PIN_9
#define Button_LED_4_GPIO_Port GPIOA
#define Button_LED_5_Pin GPIO_PIN_10
#define Button_LED_5_GPIO_Port GPIOA
#define Button_LED_7_Pin GPIO_PIN_13
#define Button_LED_7_GPIO_Port GPIOA
#define Button_LED_8_Pin GPIO_PIN_14
#define Button_LED_8_GPIO_Port GPIOA
#define Button_LED_9_Pin GPIO_PIN_15
#define Button_LED_9_GPIO_Port GPIOA
#define Button_LED_12_Pin GPIO_PIN_11
#define Button_LED_12_GPIO_Port GPIOC
#define Button_LED_13_Pin GPIO_PIN_0
#define Button_LED_13_GPIO_Port GPIOD
#define Button_LED_11_Pin GPIO_PIN_1
#define Button_LED_11_GPIO_Port GPIOD
#define Button_LED_10_Pin GPIO_PIN_2
#define Button_LED_10_GPIO_Port GPIOD
#define DAC_RESET_Pin GPIO_PIN_4
#define DAC_RESET_GPIO_Port GPIOD
#define Button_LED_1_Pin GPIO_PIN_5
#define Button_LED_1_GPIO_Port GPIOD
#define Button_LED_2_Pin GPIO_PIN_6
#define Button_LED_2_GPIO_Port GPIOD
#define Button_LED_0_Pin GPIO_PIN_7
#define Button_LED_0_GPIO_Port GPIOD
#define Button_4_Pin GPIO_PIN_4
#define Button_4_GPIO_Port GPIOB
#define Button_4_EXTI_IRQn EXTI4_IRQn
#define Button_5_Pin GPIO_PIN_5
#define Button_5_GPIO_Port GPIOB
#define Button_5_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */
#define SD_SPI_HANDLE hspi4
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
