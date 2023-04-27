/*
 * button.c
 *
 *  Created on: Apr 25, 2023
 *      Author: negi
 */

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "button.h"

uint16_t main_16_beats_var = 0;

uint32_t count[16];

uint32_t count_0 = 0;
uint32_t count14 = 0;
uint32_t count15 = 0;
uint32_t rotate_clockwise = 0;
uint32_t rotate_anti_clockwise = 0;

uint32_t gpio_pin_15_set = 0;
uint32_t gpio_pin_14_set = 0;

uint32_t pin_14_then_15 = 0;
uint32_t pin_15_then_14 = 0;

uint32_t pin_0_led = 0;

uint32_t GPIO_PIN_skip_flag[16];

uint32_t GPIO_PIN_start[16];




typedef enum {
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,
	BUTTON_10,
	BUTTON_11,
	BUTTON_12,
	BUTTON_13,
	BUTTON_14,
	BUTTON_15,
	BUTTON_16
};


uint32_t Button_Led_Lookup[][5] = {

	/*    button_no   port    pin           led_port  pin         */
		{ BUTTON_1,   GPIOD,  GPIO_PIN_15,  GPIOC,    GPIO_PIN_8 },
		{ BUTTON_2,   GPIOD,  GPIO_PIN_14,  GPIOC,    GPIO_PIN_9 },
		{ BUTTON_3,   GPIOD,  GPIO_PIN_13,  GPIOA,    GPIO_PIN_8 },
		{ BUTTON_4,   GPIOD,  GPIO_PIN_12,  GPIOA,    GPIO_PIN_9 },
		{ BUTTON_5,   GPIOD,  GPIO_PIN_11,  GPIOA,    GPIO_PIN_10 },
		{ BUTTON_6,   GPIOD,  GPIO_PIN_10,  GPIOA,    GPIO_PIN_13 },
		{ BUTTON_7,   GPIOD,  GPIO_PIN_9,   GPIOA,    GPIO_PIN_14 },
		{ BUTTON_8,   GPIOD,  GPIO_PIN_8,   GPIOA,    GPIO_PIN_15 },
		{ BUTTON_9,   GPIOE,  GPIO_PIN_7,   GPIOC,    GPIO_PIN_11 },
		{ BUTTON_10,  GPIOE,  GPIO_PIN_6,   GPIOD,    GPIO_PIN_0 },
		{ BUTTON_11,  GPIOE,  GPIO_PIN_5,   GPIOD,    GPIO_PIN_1 },
		{ BUTTON_12,  GPIOE,  GPIO_PIN_4,   GPIOD,    GPIO_PIN_2 },
		{ BUTTON_13,  GPIOE,  GPIO_PIN_3,   GPIOD,    GPIO_PIN_3 },
		{ BUTTON_14,  GPIOE,  GPIO_PIN_2,   GPIOD,    GPIO_PIN_5 },
		{ BUTTON_15,  GPIOE,  GPIO_PIN_1,   GPIOD,    GPIO_PIN_6 },
		{ BUTTON_16,  GPIOE,  GPIO_PIN_0,   GPIOD,    GPIO_PIN_7 }

};



int skip = 0, start = 0;

#define ROT_A_GPIO_Port GPIOD
#define ROT_B_GPIO_Port GPIOD

#define ROT_A_Pin GPIO_PIN_13
#define ROT_B_Pin GPIO_PIN_14

int rot_new_state = 0;
int rot_old_state = 0, rot_cnt=0, rot_cnt_prev = 0, rot_cnt_change = 0, my_count= 0;

int rot_start = 0, rot_skip_flag=0;


void init_button()
{
	memset(count, 0, 16);
	memset(GPIO_PIN_start, 0, 16);
	memset(GPIO_PIN_skip_flag, 0, 16);
}


bool get_skip_flag_status()
{
	if( (HAL_GetTick() - GPIO_PIN_start[i]) > 500) //10ms
	{
		GPIO_PIN_skip_flag[i] = 0;
	}

}


// External interrupts from rotary encoder
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {   // Interrupt handler for EXTI lines

	for(int i = 0; i < 15; i++)
	{
		if (GPIO_Pin == (GPIO_PIN_15 >> i))
		{
			if( (HAL_GetTick() - GPIO_PIN_start[i]) > 500) //10ms
			{
				GPIO_PIN_skip_flag[i] = 0;
			}

			if(GPIO_PIN_skip_flag[i] == 0)
			{
				GPIO_PIN_skip_flag[i] = 1;

				// Check if EXTI line 15 triggered the interrupt
				// PD15 has been touched with high voltage, do something here
				GPIO_PIN_start[i] = HAL_GetTick();

				// for testing
#ifdef testing
				count[i]++;
#endif

				// toggle the bit corresponding to specifc button
				main_16_beats_var ^= (0x0001 << i);

//				if ((main_16_beats_var & 0x0001) == 0x0001)
				if ((main_16_beats_var & (0x0001 << i)) == (0x0001 << i))
				{
					// LED ON
					HAL_GPIO_WritePin(Button_Led_Lookup[i][3], Button_Led_Lookup[i][4], GPIO_PIN_SET);

					pin_0_led = 1;
				}
//				if ((main_16_beats_var | (0xFFFE) == 0xFFFE)
				if ((main_16_beats_var >> i) | (0xFFFE) == 0xFFFE)
				{
					// LED OFF
					HAL_GPIO_WritePin(Button_Led_Lookup[i][3], Button_Led_Lookup[i][4], GPIO_PIN_RESET);
//					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

					pin_0_led = 0;
				}

			}
		}
	}
}

//// External interrupts from rotary encoder
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {   // Interrupt handler for EXTI lines
//
//	for(int i = 0; i < 15; i++)
//	{
//		if (GPIO_Pin == (GPIO_PIN_15 >> i))
//		{
//			if( (HAL_GetTick() - GPIO_PIN_start[i]) > 500) //10ms
//			{
//				GPIO_PIN_skip_flag[i] = 0;
//			}
//
//			if(GPIO_PIN_skip_flag[i] == 0)
//			{
//				GPIO_PIN_skip_flag[i] = 1;
//
//				// Check if EXTI line 15 triggered the interrupt
//				// PD15 has been touched with high voltage, do something here
//				GPIO_PIN_start[i] = HAL_GetTick();
//
//				// for testing
//#ifdef testing
//				count[i]++;
//#endif
//
//				main_16_beats_var ^= (0x0001 << i);
//
//				if ((main_16_beats_var & 0x0001) == 0x0001)
//				{
//					// LED ON
//					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
//
//					pin_0_led = 1;
//				}
//				if ((main_16_beats_var | 0xFFFE) == 0xFFFE)
//				{
//					// LED OFF
//					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
//
//					pin_0_led = 0;
//				}
//
//			}
//		}
//	}
//}
