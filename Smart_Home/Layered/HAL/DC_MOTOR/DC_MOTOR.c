/*
 * DC_MOTOR.c
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */

#include "../../STD_LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "DC_MOTOR_Interface.h"
#include "DC_MOTOR_config.h"

void MOTOR_INIT()
{
	DIO_SetPinDirection(MOTOR_PORT,MOTOR_PHASE_1,OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT,MOTOR_PHASE_2,OUTPUT);

}

void MOTOR_ClockWise()
{
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PHASE_1,HIGH);
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PHASE_2,LOW);


}

void MOTOR_AntiClockWise()
{
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PHASE_1,LOW);
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PHASE_2,HIGH);

}

void MOTOR_Stop()
{
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PHASE_1,LOW);
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PHASE_2,LOW);

}
