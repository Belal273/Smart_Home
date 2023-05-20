/*
 * ADC_Registers.h
 *
 *  Created on: Mar 16, 2023
 *      Author: dell
 */

#ifndef ADC_REGISTERS_H_
#define ADC_REGISTERS_H_

#define ADMUX_REG    *((volatile u8 *)0x27)
#define ADCSRA_REG   *((volatile u8 *)0x26)
#define ADCDATA_REG  *((volatile u16 *)0x24)
#define ADCL_REG  	 *((volatile u16 *)0x24)
#define ADCH_REG 	 *((volatile u16 *)0x25)
//Special function register for auto triggering

#endif /* MCAL_ADC_ADC_REGISTERS_H_ */
