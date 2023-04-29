/*
 * lcd.c
 *
 *  Created on: Apr 29, 2023
 *      Author: saura
 */

#ifndef SRC_LCD_C_
#define SRC_LCD_C_


#include "ssd1306.h"
#include "fonts.h"




#define OPTION_COUNT_PAGE_1		2
#define OPTION_COUNT_PAGE_2		10

#define TOTAL_OPTIONS_CAN_BE_DISPLYED	5

typedef enum {
	PAGE_1,
	PAGE_2,
	PAGE_3
}Page_number;

uint8_t currentLevel = PAGE_2;

uint8_t page1_highlited_option = 0;
uint8_t page2_highlited_option = 0;




char* samples[] = {
		"hat",
		"kick",
		"opHat",
		"rim",
		"snare",
		"tom1",
		"tom2",
		"tom3",
		"trash"
};


int rowLocationValue[] = {
		1, 20, 30, 40, 50
};


void lcd_init()
{
  SSD1306_Init(); // initialize the displ~ay
}


void update_change_row()
{
	switch (currentLevel) {

		case PAGE_1:

			page1_highlited_option = (page1_highlited_option + 1) % OPTION_COUNT_PAGE_1;

			lcdMenuLevel_1(page1_highlited_option);
			break;

		case PAGE_2:

			page2_highlited_option = (page2_highlited_option + 1) % OPTION_COUNT_PAGE_2;

			lcdMenuLevel_2(page2_highlited_option);
			break;

		default:
			break;
	}
}


void lcdMenuLevel_1(int itr)
{
	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();


	SSD1306_GotoXY (5, rowLocationValue[itr]); // goto 10, 10
	SSD1306_Puts ("Start prog patt", &Font_7x10, 1); // print

	itr = (itr + 1) % OPTION_COUNT_PAGE_1;

	SSD1306_GotoXY (5, rowLocationValue[itr]); // goto 10, 10
	SSD1306_Puts ("Play prog patt", &Font_7x10, 1); // print


    SSD1306_UpdateScreen(); // update screen

    HAL_Delay(2000);
}


void lcdMenuLevel_2(int itr)
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

	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]); // goto 10, 10
		SSD1306_Puts ("      Kick", &Font_7x10, 1); // print
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      opHat", &Font_7x10, 1);
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      rim", &Font_7x10, 1);
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      snare", &Font_7x10, 1);
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      tom1", &Font_7x10, 1);
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      tom2", &Font_7x10, 1);
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      tom3", &Font_7x10, 1);
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      trash", &Font_7x10, 1);
	}

  	itr = (itr + 1) % OPTION_COUNT_PAGE_2;

	if(itr < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		SSD1306_GotoXY (5, rowLocationValue[itr]);
		SSD1306_Puts ("      back", &Font_7x10, 1);
	}

    SSD1306_UpdateScreen(); // update screen

    HAL_Delay(2000);
}



#endif /* SRC_LCD_C_ */
