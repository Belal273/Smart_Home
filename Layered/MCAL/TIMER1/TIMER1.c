/*
 * TIMER1.c
 *
 *  Created on: Mar 29, 2023
 *      Author: dell
 */

#include "../../STD_LIB/STD_TYPES.h"
#include "../../STD_LIB/BIT_MATH.h"
#include "TIMER1_Interface.h"
#include "TIMER1_Config.h"
#include "TIMER1_Registers.h"

void PWM1_Init()
{
#if PWM1_MODE == FAST_PWM_MODE
	CLR_BIT(TCCR1A_REG,0);
	SET_BIT(TCCR1A_REG,1);
	SET_BIT(TCCR1B_REG,3);
	SET_BIT(TCCR1B_REG,4);

#elif PWM1_MODE == PHASE_CORRECT_PWM_MODE
	CLR_BIT(TCCR1A_REG,0);
	SET_BIT(TCCR1A_REG,1);
	CLR_BIT(TCCR1B_REG,3);
	SET_BIT(TCCR1B_REG,4);


#endif

#if  COMPARE_OUTPUT_MATCH == INVERTING
	SET_BIT(TCCR1A_REG,6);
	SET_BIT(TCCR1A_REG,7);

#elif COMPARE_OUTPUT_MATCH == NON_INVERTING
	CLR_BIT(TCCR1A_REG,6);
	SET_BIT(TCCR1A_REG,7);

#endif
}

void PWM1_SetDutyCycle(u8 DutyCycle)
{
	/*
#if PWM1_MODE == FAST_PWM_MODE
	#if  COMPARE_OUTPUT_MATCH == INVERTING
		//OCR1A_REG = Top * (1 - (DutyCycle/100));
		OCR1A_REG = ICR1_REG * (1 - (DutyCycle/100.0));

	#elif COMPARE_OUTPUT_MATCH == NON_INVERTING
		//OCR1A_REG = Top * (DutyCycle/100);
		OCR1A_REG = ICR1_REG * (DutyCycle/100.0);

	#endif
#elif PWM1_MODE == PHASE_CORRECT_PWM_MODE
	#if  COMPARE_OUTPUT_MATCH == INVERTING
		//OCR1A_REG = Top * (1 - (DutyCycle/100));
		OCR1A_REG = ICR1_REG * (1 - (DutyCycle/100.0));

	#elif COMPARE_OUTPUT_MATCH == NON_INVERTING
		//OCR1A_REG = Top * (DutyCycle/100);
		OCR1A_REG = ICR1_REG / ((DutyCycle/100.0) + 1);
	#endif
#endif
	*/

#if  COMPARE_OUTPUT_MATCH == INVERTING
	//OCR1A_REG = Top * (1 - (DutyCycle/100));
	OCR1A_REG = ICR1_REG * (1 - (DutyCycle/100.0));

#elif COMPARE_OUTPUT_MATCH == NON_INVERTING
	//OCR1A_REG = Top * (DutyCycle/100);
	OCR1A_REG = ICR1_REG * (DutyCycle/100.0);
#endif
}

void PWM1_SetFrequency(u8 Freq)
{
	//Freq is set by setting the TOP , the signal is repeated when it reaches the top
	ICR1_REG = (TIMER1_CLK * 1000000UL)/(TIMER1_PRESCALER * Freq);
}

void PWM1_Start()
{
	//Prescalar 8
	//prescaler must be same as setFreq
		CLR_BIT(TCCR1B_REG,0);
		SET_BIT(TCCR1B_REG,1);
		CLR_BIT(TCCR1B_REG,2);

}

void PWM1_Stop()
{
	CLR_BIT(TCCR1B_REG,0);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,2);
}
