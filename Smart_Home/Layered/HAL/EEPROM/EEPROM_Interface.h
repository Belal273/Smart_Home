/*
 * EEPROM_Interface.h
 *
 *  Created on: Apr 14, 2023
 *      Author: dell
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_WriteByte(u8 page,u8 location,u8 data);

u8 EEPROM_ReadByte(u8 page,u8 location);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
