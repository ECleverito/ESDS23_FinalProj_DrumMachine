/*
 * CS43L22_DAC.c
 *
 *  Created on: Apr 19, 2023
 *      Author: erich
 */

#include "CS43L22_DAC.h"

void dac_powerup_seq(I2C_HandleTypeDef *I2C_handle)
{
	//RESET line should already be set high by the PD4 HAL init routine
	uint8_t initValHolder = INIT_SEQ_VAL_1;
	HAL_I2C_Mem_Write(I2C_handle,DAC_ADDR,INIT_SEQ_REG_1,1,&initValHolder,1,UINT32_MAX);
	initValHolder = INIT_SEQ_VAL_2;
	HAL_I2C_Mem_Write(I2C_handle,DAC_ADDR,INIT_SEQ_REG_2,1,&initValHolder,1,UINT32_MAX);
	initValHolder = INIT_SEQ_VAL_3;
	HAL_I2C_Mem_Write(I2C_handle,DAC_ADDR,INIT_SEQ_REG_3,1,&initValHolder,1,UINT32_MAX);
	initValHolder = INIT_SEQ_VAL_4;
	HAL_I2C_Mem_Write(I2C_handle,DAC_ADDR,INIT_SEQ_REG_4,1,&initValHolder,1,UINT32_MAX);
	initValHolder = INIT_SEQ_VAL_5;
	HAL_I2C_Mem_Write(I2C_handle,DAC_ADDR,INIT_SEQ_REG_5,1,&initValHolder,1,UINT32_MAX);

}

uint8_t readDACreg(I2C_HandleTypeDef *I2C_handle, uint8_t regAddr, uint8_t len)
{
	//Aborted writed to set register to read
	HAL_I2C_Master_Transmit(I2C_handle,DAC_ADDR,&regAddr,1,UINT32_MAX);

	//Read from DAC with desired address set
	uint8_t regContent;
	HAL_I2C_Master_Receive(I2C_handle,DAC_ADDR,&regContent,len,UINT32_MAX);

	return regContent;
}

void configureDAC()
{
	uint8_t cfgValHolder = PWR_UP_VAL;
	HAL_I2C_Mem_Write(I2C_handle,DAC_ADDR,PWR_CTL_1_REG,1,&initValHolder,1,UINT32_MAX);

}
