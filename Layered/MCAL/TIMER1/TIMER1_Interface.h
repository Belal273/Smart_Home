/*
 * TIMER1_Interface.h
 *
 *  Created on: Mar 29, 2023
 *      Author: dell
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

//PWM-Type ( fast,phase correct) / mode (inverting or or non
void PWM1_Init();


//set CTC Register if you are fast PWM
void PWM1_SetDutyCycle(u8 DutyCycle);


//Control Top if possible
void PWM1_SetFrequency(u8 Freq);

//set Prescalar
void PWM1_Start();

//clear Prescalar
void PWM1_Stop();

#endif /* MCAL_TIMER1_TIMER1_INTERFACE_H_ */
