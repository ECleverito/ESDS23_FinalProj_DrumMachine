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
#include "lcd.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_i2s.h"
#include "stm32f4xx_hal_i2s_ex.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
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
uint16_t *currentPattern = NULL;

uint16_t userPattern1programming[NUM_SAMPS];
uint16_t userPattern2programming[NUM_SAMPS];
uint16_t demoBeatprogramming[NUM_SAMPS];

bool sendingWav = false;
bool noBeat = true;

int16_t MixingBuff[7144];
int16_t **samplePointers[10];

void initUserPrograms()
{
	memset(userPattern1programming,0,sizeof(userPattern1programming));
	memset(userPattern2programming,0,sizeof(userPattern2programming));
}

void loadPatternProgramming(Page3_options pattern)
{
	switch(pattern)
	{
	case User_1:
		currentPattern = userPattern1programming;
		break;

	case User_2:
		currentPattern = userPattern2programming;
		break;

	case Demo_pattern:
		memset(demoBeatprogramming,0,sizeof(demoBeatprogramming));
		//Set up beat programming demo
		demoBeatprogramming[HAT] = 0b0111011101110111;
		demoBeatprogramming[KICK] = 0b1000000010000000;
		demoBeatprogramming[SNARE] = 0b0000100000001000;
		currentPattern = demoBeatprogramming;
		break;
	}
	currentBeat = &currentPattern[HAT];

	updateLEDs();
}

void selectCurrentBeatProgramming(uint8_t selectedSample)
{
	if(selectedSample<RESET_PATTERN)
	{
		currentBeat = &currentPattern[selectedSample];
		updateLEDs();
	}

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
		if((currentBeat!=NULL)&&(currentPattern!=NULL))
		{

			bool firstSample = true;
			int numSamps=0;
			static uint16_t beatProgrammingBitMask=0x8000;

			memset(MixingBuff,0,sizeof(MixingBuff)/sizeof(MixingBuff[0]));

			if(currentPattern[HAT] & beatProgrammingBitMask)
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
			if(currentPattern[KICK] & beatProgrammingBitMask)
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
			if(currentPattern[SNARE] & beatProgrammingBitMask)
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
			if(currentPattern[OPHAT] & beatProgrammingBitMask)
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
			if(currentPattern[RIM] & beatProgrammingBitMask)
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
			if(currentPattern[TOM1] & beatProgrammingBitMask)
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
			if(currentPattern[TOM2] & beatProgrammingBitMask)
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
			if(currentPattern[TOM3] & beatProgrammingBitMask)
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
			if(currentPattern[TRASH] & beatProgrammingBitMask)
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

void resetProgramming()
{
	for(int i=0;i<RESET_PATTERN;i++)
	{
		currentPattern[i]=0;
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
