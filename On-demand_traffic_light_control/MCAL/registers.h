 /******************************************************************************
 *
 * Module: Registers
 *
 * File Name: registers.h
 *
 * Description: Header file for the AVR registers
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "../Util/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* GPIO registers */
#define 			PORTA			(*((volatile uint8*)0x3B))
#define 			DDRA			(*((volatile uint8*)0x3A))
#define 			PINA			(*((volatile uint8*)0x39))

#define 			PORTB			(*((volatile uint8*)0x38))
#define 			DDRB			(*((volatile uint8*)0x37))
#define				PINB			(*((volatile uint8*)0x36))

#define 			PORTC			(*((volatile uint8*)0x35))
#define 			DDRC			(*((volatile uint8*)0x34))
#define 			PINC			(*((volatile uint8*)0x33))

#define 			PORTD			(*((volatile uint8*)0x32))
#define 			DDRD			(*((volatile uint8*)0x31))
#define 			PIND			(*((volatile uint8*)0x30))

/* TIMER0 registers */
#define 			TCNT0			(*(volatile uint8*)(0x52))
#define 			TCCR0			(*(volatile uint8*)(0x53))
#define 			TIMSK			(*(volatile uint8*)(0x59))
#define 			OCR0			(*(volatile uint8*)(0x5C))
#define 			TIFR			(*((volatile uint8*)0x58))


/* EXTERNAL INTERRUPT registers */
#define 			SREG			(*(volatile uint8*)(0x5F))
#define 			GICR			(*(volatile uint8*)(0x5B))
#define 			GIFR			(*(volatile uint8*)(0x5A))
#define 			MCUCR			(*(volatile uint8*)(0x55))
#define 			MCUCSR			(*(volatile uint8*)(0x54))

#endif /* REGISTERS_H_ */
