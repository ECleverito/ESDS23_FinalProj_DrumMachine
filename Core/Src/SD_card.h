/*
 * SD_card.h
 *
 *  Created on: Apr 21, 2023
 *      Author: erich
 */

#ifndef SRC_SD_CARD_H_
#define SRC_SD_CARD_H_

#define BUFF_SIZE 16384

#include "fatfs.h"

FRESULT scan_files(char* path);

FRESULT userChooseFile(I2S_HandleTypeDef *i2s_handle);

#endif /* SRC_SD_CARD_H_ */
