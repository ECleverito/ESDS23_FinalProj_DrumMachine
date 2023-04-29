/*
 * beatEngine.c
 *
 *  Created on: Apr 27, 2023
 *      Author: erich
 */
#include "beatEngine.h"

#include "main.h"
#include "internalSamples.h"
#include "buttons.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_i2s.h"
#include "stm32f4xx_hal_i2s_ex.h"
#include "stdbool.h"
#include "stdio.h"
//#include "arm_math.h"

extern I2S_HandleTypeDef hi2s3;
extern TIM_HandleTypeDef htim1;

uint16_t hatBeatProgramming = 0;
uint16_t kickBeatProgramming = 0;
uint16_t opHatBeatProgramming = 0;
uint16_t rimBeatProgramming = 0;
uint16_t snareBeatProgramming = 0;
uint16_t tom1BeatProgramming = 0;
uint16_t tom2BeatProgramming = 0;
uint16_t tom3BeatProgramming = 0;
uint16_t trashBeatProgramming = 0;

uint16_t *currentBeat = NULL;

bool sendingWav = false;
bool noBeat = true;

int16_t MixingBuff[7144];

void demoBeatSetup()
{

	//Set up beat programming demo
	currentBeat = &hatBeatProgramming;
	*currentBeat = 0b1111011101110111;
	currentBeat = &kickBeatProgramming;
	*currentBeat = 0b1000000010000000;
	currentBeat = &snareBeatProgramming;
	*currentBeat = 0b0000100000001000;

}

void selectCurrentBeatProgramming()
{
	printf("Select one of the following drum samples for step programming: \r\n");

	printf("\t1 - Hat\r\n");

	printf("\t2 - Kick\r\n");

	printf("\t3 - Open Hat\r\n");

	printf("\t4 - Rim\r\n");

	printf("\t5 - Snare\r\n");

	printf("\t6 - Tom 1\r\n");

	printf("\t7 - Tom 2\r\n");

	printf("\t8 - Tom 3\r\n");

	printf("\t9 - Trash\r\n\n");

	uint8_t selectedSample = getchar();

	switch(selectedSample-48)
	{
	case 1:
		//Set Hat to current beat programming
		currentBeat = &hatBeatProgramming;
		break;
	case 2:
		//Set Kick to current beat programming
		currentBeat = &kickBeatProgramming;
		break;
	case 3:
		//Set Open Hat to current beat programming
		currentBeat = &opHatBeatProgramming;
		break;
	case 4:
		//Set Rim to current beat programming
		currentBeat = &rimBeatProgramming;
		break;
	case 5:
		//Set Snare to current beat programming
		currentBeat = &snareBeatProgramming;
		break;
	case 6:
		//Set Tom 1 to current beat programming
		currentBeat = &tom1BeatProgramming;
		break;
	case 7:
		//Set Tom 2 to current beat programming
		currentBeat = &tom2BeatProgramming;
		break;
	case 8:
		//Set Tom 3 to current beat programming
		currentBeat = &tom3BeatProgramming;
		break;
	case 9:
		//Set Trash to current beat programming
		currentBeat = &trashBeatProgramming;
		break;
	default:
		break;
	}

	updateLEDs();
}

void addToMixingBuff(int16_t *sampleData, size_t sampleDataSize)
{

	for(int i=0;i<sampleDataSize;i++)
	{
		MixingBuff[i] += sampleData[i];
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim1)
	{
		if(currentBeat!=NULL)
		{

			static uint16_t beatProgrammingBitMask=0x8000;

			memset(MixingBuff,0,sizeof(MixingBuff)/sizeof(MixingBuff[0]));

			if(hatBeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(hat_sample,7144);
				noBeat=false;
			}
			else if(kickBeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(kick_sample,7144);
				noBeat=false;
			}
			else if(snareBeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(snare_sample,7144);
				noBeat=false;
			}
			else if(opHatBeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(opHat_sample,7144);
				noBeat=false;
			}
			else if(rimBeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(rim_sample,7144);
				noBeat=false;
			}
			else if(tom1BeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(tom1_sample,7144);
				noBeat=false;
			}
			else if(tom2BeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(tom2_sample,7144);
				noBeat=false;
			}
			else if(tom3BeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(tom3_sample,7144);
				noBeat=false;
			}
			else if(trashBeatProgramming & beatProgrammingBitMask)
			{
				addToMixingBuff(trash_sample,7144);
				noBeat=false;
			}

			if(!noBeat)
			{
				noBeat = true;
				sendingWav = true;
				HAL_I2S_DMAStop(&hi2s3);
				HAL_I2S_Transmit_DMA(&hi2s3,MixingBuff,7144);
			}

			cascadeLEDbeat(beatProgrammingBitMask);

			beatProgrammingBitMask=(beatProgrammingBitMask>>1);
			if(beatProgrammingBitMask==0)
			{
				beatProgrammingBitMask=BEAT_PROGRAMMING_BITMASK_INIT;
			}
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
