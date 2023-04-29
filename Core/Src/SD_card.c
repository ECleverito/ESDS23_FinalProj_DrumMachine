/*
 * SD_card.c
 *
 *  Created on: Apr 21, 2023
 *      Author: erich
 */

#include "SD_card.h"

#include "internalSamples.h"
#include "beatEngine.h"

#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2s.h"
#include "stm32f4xx_hal_i2s_ex.h"

const char samplePath[] = "/Samples";
uint16_t dataBuff[BUFF_SIZE];

bool sendingWavSD = false;

//Example from FatFs lib creator elm_chan used for this implementation
//(http://elm-chan.org/fsw/ff/doc/readdir.html)
FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                res = scan_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                printf("%s/%s\n\r", path, fno.fname);
            }
        }
        printf("\n\r");
        f_closedir(&dir);
    }

    return res;
}

FRESULT userChooseFile(I2S_HandleTypeDef *i2s_handle)
{
    FRESULT res;
    DIR dir;
    static FILINFO fno;

    uint16_t fileNum=1;

	printf("Select one of the following samples to play:\r\n");

    res = f_opendir(&dir, samplePath);                       /* Open the directory */
    if (res == FR_OK)
    {
    	while(1<2)
    	{
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0)
            {
            	break;  /* Break on error or end of dir */
            }

            printf("%i. %s\n\r", fileNum++, fno.fname);

        }

        f_closedir(&dir);
    }

    printf("\r\n\nWhich file would you like to play?: ");
    scanf("%d",&fileNum);
    printf("Selected filenum: %d",fileNum);

    uint16_t counter = 0;

    res = f_opendir(&dir, samplePath);                       /* Open the directory */
    if (res == FR_OK)
    {
    	while(counter < fileNum)
    	{
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0)
            {
            	break;  /* Break on error or end of dir */
            }
//            printf("%i. %s\n\r", counter++, fno.fname);
            counter++;

        }

    	printf("\r\nSelected file: %s\r\n",fno.fname);

    	FIL selectedFile;

    	char fullSelectedFilePath[256];

    	sprintf(fullSelectedFilePath,"%s/%s",samplePath,fno.fname);

    	printf("Selected filepath: %s\r\n",fullSelectedFilePath);

    	res = f_open(&selectedFile,fullSelectedFilePath,FA_READ);
    	if(res != FR_OK)
    	{
    		printf("f_open error\r\n");
    	}

    	UINT numBytesRead;
    	UINT dataSize;
    	//Advanced read pointer to wav file data size field
    	res = f_read(&selectedFile,NULL,40,&numBytesRead);
    	if(res != FR_OK)
    	{
    		printf("f_read error(%d)\r\n",res);
    	}

    	res = f_read(&selectedFile,&dataSize,4,&numBytesRead);
    	if(res != FR_OK)
    	{
    		printf("f_read error\r\n");
    	}

    	printf("Wav file data size: %d\r\n",dataSize);

    	//Read wav file data into buffer
		res = f_read(&selectedFile,(void *)dataBuff,dataSize,&numBytesRead);
		if(res!=FR_OK)
		{
			printf("first f_read error\r\n");
		}

		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,dataBuff,(dataSize/2));

    	res = f_close(&selectedFile);
    	if(res!=FR_OK)
		{
			printf("f_close error\r\n");
		}

        res = f_closedir(&dir);
        if(res!=FR_OK)
		{
			printf("f_closedir error\r\n");
		}
    }

    return res;
}

void playInternalSample(I2S_HandleTypeDef *i2s_handle)
{
	printf("Select one of the following drum samples to play: \r\n");

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
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,hat_sample,7144);
		break;
	case 2:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,kick_sample,7144);
		break;
	case 3:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,opHat_sample,7144);
		break;
	case 4:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,opHat_sample,7144);
		break;
	case 5:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,rim_sample,7144);
		break;
	case 6:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,tom1_sample,7144);
		break;
	case 7:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,tom2_sample,7144);
		break;
	case 8:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,tom3_sample,7144);
		break;
	case 9:
		//Play Hat
		HAL_I2S_DMAStop(i2s_handle);
    	sendingWavSD = true;
		//Start DMA
		HAL_I2S_Transmit_DMA(i2s_handle,trash_sample,7144);
		break;
	default:
		break;

	}
}




