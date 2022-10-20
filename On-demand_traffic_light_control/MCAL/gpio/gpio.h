 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_
/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "../../Util/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define 		NUM_OF_PORTS           4
#define 		NUM_OF_PINS_PER_PORT   8

#define 		PORTA_ID               0
#define 		PORTB_ID               1
#define 		PORTC_ID               2
#define 		PORTD_ID               3

#define 		PIN0_ID                0
#define 		PIN1_ID                1
#define 		PIN2_ID                2
#define 		PIN3_ID                3
#define 		PIN4_ID                4
#define 		PIN5_ID                5
#define 		PIN6_ID                6
#define 		PIN7_ID                7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

typedef enum{
	GPIO_OK = 3,
	GPIO_ERROR
}GPIO_ErrorType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Function Name: GPIO_setupPinDirection
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
GPIO_ErrorType GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/* Function Name: GPIO_writePin
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
GPIO_ErrorType GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Function Name: GPIO_readPin
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

#endif /* GPIO_H_ */
