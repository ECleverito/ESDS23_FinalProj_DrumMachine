/*
 * lcd.c
 *
 *  Created on: Apr 29, 2023
 *      Author: saura
 */

#ifndef SRC_LCD_C_
#define SRC_LCD_C_


#include "lcd.h"
#include "ssd1306.h"
#include "fonts.h"




#define OPTION_COUNT_PAGE_1					2
#define OPTION_COUNT_PAGE_2					10
#define TOTAL_OPTIONS_CAN_BE_DISPLYED		5




typedef enum {
	PAGE_1,
	PAGE_2,
	PAGE_3
} Page_number;

uint8_t currentLevel = PAGE_2;


typedef enum {
	START_PROG_SOUNDS,
	PLAY_PROG_SOUNDS
} Page1_options;

Page1_options currentSelectedOption_Page1 = START_PROG_SOUNDS;



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
	BACK
} Page2_options;

Page2_options currentSelectedOption_Page2 = HAT;



uint8_t page1_highlited_option = 0;
uint8_t page2_highlited_option = 0;


int rowLocationValue[] = {
		1, 20, 30, 40, 50
};


void lcdMenuLevel_1(int itr, movement_type type);
void lcdMenuLevel_2(int itr, movement_type type);


void lcd_init()
{
    SSD1306_Init(); // initialize the display
}


void setPage(movement_type type)
{
	currentLevel = type;
}


void buttonPressed()
{
	if(currentLevel == PAGE_1) {

	}
	else if(currentLevel == PAGE_2) {

	}
}


void rotateMenu(movement_type type)
{
	switch (currentLevel) {

		case PAGE_1:

			page1_highlited_option = (page1_highlited_option + 1) % OPTION_COUNT_PAGE_1;

			lcdMenuLevel_1(page1_highlited_option, type);
			break;

		case PAGE_2:

			page2_highlited_option = (page2_highlited_option + 1) % OPTION_COUNT_PAGE_2;

			lcdMenuLevel_2(page2_highlited_option, type);
			break;

		default:
			break;
	}
}


void perfromMovement(int* itr, movement_type type, Page_number num)
{
	int total_options = 0;


	// find total option count
	if(num == PAGE_1)
	{
		total_options = OPTION_COUNT_PAGE_1;
	}
	else if(num == PAGE_2)
	{
		total_options = OPTION_COUNT_PAGE_2;
	}


	// update itr according to the movement and page numnber
	if(type == MOVE_UP)
	{
		*itr = (*itr + 1) % total_options;
	}
	else if(type == MOVE_DOWN)
	{
		if(*itr == 0)
		{
			*itr = total_options - 1;
		}
		else
		{
			(*itr)--;
		}
	}

//	return itr;
}


void lcdMenuLevel_1(int itr, movement_type type)
{
	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();


	SSD1306_GotoXY (5, rowLocationValue[itr]); // goto 10, 10
	SSD1306_Puts ("Start prog patt", &Font_7x10, 1); // print

	perfromMovement(&itr, type, PAGE_1);

	SSD1306_GotoXY (5, rowLocationValue[itr]); // goto 10, 10
	SSD1306_Puts ("Play prog patt", &Font_7x10, 1); // print


    SSD1306_UpdateScreen(); // update screen

    HAL_Delay(2000);
}


void lcdMenuLevel_2(int itr, movement_type type)
{
	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();


	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]); // goto 10, 10
		SSD1306_Puts ("      Hat", &Font_7x10, 1); // print
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]); // goto 10, 10
		SSD1306_Puts ("      Kick", &Font_7x10, 1); // print
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      opHat", &Font_7x10, 1);
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      rim", &Font_7x10, 1);
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      snare", &Font_7x10, 1);
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      tom1", &Font_7x10, 1);
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      tom2", &Font_7x10, 1);
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      tom3", &Font_7x10, 1);
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      trash", &Font_7x10, 1);
	}

	perfromMovement(&itr, type, PAGE_2);

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      back", &Font_7x10, 1);
	}

    SSD1306_UpdateScreen(); // update screen

    HAL_Delay(2000);
}




#endif /* SRC_LCD_C_ */
