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



void lcd_init(void);
void setPage(movement_type type);
void rotateMenu(movement_type type);


#endif /* SRC_LCD_H_ */
