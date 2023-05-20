/*
 * TWI_Registers.h
 *
 *  Created on: Apr 8, 2023
 *      Author: dell
 */

#ifndef TWI_REGISTERS_H_
#define TWI_REGISTERS_H_

#define TWBR_REG		*((volatile u8 *)0x20)
#define TWCR_REG		*((volatile u8 *)0x56)
#define TWSR_REG		*((volatile u8 *)0x21)
#define TWAR_REG		*((volatile u8 *)0x22)
#define TWDR_REG		*((volatile u8 *)0x23)

#endif /* MCAL_TWI_TWI_REGISTERS_H_ */
