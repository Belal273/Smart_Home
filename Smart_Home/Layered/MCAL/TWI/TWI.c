/*
 * TWI.c
 *
 *  Created on: Apr 8, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../STD_LIB/BIT_MATH.h"

#include "TWI_Config.h"
#include "TWI_Interface.h"
#include "TWI_Registers.h"

#include "../DIO/DIO_Interface.h"

void TWI_MasterInit()
{
//	//set clock to 200kHz
//	TWBR_REG = 6;
//	//or from equation

	//set clock to 200KHz
		TWBR_REG = 2;
		CLR_BIT(TWSR_REG,0);
		CLR_BIT(TWSR_REG,1);
		//enable ack
		SET_BIT(TWCR_REG,6);
		//enable TWI circuit
		SET_BIT(TWCR_REG,2);
}

void TWI_SlaveInit(u8 address)
{
	//enable ack
		SET_BIT(TWCR_REG,6);
		//set address of slave
		TWAR_REG = address<<1;

		//enable TWI circuit
		SET_BIT(TWCR_REG,2);
}

void TWI_StartCondition()
{

	//start condition
	SET_BIT(TWCR_REG,5);
	//clear the flag
		SET_BIT(TWCR_REG,7);
	//wait until the flag is set
	while(GET_BIT(TWCR_REG,7) == 0);
	//Action happened but whicj action >> check on slave

	//Check on start condition status
//	if ( (TWSR_REG & 0xF8) != 0x08)
//	{
//		repport error
//	}
	while ((TWSR_REG & 0xF8) != 0x08);
	//DIO_SetPinValue(PORTA,PIN1,HIGH);
}

void TWI_StopCondition()
{
	//stop condition
		SET_BIT(TWCR_REG,4);
		//clear the flag
		SET_BIT(TWCR_REG,7);
	//wait until the flag is set
	//while(GET_BIT(TWCR_REG,7) == 0);
	//DIO_SetPinValue(PORTA,PIN3,HIGH);
}

void TWI_SendSlaveAddressWithWrite(u8 SlaveAdress)
{
	// All data on regster then download to bus
	//send slave address on TWDR
	TWDR_REG = SlaveAdress<<1;
	//write operation
	CLR_BIT(TWDR_REG,0);
	//Disable Start condition
		CLR_BIT(TWCR_REG,5);

	//clear the flag
	SET_BIT(TWCR_REG,7);

	//download on bus bit by bit
//	//clear the flag
//	SET_BIT(TWCR_REG,7);
//	//send slave address on TWDR
//	TWDR_REG = SlaveAdress<<1;
//	//write operation
//	CLR_BIT(TWDR_REG,0);
//	//clear the flag
//	SET_BIT(TWCR_REG,7);

	//wait until the flag is set
	while(GET_BIT(TWCR_REG,7) == 0);

	//check on SLA_W is transmitted status
	while((TWSR_REG & 0xF8) != 0x18);
	//DIO_SetPinValue(PORTA,PIN2,HIGH);
}

void TWI_SendSlaveAddressWithRead(u8 SlaveAdress)
{
	//send SLA on TWDR
		TWDR_REG = SlaveAdress<<1;
		//Read operation
		SET_BIT(TWDR_REG,0);
		//Disable Start condition
		CLR_BIT(TWCR_REG,5);
		//clear the flag
		SET_BIT(TWCR_REG,7);
		//wait until the flag is set
		while(GET_BIT(TWCR_REG,7) == 0);

		//check on SLA_R is Transimited status
		while((TWSR_REG & 0xF8) != 0x40);
	//DIO_SetPinValue(PORTA,PIN3,HIGH);
}

void TWI_MasterWriteData(u8 Data)
{


	//write data on TWDR register
	TWDR_REG = Data;

	//clear the flag
		SET_BIT(TWCR_REG,7);

	//wait until the flag is set
	while(GET_BIT(TWCR_REG,7) == 0);

	//check on Data is transmitted status
		while((TWSR_REG & 0xF8) != 0x28);
		//DIO_SetPinValue(PORTA,PIN4,HIGH);

}

u8 TWI_MasterReadData()
{
	//clear the flag
	SET_BIT(TWCR_REG,7);

	//wait until the flag is set
	while(GET_BIT(TWCR_REG,7) == 0);
	//check on Data is Received status
	while((TWSR_REG & 0xF8) != 0x28);
	return TWDR_REG;
}

void TWI_RepeatedStartCondition()
{
	//clear the flag
		SET_BIT(TWCR_REG,7);
		//start condition
		SET_BIT(TWCR_REG,5);
		//wait until the flag is set
		while(GET_BIT(TWCR_REG,7) == 0);
		//Action happened but whicj action >> check on slave

		//Check on Re-start condition status
		while ((TWSR_REG & 0xF8) != 0x10);
}

u8 TWI_SlaveReceiveData()
{
	/*Wait to receive the slave address*/
		while((TWSR_REG &0xf8 )!=0x60);
		//clear the flag
		SET_BIT(TWCR_REG,7);

		//wait until the flag is set
		while(GET_BIT(TWCR_REG,7) == 0);

		//check on Re-start condition status
		while((TWSR_REG & 0xF8) != 0x80);

		return TWDR_REG;
}

//u8 TWI_ReadStatusCode()
//{
//	u8 StatusCode = (TWSR_REG & 0xF8);
//
//
//	switch(StatusCode)
//	{
//	case 0x08:
//	}
//}
