/*
 * button.c
 *
 *  Created on: Apr 25, 2023
 *      Author: negi
 */

#include "main.h"
#include "stdio.h"





static int count_15 = 0;
static int count_14 = 0;
static int count_13 = 0;
static int count_12 = 0;


uint32_t skip_flag = 0;
uint32_t first = 0;
uint32_t prev_time_15 = 0;
uint32_t prev_time_14 = 0;
uint32_t prev_time_13 = 0;
uint32_t prev_time_12 = 0;

void led_control(void);

void button_sensing()
{
	  led_control();

	  HAL_Delay(35);
}

static int row = 0;
void led_control(void)
{
	// r1
	if(row == 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);   // Set PD11 high

		row = 1;
	}
	else if(row == 1)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);

		// r2
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);

		row = 2;
	}
	else if(row == 2)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);

		// r2
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);

		row = 3;
	}
	else if(row == 3)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);

		// r2
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);

		row = 0;
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {   // Interrupt handler for EXTI lines

	if(skip_flag == 0)
	{
		skip_flag = 1;

		first = HAL_GetTick();

		// c1  //r0
		if (GPIO_Pin == GPIO_PIN_15) {       // Check if EXTI line 15 triggered the interrupt
		// PD15 has been touched with high voltage, do something here

			uint32_t curr = HAL_GetTick();

			if(curr - prev_time_15  < 300) // 150 ms
			{
				//skip
			}
			else
			{
				count_15++;

				// change coulumn GPIO state
			}

			prev_time_15 = HAL_GetTick();
		}

		// c2 //r1
		if (GPIO_Pin == GPIO_PIN_14) {       // Check if EXTI line 15 triggered the interrupt
		// PD15 has been touched with high voltage, do something here

			uint32_t curr = HAL_GetTick();

			if(curr - prev_time_14  < 300) // 150 ms
			{
				//skip
			}
			else
			{
				count_14++;
			}

			prev_time_14 = HAL_GetTick();
		}

		// c3  //r2
		if (GPIO_Pin == GPIO_PIN_13) {       // Check if EXTI line 15 triggered the interrupt
		// PD15 has been touched with high voltage, do something here

			uint32_t curr = HAL_GetTick();

			if(curr - prev_time_13  < 300) // 150 ms
			{
				//skip
			}
			else
			{
				count_13++;
			}

			prev_time_13 = HAL_GetTick();
		}

		// c4  //r3
		if (GPIO_Pin == GPIO_PIN_12) {       // Check if EXTI line 15 triggered the interrupt
		// PD15 has been touched with high voltage, do something here

			uint32_t curr = HAL_GetTick();

			if(curr - prev_time_12  < 300) // 150 ms
			{
				//skip
			}
			else
			{
				count_12++;
			}

			prev_time_12 = HAL_GetTick();
		}
	}
	else
	{
		if( (HAL_GetTick() - first) > 15) //15ms
		{
			skip_flag = 0;
		}
	}
}
