/*
 * ADC_Interface.h
 *
 *  Created on: Mar 16, 2023
 *      Author: dell
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

enum ADC_Channels
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7

};

void ADC_Init();

u16 ADC_READ(u8 ADC_Pin);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
