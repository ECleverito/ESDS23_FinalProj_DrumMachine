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
	MOVE_DOWN
} movement_type;

typedef enum {
	PAGE_1,
	PAGE_2,
	PAGE_3,
	NUM_PGS
} Page_number;

typedef enum {
	START_PROG_SOUNDS,
	PLAY_PROG_SOUNDS,
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

typedef enum {
	Demo_pattern,
	Tunak_Tunak,
	PRETTY_BOY,
	BWAHAAA,
	PAGE3_BACK,
	NUM_PG3_OPS
} Page3_options;

void lcd_init(void);
void setPage(movement_type type);
void rotateMenu(movement_type type);
void buttonPressed(void);


#endif /* SRC_LCD_H_ */
