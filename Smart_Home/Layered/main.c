/*
 * main.c
 *
 *  Created on: Feb 10, 2023
 *      Author: dell
 */

#include "STD_LIB/BIT_MATH.h"
#include "STD_LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO_Interface.h"
#include <avr/delay.h>
#include "HAL/LED/LED.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "HAL/TEMP_SENSOR/TEMP_SENSOR_Interface.h"
#include "HAL/LDR/LDR_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/KEYPAD/KEYPAD_Interface.h"
#include "MCAL/TIMER0/TIMER0_Interface.h"
#include "MCAL/TIMER1/TIMER1_Interface.h"
#include "MCAL/WDT/WDT_Interface.h"
#include "MCAL/GLOBAL_INT/GLOBAL_INT_Interface.h"
#include "MCAL/EXT_INT/EXT_INT_Interface.h"

void checkPassFunc(u8 * myDefaultPass,u8 * userInputPass);
void getdefaultPassword(u8 * myArray, u8 myKeypadInit);
void getUserPassword(u8 * myDefaultPass, u8 * myArray, u8 myKeypadInit);
void resetFunc(u8 * userInputPass);
void extIntFunc();
void timer0Func();

//Tokens are used to write something in LCD one time only
static u8 mainView= 1;
static u8 firstViewToken= 0;
static u8 secondViewToken= 0;

static u8 i= 0;
static u8 modes= 0;
static u8 passwordToken = 0;
static u8 loginToken = 0;
static u8 defaultPassIndex = 0;

void main()
{
	//Initialization
	DIO_INIT();
	LCD_8bit_INT();
	ADC_Init();
	KEYPAD_INIT();

	//External Interrupt
	GI_Enable();
	EXT_INT_Enable(EXT_INT0); //PD2
	EXT_INT_SenseControl(EXT_INT0, FallingEdge);
	EXT_INT0_CallBack(&extIntFunc);

	//PWM For Servo from Timer1
	PWM1_Init();
	PWM1_SetFrequency(50);
	PWM1_Start();

	//Timer
	TIMER0_Init ();
	//TIMER0_Start( PRESCALER_1024 );
	u32 Desired_Time = 20;
	TIMER0_SetTime(Desired_Time);
	TIMER0_CallBack( &timer0Func);

	//Temperature Sensor
	u16 myTempReading = (ADC_READ(ADC0)-1)/2.0;

	//LCD
	u8  myInitFan = myTempReading>=25?HIGH:LOW;
//	//FAN is on PORTA , PIN0

	//KeyPad
	u8 myKeypadInit =  KEYPAD_GetKeyPressed();
	static u8 myDefaultPass[5] = "12345";
	u8 userInputPass[5] = "54321";

	//LDR
	//LDR_Reading
	//LDR_Intensity_Level
	//ADC_READ
	u16 LDRVal = ADC_READ(ADC3);


	while (1)
	{

		//Using Temperature sensor of Proteus , proteus gives voltage +1 directly
		//in Proteus : Volt = 2*Temperature , and Temperature sensor output volt - 1 directly
		//Temperature = value /2 = (Value -1)/2
		//Short delay for proteus , long delay real HW
		myTempReading = (ADC_READ(ADC0)-1)/2.0;
		myInitFan = myTempReading>=25?HIGH:LOW;
		DIO_SetPinValue(PORTA,PIN2,myInitFan);
		LDRVal = ADC_READ(ADC3);

		if ( mainView == 1)
		{
			//Token used to write something in LCD one time only
			if ( firstViewToken == 0)
			{
				TIMER0_Stop();
				LCD_WriteInstruction(LCD_Clear);
				LCD_GoTo( 0,1);
				LCD_WriteString("TEMP:");
				LCD_GoTo( 5,1);
				LCD_WriteIntNumber(myTempReading);
				LCD_GoTo( 9,1);
				LCD_WriteString("FAN:");
				LCD_GoTo( 13,1);
				myInitFan?LCD_WriteString("ON "):LCD_WriteString("OFF");
				LCD_GoTo( 1,2);
				LCD_WriteString("LDR LEDS:");
				LCD_GoTo( 15,2);
				LCD_WriteIntNumber(LDRVal-670);
				//secondViewToken = 0;
				firstViewToken = 1;
			}
			//Always writing
					LCD_GoTo( 5,1);
					LCD_WriteIntNumber(myTempReading);
					LCD_GoTo( 13,1);
					myInitFan?LCD_WriteString("ON "):LCD_WriteString("OFF");
					LCD_GoTo( 15,2);
					LCD_WriteIntNumber(LDRVal-670);
		}

		else if ( mainView == 2 )
		{
			//Token used to write something in LCD one time only
			if ( secondViewToken == 0)
			{
				TIMER0_Start( PRESCALER_1024 );
				LCD_WriteInstruction(LCD_Clear);
				LCD_GoTo( 0,1);
				LCD_WriteString("1.Password:");
				LCD_GoTo( 1,2);
				LCD_WriteString("2.Login.");
				//firstViewToken = 0;
				secondViewToken = 1;
			}
			//Check the mode
			if (modes == 0)
			{
				//TIMER0_Start( PRESCALER_1024 );
				myKeypadInit =  KEYPAD_GetKeyPressed();
				if (myKeypadInit != 0 )
				{
					TIMER0_Reset();
					//TIMER0_Stop();
					if (myKeypadInit == '1')
					{
						LCD_GoTo( 11,1);
						LCD_WriteCharacter('1');
						modes=1;
					}
					else if (myKeypadInit == '2')
					{
						LCD_GoTo( 11,1);
						LCD_WriteCharacter('2');
						modes=2;
					}
				}
//				else
//				{
//					TIMER0_Start( PRESCALER_1024 );
//				}
			}
			else if (modes == 1)
			{
				//TIMER0_Start( PRESCALER_1024 );
				//Token used to write something in LCD one time only
				//Initialization
				if (passwordToken == 0)
				{
						LCD_WriteInstruction(LCD_Clear);
						LCD_GoTo( 0,1);
						LCD_WriteString("1.Password:");
						LCD_GoTo( 11,1);
						passwordToken = 1;
						i=0;

				}

				//C key To reset
				myKeypadInit =  KEYPAD_GetKeyPressed();
				if (myKeypadInit == 'C')
				{
					TIMER0_Reset();
					//	TIMER0_Stop();
					 resetFunc(userInputPass);
				}
				else if (myKeypadInit != 0 )
					{
						TIMER0_Reset();
						//TIMER0_Stop();
						getUserPassword(myDefaultPass, userInputPass, myKeypadInit);
					}
//				else
//				{
//					TIMER0_Start( PRESCALER_1024 );
//				}

			}
			else if (modes == 2)
			{
			//	TIMER0_Start( PRESCALER_1024 );
				//Token used to write something in LCD one time only
				if ( loginToken == 0)
				{
//						TIMER0_Start( PRESCALER_1024 );
						LCD_WriteInstruction(LCD_Clear);
						LCD_GoTo( 0,1);
						//LCD_WriteString("Login Mode:");
						LCD_WriteString("New Pass:");
						LCD_GoTo( 9,1);
						loginToken = 1;
						defaultPassIndex=0;
				}


				//C key To reset
				myKeypadInit =  KEYPAD_GetKeyPressed();
				if (myKeypadInit == 'C')
				{
					TIMER0_Reset();
					//TIMER0_Stop();
					 resetFunc(userInputPass);
				}
				else if (myKeypadInit != 0 )
				{
					TIMER0_Reset();
					//TIMER0_Stop();
					getdefaultPassword(myDefaultPass, myKeypadInit);
				}
//				else
//				{
//					TIMER0_Start( PRESCALER_1024 );
//				}
			}

		}
//		LDRVal = ADC_READ(ADC3);
//		LCD_GoTo( 0,1);
//		LCD_WriteIntNumber(LDRVal-670);

	}
}

void extIntFunc()
{
	//DIO_TogglePin(PORTA,PIN4);
	firstViewToken = 0;
	mainView = 2;
}

void timer0Func()
{
	secondViewToken = 0;
	mainView = 1;
	//DIO_TogglePin(PORTA,PIN4);
}


void getdefaultPassword(u8 * myArray, u8 myKeypadInit)
{
	TIMER0_Reset();
	//TIMER0_Stop();

	myArray[defaultPassIndex] = myKeypadInit;
		(defaultPassIndex++);
		if (defaultPassIndex <= 5){LCD_WriteCharacter('*');}

		if (defaultPassIndex == 5)
				{
					//Debugging what is the myDefaultPass now
//					LCD_GoTo( 1,2);
//					LCD_WriteString(myArray);
					LCD_GoTo( 1,2);
					LCD_WriteString("Password Changed");
				}
}

void getUserPassword(u8 * myDefaultPass, u8 * myArray, u8 myKeypadInit)
{
	TIMER0_Reset();
	//TIMER0_Stop();
	myArray[i] = myKeypadInit;
		(i++);
		if (i <= 5){LCD_WriteCharacter('*');}

			if (i == 5)
					{
						//Debugging what is the user input
//						LCD_GoTo( 1,2);
//						LCD_WriteString(myArray);
//								for (u8 j=0;j<5;j++)
//									{
//									LCD_WriteCharacter(userInputPass[j]);
//									}
						//Checking if password is correct
						checkPassFunc(myDefaultPass,myArray);
					}
}


void checkPassFunc(u8 * myDefaultPass,u8 * userInputPass)
{
	TIMER0_Reset();
	//TIMER0_Stop();
	static count_pass=0;
	u8 checkCorrectPass = 0;
	for (u8 j=0;j<5;j++)
		{
			if (myDefaultPass[j] == userInputPass[j])
			{
				checkCorrectPass = 1;
			}
			else
			{
				checkCorrectPass = 0;
				break;
			}
		}
		if (checkCorrectPass == 1)
			{
			//Actions if Password is correct
//			LCD_GoTo( 7,2);
//			LCD_WriteCharacter('G');
			LCD_WriteInstruction(LCD_Clear);
			LCD_GoTo( 0,1);
			LCD_WriteString("Welcome !");
			//LED_ON(PORTA, PIN3);
			PWM1_SetDutyCycle(5);
			_delay_ms(300);
			PWM1_SetDutyCycle(0);
			//PWM1_Stop();
			//LED_OFF(PORTA, PIN3);

			count_pass=0;
			}
		else
			{
			//Actions if Password is wrong still has trials
			//LCD_GoTo( 7,2);
			//LCD_WriteCharacter('B');
			//LCD_GoTo( 1,2);
			count_pass++;
		//	LCD_WriteString("Wrong Try Again");
				if (count_pass>=3)
				{
					//Entered Pass wrong for three times
					//Wrong Pass Mode
					//Actions if Password is wrong and no more trials
					LCD_WriteInstruction(LCD_Clear);
					LCD_GoTo( 0,1);
					LCD_WriteString("Wrong Password");

					//Buzzer not LED
					LED_ON(PORTA, PIN4);
					_delay_ms(300);
					LED_OFF(PORTA, PIN4);
					i=6;
					count_pass=0;
				}
				else
				{
					LCD_GoTo( 1,2);
					LCD_WriteString("Wrong Try Again");
					//User have chance to try again
					LCD_WriteInstruction(LCD_Clear);
					LCD_GoTo( 0,1);
					LCD_WriteString("1.Password:");
					LCD_GoTo( 11,1);
					i=0;
				}
			}
}

void resetFunc(u8 * userInputPass)
{
	TIMER0_Reset();
	//TIMER0_Stop();
	i= 0;
	passwordToken = 0;
	defaultPassIndex= 0;
	loginToken = 0;

	for (u8 j=0;j<8;j++)
	{
		userInputPass[j] = 0 ;
	}

	LCD_WriteInstruction(LCD_Clear);
	LCD_GoTo( 0,1);
	LCD_WriteString("1.Password:");
	LCD_GoTo( 1,2);
	LCD_WriteString("2.Login.");
	modes= 0;
}
