 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR timer0 driver
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/
#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "../../Util/std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/
#define 			FOC0_POSITION 			7
#define 			TOV0_POSITION 			0
/*******************************************************************************
 *                               Defined Types                                 *
 *******************************************************************************/
typedef enum {
	NO_CLK,
	CLK_1,
	CLK_8,
	CLK_64,
	CLK_256,
	CLK_1024,
	CLK_FALLING,
	CLK_RISING
} Timer0_Prescaler;

typedef enum{
	TIMER_OK,
	TIMER_ERROR
} Timer_ErrorType;
/*******************************************************************************
 *                             Function Prototypes                             *
 *******************************************************************************/
/*
 * Function Name: Timer0_Init
 * Description :
 * Function to initialize timer0 in the overflow mode and set its prescaler
 * and initial value
 */
Timer_ErrorType Timer0_Init(Timer0_Prescaler prescaler, uint8 initialValue);

/*
 * Function Name: Timer0_GetCounts
 * Description :
 * Function to return the value of TCNT0
 */
uint8 Timer0_GetCounts(void);

/*
 * Function Name: Timer0_SetCounts
 * Description :
 * Function to set the value of TCNT0
 */
void Timer0_SetCounts(uint8 counts);

/*
 * Function Name: Timer0_Deinit
 * Description :
 * Function to stop the timer
 */
void Timer0_Deinit(void);

/*
 * Function Name: Timer0_Delay_250ms
 * Description :
 * Function to make a 250ms delay per one overflow for 1MHZ clock
 */
Timer_ErrorType Timer0_Delay_250ms(uint8 overflowsNum);
#endif /* TIMER_TIMER_H_ */
