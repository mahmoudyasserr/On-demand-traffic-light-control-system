 /******************************************************************************
 *
 * Module: external interrupt
 *
 * File Name:  external_interrupt.h
 *
 * Description: Header file for the AVR external interrupt driver
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

/*******************************************************************************
 *                                 Definitions                                 *
 *******************************************************************************/
/* Disable internal pull up resistor of interrupt pin */
#define 		INT_InternalPullUpDisable 		0

/* Enable internal pull up resistor of interrupt pin */
#define 		INT_InternalPullUpEnable 		1

/* Disable interrupt nesting */
#define 		INT_DisableNesting 				0

/* Enable interrupt nesting */
#define 		INT_EnableNesting 				1

/* External Interrupt Pins */
#define			PD2								2
#define 		PD3								3
#define			PB2								2

/* External Interrupt Register Bits */
#define			I_POSITION						7
#define			INT0_POSITION					6
#define			INT1_POSITION					7
#define			INT2_POSITION					5
#define			ISC00_POSITION					0
#define 		ISC01_POSITION					1
#define 		ISC10_POSITION					2
#define 		ISC11_POSITION					3
#define 		ISC2_POSITION					6

/*******************************************************************************
 *                               Configurations                                *
 *******************************************************************************/
/*
 * Option to enable/disable internal pull up resistor of INT0 pin
 * Takes one of these Values (INT_InternalPullUpDisable , INT_InternalPullUpEnable)
 */
#define 		INT0_InternalPullUp 		INT_InternalPullUpDisable

/*
 * Option to enable/disable interrupt nesting of INT0
 * Takes one of these Values (INT_DisableNesting , INT_EnableNesting)
 */
#define 		INT0_Nesting 				INT_DisableNesting

/*******************************************************************************
 *                                 Type definitions                            *
 *******************************************************************************/
typedef enum{
	INT0_INT1_LowLevel,
	INT0_INT1_logicalChange,
	INT0_INT1_fallingEdge,
	INT0_INT1_risingEdge
} INT0_INT1_Sense_Control;


typedef enum{
	INT_OK,
	INT_ERROR
} INT_ErrorType;

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/*
 * Function Name: INT0_init
 * Parameters:
 				INT0_INT1_Sense_Control sensitivity: one of four sensitivity options:
 													INT0_INT1_LowLevel, INT0_INT1_logicalChange,
 													INT0_INT1_fallingEdge, INT0_INT1_risingEdge
   				void (*callBack_ptr)(void): a pointer to function
 * Return Value: void
 * Description: Function to initialize INT0 and set the call back function of INT0
 */
INT_ErrorType INT0_init(INT0_INT1_Sense_Control sensitivity, void (*callBack_ptr)(void)) ;


#endif /* EXTERNAL_INTERRUPT_H_ */
