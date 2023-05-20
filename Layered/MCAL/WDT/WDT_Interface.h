/*
 * WDT_Interface.h
 *
 *  Created on: Mar 25, 2023
 *      Author: aaa
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

enum WDT_PRESCALAR
{
	TimeOut_16_3_ms,
	TimeOut_32_5_ms,
	TimeOut_65_ms,
	TimeOut_130_ms,
	TimeOut_260_ms,
	TimeOut_520_ms,
	TimeOut_1_Sec,
	TimeOut_2_1_Sec
};

void WDT_START();

void WDT_CLEAR();

void WDT_SetTimeOut(u8 prescalar);

#endif /* MCAL_WDT_WDT_INTERFACE_H_ */
