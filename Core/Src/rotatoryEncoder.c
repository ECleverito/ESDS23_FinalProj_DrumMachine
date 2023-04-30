/*
 * rotatoryEncoder.c
 *
 *  Created on: Apr 28, 2023
 *      Author: erich
 */

#include "rotatoryEncoder.h"
#include "lcd.h"
#include "main.h"
#include "lcd.h"

#include "stm32f4xx_it.h"

#include "stdint.h"
#include "stdio.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;


uint32_t prev_pos_value = 0;

void init_rotatory_encoder(void)
{
	TIM2->CNT=TIM1->ARR;
	HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);

	HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);


	// for lcd rotary
	TIM3->CNT = 30000;
	prev_pos_value = 30000;
}



void rotatory_sensor_sense(void)
{
	// limiting upper value
	if(TIM2->CNT > 65500)
	{
		TIM2->CNT = 65500;
	}

	// limiting lower value
	if(TIM2->CNT < 468)
	{
		TIM2->CNT = 468;
	}

	TIM1->ARR = TIM2->CNT;
}


void rotatory_sensor_lcd(void)
{
	if(prev_pos_value > TIM3->CNT)
	{
		// here means rotation happened
		rotateMenu(MOVE_UP);
	}
	else if(prev_pos_value < TIM3->CNT)
	{
		// here means rotation happened
		rotateMenu(MOVE_DOWN);
	}

	prev_pos_value = TIM3->CNT;
}
