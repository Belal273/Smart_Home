/*
 * DC_MOTOR_Interface.h
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */

#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_

enum MOTOR_STATE
{
	MOTOR_OK,
	MOTOR_NOTOK,
	MOTOR_SC,
	MOTOR_OC
};

void MOTOR_INIT();

void MOTOR_ClockWise();

void MOTOR_AntiClockWise();

void MOTOR_Stop();

#endif /* HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_ */
