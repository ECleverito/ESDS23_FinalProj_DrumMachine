/*
 * CS43L22_DAC.h
 *
 *  Created on: Apr 19, 2023
 *      Author: erich
 */

#pragma once

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

#define DAC_ADDR 0x94

//Init sequence values
#define INIT_SEQ_REG_1	0x99
#define INIT_SEQ_VAL_1	0x00
#define INIT_SEQ_REG_2	0x80
#define INIT_SEQ_VAL_2	0x47
#define INIT_SEQ_REG_3	0x32
#define INIT_SEQ_VAL_3	0x80
#define INIT_SEQ_REG_4	0x32
#define INIT_SEQ_VAL_4	0x00
#define INIT_SEQ_REG_5	0x00
#define INIT_SEQ_VAL_5	0x00

//Register map
#define	CHIP_ID_AND_REV_REG	0x01

#define PWR_CTL_1_REG	0x02
#define PWR_UP_VAL		0x9E
#define PWR_DN_VAL		0x01

#define PWR_CTL_2_REG	0x04
#define HP_AB_ALWYS_ON	0xA0

#define CLK_CTL_REG		0x05
#define AUTO_DTCT_DS	0x00
#define AUTO_DTCT_EN	0x01
#define SNGL_SPD_MOD	0x20

#define IX_CTL_1_REG	0x06
#define SLVE_MOD_MSK	0x7F
#define MSTER_MOD		0x80
#define INV_SCLK		0x40
#define I2S_MOD			0x04
#define SIXTEEN_BIT_MOD	0x03
#define SCLK_EQ_MCLK	0x40

#define MISC_CTL_REG		0x0E
#define PASSTHRU_ANLG_EN	0xC0
#define SOFTRAMP_EN			0x02

#define PASSTHRU_VOL_REG	0x15
#define NEG_60_DB			0x88

#define PASSTHRU_SELECT_REG	0x09
#define AIN1_EN				0x01
#define AIN2_EN				0x02
#define AIN3_EN				0x04
#define AIN4_EN				0x08

#include <stdint.h>

void dac_powerup_seq(I2C_HandleTypeDef *I2C_handle);

uint8_t readDACreg(I2C_HandleTypeDef *I2C_handle, uint8_t regAddr, uint8_t len);

void configureDAC(I2C_HandleTypeDef *I2C_handle);
