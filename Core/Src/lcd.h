/*
 * lcd.h
 *
 *  Created on: Apr 29, 2023
 *      Author: saura
 */

#ifndef SRC_LCD_H_
#define SRC_LCD_H_

typedef enum {
	MOVE_UP,
	MOVE_DOWN,
	NO_ROT_MVMT
} rotatatory_encoder_evt_t;

typedef enum {
	PAGE_1,
	PAGE_2,
	PAGE_3,
	NUM_PGS
} Page_number;

typedef enum {
	SELECT_PATTERNS,
	PROGRAM_PATTERNS,
	NUM_PG1_OPS
} Page1_options;

typedef enum {
	HAT,
	KICK,
	OPHAT,
	RIM,
	SNARE,
	TOM1,
	TOM2,
	TOM3,
	TRASH,
	RESET_PATTERN,
	PAGE2_BACK,
	NUM_PG2_OPS
} Page2_options;

#define NUM_SAMPS (NUM_PG2_OPS-1)

typedef enum {
	User_1,
	User_2,
	Demo_pattern,
	Tunak_Tunak,
	PRETTY_BOY,
	BWAHAAA,
	PAGE3_BACK,
	NUM_PG3_OPS
} Page3_options;

void lcd_init(void);
void setPage(rotatatory_encoder_evt_t type);
void rotateMenu(rotatatory_encoder_evt_t type);
void buttonPressed(void);


#endif /* SRC_LCD_H_ */
