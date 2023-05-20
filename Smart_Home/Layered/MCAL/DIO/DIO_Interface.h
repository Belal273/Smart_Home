/*
 * DIO_Interface.h
 *
 *  Created on: Feb 10, 2023
 *      Author: aaa
 */

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

enum DIO_ErrorState
{
	DIO_OK,
	DIO_PinOutOfRange,
	DIO_PortOutOfRange,
	DIO_ValueNotCorrect,
	DIO_DirectionNotCorrect,
	DIO_ERROR
};
#define OUTPUT		1
#define INPUT		0

#define OUTPUT_PORT		0xFF
#define INPUT_PORT		0x00

#define HIGH_PORT		0xFF
#define LOW_PORT		0x00

#define HIGH		1
#define LOW			0

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define PORTA		0
#define PORTB		1
#define PORTC		2
#define PORTD		3

void DIO_INIT(void);

u8 DIO_SetPinDirection(u8 Port_ID,u8 Pin_ID,u8 Pin_Dir);

u8 DIO_SetPinValue(u8 Port_ID,u8 Pin_ID,u8 Pin_Val);

u8	DIO_ReadPin(u8 Port_ID,u8 Pin_ID,u8 * PinReading);

u8 DIO_TogglePin(u8 Port_ID,u8 Pin_ID);

u8 DIO_SetPortDirection(u8 Port_ID,u8 Pin_Dir);

u8 DIO_SetPortValue(u8 Port_ID,u8 Pin_Val);

u8	DIO_ReadPort(u8 Port_ID,u8 * PortReading);

u8  DIO_TogglePort(u8 Port_ID);

#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
