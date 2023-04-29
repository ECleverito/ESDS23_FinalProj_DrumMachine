/*
 * beatEngine.c
 *
 *  Created on: Apr 27, 2023
 *      Author: erich
 */
#include "beatEngine.h"

#include "internalSamples.h"
#include "buttons.h"

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_i2s.h"
#include "stm32f4xx_hal_i2s_ex.h"
#include "stdbool.h"

extern I2S_HandleTypeDef hi2s3;
extern TIM_HandleTypeDef htim1;

//uint16_t stepBuffer[7144];

uint16_t hatBeatProgramming = 0;
uint16_t kickBeatProgramming = 0;
uint16_t opHatBeatProgramming = 0;
uint16_t rimBeatProgramming = 0;
uint16_t snareBeatProgramming = 0;
uint16_t tom1BeatProgramming = 0;
uint16_t tom2BeatProgramming = 0;
uint16_t tom3BeatProgramming = 0;
uint16_t trashBeatProgramming = 0;

uint16_t *currentBeat = &hatBeatProgramming;

bool sendingWav = false;

void demoBeatSetup()
{

	//Set up beat programming demo
	*currentBeat = 0b0111011101110111;
	currentBeat = &kickBeatProgramming;
	*currentBeat = 0b1000000010000000;
	currentBeat = &snareBeatProgramming;
	*currentBeat = 0b0000100000001000;

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim1)
	{

		static uint16_t beatProgrammingBitMask=0x8000;

		if(hatBeatProgramming & beatProgrammingBitMask)
		{
			HAL_I2S_DMAStop(&hi2s3);
			sendingWav = true;
			//Start DMA
			HAL_I2S_Transmit_DMA(&hi2s3,hat_sample,7144);
		}
		else if(kickBeatProgramming & beatProgrammingBitMask)
		{
			HAL_I2S_DMAStop(&hi2s3);
			sendingWav = true;
			//Start DMA
			HAL_I2S_Transmit_DMA(&hi2s3,kick_sample,7144);
		}
		else if(snareBeatProgramming & beatProgrammingBitMask)
		{
			HAL_I2S_DMAStop(&hi2s3);
			sendingWav = true;
			//Start DMA
			HAL_I2S_Transmit_DMA(&hi2s3,snare_sample,7144);
		}

		cascadeLEDbeat(beatProgrammingBitMask);

		beatProgrammingBitMask=(beatProgrammingBitMask>>1);
		if(beatProgrammingBitMask==0)
		{
			beatProgrammingBitMask=BEAT_PROGRAMMING_BITMASK_INIT;
		}

	}
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{

	if(sendingWav)
	{
		sendingWav=false;
		HAL_I2S_DMAStop(&hi2s3);
		HAL_I2S_Transmit_DMA(&hi2s3, silenceData, 10);
	}

}
