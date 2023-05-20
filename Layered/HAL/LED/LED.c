/*
 * LED.c
 *
 *  Created on: Feb 11, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../STD_LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LED.h"
#include "avr/delay.h"


void LED_INIT(u8 Port_ID,u8 Pin_Id)
{
	DIO_SetPinDirection(Port_ID,Pin_Id,OUTPUT);
}
void LED_ON(u8 Port_ID,u8 Pin_Id)
{
	DIO_SetPinValue(Port_ID,Pin_Id,HIGH);
}

void LED_OFF(u8 Port_ID,u8 Pin_Id)
{
	DIO_SetPinValue(Port_ID,Pin_Id,LOW);
}

void LED_TOG(u8 Port_ID,u8 Pin_Id)
{
	DIO_TogglePin(Port_ID,Pin_Id);
}


