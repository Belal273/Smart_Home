/*
  ADC.c
 *
 *  Created on: Mar 16, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../STD_LIB/BIT_MATH.h"
#include "ADC_Interface.h"
#include "ADC_Registers.h"
#include "ADC_Config.h"

void ADC_Init()
{
	//Voltage Reference
#if   ADC_VREF == ADC_INTERNAL_2_56v
	SET_BIT(ADMUX_REG,7);
	SET_BIT(ADMUX_REG,6);
	//Name bits 7,6 to avoid magic numbers
#elif 	ADC_VREF == ADC_INTERNAL_AVCC
	CLR_BIT(ADMUX_REG,7);
	SET_BIT(ADMUX_REG,6);
#elif   ADC_VREF == ADC_EXTERNAL
	CLR_BIT(ADMUX_REG,7);
	CLR_BIT(ADMUX_REG,6);
#endif

	/*select to ADJUST result*/
	//right or left
#if   ADC_AJUST == ADC_LEFT
	SET_BIT(ADMUX_REG,5);
#elif ADC_AJUST == ADC_RIGHT
	CLR_BIT(ADMUX_REG,5);
#endif

	/*select prescalar*/
#if ADC_PRESCALAR == ADC_PRESCALAR_2
	CLR_BIT(ADCSRA_REG,0);
	CLR_BIT(ADCSRA_REG,1);
	CLR_BIT(ADCSRA_REG,2);
#elif ADC_PRESCALAR == ADC_PRESCALAR_4
	CLR_BIT(ADCSRA_REG,0);
	SET_BIT(ADCSRA_REG,1);
	CLR_BIT(ADCSRA_REG,2);
#elif ADC_PRESCALAR == ADC_PRESCALAR_8
	SET_BIT(ADCSRA_REG,0);
	SET_BIT(ADCSRA_REG,1);
	CLR_BIT(ADCSRA_REG,2);
#elif ADC_PRESCALAR == ADC_PRESCALAR_16
	CLR_BIT(ADCSRA_REG,0);
	CLR_BIT(ADCSRA_REG,1);
	SET_BIT(ADCSRA_REG,2);
#elif ADC_PRESCALAR == ADC_PRESCALAR_32
	SET_BIT(ADCSRA_REG,0);
	CLR_BIT(ADCSRA_REG,1);
	SET_BIT(ADCSRA_REG,2);
#elif ADC_PRESCALAR == ADC_PRESCALAR_64
	CLR_BIT(ADCSRA_REG,0);
	SET_BIT(ADCSRA_REG,1);
	SET_BIT(ADCSRA_REG,2);
#elif ADC_PRESCALAR == ADC_PRESCALAR_128
	SET_BIT(ADCSRA_REG,0);
	SET_BIT(ADCSRA_REG,1);
	SET_BIT(ADCSRA_REG,2);
#endif

	/*Auto trigger or free running*/
	CLR_BIT(ADCSRA_REG,5);

	/*Enable ADC Circuit*/
	SET_BIT(ADCSRA_REG,7);
}

u16 ADC_READ(u8 ADC_Pin)
{
	ADCDATA_REG=0x00;
		/*select ADC channel*/
		switch (ADC_Pin){
		case ADC0:CLR_BIT(ADMUX_REG,0);CLR_BIT(ADMUX_REG,1);CLR_BIT(ADMUX_REG,2);	break;
		case ADC1:SET_BIT(ADMUX_REG,0);CLR_BIT(ADMUX_REG,1);CLR_BIT(ADMUX_REG,2);	break;
		case ADC2:CLR_BIT(ADMUX_REG,0);SET_BIT(ADMUX_REG,1);CLR_BIT(ADMUX_REG,2);	break;
		case ADC3:SET_BIT(ADMUX_REG,0);SET_BIT(ADMUX_REG,1);CLR_BIT(ADMUX_REG,2);	break;
		case ADC4:CLR_BIT(ADMUX_REG,0);CLR_BIT(ADMUX_REG,1);SET_BIT(ADMUX_REG,2);	break;
		case ADC5:SET_BIT(ADMUX_REG,0);CLR_BIT(ADMUX_REG,1);SET_BIT(ADMUX_REG,2);	break;
		case ADC6:CLR_BIT(ADMUX_REG,0);SET_BIT(ADMUX_REG,1);SET_BIT(ADMUX_REG,2);	break;
		case ADC7:SET_BIT(ADMUX_REG,0);SET_BIT(ADMUX_REG,1);SET_BIT(ADMUX_REG,2);	break;
		default:	break;//report error
		}
		/*start conversion*/
		SET_BIT(ADCSRA_REG,6);

		/*wait until conversion is completed*/
		while( GET_BIT(ADCSRA_REG,4) == 0);

		/*Clear ADC Flag*/
		SET_BIT(ADCSRA_REG,4);
		/*read ADCchannel register*/
#if ADC_AJUST == ADC_RIGHT
		return ADCDATA_REG;
#elif ADC_AJUST == ADC_LEFT
		//Calculations
		return ADCDATA_REG>>6;
		//Right
#endif




}
