/*
 * beatEngine.h
 *
 *  Created on: Apr 27, 2023
 *      Author: erich
 */

#ifndef SRC_BEATENGINE_H_
#define SRC_BEATENGINE_H_

#include "stdint.h"
#include "stddef.h"

//#define DRUM_DEBUG	1

void demoBeatSetup();

void selectCurrentBeatProgramming();

void addToMixingBuff_primitive(int16_t *sampleData, size_t sampleDataSize);

void addToMixingBuff_nSamples(int16_t **samplePointers, size_t sampleDataSize, uint8_t sampleNum);

#endif /* SRC_BEATENGINE_H_ */
