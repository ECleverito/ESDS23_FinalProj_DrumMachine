/*
 * buttons.c
 *
 *  Created on: Apr 28, 2023
 *      Author: erich
 */
#include "buttons.h"

#include "beatEngine.h"

#include "stdbool.h"
#include <string.h>

#include "main.h"
#include "stm32f411xe.h"
#include "stm32f4xx_hal_gpio.h"

extern uint16_t *currentBeat;

#ifdef DRUM_DEBUG
#else
uint32_t buttonPushStartTime[16];
bool buttonIntSkipFlag[16];
#endif


void initButtons()
{


#ifdef DRUM_DEBUG
#else
	//Initialize variables used for debouncing
	memset(buttonPushStartTime,0,BUTTON_COUNT*sizeof(buttonPushStartTime[0]));
	memset(buttonIntSkipFlag,0,BUTTON_COUNT*sizeof(buttonIntSkipFlag[0]));

	//Turn off all LEDs initially
	HAL_GPIO_WritePin(Button_LED_0_GPIO_Port, Button_LED_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_1_GPIO_Port, Button_LED_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_2_GPIO_Port, Button_LED_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_3_GPIO_Port, Button_LED_3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_4_GPIO_Port, Button_LED_4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_5_GPIO_Port, Button_LED_5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_6_GPIO_Port, Button_LED_6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_7_GPIO_Port, Button_LED_7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_8_GPIO_Port, Button_LED_8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_9_GPIO_Port, Button_LED_9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_10_GPIO_Port, Button_LED_10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_11_GPIO_Port, Button_LED_11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_12_GPIO_Port, Button_LED_12_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_13_GPIO_Port, Button_LED_13_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_14_GPIO_Port, Button_LED_14_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_15_GPIO_Port, Button_LED_15_Pin, GPIO_PIN_RESET);
#endif

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

#ifdef DRUM_DEBUG
#else
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
			//Toggle beat programming & LED
			*currentBeat ^= 0x8000;
			HAL_GPIO_TogglePin(Button_LED_0_GPIO_Port, Button_LED_0_Pin);
			break;
		case Button_1_Pin:
			*currentBeat ^= 0x4000;
			HAL_GPIO_TogglePin(Button_LED_1_GPIO_Port, Button_LED_1_Pin);
			break;
		case Button_2_Pin:
			*currentBeat ^= 0x2000;
			HAL_GPIO_TogglePin(Button_LED_2_GPIO_Port, Button_LED_2_Pin);
			break;
		case Button_3_Pin:
			*currentBeat ^= 0x1000;
			HAL_GPIO_TogglePin(Button_LED_3_GPIO_Port, Button_LED_3_Pin);
			break;
		case Button_4_Pin:
			*currentBeat ^= 0x0800;
			HAL_GPIO_TogglePin(Button_LED_4_GPIO_Port, Button_LED_4_Pin);
			break;
		case Button_5_Pin:
			*currentBeat ^= 0x0400;
			HAL_GPIO_TogglePin(Button_LED_5_GPIO_Port, Button_LED_5_Pin);
			break;
		case Button_6_Pin:
			*currentBeat ^= 0x0200;
			HAL_GPIO_TogglePin(Button_LED_6_GPIO_Port, Button_LED_6_Pin);
			break;
		case Button_7_Pin:
			*currentBeat ^= 0x0100;
			HAL_GPIO_TogglePin(Button_LED_7_GPIO_Port, Button_LED_7_Pin);
			break;
		case Button_8_Pin:
			*currentBeat ^= 0x0080;
			HAL_GPIO_TogglePin(Button_LED_8_GPIO_Port, Button_LED_8_Pin);
			break;
		case Button_9_Pin:
			*currentBeat ^= 0x0040;
			HAL_GPIO_TogglePin(Button_LED_9_GPIO_Port, Button_LED_9_Pin);
			break;
		case Button_10_Pin:
			*currentBeat ^= 0x0020;
			HAL_GPIO_TogglePin(Button_LED_10_GPIO_Port, Button_LED_10_Pin);
			break;
		case Button_11_Pin:
			*currentBeat ^= 0x0010;
			HAL_GPIO_TogglePin(Button_LED_11_GPIO_Port, Button_LED_11_Pin);
			break;
		case Button_12_Pin:
			*currentBeat ^= 0x0008;
			HAL_GPIO_TogglePin(Button_LED_12_GPIO_Port, Button_LED_12_Pin);
			break;
		case Button_13_Pin:
			*currentBeat ^= 0x0004;
			HAL_GPIO_TogglePin(Button_LED_13_GPIO_Port, Button_LED_13_Pin);
			break;
		case Button_14_Pin:
			*currentBeat ^= 0x0002;
			HAL_GPIO_TogglePin(Button_LED_14_GPIO_Port, Button_LED_14_Pin);
			break;
		case Button_15_Pin:
			*currentBeat ^= 0x0001;
			HAL_GPIO_TogglePin(Button_LED_15_GPIO_Port, Button_LED_15_Pin);
			break;
		}
	}
#endif

}

void cascadeLEDbeat(uint16_t beatProgrammingBitMask)
{

#ifdef DRUM_DEBUG
#else
	switch(beatProgrammingBitMask)
	{
	case 0x8000:
		HAL_GPIO_WritePin(Button_LED_0_GPIO_Port, Button_LED_0_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0001))
		{
			HAL_GPIO_WritePin(Button_LED_15_GPIO_Port, Button_LED_15_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x4000:
		HAL_GPIO_WritePin(Button_LED_1_GPIO_Port, Button_LED_1_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x8000))
		{
			HAL_GPIO_WritePin(Button_LED_0_GPIO_Port, Button_LED_0_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x2000:
		HAL_GPIO_WritePin(Button_LED_2_GPIO_Port, Button_LED_2_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x4000))
		{
			HAL_GPIO_WritePin(Button_LED_1_GPIO_Port, Button_LED_1_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x1000:
		HAL_GPIO_WritePin(Button_LED_3_GPIO_Port, Button_LED_3_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x2000))
		{
			HAL_GPIO_WritePin(Button_LED_2_GPIO_Port, Button_LED_2_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0800:
		HAL_GPIO_WritePin(Button_LED_4_GPIO_Port, Button_LED_4_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x1000))
		{
			HAL_GPIO_WritePin(Button_LED_3_GPIO_Port, Button_LED_3_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0400:
		HAL_GPIO_WritePin(Button_LED_5_GPIO_Port, Button_LED_5_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0800))
		{
			HAL_GPIO_WritePin(Button_LED_4_GPIO_Port, Button_LED_4_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0200:
		HAL_GPIO_WritePin(Button_LED_6_GPIO_Port, Button_LED_6_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0400))
		{
			HAL_GPIO_WritePin(Button_LED_5_GPIO_Port, Button_LED_5_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0100:
		HAL_GPIO_WritePin(Button_LED_7_GPIO_Port, Button_LED_7_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0200))
		{
			HAL_GPIO_WritePin(Button_LED_6_GPIO_Port, Button_LED_6_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0080:
		HAL_GPIO_WritePin(Button_LED_8_GPIO_Port, Button_LED_8_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0100))
		{
			HAL_GPIO_WritePin(Button_LED_7_GPIO_Port, Button_LED_7_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0040:
		HAL_GPIO_WritePin(Button_LED_9_GPIO_Port, Button_LED_9_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0080))
		{
			HAL_GPIO_WritePin(Button_LED_8_GPIO_Port, Button_LED_8_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0020:
		HAL_GPIO_WritePin(Button_LED_10_GPIO_Port, Button_LED_10_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0040))
		{
			HAL_GPIO_WritePin(Button_LED_9_GPIO_Port, Button_LED_9_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0010:
		HAL_GPIO_WritePin(Button_LED_11_GPIO_Port, Button_LED_11_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0020))
		{
			HAL_GPIO_WritePin(Button_LED_10_GPIO_Port, Button_LED_10_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0008:
		HAL_GPIO_WritePin(Button_LED_12_GPIO_Port, Button_LED_12_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0010))
		{
			HAL_GPIO_WritePin(Button_LED_11_GPIO_Port, Button_LED_11_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0004:
		HAL_GPIO_WritePin(Button_LED_13_GPIO_Port, Button_LED_13_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0008))
		{
			HAL_GPIO_WritePin(Button_LED_12_GPIO_Port, Button_LED_12_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0002:
		HAL_GPIO_WritePin(Button_LED_14_GPIO_Port, Button_LED_14_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0004))
		{
			HAL_GPIO_WritePin(Button_LED_13_GPIO_Port, Button_LED_13_Pin, GPIO_PIN_RESET);
		}
		break;
	case 0x0001:
		HAL_GPIO_WritePin(Button_LED_15_GPIO_Port, Button_LED_15_Pin, GPIO_PIN_SET);
		if(!(*currentBeat & 0x0002))
		{
			HAL_GPIO_WritePin(Button_LED_14_GPIO_Port, Button_LED_14_Pin, GPIO_PIN_RESET);
		}
		break;
	}
#endif

}

void updateLEDs()
{
#ifdef DRUM_DEBUG
#else
	uint16_t ledBitMask = BEAT_PROGRAMMING_BITMASK_INIT;

	//Turn all LEDs off
	HAL_GPIO_WritePin(Button_LED_0_GPIO_Port, Button_LED_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_1_GPIO_Port, Button_LED_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_2_GPIO_Port, Button_LED_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_3_GPIO_Port, Button_LED_3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_4_GPIO_Port, Button_LED_4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_5_GPIO_Port, Button_LED_5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_6_GPIO_Port, Button_LED_6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_7_GPIO_Port, Button_LED_7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_8_GPIO_Port, Button_LED_8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_9_GPIO_Port, Button_LED_9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_10_GPIO_Port, Button_LED_10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_11_GPIO_Port, Button_LED_11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_12_GPIO_Port, Button_LED_12_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_13_GPIO_Port, Button_LED_13_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_14_GPIO_Port, Button_LED_14_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Button_LED_15_GPIO_Port, Button_LED_15_Pin, GPIO_PIN_RESET);

	while(ledBitMask)
	{

		switch(ledBitMask&(*currentBeat))
		{
		case 0x8000:
			HAL_GPIO_WritePin(Button_LED_0_GPIO_Port, Button_LED_0_Pin, GPIO_PIN_SET);
			break;
		case 0x4000:
			HAL_GPIO_WritePin(Button_LED_1_GPIO_Port, Button_LED_1_Pin, GPIO_PIN_SET);
			break;
		case 0x2000:
			HAL_GPIO_WritePin(Button_LED_2_GPIO_Port, Button_LED_2_Pin, GPIO_PIN_SET);
			break;
		case 0x1000:
			HAL_GPIO_WritePin(Button_LED_3_GPIO_Port, Button_LED_3_Pin, GPIO_PIN_SET);
			break;
		case 0x0800:
			HAL_GPIO_WritePin(Button_LED_4_GPIO_Port, Button_LED_4_Pin, GPIO_PIN_SET);
			break;
		case 0x0400:
			HAL_GPIO_WritePin(Button_LED_5_GPIO_Port, Button_LED_5_Pin, GPIO_PIN_SET);
			break;
		case 0x0200:
			HAL_GPIO_WritePin(Button_LED_6_GPIO_Port, Button_LED_6_Pin, GPIO_PIN_SET);
			break;
		case 0x0100:
			HAL_GPIO_WritePin(Button_LED_7_GPIO_Port, Button_LED_7_Pin, GPIO_PIN_SET);
			break;
		case 0x0080:
			HAL_GPIO_WritePin(Button_LED_8_GPIO_Port, Button_LED_8_Pin, GPIO_PIN_SET);
			break;
		case 0x0040:
			HAL_GPIO_WritePin(Button_LED_9_GPIO_Port, Button_LED_9_Pin, GPIO_PIN_SET);
			break;
		case 0x0020:
			HAL_GPIO_WritePin(Button_LED_10_GPIO_Port, Button_LED_10_Pin, GPIO_PIN_SET);
			break;
		case 0x0010:
			HAL_GPIO_WritePin(Button_LED_11_GPIO_Port, Button_LED_11_Pin, GPIO_PIN_SET);
			break;
		case 0x0008:
			HAL_GPIO_WritePin(Button_LED_12_GPIO_Port, Button_LED_12_Pin, GPIO_PIN_SET);
			break;
		case 0x0004:
			HAL_GPIO_WritePin(Button_LED_13_GPIO_Port, Button_LED_13_Pin, GPIO_PIN_SET);
			break;
		case 0x0002:
			HAL_GPIO_WritePin(Button_LED_14_GPIO_Port, Button_LED_14_Pin, GPIO_PIN_SET);
			break;
		case 0x0001:
			HAL_GPIO_WritePin(Button_LED_15_GPIO_Port, Button_LED_15_Pin, GPIO_PIN_SET);
			break;
		case 0:
			break;
		}
		ledBitMask=ledBitMask>>1;
	}
#endif
}
