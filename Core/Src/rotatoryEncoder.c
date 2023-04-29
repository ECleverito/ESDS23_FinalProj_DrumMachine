/*
 * rotatoryEncoder.c
 *
 *  Created on: Apr 28, 2023
 *      Author: erich
 */

#include "rotatoryEncoder.h"
#include "lcd.h"
#include "main.h"

#include "stm32f4xx_it.h"

#include "stdint.h"
#include "stdio.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

uint16_t tempoEncoderSetpoint;

void init_rotatory_encoder(void)
{
	tempoEncoderSetpoint=TIM1->ARR;
	HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
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

uint32_t prev_pos_value = 0;

//void rotatory_sensor_lcd(void)
//{
//	if(prev_pos_value > TIM3->CNT)
//	{
//		// here means rotation happened
//		update_change_row(1);
//	}
//	else if(prev_pos_value < TIM3->CNT)
//	{
//		// here means rotation happened
//		update_change_row(1);
//	}
//	prev_pos_value = TIM3->CNT;
//}

