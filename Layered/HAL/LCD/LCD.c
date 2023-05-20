/*
 * LCD.c
 *
 *  Created on: Feb 17, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_config.h"
#include<avr/delay.h>

void LCD_8bit_INT(void)
{

	_delay_ms(35);
	LCD_WriteInstruction(LCD_Function_Set);
	_delay_ms(1);
	LCD_WriteInstruction(LCD_DisplayOnOFF);
	_delay_ms(1);
	LCD_WriteInstruction(LCD_Clear);
	_delay_ms(2);
	LCD_WriteInstruction(LCD_SetEntryMode);
	_delay_ms(1);
}

void LCD_WriteInstruction(u8 Instruction)
{
	//set RS pin to low to select Instruction
	DIO_SetPinValue(Control_Port,RS,LOW);
	//set RW pin to low to select Write
	DIO_SetPinValue(Control_Port,RW,LOW);

	//load the Instruction on Data pins
	DIO_SetPortValue(Data_PORT,Instruction);

	//Set Enable in Writing Mode by making a falling edge to enable pin
	DIO_SetPinValue(Control_Port,E,HIGH);
	_delay_ms(5);
	DIO_SetPinValue(Control_Port,E,LOW);
	_delay_ms(5);
}

void LCD_WriteCharacter (u8 Data)
{
	//set RS pin to High to select Data
		DIO_SetPinValue(Control_Port,RS,HIGH);
		//set RW pin to low to select Write
		DIO_SetPinValue(Control_Port,RW,LOW);

		//load the data on Data pins
		DIO_SetPortValue(Data_PORT,Data);

		//Set Enable in Writing Mode by making a falling edge to enable pin
		DIO_SetPinValue(Control_Port,E,HIGH);
		_delay_ms(5);
		DIO_SetPinValue(Control_Port,E,LOW);
		_delay_ms(5);
}

void LCD_WriteString(u8 * String)
{
	u8 iteration =0;
	while(String[iteration] != '\0')
	{
		LCD_WriteCharacter(String[iteration++]);

	}
}

void LCD_GoTo(u8 x,u8 y)
{
	if(x>=0 && x<=16)
	{
		switch(y)
		{
		case 1:
			LCD_WriteInstruction(LCD_Line_1+x);break;
		case 2:
			LCD_WriteInstruction(LCD_Line_2+x);break;
		default:/*reporterror*/break;
		}
	}
}

void LCD_WriteCustomChar(u8 * CustomArray)
{
	/*Move from DDRAM to CGRAM */
	LCD_WriteInstruction(LCD_MoveToCGRAM);
	for(u8 i = 0;i<16;i++)
	{
		LCD_WriteCharacter(CustomArray[i]);
	}
	/*Move from CGRAM to DDRAM */
	LCD_WriteInstruction(LCD_Line_1);
	/*
	for(u8 i = 0;i<8;i++)
		{
			LCD_WriteCharacter(i);
			_delay_ms(5);
		}
		*/
	LCD_WriteCharacter(0);

}

void LCD_WriteIntNumber(u32 Num)
{
	//LCD_WriteCharacter(48+Num);
	s8 i=0,j=0;
		u32 x=Num;
		u8 base_NUM[10]={0};
		f64 y=0;
		if (Num<0)
		{
			Num*=-1;
			x=Num;
			LCD_WriteCharacter('-');
		}
		y=(((Num+1.0)-x)*10000000);
		while(x !=0)
		{
			base_NUM[i++] = x % 10;
			x/=10;
		}
		u8 k=i--;
		while(i>=0)
		{
			LCD_WriteCharacter(base_NUM[i--]+48);
		}
		u8 F_NUM[10]={0};
		i=0;
		u32 z=y;
		LCD_WriteCharacter('.');
		while(z !=0)
		{
			F_NUM[i++] = z % 10;
			z/=10;
		}
		i-=2;
		for(j=0;j<10;j++)
		{
			if(F_NUM[j]==0)
			{
				F_NUM[j]='k';
			}
			else
			{
				break;
			}
		}
		while(F_NUM[i]!='k'&& k!=7)
		{
			LCD_WriteCharacter(F_NUM[i--]+48);
			k++;
		}

}

void LCD_WriteFloattttNumber(f64 number)
{
	s8 i=0,j=0;
	u32 x=number;
	u8 base_NUM[10]={0};
	f64 y=0;
	if (number<0)
	{
		number*=-1;
		x=number;
		LCD_WriteCharacter('-');
	}
	y=(((number+1.0)-x)*10000000);
	while(x !=0)
	{
		base_NUM[i++] = x % 10;
		x/=10;
	}
	u8 k=i--;
	while(i>=0)
	{
		LCD_WriteCharacter(base_NUM[i--]+48);
	}
	u8 F_NUM[10]={0};
	i=0;
	u32 z=y;
	LCD_WriteCharacter('.');
	while(z !=0)
	{
		F_NUM[i++] = z % 10;
		z/=10;
	}
	i-=2;
	for(j=0;j<10;j++)
	{
		if(F_NUM[j]==0)
		{
			F_NUM[j]='k';
		}
		else
		{
			break;
		}
	}
	while(F_NUM[i]!='k'&& k!=7)
	{
		LCD_WriteCharacter(F_NUM[i--]+48);
		k++;
	}

}
