/*************************************************************************/
/*	Author:  AbdelRahman Ra'fat Hegazy									*/
/*	Date: 	 29/4/2022													*/
/*	Version: V01														*/
/*************************************************************************/


#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(reg,n) (reg|=(1<<n))
#define CLR_BIT(reg,n) (reg&=~(1<<n))
#define TOG_BIT(reg,n) (reg^=(1<<n))
#define GET_BIT(reg,n) (((reg)>>(n))&1)


#define GET_REG(reg)	(reg)
#define SET_REG(reg)	((reg)=0xFF)
#define CLR_REG(reg)	((reg)=0x00)
#define TOG_REG(reg)	((reg)^=0xFF)
#define ASSIGN_REG(reg,value)	((reg)=value)

#endif