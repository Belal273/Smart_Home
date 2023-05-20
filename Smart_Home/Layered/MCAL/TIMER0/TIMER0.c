/*
 * TIMER0.c
 *
 *  Created on: Mar 17, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../STD_LIB/BIT_MATH.h"
#include "../GLOBAL_INT/GLOBAL_INT_Interface.h"
#include "TIMER0_Interface.h"
#include "TIMER0_Register.h"
#include "TIMER0_Config.h"
#include "../DIO/DIO_Interface.h"

u32 TIMER0_Num_Of_OVF = 0.0 ; //can be u32
u32 TIMER0_Pre_Load_Value = 0 ;
void(*TIMER0_CALL_BACK_PF)(void);

static u32 counter = 0.0;
//Added Newly
void TIMER0_Reset()
{
	counter = 0.0;
	TCNT0_REG= 0;
}

void TIMER0_Init(void)
{
	//select Timer Mode (normal / CTC/Phase correct PWM/ fast PWM )
#if TIMER0_MODE == NORMAL_MODE
	CLR_BIT(TCCR0_REG,3);
	CLR_BIT(TCCR0_REG,6);
#elif TIMER0_MODE == CTC_MODE
	SET_BIT(TCCR0_REG,3);
	CLR_BIT(TCCR0_REG,6);
#elif TIMER0_MODE == PHASE_CORRECT_PWM_MODE
	CLR_BIT(TCCR0_REG,3);
	SET_BIT(TCCR0_REG,6);
#elif TIMER0_MODE == FAST_PWM_MODE
	SET_BIT(TCCR0_REG,3);
	SET_BIT(TCCR0_REG,6);

#endif

#if TIMER0_MODE == NORMAL_MODE
	//enable TIMER Interrupt for OVF
SET_BIT(TIMSK_REG,0);
#elif TIMER0_MODE == CTC_MODE
//enable TIMER Interrupt for CTC
SET_BIT(TIMSK_REG,1);
#endif
	//enable Global Interrupt
GI_Enable();
}

void TIMER0_Start(u16 Prescaler)
{
	//Better To be #if fromn Config
	switch (Prescaler)
	{
	case PRESCALER_1: SET_BIT(TCCR0_REG,0);CLR_BIT(TCCR0_REG,1);CLR_BIT(TCCR0_REG,2);break;
	case PRESCALER_8:CLR_BIT(TCCR0_REG,0);SET_BIT(TCCR0_REG,1);CLR_BIT(TCCR0_REG,2);break;
	case PRESCALER_64: SET_BIT(TCCR0_REG,0);SET_BIT(TCCR0_REG,1);CLR_BIT(TCCR0_REG,2);break;
	case PRESCALER_256: CLR_BIT(TCCR0_REG,0);CLR_BIT(TCCR0_REG,1);SET_BIT(TCCR0_REG,2);break;
	case PRESCALER_1024: SET_BIT(TCCR0_REG,0);CLR_BIT(TCCR0_REG,1);SET_BIT(TCCR0_REG,2);break;
	default: CLR_BIT(TCCR0_REG,0);CLR_BIT(TCCR0_REG,1);CLR_BIT(TCCR0_REG,2);break;

	}
}

void TIMER0_Stop()
{
	CLR_BIT(TCCR0_REG,0);CLR_BIT(TCCR0_REG,1);CLR_BIT(TCCR0_REG,2);
}

//Desired Time is in ms
void TIMER0_SetTime(u32 Desired_Time)
{
// need not of overflows = ?
	//Desired Time is in ms
	Desired_Time*=1000;
	//Desired time is now in micro sec

	//Timer Freq
	f32 TIMER0_FREQ = (f32)TIMER0_CLK/TIMER0_PRESCALER;
	//CLK is in Mega , so the the time will be in micro sec

	//Tick Time
	f32 TIMER0_TICK_TIME = 1.0/TIMER0_FREQ;
	//in micro sec
	//f32 TIMER0_TICK_TIME = (f32)TIMER0_PRESCALER/TIMER0_CLK;
#if TIMER0_MODE == NORMAL_MODE
	//Number of Ticks
	u32 NUM_Of_Ticks = TIMER0_RESOLUTION;
	//Overflow Time
	f64 TIMER0_OVF_TIME = TIMER0_TICK_TIME * NUM_Of_Ticks;
	//TIMER0_OVF_TIME is in micro sec

	//Number of Ticks Needed for DT INSTEAD of No of overflows, will count ticks instead of overflows
	u32 NUM_Of_Total_Ticks = Desired_Time / TIMER0_TICK_TIME;

	//Number of Overflows
	//Global variable
	TIMER0_Num_Of_OVF = Desired_Time / TIMER0_OVF_TIME;
	//Pre-load value
	if (Desired_Time % ((u32)TIMER0_OVF_TIME) != 0 )
	{
		f32 Reminder = (Desired_Time % ((u32)TIMER0_OVF_TIME) / TIMER0_OVF_TIME ;
		//f32 Remider = ((f64)(Disered_Time/TIMER0_OVF_TIME)) - ((u32)(Disered_Time/TIMER0_OVF_TIME));
		/*
		 f32 Remider = ((f64)(Disered_Time/TIMER0_OVF_TIME)) - ((u32)(Disered_Time/TIMER0_OVF_TIME));
		f32 Remider = (Disered_Time % (u32)TIMER0_OVF_TIME)/TIMER0_OVF_TIME;
		 */
		TIMER0_Pre_Load_Value = TIMER0_RESOLUTION - (TIMER0_RESOLUTION * Reminder);
		TCNT0_REG = TIMER0_Pre_Load_Value;
		TIMER0_Num_Of_OVF++;

	}
#elif TIMER0_MODE == CTC_MODE
	//load CTC value to OCR0 Register
	u8 TIMER0_CTC_VALUE = 255;
	OCR0_REG = TIMER0_CTC_VALUE;
	//Number of Ticks
		u32 NUM_Of_Ticks = TIMER0_CTC_VALUE;
		//Overflow Time
		f64 TIMER0_OVF_TIME = TIMER0_TICK_TIME * NUM_Of_Ticks;
		//TIMER0_OVF_TIME is in micro sec
		//Number of Ticks Needed for DT INSTEAD of No of overflows, will count ticks instead of overflows
		u32 NUM_Of_Total_Ticks = Desired_Time / TIMER0_TICK_TIME;
		//Number of Overflows
		//Global variable
		TIMER0_Num_Of_OVF = Desired_Time / TIMER0_OVF_TIME;
		//Customize CTC value
		//Pre-load value
		while (Desired_Time % ((u32)TIMER0_OVF_TIME) != 0 )
		{
			TIMER0_CTC_VALUE--;
			//Number of Ticks
			 NUM_Of_Ticks = TIMER0_CTC_VALUE;
			//Overflow Time
			 TIMER0_OVF_TIME = TIMER0_TICK_TIME * NUM_Of_Ticks;
			//TIMER0_OVF_TIME is in micro sec
			//Number of Ticks Needed for DT INSTEAD of No of overflows, will count ticks instead of overflows
			 NUM_Of_Total_Ticks = Desired_Time / TIMER0_TICK_TIME;
			//Number of Overflows
			//Global variable
			TIMER0_Num_Of_OVF = Desired_Time / TIMER0_OVF_TIME;

		}
		OCR0_REG = TIMER0_CTC_VALUE;

#endif

}
void TIMER0_SET_OC0_PIN(u8 Pin_Value)
{
	switch (Pin_Value)
	{
	case Toggle:CLR_BIT(TCCR0_REG,4);SET_BIT(TCCR0_REG,5);break;
	case Set:SET_BIT(TCCR0_REG,4);SET_BIT(TCCR0_REG,5);break;
	case Clear:SET_BIT(TCCR0_REG,4);CLR_BIT(TCCR0_REG,5);break;
	default:CLR_BIT(TCCR0_REG,4);CLR_BIT(TCCR0_REG,5);break;
	}
}

void TIMER0_Set_CTC(u8 CTC_Value)
{
	//DIO_TogglePin(PORTA,PIN4);
	OCR0_REG = CTC_Value;
}

void TIMER0_CallBack( void (*PF)(void))
{
	//DIO_TogglePin(PORTA,PIN4);
	TIMER0_CALL_BACK_PF=PF;
}



void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	//DIO_SetPinValue(PORTA,PIN0,HIGH);
	//static u32 counter = 0.0;
	counter++;
	if (counter ==  TIMER0_Num_Of_OVF)
	{
		//action
		//call the call back function
		//DIO_TogglePin(PORTA,PIN0);

		TIMER0_CALL_BACK_PF();
		//Pointer to function

		counter = 0;
		TCNT0_REG = TIMER0_Pre_Load_Value;
	}
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	//DIO_SetPinValue(PORTA,PIN0,HIGH);
//	static u32 counter = 0.0;
	counter++;
	if (counter ==  TIMER0_Num_Of_OVF)
	{
		//action
		//call the call back function
		//DIO_TogglePin(PORTA,PIN0);

		TIMER0_CALL_BACK_PF();
		//Pointer to function

		counter = 0;
		//TCNT0_REG = TIMER0_Pre_Load_Value;
	}
}

