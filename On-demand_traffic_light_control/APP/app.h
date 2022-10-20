 /******************************************************************************
 *
 * Module: app
 *
 * File Name: app.h
 *
 * Description: Header file for the application
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

#ifndef APP_H_
#define APP_H_

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	STATE_NORMAL,
	STATE_PEDSTRIAN
}App_State;

typedef enum{
	TRAFFIC_GREEN,
	TRAFFIC_YELLOW,
	TRAFFIC_RED
}Cars_Traffic_State;

typedef enum{
	APP_OK,
	APP_ERROR
}App_ErrorType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Function Name: App_Init
 * Description :
 * Function to initialize modules used in the application
 */
App_ErrorType App_Init(void);

/*
 * Function Name: App_Start
 * Description :
 * Function to run the application
 */
App_ErrorType App_Start(void);

#endif /* APP_H_ */
