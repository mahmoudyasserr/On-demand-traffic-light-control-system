/******************************************************************************
 *
 * Module: led
 *
 * File Name: led.c
 *
 * Description: Source file for the AVR led driver
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

/*******************************************************************************
 *                                   Includes                                  *
 *******************************************************************************/
#include "led.h"
#include "../../Util/common_macros.h"

/*******************************************************************************
 *                               Functions                                     *
 *******************************************************************************/
Led_ErrorType Led_Init(uint8 ledPort, uint8 ledPin) {
	Led_ErrorType ledError = LED_OK;
	if (ledPort >= NUM_OF_PORTS) {
		ledError = LED_ERROR;
	} else if (ledPin >= NUM_OF_PINS_PER_PORT) {
		ledError = LED_ERROR;
	}
	if (GPIO_setupPinDirection(ledPort, ledPin, PIN_OUTPUT) == GPIO_ERROR) {
		ledError = LED_ERROR;
	}

	if (Led_Off(ledPort, ledPin) == LED_ERROR) {
		ledError = LED_ERROR;
	}
	return ledError;
}

Led_ErrorType Led_On(uint8 ledPort, uint8 ledPin) {
	Led_ErrorType ledError = LED_OK;
	if (ledPort > NUM_OF_PORTS) {
		ledError = LED_ERROR;
	} else if (ledPin > NUM_OF_PINS_PER_PORT) {
		ledError = LED_ERROR;
	}
	if (GPIO_writePin(ledPort, ledPin, LOGIC_HIGH) == GPIO_ERROR) {
		ledError = LED_ERROR;
	}
	return ledError;
}

Led_ErrorType Led_Off(uint8 ledPort, uint8 ledPin) {
	Led_ErrorType ledError = LED_OK;
	if (ledPort > NUM_OF_PORTS) {
		ledError = LED_ERROR;
	} else if (ledPin > NUM_OF_PINS_PER_PORT) {
		ledError = LED_ERROR;
	}
	if(GPIO_writePin(ledPort, ledPin, LOGIC_LOW) == GPIO_ERROR){
		ledError = LED_ERROR;
	}
	return ledError;
}

Led_ErrorType Leds_Init(void) {
	Led_ErrorType error = LED_OK;
	error = Led_Init(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN);
	if (error == LED_OK) {
		error = Led_Init(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN);
	}
	if (error == LED_OK) {
		error = Led_Init(CARS_RED_LED_PORT, CARS_RED_LED_PIN);
	}
	if (error == LED_OK) {
		error = Led_Init(PEDESTRIAN_GREEN_LED_PORT, PEDESTRIAN_GREEN_LED_PIN);
	}
	if (error == LED_OK) {
		error = Led_Init(PEDESTRIAN_YELLOW_LED_PORT, PEDESTRIAN_YELLOW_LED_PIN);
	}
	if (error == LED_OK) {
		error = Led_Init(PEDESTRIAN_RED_LED_PORT, PEDESTRIAN_RED_LED_PIN);
	}
	return error;
}
