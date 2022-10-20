 /******************************************************************************
 *
 * Module: external interrupt
 *
 * File Name:  external_interrupt.c
 *
 * Description: Source file for the AVR external interrupt driver
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "external_interrupt.h"
#include "external_interrupt_lib.h"
#include "../registers.h"
#include "../../Util/common_macros.h"
#include "../../Util/std_types.h"

/*******************************************************************************
 *                            Static Functions Prototypes                      *
 *******************************************************************************/
/*
 * Function Name: INT0_setCallBack
 * Parameters: void (*callBack_ptr)(void): a pointer to function.
 * Return Value: void
 * Description: Function to set the call back function of INT0
 */
static void INT0_setCallBack (void (*callBack_ptr)(void));

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
static volatile void (*g_INT0_callBack_ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                                   ISRs                                      *
 *******************************************************************************/
ISR(INT0_vect) {
#if INT0_Nesting == INT_EnableNesting
	SREG |= (1 << I_POSITION);	/* enable the global interrupt for interrupt nesting */
#endif
	(*g_INT0_callBack_ptr)();
}

/*******************************************************************************
 *                                 Functions                                   *
 *******************************************************************************/
static void INT0_setCallBack(void (*callBack_ptr)(void)) {
	g_INT0_callBack_ptr = callBack_ptr;
}


INT_ErrorType INT0_init(INT0_INT1_Sense_Control sensitivity, void (*callBack_ptr)(void)) {
	if(sensitivity > INT0_INT1_risingEdge){
		return INT_ERROR;
	}
	else if(callBack_ptr == NULL_PTR){
		return INT_ERROR;
	}
	INT0_setCallBack(callBack_ptr);		/*setting the call back function*/
	CLEAR_BIT(SREG, I_POSITION); /* disable the global interrupt by clearing the I bit in SREG */
	CLEAR_BIT(DDRD, PD2); /* initialize PD2 (INT0) as input pin */

#if INT0_InternalPullUp == INT_InternalPullUpEnable
	SET_BIT(PORTD, PD2); /* enable the pull up resistor on PD2(INT0) pin */
#endif
	/* Clearing bits 0(ISC00) ,1(ISC10) of the MCUCR register
	 *  extracting the first two bits of the variable sensitivity and inserting them in MCUCR
	 *  Summary: ISC01 ISC00 = first two bits of sensitivity variable */
	MCUCR = (MCUCR & 0xFC) | (sensitivity & 0x03);
	SET_BIT(GICR, INT0_POSITION); /* enable INT0 */
	SET_BIT(SREG, I_POSITION); /* enable the global interrupt by setting the I bit in SREG */
	return INT_OK;
}

