/*
 * SWITCH.h
 *
 *  Created on: Feb 22, 2023
 *      Author: dell
 */

#ifndef SWITCH_H
#define SWITCH_H

void SWITCH_INIT(u8 Port_ID,u8 Pin_Id);

void SWITCH_GET_VAL(u8 Port_ID,u8 Pin_ID,u8 PinReading);

void SWITCH_DIPTHREE_INIT(u8 Port_ID);




#endif /* HAL_SWITCH_SWITCH_H_ */
