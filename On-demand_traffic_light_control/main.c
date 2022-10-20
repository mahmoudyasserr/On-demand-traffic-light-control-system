/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: Source file of the main function of the application
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/
#include <assert.h>
#include <stdlib.h>
#include "Util/common_macros.h"
#include "APP/app.h"
#include "MCAL/registers.h"
#include "MCAL/gpio/gpio.h"
#include "HAL/led/led.h"
#include "MCAL/timer/timer.h"
#include "MCAL/ext_int/external_interrupt.h"
#include "main.h"

#if CURRENTLY_RUNNING == GPIO_TESTING
static void GPIO_Testing(void);
#endif
#if CURRENTLY_RUNNING == TIMER_TESTING
static void Timer_Testing();
#endif
#if CURRENTLY_RUNNING == EXTERNAL_INTERRUPTS_TESTING
static void External_Interrupts_Testing(void);
#endif
#if CURRENTLY_RUNNING == LED_TESTING
static void Led_Testing(void);
#endif
int main(void) {
#if CURRENTLY_RUNNING == APPLICATION_RUNNING
	if (App_Init() == APP_ERROR) {
		abort();
	}
#endif
#if CURRENTLY_RUNNING == GPIO_TESTING
	GPIO_Testing();
#endif
#if CURRENTLY_RUNNING == TIMER_TESTING
	Timer_Testing();
#endif
#if CURRENTLY_RUNNING == EXTERNAL_INTERRUPTS_TESTING
	External_Interrupts_Testing();
#endif
#if CURRENTLY_RUNNING == LED_TESTING
Led_Testing();
#endif
	while (1) {
#if CURRENTLY_RUNNING == APPLICATION_RUNNING
		if (App_Start() == APP_ERROR) {
			abort();
		}
#endif
	}
	return 0;
}

#if CURRENTLY_RUNNING == GPIO_TESTING
static void GPIO_Testing(void) {
	GPIO_ErrorType status = GPIO_OK;
	uint8 value = 0;

	/* negative testing */
	status = GPIO_setupPinDirection(4, PIN0_ID, PIN_OUTPUT);
	assert(status == GPIO_ERROR);
	status = GPIO_writePin(PORTC_ID, 15, LOGIC_HIGH);
	assert(status == GPIO_ERROR);
	status = GPIO_readPin(8, 13);
	assert(status == GPIO_ERROR);

	/* positive testing */
	status = GPIO_setupPinDirection(PORTA_ID, PIN0_ID, PIN_OUTPUT);
	assert(status == GPIO_OK);
	status = GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_HIGH);
	assert(status == GPIO_OK);
	value = GPIO_readPin(PORTA_ID, PORTA_ID);
	assert(value == LOGIC_HIGH);
}
#endif

#if CURRENTLY_RUNNING == TIMER_TESTING
static void Timer_Testing() {
	Timer_ErrorType status = TIMER_OK;

	Led_Init(PORTA_ID, PIN0_ID);
	Led_Init(PORTA_ID, PIN1_ID);
	/* negative testing */
	status = Timer0_Init(9, 50);
	assert(status == TIMER_ERROR);
	status = Timer0_Delay_250ms(0);
	assert(status == TIMER_ERROR);

	/* positive testing */

	/* testing Timer0_Init function */
	Led_On(PORTA_ID, PIN0_ID);
	status = Timer0_Init(CLK_1024, 12);
	assert(status == TIMER_OK);
	while (GET_BIT(TIFR, TOV0_POSITION) == 0)
		;
	SET_BIT(TIFR, TOV0_POSITION);
	Led_Off(PORTA_ID, PIN0_ID);
	while (GET_BIT(TIFR, TOV0_POSITION) == 0)
		;
	SET_BIT(TIFR, TOV0_POSITION);
	Led_On(PORTA_ID, PIN0_ID);
	status = Timer0_Init(CLK_1024, 12);
	assert(status == TIMER_OK);
	while (GET_BIT(TIFR, TOV0_POSITION) == 0)
		;
	SET_BIT(TIFR, TOV0_POSITION);

	/* testing Timer0_Delay_250ms function */
	Led_On(PORTA_ID, PIN1_ID);
	status = Timer0_Delay_250ms(1);
	assert(status == TIMER_OK);
	Led_Off(PORTA_ID, PIN1_ID);
	status = Timer0_Delay_250ms(1);
	assert(status == TIMER_OK);
	Led_On(PORTA_ID, PIN1_ID);
	status = Timer0_Delay_250ms(1);
	assert(status == TIMER_OK);
}
#endif

#if CURRENTLY_RUNNING == EXTERNAL_INTERRUPTS_TESTING
void callBack(void) {
	Led_On(PORTA_ID, PIN1_ID);
}

static void External_Interrupts_Testing(void) {
	INT_ErrorType status = INT_OK;
	Led_Init(PORTA_ID, PIN1_ID);

	/* negative testing */
	status = INT0_init(5, callBack);
	assert(status == INT_ERROR);
	status = INT0_init(INT0_INT1_risingEdge, NULL_PTR);
	assert(status == INT_ERROR);

	/* positive testing */
	status = INT0_init(INT0_INT1_risingEdge, callBack);
	assert(status == INT_OK);
}
#endif

#if CURRENTLY_RUNNING == LED_TESTING
static void Led_Testing(void) {
	Led_ErrorType status = LED_OK;

	/* negative testing */
	status = Led_Init(4, PIN0_ID);
	assert(status == LED_OK);
	status = Led_On(4, PIN0_ID);
	assert(status == LED_ERROR);

	/* positive testing */
	status = Led_Init(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
	assert(status == LED_OK);
	status = Led_On(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
	assert(status == LED_OK);
}
#endif
