/*
 * EXT_INT_Registers.h
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */

#ifndef EXT_INT_REGISTERS_H_
#define EXT_INT_REGISTERS_H_


#define GICR_REG    *((volatile u8 *)0x5B)
#define MCUCR_REG   *((volatile u8 *)0x55)
#define GIFR_REG    *((volatile u8 *)0x5A)
#define MCUCSR_REG  *((volatile u8 *)0x54)

enum GICR_REG_BITs
{
	IVCE,
	IVSE,
	INT2=5,
	INT0,
	INT1
};

enum MCUCR_REG_BITs
{
	ISC00,
	ISC01,
	ISC10,
	ISC11,
	SM0,
	SM1,
	SM2,
	SE
};

enum GIFR_REG_BITs
{
	INTF2=5,
	INTF0,
	INTF1

};

#define ISC2  6

#endif /* MCAL_EXT_INT_EXT_INT_REGISTERS_H_ */
