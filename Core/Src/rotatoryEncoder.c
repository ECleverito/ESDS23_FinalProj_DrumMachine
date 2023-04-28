/*
 * rotatoryEncoder.c
 *
 *  Created on: Apr 28, 2023
 *      Author: erich
 */

#include "rotatoryEncoder.h"

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


