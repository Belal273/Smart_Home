/*
 * LDR.c
 *
 *  Created on: Mar 27, 2023
 *      Author: dell
 */
#include "../../STD_LIB/STD_TYPES.h"
#include "LDR_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"

u16 LDR_Reading(u8 ADC_CHA)
{
	u16 ADC_Reading = ADC_READ(ADC_CHA);
	u16 volt = ((u32)(ADC_Reading * 5000))/1024;
	return volt;
}

u8 LDR_Intensity_Level(u8 ADC_CHA)
{
	u16 LDR_Reading_Value = LDR_Reading(ADC_CHA);
	 if (LDR_Reading_Value>=0 && LDR_Reading_Value<= 1000)
		 return LDR_LEVEL_5;
	 else if (LDR_Reading_Value> 1000 && LDR_Reading_Value<= 2000)
			 return LDR_LEVEL_4;
	 else if (LDR_Reading_Value> 2000 && LDR_Reading_Value<= 3000)
	 			 return LDR_LEVEL_3;
	 else if (LDR_Reading_Value> 3000 && LDR_Reading_Value<= 4000)
	 			 return LDR_LEVEL_2;
	 else if (LDR_Reading_Value> 4000 && LDR_Reading_Value<= 5000)
	 			 return LDR_LEVEL_1;
	 else
		 return UnValid;
}

