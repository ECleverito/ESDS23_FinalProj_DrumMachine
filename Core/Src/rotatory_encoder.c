/*
 * rotatory_encoder.c
 *
 *  Created on: Apr 25, 2023
 *      Author: negi
 */

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "rotatory_encoder.h"




extern TIM_HandleTypeDef htim3;


static uint32_t r_count = 0;




void init_rotatory_encoder(void)
{
	HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
}

void rotatory_sensor_sense(void)
{
	// limiting upper value
	if(TIM3->CNT > 90)
	{
		TIM3->CNT = 90;
	}

	// limiting lower value
	if(TIM3->CNT < 10)
	{
		TIM3->CNT = 10;
	}

	r_count = TIM3->CNT;
}

uint32_t get_rotatory_sensor_value(void)
{
	return r_count;
}
