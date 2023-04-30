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
#include "beatEngine.h"




#define OPTION_COUNT_PAGE_1					2
#define OPTION_COUNT_PAGE_2					10
#define OPTION_COUNT_PAGE_3					5
#define TOTAL_OPTIONS_CAN_BE_DISPLYED		5




typedef enum {
	PAGE_1,
	PAGE_2,
	PAGE_3
} Page_number;

uint8_t currentLevel = PAGE_1;


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
	PAGE2_BACK
} Page2_options;

Page2_options currentSelectedOption_Page2 = HAT;


typedef enum {
	demo_pattern,
	Tunak_Tunak,
	PRETTY_BOY,
	BWAHAAA,
	PAGE3_BACK
} Page3_options;

Page3_options currentSelectedOption_Page3 = demo_pattern;


uint8_t page1_highlited_option = 0;
uint8_t page2_highlited_option = 0;
uint8_t page3_highlited_option = 0;


int rowLocationValue[] = {
		1, 20, 30, 40, 50
};


void lcdMenuLevel_1(int itr, movement_type type);
void lcdMenuLevel_2(int itr, movement_type type);
void lcdMenuLevel_3(int itr, movement_type type);


void defaultPage1_display()
{
    SSD1306_Init(); // initialize the display

	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();

	SSD1306_GotoXY (5, rowLocationValue[0]);
	SSD1306_Puts ("Start prog patt", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[1]);
	SSD1306_Puts ("Play prog patt", &Font_7x10, 1);

    SSD1306_UpdateScreen(); // update screen
}


void defaultPage2_display()
{
    SSD1306_Init(); // initialize the display

	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();


	SSD1306_GotoXY (5, rowLocationValue[0]);
	SSD1306_Puts ("      Hat", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[1]);
	SSD1306_Puts ("      Kick", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[2]);
	SSD1306_Puts ("      opHat", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[3]);
	SSD1306_Puts ("      rim", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[4]);
	SSD1306_Puts ("      snare", &Font_7x10, 1);

    SSD1306_UpdateScreen(); // update screen
}


void defaultPage3_display()
{
    SSD1306_Init(); // initialize the display

	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();


	SSD1306_GotoXY (5, rowLocationValue[0]);
	SSD1306_Puts ("demo pattern", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[1]);
	SSD1306_Puts ("Tunak Tunak", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[2]);
	SSD1306_Puts ("PRETTY BOY", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[3]);
	SSD1306_Puts ("BWAHAAA", &Font_7x10, 1);

	SSD1306_GotoXY (5, rowLocationValue[4]);
	SSD1306_Puts ("<back>", &Font_7x10, 1);

    SSD1306_UpdateScreen(); // update screen
}


void lcd_init()
{
	defaultPage1_display();
}


void setPage(movement_type type)
{
	currentLevel = type;
}


void buttonPressed()
{
	if(currentLevel == PAGE_1)
	{
		if(currentSelectedOption_Page1 == START_PROG_SOUNDS)
		{
			currentLevel = PAGE_2;

			defaultPage2_display();

			selectCurrentBeatProgramming(currentSelectedOption_Page2);
		}
		else if(currentSelectedOption_Page1 == PLAY_PROG_SOUNDS)
		{
			currentLevel = PAGE_3;
			defaultPage3_display();
		}
	}
	else if(currentLevel == PAGE_2)
	{
		if(currentSelectedOption_Page2 == PAGE2_BACK)
		{
			currentLevel = PAGE_1;

			defaultPage1_display();
		}
	}
	else if(currentLevel == PAGE_3)
	{
		if(currentSelectedOption_Page3 == demo_pattern)
		{
			currentLevel = PAGE_1;

			demoBeatSetup();

			defaultPage1_display();
		}

		if(currentSelectedOption_Page3 == PAGE3_BACK)
		{
			currentLevel = PAGE_1;

			defaultPage1_display();
		}
	}
}


void rotateMenu(movement_type type)
{
	switch (currentLevel)
	{
		case PAGE_1:

			if(type == MOVE_UP)
			{
				page1_highlited_option = (page1_highlited_option + 1) % OPTION_COUNT_PAGE_1;
			}
			else if(type == MOVE_DOWN)
			{
				if(page1_highlited_option == 0)
				{
					page1_highlited_option = OPTION_COUNT_PAGE_1 - 1;
				}
				else
				{
					page1_highlited_option--;
				}
			}

			currentSelectedOption_Page1 = page1_highlited_option;

//			page1_highlited_option = (page1_highlited_option + 1) % OPTION_COUNT_PAGE_1;

			lcdMenuLevel_1(page1_highlited_option, type);
			break;

		case PAGE_2:

			if(type == MOVE_UP)
			{
				page2_highlited_option = (page2_highlited_option + 1) % OPTION_COUNT_PAGE_2;
			}
			else if(type == MOVE_DOWN) // clockwise
			{
				if(page2_highlited_option == 0)
				{
					page2_highlited_option = OPTION_COUNT_PAGE_2 - 1;
				}
				else
				{
					page2_highlited_option--;
				}
			}

			currentSelectedOption_Page2 = page2_highlited_option;

			// change the beat
			selectCurrentBeatProgramming(currentSelectedOption_Page2);

//			page2_highlited_option = (page2_highlited_option + 1) % OPTION_COUNT_PAGE_2;

			lcdMenuLevel_2(page2_highlited_option, type);
			break;

		case PAGE_3:

			if(type == MOVE_UP)
			{
				page3_highlited_option = (page3_highlited_option + 1) % OPTION_COUNT_PAGE_3;
			}
			else if(type == MOVE_DOWN) // clockwise
			{
				if(page3_highlited_option == 0)
				{
					page3_highlited_option = OPTION_COUNT_PAGE_3 - 1;
				}
				else
				{
					page3_highlited_option--;
				}
			}

			currentSelectedOption_Page3 = page3_highlited_option;

//			page2_highlited_option = (page2_highlited_option + 1) % OPTION_COUNT_PAGE_2;

			lcdMenuLevel_3(page3_highlited_option, type);
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
}


// PAGE 3
void lcdMenuLevel_3(int itr, movement_type type)
{
	int pos = 0;

	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();

	while(pos < TOTAL_OPTIONS_CAN_BE_DISPLYED &&
			pos < OPTION_COUNT_PAGE_3)
	{
		switch(itr)  //start printing from the highlighted option
		{
			case 0:
				SSD1306_GotoXY (5, rowLocationValue[pos++]); // goto 10, 10
				SSD1306_Puts ("demo pattern", &Font_7x10, 1); // print
				break;

			case 1:
				SSD1306_GotoXY (5, rowLocationValue[pos++]); // goto 10, 10
				SSD1306_Puts ("Tunak Tunak", &Font_7x10, 1); // print
				break;

			case 2:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("PRETTY BOY", &Font_7x10, 1);
				break;

			case 3:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("BWAHAAA", &Font_7x10, 1);
				break;

			case 4:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("<back>", &Font_7x10, 1);
				break;

			default:
				break;
		}

		itr = (itr + 1) % OPTION_COUNT_PAGE_3;

		/* Update screen */
		SSD1306_UpdateScreen();
	}

    SSD1306_UpdateScreen(); // update screen
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
}


// PAGE 2  ->  Start Programming patterns
void lcdMenuLevel_2(int itr, movement_type type)
{
	int pos = 0;

	/* Clear screen */
	SSD1306_Fill(0);

	/* Update screen */
	SSD1306_UpdateScreen();

	while(pos < TOTAL_OPTIONS_CAN_BE_DISPLYED)
	{
		switch(itr)  //start printing from the highlighted option
		{
			case 0:
				SSD1306_GotoXY (5, rowLocationValue[pos++]); // goto 10, 10
				SSD1306_Puts ("      Hat", &Font_7x10, 1); // print
				break;

			case 1:
				SSD1306_GotoXY (5, rowLocationValue[pos++]); // goto 10, 10
				SSD1306_Puts ("      Kick", &Font_7x10, 1); // print
				break;

			case 2:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("      opHat", &Font_7x10, 1);
				break;

			case 3:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("      rim", &Font_7x10, 1);
				break;

			case 4:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("      snare", &Font_7x10, 1);
				break;

			case 5:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("      tom 1", &Font_7x10, 1);
				break;

			case 6:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("      tom 2", &Font_7x10, 1);
				break;

			case 7:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("      tom 3", &Font_7x10, 1);
				break;

			case 8:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("      trash", &Font_7x10, 1);
				break;

			case 9:
				SSD1306_GotoXY (5, rowLocationValue[pos++]);
				SSD1306_Puts ("     <back>", &Font_7x10, 1);
				break;

			default:
				break;
		}

		itr = (itr + 1) % OPTION_COUNT_PAGE_2;

		/* Update screen */
		SSD1306_UpdateScreen();
	}
}




#endif /* SRC_LCD_C_ */
