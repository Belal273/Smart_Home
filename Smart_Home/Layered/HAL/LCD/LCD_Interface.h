/*
 * LCD_Interface.h
 *
 *  Created on: Feb 17, 2023
 *      Author: dell
 */

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LCD_Clear          0x01
#define LCD_Function_Set   0b00111000
#define LCD_DisplayOnOFF   0b00001100
#define LCD_SetEntryMode   0b00000110
#define LCD_Line_1         128
#define LCD_Line_2         191
#define LCD_MoveToCGRAM    64

void LCD_8bit_INT(void);

void LCD_WriteCharacter(u8 Data);

void LCD_WriteString(u8 * String);

void LCD_WriteInstruction(u8 Instruction);

void LCD_WriteIntNumber(u32 Num);

void LCD_WriteFloatNumber(u32 Num_Float);

void LCD_GoTo(u8 x,u8 y);

void LCD_WriteCustomChar(u8 * CustomArray);

void LCD_WriteFloattttNumber(f64 number);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
