/*
 * LED.h
 *
 *  Created on: Feb 11, 2023
 *      Author: dell
 */

#ifndef LED_H
#define LED_H

void LED_INIT(u8 Port_ID,u8 Pin_Id);

void LED_ON(u8 Port_ID,u8 Pin_Id);

void LED_OFF(u8 Port_ID,u8 Pin_Id);

void LED_TOG(u8 Port_ID,u8 Pin_Id);


#endif /* HAL_LED_LED_H_ */
