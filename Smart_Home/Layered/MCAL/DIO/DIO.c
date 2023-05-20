/*
 * DIO.c
 *
 *  Created on: Feb 10, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../STD_LIB/BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Registers.h"
#include "DIO_Config.h"

void DIO_INIT(void)
{

  DDRA_REG  = Conc(DIO_PORTA_PIN7_INIT_DIR, DIO_PORTA_PIN6_INIT_DIR, DIO_PORTA_PIN5_INIT_DIR, DIO_PORTA_PIN4_INIT_DIR, DIO_PORTA_PIN3_INIT_DIR, DIO_PORTA_PIN2_INIT_DIR, DIO_PORTA_PIN1_INIT_DIR, DIO_PORTA_PIN0_INIT_DIR);
  DDRB_REG  = Conc(DIO_PORTB_PIN7_INIT_DIR, DIO_PORTB_PIN6_INIT_DIR, DIO_PORTB_PIN5_INIT_DIR, DIO_PORTB_PIN4_INIT_DIR, DIO_PORTB_PIN3_INIT_DIR, DIO_PORTB_PIN2_INIT_DIR, DIO_PORTB_PIN1_INIT_DIR, DIO_PORTB_PIN0_INIT_DIR);
  DDRC_REG  = Conc(DIO_PORTC_PIN7_INIT_DIR, DIO_PORTC_PIN6_INIT_DIR, DIO_PORTC_PIN5_INIT_DIR, DIO_PORTC_PIN4_INIT_DIR, DIO_PORTC_PIN3_INIT_DIR, DIO_PORTC_PIN2_INIT_DIR, DIO_PORTC_PIN1_INIT_DIR, DIO_PORTC_PIN0_INIT_DIR);
  DDRD_REG  = Conc(DIO_PORTD_PIN7_INIT_DIR, DIO_PORTD_PIN6_INIT_DIR, DIO_PORTD_PIN5_INIT_DIR, DIO_PORTD_PIN4_INIT_DIR, DIO_PORTD_PIN3_INIT_DIR, DIO_PORTD_PIN2_INIT_DIR, DIO_PORTD_PIN1_INIT_DIR, DIO_PORTD_PIN0_INIT_DIR);

  PORTA_REG  = Conc(DIO_PORTA_PIN7_INIT_VAL, DIO_PORTA_PIN6_INIT_VAL, DIO_PORTA_PIN5_INIT_VAL, DIO_PORTA_PIN4_INIT_VAL, DIO_PORTA_PIN3_INIT_VAL, DIO_PORTA_PIN2_INIT_VAL, DIO_PORTA_PIN1_INIT_VAL, DIO_PORTA_PIN0_INIT_VAL);
  PORTB_REG  = Conc(DIO_PORTB_PIN7_INIT_VAL, DIO_PORTB_PIN6_INIT_VAL, DIO_PORTB_PIN5_INIT_VAL, DIO_PORTB_PIN4_INIT_VAL, DIO_PORTB_PIN3_INIT_VAL, DIO_PORTB_PIN2_INIT_VAL, DIO_PORTB_PIN1_INIT_VAL, DIO_PORTB_PIN0_INIT_VAL);
  PORTC_REG  = Conc(DIO_PORTC_PIN7_INIT_VAL, DIO_PORTC_PIN6_INIT_VAL, DIO_PORTC_PIN5_INIT_VAL, DIO_PORTC_PIN4_INIT_VAL, DIO_PORTC_PIN3_INIT_VAL, DIO_PORTC_PIN2_INIT_VAL, DIO_PORTC_PIN1_INIT_VAL, DIO_PORTC_PIN0_INIT_VAL);
  PORTD_REG  = Conc(DIO_PORTD_PIN7_INIT_VAL, DIO_PORTD_PIN6_INIT_VAL, DIO_PORTD_PIN5_INIT_VAL, DIO_PORTD_PIN4_INIT_VAL, DIO_PORTD_PIN3_INIT_VAL, DIO_PORTD_PIN2_INIT_VAL, DIO_PORTD_PIN1_INIT_VAL, DIO_PORTD_PIN0_INIT_VAL);

}

u8 DIO_SetPinDirection(u8 Port_ID,u8 Pin_ID, u8 Pin_Dir)
{
	u8 ErroState =0;
	if (Pin_ID >= PIN0 && Pin_ID <=PIN7 )
	{
		if (Pin_Dir == OUTPUT)
		{
            switch(Port_ID)
            {
            case PORTA:SET_BIT(DDRA_REG,Pin_ID);break;
            case PORTB:SET_BIT(DDRB_REG,Pin_ID);break;
            case PORTC:SET_BIT(DDRC_REG,Pin_ID);break;
            case PORTD:SET_BIT(DDRD_REG,Pin_ID);break;
            default: ErroState=DIO_PortOutOfRange; break;
            //use default to comply with mezra c
            }
		}
		else if (Pin_Dir == INPUT)
		{
			 switch(Port_ID)
			       {
			       case PORTA:CLR_BIT(DDRA_REG,Pin_ID);break;
			       case PORTB:CLR_BIT(DDRB_REG,Pin_ID);break;
			       case PORTC:CLR_BIT(DDRC_REG,Pin_ID);break;
			       case PORTD:CLR_BIT(DDRD_REG,Pin_ID);break;
			       default: ErroState=DIO_PortOutOfRange; break;
			       //use default to comply with mezra c
			       }
		}
		else
		{
			ErroState = DIO_DirectionNotCorrect;
		}
	}
	else
	{
		ErroState=DIO_PinOutOfRange;
	}
	return ErroState;
}

u8 DIO_SetPinValue(u8 Port_ID,u8 Pin_ID, u8 Pin_Val)
{
	u8 ErroState =0;
	if (Pin_ID >= PIN0 && Pin_ID <=PIN7 )
		{
			if (Pin_Val == HIGH)
			{
	            switch(Port_ID)
	            {
	            case PORTA:SET_BIT(PORTA_REG,Pin_ID);break;
	            case PORTB:SET_BIT(PORTB_REG,Pin_ID);break;
	            case PORTC:SET_BIT(PORTC_REG,Pin_ID);break;
	            case PORTD:SET_BIT(PORTD_REG,Pin_ID);break;
	            default: ErroState=DIO_PortOutOfRange; break;
	            //use default to comply with mezra c
	            }
			}
			else if (Pin_Val == LOW)
			{
				 switch(Port_ID)
				  {
				    case PORTA:CLR_BIT(PORTA_REG,Pin_ID);break;
				    case PORTB:CLR_BIT(PORTB_REG,Pin_ID);break;
				    case PORTC:CLR_BIT(PORTC_REG,Pin_ID);break;
				    case PORTD:CLR_BIT(PORTD_REG,Pin_ID);break;
				    default: ErroState=DIO_PortOutOfRange; break;
				    //use default to comply with mezra c
				   }
			}
			else
			{
				ErroState=DIO_ValueNotCorrect;
			}
		}
		else
		{
			ErroState=DIO_PinOutOfRange;
		}
	return ErroState;
}

u8 DIO_ReadPin(u8 Port_ID,u8 Pin_ID,u8 * Pin_Reading)
{
	u8 ErroState =0;
	* Pin_Reading=0;
	if (Pin_ID >= PIN0 && Pin_ID <=PIN7 )
			{

		            switch(Port_ID)
		            {
		            case PORTA:* Pin_Reading = GET_BIT(PINA_REG,Pin_ID);break;
		            case PORTB:* Pin_Reading = GET_BIT(PINB_REG,Pin_ID);break;
		            case PORTC:* Pin_Reading = GET_BIT(PINC_REG,Pin_ID);break;
		            case PORTD:* Pin_Reading = GET_BIT(PIND_REG,Pin_ID);break;
		            default: ErroState=DIO_PortOutOfRange; break;
		            //use default to comply with mezra c
		            }
			}
			else
			{
				ErroState=DIO_PinOutOfRange;
			}
	return ErroState;
}

u8 DIO_TogglePin(u8 Port_ID,u8 Pin_ID)
{
	u8 ErroState =DIO_OK;

		if (Pin_ID >= PIN0 && Pin_ID <=PIN7 )
				{

			            switch(Port_ID)
			            {
			            case PORTA:TOG_BIT(PORTA_REG,Pin_ID);break;
			            case PORTB:TOG_BIT(PORTB_REG,Pin_ID);break;
			            case PORTC:TOG_BIT(PORTC_REG,Pin_ID);break;
			            case PORTD:TOG_BIT(PORTD_REG,Pin_ID);break;
			            default: ErroState=DIO_PortOutOfRange; break;
			            //use default to comply with mezra c
			            }
				}
		else
		       {
			ErroState=DIO_PinOutOfRange;
		       }
		return ErroState;
}


u8 DIO_SetPortDirection(u8 Port_ID, u8 Port_Dir)
{
	u8 ErroState =DIO_OK;

  if (Port_ID >= PORTA && Port_ID <=PORTD && Port_Dir>=0 && Port_Dir<=255)
  {
	  if (Port_Dir == OUTPUT_PORT)
	  {
		  switch (Port_ID)
	      {
		    case PORTA: SET_REG(DDRA_REG);break;
		    case PORTB: SET_REG(DDRB_REG);break;
            case PORTC: SET_REG(DDRC_REG);break;
		 	case PORTD: SET_REG(DDRD_REG);break;
		 	//default: ErroState=DIO_PortOutOfRange; break;
	      }
	  }
	  else if (Port_Dir == INPUT_PORT)
	  {
		  switch (Port_ID)
		  {
		   case PORTA: CLR_REG(DDRA_REG);break;
		   case PORTB: CLR_REG(DDRB_REG);break;
		   case PORTC: CLR_REG(DDRC_REG);break;
		   case PORTD: CLR_REG(DDRD_REG);break;
		   //default: ErroState=DIO_PortOutOfRange; break;
		  }
	  }
	  else
	 		 	  {
		  switch (Port_ID)
		  	 {
		  	case PORTA: DDRA_REG=Port_Dir;break;
		  	case PORTB: DDRB_REG=Port_Dir;break;
		  	case PORTC: DDRC_REG=Port_Dir;break;
		  	case PORTD: DDRD_REG=Port_Dir;break;
		  	//default: ErroState=DIO_PortOutOfRange; break;
		  	}
	 		 	  }
  }
  else
 		 	  {
	  ErroState=DIO_ERROR;
 		 	  }
  return ErroState;
}

u8 DIO_SetPortValue(u8 Port_ID, u8 Port_Val )
{
	u8 ErroState =DIO_OK;
	 if (Port_ID >= PORTA && Port_ID <=PORTD && Port_Val>=0 && Port_Val<=255)
	 {
		 if (Port_Val == HIGH_PORT)
		 	  {
		 		  switch (Port_ID)
		 	      {
		 		    case PORTA: SET_REG(PORTA_REG);break;
		 		    case PORTB: SET_REG(PORTB_REG);break;
		            case PORTC: SET_REG(PORTC_REG);break;
		 		 	case PORTD: SET_REG(PORTD_REG);break;
		 		 	//default: ErroState=DIO_PortOutOfRange; break;
		 	      }
		 	  }
		 	  else if (Port_Val == LOW_PORT)
		 	  {
		 		  switch (Port_ID)
		 		  {
		 		   case PORTA: CLR_REG(PORTA_REG);break;
		 		   case PORTB: CLR_REG(PORTB_REG);break;
		 		   case PORTC: CLR_REG(PORTC_REG);break;
		 		   case PORTD: CLR_REG(PORTD_REG);break;
		 		   //default: ErroState=DIO_PortOutOfRange; break;
		 		  }
		 	  }
		 	  else
		 	  {
		 		 switch (Port_ID)
		 		{
		 			case PORTA: PORTA_REG=Port_Val;break;
		 			case PORTB: PORTB_REG=Port_Val;break;
		 			case PORTC: PORTC_REG=Port_Val;break;
		 			case PORTD: PORTD_REG=Port_Val;break;
		 			//default: ErroState=DIO_PortOutOfRange; break;
		 				  	}
		 	  }
	 }
	 else
			 	  {
		 ErroState=DIO_ERROR;
			 	  }
	  return ErroState;
}

u8 DIO_ReadPort(u8 Port_ID,u8 * PortReading)
{
	u8 ErroState =DIO_OK;
	* PortReading = 0;
	 if (Port_ID >= PORTA && Port_ID <=PORTD)
	 {
		 switch (Port_ID)
		  {
		          case PORTA: *PortReading = GET_REG(PINA_REG);break;
		          case PORTB: *PortReading = GET_REG(PINB_REG);break;
		 		  case PORTC: *PortReading = GET_REG(PINC_REG);break;
		 		  case PORTD: *PortReading = GET_REG(PIND_REG);break;
		 		  default: ErroState=DIO_PortOutOfRange; break;
		 }
	 }
	 else
	 {
		 ErroState=DIO_ERROR;
	 }
	 return ErroState;
}

u8 DIO_TogglePort(u8 Port_ID)
{
	u8 ErroState =DIO_OK;
	if (Port_ID >= PORTA && Port_ID <=PORTD)
	{
		switch (Port_ID)
		 {
			 case PORTA: TOG_REG(PORTA_REG);break;
			 case PORTB: TOG_REG(PORTB_REG);break;
			 case PORTC: TOG_REG(PORTC_REG);break;
			 case PORTD: TOG_REG(PORTD_REG);break;
			 default: ErroState=DIO_PortOutOfRange; break;
		 }
	}
	 return ErroState;
}


