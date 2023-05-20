/*
 * KEYPAD.c
 *
 *  Created on: Feb 18, 2023
 *      Author: dell
 */

#include "../../STD_LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "KEYPAD_Interface.h"
#include "KEYPAD_Config.h"
#include "avr/delay.h"

u8 SwitchValue [4][4] = { {'7','8','9','/'},
		                   {'4','5','6','*'},
						   {'1','2','3','-'},
						   {'C','0','=','+'}};

void KEYPAD_INIT()
{
	/*Make Row pins Input and Columns pins Output */
	DIO_SetPortDirection(KEYPAD_PORT,0xF0);
	/*Make Row pins to internal pull up and Columns pins are set to high */
	DIO_SetPortValue(KEYPAD_PORT,0xFF);
}

u8 KEYPAD_GetKeyPressed()
{
	u8 KeyPressed = 0;
	u8 GetPinReading = 0;
	for(u8 col = C1 ; col <=C4; col++)
	{
		DIO_SetPinValue(KEYPAD_PORT,col,LOW);
		for(u8 row = R1; row<=R4 ; row++)
		{
			DIO_ReadPin(KEYPAD_PORT,row,&GetPinReading);
			if( GetPinReading == LOW)
			{
				KeyPressed = SwitchValue[row][col-C1];
				//For Debouncing
				_delay_ms(20);
				while(GetPinReading == LOW)
				{
					DIO_ReadPin(KEYPAD_PORT,row,&GetPinReading);
				}
			}
		}
		DIO_SetPinValue(KEYPAD_PORT,col,HIGH);
	}

	return KeyPressed;
}
