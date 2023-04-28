/*
 * buttons.c
 *
 *  Created on: Apr 28, 2023
 *      Author: erich
 */
#include "buttons.h"

#include "stdint.h"
#include "stdbool.h"

#include "main.h"
#include "stm32f411xe.h"
#include "stm32f4xx_hal_gpio.h"

uint32_t buttonPushStartTime[16];
bool buttonIntSkipFlag[16];

void initButtonDebounceVars()
{
	memset(buttonPushStartTime,0,BUTTON_COUNT*sizeof(buttonPushStartTime[0]));
	memset(buttonIntSkipFlag,0,BUTTON_COUNT*sizeof(buttonIntSkipFlag[0]));
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	int pinNum;
	switch(GPIO_Pin)
	{
	case Button_0_Pin:
		pinNum=0;
		break;
	case Button_1_Pin:
		pinNum=1;
		break;
	case Button_2_Pin:
		pinNum=2;
		break;
	case Button_3_Pin:
		pinNum=3;
		break;
	case Button_4_Pin:
		pinNum=4;
		break;
	case Button_5_Pin:
		pinNum=5;
		break;
	case Button_6_Pin:
		pinNum=6;
		break;
	case Button_7_Pin:
		pinNum=7;
		break;
	case Button_8_Pin:
		pinNum=8;
		break;
	case Button_9_Pin:
		pinNum=9;
		break;
	case Button_10_Pin:
		pinNum=10;
		break;
	case Button_11_Pin:
		pinNum=11;
		break;
	case Button_12_Pin:
		pinNum=12;
		break;
	case Button_13_Pin:
		pinNum=13;
		break;
	case Button_14_Pin:
		pinNum=14;
		break;
	case Button_15_Pin:
		pinNum=15;
		break;
	}

	if( (HAL_GetTick() - buttonPushStartTime[pinNum]) > DEBOUNCE_DELAY) //10ms
	{
		buttonIntSkipFlag[pinNum] = false;
	}

	if(buttonIntSkipFlag[pinNum] == false)
	{
		buttonIntSkipFlag[pinNum] = true;

		// Check if EXTI line 15 triggered the interrupt
		// PD15 has been touched with high voltage, do something here
		buttonPushStartTime[pinNum] = HAL_GetTick();

		switch(GPIO_Pin)
		{
		case Button_0_Pin:
			HAL_GPIO_TogglePin(Button_LED_0_GPIO_Port, Button_LED_0_Pin);
			break;
		case Button_1_Pin:
			HAL_GPIO_TogglePin(Button_LED_1_GPIO_Port, Button_LED_1_Pin);
			break;
		case Button_2_Pin:
			HAL_GPIO_TogglePin(Button_LED_2_GPIO_Port, Button_LED_2_Pin);
			break;
		case Button_3_Pin:
			HAL_GPIO_TogglePin(Button_LED_3_GPIO_Port, Button_LED_3_Pin);
			break;
		case Button_4_Pin:
			HAL_GPIO_TogglePin(Button_LED_4_GPIO_Port, Button_LED_4_Pin);
			break;
		case Button_5_Pin:
			HAL_GPIO_TogglePin(Button_LED_5_GPIO_Port, Button_LED_5_Pin);
			break;
		case Button_6_Pin:
			HAL_GPIO_TogglePin(Button_LED_6_GPIO_Port, Button_LED_6_Pin);
			break;
		case Button_7_Pin:
			HAL_GPIO_TogglePin(Button_LED_7_GPIO_Port, Button_LED_7_Pin);
			break;
		case Button_8_Pin:
			HAL_GPIO_TogglePin(Button_LED_8_GPIO_Port, Button_LED_8_Pin);
			break;
		case Button_9_Pin:
			HAL_GPIO_TogglePin(Button_LED_9_GPIO_Port, Button_LED_9_Pin);
			break;
		case Button_10_Pin:
			HAL_GPIO_TogglePin(Button_LED_10_GPIO_Port, Button_LED_10_Pin);
			break;
		case Button_11_Pin:
			HAL_GPIO_TogglePin(Button_LED_11_GPIO_Port, Button_LED_11_Pin);
			break;
		case Button_12_Pin:
			HAL_GPIO_TogglePin(Button_LED_12_GPIO_Port, Button_LED_12_Pin);
			break;
		case Button_13_Pin:
			HAL_GPIO_TogglePin(Button_LED_13_GPIO_Port, Button_LED_13_Pin);
			break;
		case Button_14_Pin:
			HAL_GPIO_TogglePin(Button_LED_14_GPIO_Port, Button_LED_14_Pin);
			break;
		case Button_15_Pin:
			HAL_GPIO_TogglePin(Button_LED_15_GPIO_Port, Button_LED_15_Pin);
			break;
		}
	}
}
