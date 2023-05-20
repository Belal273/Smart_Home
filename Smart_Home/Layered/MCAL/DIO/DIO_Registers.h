/*
 * DIO_Registers.h
 *
 *  Created on: Feb 10, 2023
 *      Author: dell
 */

#ifndef DIO_REGISTERS_H
#define DIO_REGISTERS_H

#define Conc(b7,b6,b5,b4,b3,b2,b1,b0)       Conc_Help(b7,b6,b5,b4,b3,b2,b1,b0)
#define Conc_Help(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0

#define PORTA_REG *((volatile u8*)0X3B)
#define DDRA_REG  *((volatile u8*)0X3A)
#define PINA_REG  *((volatile u8*)0X39)

#define PORTB_REG *((volatile u8*)0X38)
#define DDRB_REG  *((volatile u8*)0X37)
#define PINB_REG  *((volatile u8*)0X36)

#define PORTC_REG *((volatile u8*)0X35)
#define DDRC_REG  *((volatile u8*)0X34)
#define PINC_REG  *((volatile u8*)0X33)

#define PORTD_REG *((volatile u8*)0X32)
#define DDRD_REG  *((volatile u8*)0X31)
#define PIND_REG  *((volatile u8*)0X30)


#endif /* MCAL_DIO_DIO_REGISTERS_H_ */
