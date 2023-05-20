/*
 * EXT_INT.c
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */
#include "../../STD_LIB/BIT_MATH.h"
#include "../../STD_LIB/STD_TYPES.h"
#include "EXT_INT_Interface.h"
#include "EXT_INT_Registers.h"
#include "EXT_INT_Config.h"
#include "../DIO/DIO_Interface.h"

void (*EXT1_PF)(void);
void (*EXT0_PF)(void);
void (*EXT2_PF)(void);
//ptr_to_func2

void EXT_INT_Enable(u8 INT_ID)
{
	if (INT_ID >= EXT_INT0 && INT_ID <=EXT_INT2)
	{
		switch(INT_ID)
		{
		case EXT_INT0:SET_BIT(GICR_REG,INT0);break;
		case EXT_INT1:SET_BIT(GICR_REG,INT1);break;
		case EXT_INT2:SET_BIT(GICR_REG,INT2);break;
		default:break;
		}
	}
	else
	{
		//report error state
	}
}

void EXT_INT_Disable(u8 INT_ID)
{
	if (INT_ID >= EXT_INT0 && INT_ID <=EXT_INT2)
	{
		switch(INT_ID)
		{
		case EXT_INT0:CLR_BIT(GICR_REG,INT0);break;
		case EXT_INT1:CLR_BIT(GICR_REG,INT1);break;
		case EXT_INT2:CLR_BIT(GICR_REG,INT2);break;
		default:break;
		}
	}
	else
	{
		//report error state
	}
}

void EXT_INT_SenseControl(u8 INT_ID,u8 INT_Trigger)
{
	if(INT_Trigger >= FallingEdge && INT_Trigger <= LowLevel )
	{
		if(INT_Trigger == FallingEdge)
		{
			switch(INT_ID)
			{
			case EXT_INT0:CLR_BIT(MCUCR_REG,ISC00);
			              SET_BIT(MCUCR_REG,ISC01);
			             break;
			case EXT_INT1:CLR_BIT(MCUCR_REG,ISC10);
                          SET_BIT(MCUCR_REG,ISC11);
                          break;
			case EXT_INT2:CLR_BIT(MCUCSR_REG,ISC2);
                          break;
			default:break;

			}
		}
		else if(INT_Trigger == RisingEdge)
				{
					switch(INT_ID)
					{
					case EXT_INT0:SET_BIT(MCUCR_REG,ISC00);
					              SET_BIT(MCUCR_REG,ISC01);
					             break;
					case EXT_INT1:SET_BIT(MCUCR_REG,ISC10);
		                          SET_BIT(MCUCR_REG,ISC11);
		                          break;
					case EXT_INT2:SET_BIT(MCUCSR_REG,ISC2);
		                          break;
					default:break;

					}
				}
		else if(INT_Trigger == OnChange)
					{
						switch(INT_ID)
						{
						case EXT_INT0:SET_BIT(MCUCR_REG,ISC00);
						              CLR_BIT(MCUCR_REG,ISC01);
						             break;
						case EXT_INT1:SET_BIT(MCUCR_REG,ISC10);
						              CLR_BIT(MCUCR_REG,ISC11);
			                          break;
						default:break;

						}
					}
		else if (INT_Trigger == LowLevel)
		{
			switch(INT_ID)
									{
									case EXT_INT0:CLR_BIT(MCUCR_REG,ISC00);
									              CLR_BIT(MCUCR_REG,ISC01);
									             break;
									case EXT_INT1:CLR_BIT(MCUCR_REG,ISC10);
									              CLR_BIT(MCUCR_REG,ISC11);
						                          break;
									default:break;

									}
		}

	}
}

void EXT_INT_ReturnFlag(u8 INT_ID,u8 * PIF)
{

	if (INT_ID >= EXT_INT0 && INT_ID <=EXT_INT2)
		{
			switch(INT_ID)
			{
			case EXT_INT0:*PIF = GET_BIT(GIFR_REG,INTF0);break;
			case EXT_INT1:*PIF =GET_BIT(GIFR_REG,INTF1);break;
			case EXT_INT2:*PIF =GET_BIT(GIFR_REG,INTF2);break;
			default:break;
			}
		}
		else
		{
			//report error state
		}
}


void EXT_INT1_CallBack(void(*PF)(void))
{
	//ptr_to_func2 = ptr_to_func;
	EXT1_PF = PF;

}

void EXT_INT0_CallBack(void(*PF)(void))
{
	//ptr_to_func2 = ptr_to_func;
	EXT0_PF = PF;

}

void EXT_INT2_CallBack(void(*PF)(void))
{
	//ptr_to_func2 = ptr_to_func;
	EXT2_PF = PF;

}

//ISR for INT1
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	//DIO_SetPinValue(PORTA,PIN4,HIGH);
	//ptr_to_func2;
	EXT1_PF();

}

//ISR for INT0
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	//DIO_SetPinValue(PORTA,PIN4,HIGH);
	//ptr_to_func2;
	EXT0_PF();
	//Do The highest priority only
	//Clear other flags
	/*
	SET_BIT(GIFR_REG,INTF1);
	SET_BIT(GIFR_REG,INTF2);
	*/

}

//ISR for INT2
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	//DIO_SetPinValue(PORTA,PIN4,HIGH);
	//ptr_to_func2;
	EXT2_PF();

}
