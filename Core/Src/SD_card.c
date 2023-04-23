/*
 * SD_card.c
 *
 *  Created on: Apr 21, 2023
 *      Author: erich
 */

#include "SD_card.h"

#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2s.h"
#include "stm32f4xx_hal_i2s_ex.h"

const char samplePath[] = "/Samples";
int16_t dataBuff[BUFF_SIZE];
static volatile int16_t *outBuffPtr = dataBuff;
volatile bool dataReady;
bool firstPass;
bool stopDMA;
bool endOfData;

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

    	uint32_t buffSize;
    	uint32_t dataPos=0;
    	dataReady = false;
    	firstPass = true;
    	stopDMA = false;
    	endOfData = false;

    	while(!endOfData)
    	{
    		//Determine amount of data to be pushed to DMA buffer
    		if((dataSize-dataPos)<BUFF_SIZE)
    		{
    			buffSize=dataSize-dataPos;
    			endOfData=true;
    		}
    		else
    		{
    			buffSize=BUFF_SIZE;
    		}

    		//Pass SPI data to buffer
    		if(firstPass)
    		{

    			res = f_read(&selectedFile,outBuffPtr,buffSize*2,&numBytesRead);
    			if(res!=FR_OK)
    			{
    				printf("first f_read error\r\n");
    				break;
    			}
    			if(numBytesRead!=(buffSize*2))
    			{
    				printf("first f_read bytes read mismatch: %i\r\n",numBytesRead);
    				break;
    			}
//    			printf("First f_read of %d bytes\r\n",BUFF_SIZE*2);

    			//Initiate DMA
    			HAL_I2S_Transmit_DMA(i2s_handle,(void *)outBuffPtr,buffSize);

    			firstPass = false;
        		dataPos+=(buffSize*2);
    		}
    		else if(!endOfData)
    		{
    			__disable_irq();

    			res = f_read(&selectedFile,outBuffPtr,BUFF_SIZE,&numBytesRead);

    			__enable_irq();

    			if(res!=FR_OK)
				{
					printf("sequential f_read error\r\n");
					break;
				}
    			if(numBytesRead!=BUFF_SIZE)
    			{
    				HAL_I2S_DMAStop(i2s_handle);
    				printf("sequential f_read bytes read mismatch: %i\r\n",numBytesRead);
    				break;
    			}
//    			printf("First f_read of %d bytes\r\n",BUFF_SIZE);

        		dataPos+=BUFF_SIZE;
    		}
    		else
    		{
//    			printf("Last read!\r\n");//For debugging, remove when done
    			__disable_irq();
    			res = f_read(&selectedFile,outBuffPtr,buffSize,&numBytesRead);
    			if(res!=FR_OK)
				{
					printf("final f_read error\r\n");
				}
    			//Fill remainder of DMA buffer with zeros
    			memset(outBuffPtr+buffSize,0,(BUFF_SIZE-buffSize)*2);
    			__enable_irq();
    			break;
    		}

    		//Wait for buffer to empty a half for SD card to fill
    		while(!dataReady)
    			;
			dataReady = false;
    	}

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

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	outBuffPtr = dataBuff;
	dataReady = true;
	if(stopDMA)
	{
		HAL_I2S_DMAStop(hi2s);
	}
	else if(endOfData)
	{
		stopDMA=true;
	}
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	outBuffPtr = &dataBuff[BUFF_SIZE/2];
	dataReady = true;
	if(stopDMA)
	{
		HAL_I2S_DMAStop(hi2s);
	}
	else if(endOfData)
	{
		stopDMA=true;
	}
}
