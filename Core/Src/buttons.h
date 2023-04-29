/*
 * buttons.h
 *
 *  Created on: Apr 28, 2023
 *      Author: erich
 */

#ifndef SRC_BUTTONS_H_
#define SRC_BUTTONS_H_

#include "stdint.h"
#include "beatEngine.h"

#ifdef DRUM_DEBUG
#define BUTTON_COUNT 	8
#define BEAT_PROGRAMMING_BITMASK_INIT	0x80
#else
#define BUTTON_COUNT	16
#define BEAT_PROGRAMMING_BITMASK_INIT	0x8000
#endif

#define DEBOUNCE_DELAY	100

void initButtons();

void cascadeLEDbeat(uint16_t beatProgrammingBitMask);

void updateLEDs();

#endif /* SRC_BUTTONS_H_ */
