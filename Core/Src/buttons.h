/*
 * buttons.h
 *
 *  Created on: Apr 28, 2023
 *      Author: erich
 */

#ifndef SRC_BUTTONS_H_
#define SRC_BUTTONS_H_

#include "stdint.h"

#define BUTTON_COUNT	16

#define DEBOUNCE_DELAY	100

void initButtons();

void cascadeLEDbeat(uint16_t beatProgrammingBitMask);

#endif /* SRC_BUTTONS_H_ */
