/*
 * EEPROM.c
 *
 *  Created on: Apr 14, 2023
 *      Author: dell
 */

#include "../../STD_LIB/STD_TYPES.h"
#include "../../STD_LIB/BIT_MATH.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Config.h"
#include "../../MCAL/TWI/TWI_Interface.h"

void EEPROM_WriteByte(u8 page,u8 location,u8 data)
{
	//Start Condition
	TWI_StartCondition();
	//SLA + W
	TWI_SendSlaveAddressWithWrite((EEPROM_FIXED_ADD) | (EEPROM_A2_Value<<2) | (page&3));
	//Send Location
	TWI_MasterWriteData(location);
	//Write data
	TWI_MasterWriteData(data);
	//Stop Condition
	TWI_StopCondition();
}

u8 EEPROM_ReadByte(u8 page,u8 location)
{
	u8 data = 0;
	//Start Condition
	TWI_StartCondition();
	//SLA + W
	TWI_SendSlaveAddressWithWrite((EEPROM_FIXED_ADD) | (EEPROM_A2_Value<<2) | (page&3));
	//Send Location
	TWI_MasterWriteData(location);
	//Repeat Start Condition with read
	TWI_RepeatedStartCondition();
	//SLA + R
	TWI_SendSlaveAddressWithRead((EEPROM_FIXED_ADD) | (EEPROM_A2_Value<<2) | (page&3));
//	//Send location
//	TWI_MasterWriteData(location);
	//Receive data
	data = TWI_MasterReadData();
	//Stop Condition
	TWI_StopCondition();

	return data;
}
