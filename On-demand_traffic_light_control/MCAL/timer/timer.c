 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR timer0 driver (Overflow mode using polling)
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/
#include "../../Util/common_macros.h"
#include "../registers.h"
#include "timer.h"


/*******************************************************************************
 *                                 Functions                                   *
 *******************************************************************************/
Timer_ErrorType Timer0_Init(Timer0_Prescaler prescaler, uint8 initialValue) {
	if(prescaler > CLK_RISING){
		return TIMER_ERROR;
	}
	/*
	 * TCCR0: FOC0 = 1 (Non-PWM mode)
	 * TCCR0: CS02 CS01 CS00 = prescaler
	 * TCNT0 = initial value
	 */
	SET_BIT(TCCR0, FOC0_POSITION);

	TCCR0 = (TCCR0 & 0xF8) | (prescaler & 0x07);
	TCNT0 = initialValue;
	return TIMER_OK;

}

uint8 Timer0_GetCounts(void){
	return TCNT0;
}

void Timer0_SetCounts(uint8 counts){
	TCNT0 = counts;
}

void Timer0_Deinit(void) {
	TCCR0 = 0;
	TCNT0 = 0;
}

Timer_ErrorType Timer0_Delay_250ms(uint8 overflowsNum) {
	if(overflowsNum == 0){
		return TIMER_ERROR;
	}
	/*
	 * Delay = 250ms
	 * F(CPU) = 1MHZ
	 * Prescaler = 1024
	 * T(Tick) = 1.024 ms
	 * T(Max. Delay) = 0.262144 s
	 * Number of Overflows = 1
	 * Timer initial value = 12
	 */
	Timer0_Init(CLK_1024, 12);
	for (uint8 i = 0; i < overflowsNum; i++) {
		while (GET_BIT(TIFR, TOV0_POSITION) == 0)
			;
		SET_BIT(TIFR, TOV0_POSITION);
	}
	return TIMER_OK;
}

