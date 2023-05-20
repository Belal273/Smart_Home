/*
 * TIMER0_Interface.h
 *
 *  Created on: Mar 17, 2023
 *      Author: dell
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

enum TIMER0_PRESCALER
{
	PRESCALER_1=1,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024
};


enum TIMER0_OC0_Pin_Value
{
	Clear,
	Set,
	Toggle
};
void TIMER0_Init (void);

//Added Newly
void TIMER0_Reset();

void TIMER0_SetTime(u32 Desired_Time);


void TIMER0_CallBack( void (*PF)(void));
//Make CallBack for CTC


void TIMER0_Start(u16 Prescaler);



void TIMER0_Stop();

void TIMER0_SET_OC0_PIN(u8 Pin_Value);

void TIMER0_Set_CTC(u8 CTC_Value);


#endif /* MCAL_TIMER0_TIMER0_INTERFACE_H_ */
