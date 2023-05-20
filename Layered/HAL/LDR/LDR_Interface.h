/*
 * LDR_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: dell
 */

#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

enum LDR_LEVELS
{
	LDR_LEVEL_1,
	LDR_LEVEL_2,
	LDR_LEVEL_3,
	LDR_LEVEL_4,
	LDR_LEVEL_5,
	UnValid
};

u16 LDR_Reading(u8 ADC_CHA);

u8 LDR_Intensity_Level(u8 ADC_CHA);

#endif /* HAL_LDR_LDR_INTERFACE_H_ */
