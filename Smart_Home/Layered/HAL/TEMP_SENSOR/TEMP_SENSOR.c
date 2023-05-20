/*
 * TEMP_SENSOR.c
 *
 *  Created on: Mar 27, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "TEMP_SENSOR_Interface.h"

u16 TEMP_Reading(u8 ADC_CHANNEL)
{
	u16 ADC_Reading = ADC_READ(ADC_CHANNEL);
	f32 volt = ((u32)(ADC_Reading * 5000))/1024.0;
	f32 Temp = volt/10.0;
	return Temp;
}
