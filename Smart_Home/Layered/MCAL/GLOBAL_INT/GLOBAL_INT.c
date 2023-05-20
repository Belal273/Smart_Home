/*
 * GLOBAL_INT.c
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */

#include "../../STD_LIB/BIT_MATH.h"
#include "../../STD_LIB/STD_TYPES.h"
#include "GLOBAL_INT_Interface.h"
#include "GLOBAL_INT_Registers.h"

void GI_Enable(void)
{
	SET_BIT(SREG_REG,GIE);
}

void GI_Disable(void)
{
	CLR_BIT(SREG_REG,GIE);
}
