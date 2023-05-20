/*
 * EXT_INT_Interface.h
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */

#ifndef EXT_INT_INTERFACE_H_
#define EXT_INT_INTERFACE_H_

enum EXT_INT_Triggering
{
	FallingEdge,
	RisingEdge,
	OnChange,
	LowLevel
};

#define EXT_INT0  0
#define EXT_INT1  1
#define EXT_INT2  2

void EXT_INT_Enable(u8 INT_ID);

void EXT_INT_Disable(u8 INT_ID);

void EXT_INT_SenseControl(u8 INT_ID,u8 INT_Trigger);

void EXT_INT_ReturnFlag(u8 INT_ID,u8 * PIF);

void EXT_INT1_CallBack(void(*PF)(void));

void EXT_INT0_CallBack(void(*PF)(void));

void EXT_INT2_CallBack(void(*PF)(void));

#endif /* MCAL_EXT_INT_EXT_INT_INTERFACE_H_ */
