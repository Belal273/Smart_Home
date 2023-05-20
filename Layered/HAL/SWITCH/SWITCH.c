/*
 * SWITCH.c
 *
 *  Created on: Feb 22, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "SWITCH.h"

void SWITCH_INIT(u8 Port_ID,u8 Pin_Id)
{
	DIO_SetPinDirection(Port_ID, Pin_Id, INPUT);
}
void SWITCH_GET_VAL(u8 Port_ID,u8 Pin_ID,u8 PinReading)
 {
	 DIO_ReadPin( Port_ID, Pin_ID, &PinReading);
 }
void SWITCH_DIPTHREE_INIT(u8 Port_ID)
{
		DIO_SetPortDirection(Port_ID,INPUT_PORT);
}



