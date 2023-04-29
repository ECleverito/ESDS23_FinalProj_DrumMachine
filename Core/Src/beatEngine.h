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

void addToMixingBuff(int16_t *sampleData, size_t sampleDataSize);

#endif /* SRC_BEATENGINE_H_ */
