 /******************************************************************************
 *
 * Module: led
 *
 * File Name: led.h
 *
 * Description: Header file for the AVR led driver
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

/*******************************************************************************
 *                                   Includes                                  *
 *******************************************************************************/
#include "../../MCAL/gpio/gpio.h"

/*******************************************************************************
 *                                 Configurations                              *
 *******************************************************************************/
#define 		CARS_GREEN_LED_PORT					PORTA_ID
#define 		CARS_GREEN_LED_PIN					PIN0_ID

#define 		CARS_YELLOW_LED_PORT				PORTA_ID
#define 		CARS_YELLOW_LED_PIN					PIN1_ID

#define 		CARS_RED_LED_PORT					PORTA_ID
#define 		CARS_RED_LED_PIN					PIN2_ID

#define 		PEDESTRIAN_GREEN_LED_PORT			PORTB_ID
#define 		PEDESTRIAN_GREEN_LED_PIN			PIN0_ID

#define 		PEDESTRIAN_YELLOW_LED_PORT			PORTB_ID
#define 		PEDESTRIAN_YELLOW_LED_PIN			PIN1_ID

#define 		PEDESTRIAN_RED_LED_PORT				PORTB_ID
#define 		PEDESTRIAN_RED_LED_PIN				PIN2_ID

/*******************************************************************************
 *                                  Defined Types                              *
 *******************************************************************************/
typedef enum{
	LED_OK,
	LED_ERROR
}Led_ErrorType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Function Name: Led_Init
 * Description :
 * Function to initialize a led
 */
Led_ErrorType Led_Init(uint8 ledPort, uint8 ledPin);

/*
 * Function Name: Led_On
 * Description :
 * Function to turn on a led
 */
Led_ErrorType Led_On(uint8 ledPort, uint8 ledPin);

/*
 * Function Name: Led_Off
 * Description :
 * Function to turn off a led
 */
Led_ErrorType Led_Off(uint8 ledPort, uint8 ledPin);

/*
 * Function Name: Leds_Init
 * Description :
 * Function to initialize the 6 leds
 * and initial value
 */
Led_ErrorType Leds_Init(void);

#endif /* LED_H_ */
