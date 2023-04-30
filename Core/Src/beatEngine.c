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
//Considered using vector addition methods from CMSIS libs but these
//require 32-bit float format sample data

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
int16_t **samplePointers[10];

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

void selectCurrentBeatProgramming(uint8_t selectedSample)
{
	switch(selectedSample)
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

void addToMixingBuff_Vttoth(int16_t *sampleData, size_t sampleDataSize)
{
	//Example from https://stackoverflow.com/questions/12089662/mixing-16-bit-linear-pcm-streams-and-avoiding-clipping-overflow

	for(int i=0;i<sampleDataSize;i++)
	{
		int a = MixingBuff[i];
		int b = sampleData[i];
		int res;
		// Make both samples unsigned (0..65535)
		a+=32768;
		b+=32768;

		// Pick the equation
		if((a < 32768) || (b < 32768))
		{
		    // Viktor's first equation when both sources are "quiet"
		    // (i.e. less than middle of the dynamic range)
			res = (a * b) / 32768;
		}
		else
		{
		    // Viktor's second equation when one or both sources are loud
			res = (2 * (a + b)) - (a * b) - 65536;
		}

		// Output is unsigned (0..65536) so convert back to signed (-32768..32767)
		if (res == 65536) res = 65535;
		MixingBuff[i] = (res-32768);
	}



}

void addToMixingBuff(int16_t *sampleData, size_t sampleDataSize)
{
	for(int i=0;i<sampleDataSize;i++)
	{
		int res = (MixingBuff[i]/2+sampleData[i]/2);
		if(res>INT16_MAX)
		{
			MixingBuff[i]=INT16_MAX;
		}
		else if(res<INT16_MIN)
		{
			MixingBuff[i]=INT16_MIN;
		}
		else
		{
			MixingBuff[i]=res;
		}

	}
}

void addToMixingBuff_nSamples(int16_t **samplePointers, size_t sampleDataSize, uint8_t sampleNum)
{
	int dataHolder;

	for(int x=0;x<sampleDataSize;x++)
	{
		for(int y=0;y<sampleNum;y++)
		{
			dataHolder+=(*samplePointers[x]/sampleNum);
		}

		if(dataHolder>INT16_MAX)
		{
			MixingBuff[x]=INT16_MAX;
		}
		else if(dataHolder<INT16_MIN)
		{
			MixingBuff[x]=INT16_MIN;
		}
		else
		{
			MixingBuff[x]=dataHolder;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim1)
	{
		if(currentBeat!=NULL)
		{

			bool firstSample = true;
			int numSamps=0;
			static uint16_t beatProgrammingBitMask=0x8000;

			memset(MixingBuff,0,sizeof(MixingBuff)/sizeof(MixingBuff[0]));

			if(hatBeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,hat_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(hat_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(kickBeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,kick_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(kick_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(snareBeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,snare_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(snare_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(opHatBeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,opHat_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(opHat_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(rimBeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,rim_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(rim_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(tom1BeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,tom1_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(tom1_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(tom2BeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,tom2_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(tom2_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(tom3BeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,tom3_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(tom3_sample,7144);
				}
				noBeat=false;
				numSamps++;
			}
			if(trashBeatProgramming & beatProgrammingBitMask)
			{
				if(firstSample)
				{
					memcpy(MixingBuff,trash_sample,7144*2);
					firstSample=false;
				}
				else
				{
					addToMixingBuff(trash_sample,7144);
				}
				noBeat=false;
				numSamps++;
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
