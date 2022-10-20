 /******************************************************************************
 *
 * Module: External Interrupts Library
 *
 * File Name: external_interrupt_lib.h
 *
 * Description: Header file for the AVR external interrupts library
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/
#ifndef INTERRUPT_LIB_H_
#define INTERRUPT_LIB_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define 			INT0_vect 					__vector_1
#define 			INT1_vect 					__vector_2
#define 			INT2_vect 					__vector_3

#define 			ISR(INT_VECT)				void INT_VECT(void) __attribute__ ((signal,used));\
												void INT_VECT(void)

#endif /* INTERRUPT_LIB_H_ */
