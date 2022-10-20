/******************************************************************************
 *
 * Module: app
 *
 * File Name: app.c
 *
 * Description: Source file for the application
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "app.h"
#include "../HAL/led/led.h"
#include "../MCAL/ext_int/external_interrupt.h"
#include "../MCAL/timer/timer.h"


/*******************************************************************************
 *                            Static Functions Prototypes                      *
 *******************************************************************************/
/*
 * Function Name: INT0_CallBack
 * Description :
 * Callback function of INT0
 */
static void INT0_CallBack(void);

/*
 * Function Name: Cars_Go
 * Description :
 * Function to turn the green light of the cars traffic for 5 seconds
 */
static App_ErrorType Cars_Go(void);

/*
 * Function Name: Cars_Ready
 * Description :
 * Function to blink the yellow light of the cars traffic for 5 seconds
 */
static App_ErrorType Cars_Ready(void);

/*
 * Function Name: Cars_Pedestrains_Ready
 * Description :
 * Function to blink the yellow light of the cars traffic and the pedestrians traffic for 5 seconds
 */
static App_ErrorType Cars_Pedestrains_Ready(void);

/*
 * Function Name: Cars_Stop
 * Description :
 * Function to turn on the green light of the cars traffic for five seconds
 */
static App_ErrorType Cars_Stop(void);

/*
 * Function Name: Normal_Mode
 * Description :
 * Function to run in normal mode
 */
static App_ErrorType Normal_Mode(void);

/*
 * Function Name: Pedstrians_Go
 * Description :
 * Function to turn on green light of the pedestrians traffic
 */
static App_ErrorType Pedstrians_Go(void);

/*
 * Function Name: Pedstrians_Done
 * Description :
 * Function to turn off all lights of cars and pedestrians traffic
 */
static App_ErrorType Pedstrians_Done(void);

/*
 * Function Name: Traffic_Green_Or_Yellow_Handler
 * Description :
 * Function to handle the scenario if the button is pressed
 * in case of green or yellow cars traffic lights
 */
static App_ErrorType Traffic_Green_Or_Yellow_Handler(void);

/*
 * Function Name: Traffic_Red_Handler
 * Description :
 * Function to handle the scenario if the button is pressed
 * in case of red cars traffic lights
 */
static App_ErrorType Traffic_Red_Handler(void);

/*
 * Function Name: Pedestrian_Mode
 * Description :
 * Function to run in pedestrian mode
 */
static App_ErrorType Pedestrian_Mode(void);

/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/
static App_State currentState = STATE_NORMAL;
static Cars_Traffic_State trafficState;

/*******************************************************************************
 *                                  Functions                                  *
 *******************************************************************************/
static void INT0_CallBack(void) {
	/*
	 * if currentState is Normal:
	 * change the state to Pedestrian state
	 * switch to pedestrian mode
	 * return to Normal state
	 */
	if (currentState == STATE_NORMAL) {
		currentState = STATE_PEDSTRIAN;
		if(Pedestrian_Mode() == APP_ERROR){
			abort();
		}
		currentState = STATE_NORMAL;
	}
}

static App_ErrorType Cars_Go(void) {
	App_ErrorType error = APP_OK;
	trafficState = TRAFFIC_GREEN;
	if (Led_On(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN) == LED_ERROR) {
		error = APP_ERROR;
	}
	if (error == APP_OK) {
		if (Led_Off(CARS_RED_LED_PORT, CARS_RED_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}

	if (error == APP_OK) {
		if (Led_Off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}

	if (error == APP_OK) {
		if (Timer0_Delay_250ms(20) == TIMER_ERROR) {
			error = APP_ERROR;
		}
	}
	return error;
}

static App_ErrorType Cars_Ready(void) {
	App_ErrorType error = APP_OK;
	trafficState = TRAFFIC_YELLOW;
	if (error == APP_OK) {
		if (Led_Off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}
	if (error == APP_OK) {
		if (Led_Off(CARS_RED_LED_PORT, CARS_RED_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}

	for (uint8 i = 0; i < 5; i++) {
		if (error == APP_OK) {
			if (Led_On(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN)
					== LED_ERROR) {
				error = APP_ERROR;
			}
		}

		if (error == APP_OK) {
			if (Timer0_Delay_250ms(2) == TIMER_ERROR) {
				error = APP_ERROR;
			}
		}

		if (error == APP_OK) {
			if (Led_Off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN)
					== LED_ERROR) {
				error = APP_ERROR;
			}
		}

		if (error == APP_OK) {
			if (Timer0_Delay_250ms(2) == TIMER_ERROR) {
				error = APP_ERROR;
			}
		}
	}
	return error;
}

static App_ErrorType Cars_Pedestrains_Ready(void) {
	App_ErrorType error = APP_OK;
	trafficState = TRAFFIC_YELLOW;

	if (error == APP_OK) {
		if (Led_Off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}

	if (error == APP_OK) {
		if (Led_Off(CARS_RED_LED_PORT, CARS_RED_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}

	if (error == APP_OK) {
		if (Led_Off(PEDESTRIAN_GREEN_LED_PORT, PEDESTRIAN_GREEN_LED_PIN)
				== LED_ERROR) {
			error = APP_ERROR;
		}
	}

	if (error == APP_OK) {
		if (Led_Off(PEDESTRIAN_RED_LED_PORT, PEDESTRIAN_RED_LED_PIN)
				== LED_ERROR) {
			error = APP_ERROR;
		}
	}

	for (uint8 i = 0; i < 5; i++) {
		if (error == APP_OK) {
			if (Led_On(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN)
					== LED_ERROR) {
				error = APP_ERROR;
			}
		}

		if (error == APP_OK) {
			if (Led_On(PEDESTRIAN_YELLOW_LED_PORT, PEDESTRIAN_YELLOW_LED_PIN)
					== LED_ERROR) {
				error = APP_ERROR;
			}
		}

		if (error == APP_OK) {
			if (Timer0_Delay_250ms(2) == TIMER_ERROR) {
				error = APP_ERROR;
			}
		}
		if (error == APP_OK) {
			if (Led_Off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN)
					== LED_ERROR) {
				error = APP_ERROR;
			}
		}

		if (error == APP_OK) {
			if (Led_Off(PEDESTRIAN_YELLOW_LED_PORT, PEDESTRIAN_YELLOW_LED_PIN)
					== LED_ERROR) {
				error = APP_ERROR;
			}
		}

		if (error == APP_OK) {
			if (Timer0_Delay_250ms(2) == TIMER_ERROR) {
				error = APP_ERROR;
			}
		}
	}
	return error;
}

static App_ErrorType Cars_Stop(void) {
	trafficState = TRAFFIC_RED;
	App_ErrorType error = APP_OK;
	if (Led_Off(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN) == LED_ERROR) {
		error = APP_ERROR;
	}

	if (error == APP_OK) {
		if (Led_On(CARS_RED_LED_PORT, CARS_RED_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}

	if (error == APP_OK) {
		if (Led_Off(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}

	if (error == APP_OK) {
		if (Timer0_Delay_250ms(20) == TIMER_ERROR) {
			error = APP_ERROR;
		}
	}
	return error;
}

static App_ErrorType Normal_Mode(void) {
	App_ErrorType error = APP_OK;
	/*
	 * Turn on green
	 * Switch to yellow
	 * Switch to red
	 * Switch to yellow
	 */
	error = Cars_Go();
	if (error == APP_OK) {
		error = Cars_Ready();
	}
	if (error == APP_OK) {
		error = Cars_Stop();
	}
	if (error == APP_OK) {
		error = Cars_Ready();
	}
	return error;
}

static App_ErrorType Pedstrians_Go(void) {
	App_ErrorType error = APP_OK;
	if (Led_On(PEDESTRIAN_GREEN_LED_PORT, PEDESTRIAN_GREEN_LED_PIN)
			== LED_ERROR) {
		error = APP_ERROR;
	}

	if (error == APP_OK) {
		if (Led_Off(PEDESTRIAN_RED_LED_PORT, PEDESTRIAN_RED_LED_PIN)
				== LED_ERROR) {
			error = APP_ERROR;
		}
	}
	if (error == APP_OK) {
		if (Led_Off(PEDESTRIAN_YELLOW_LED_PORT, PEDESTRIAN_YELLOW_LED_PIN)
				== LED_ERROR) {
			error = APP_ERROR;
		}
	}
	return error;
}

static App_ErrorType Pedstrians_Done(void) {
	App_ErrorType error = APP_OK;
	if (Led_Off(PEDESTRIAN_GREEN_LED_PORT, PEDESTRIAN_GREEN_LED_PIN)
			== LED_ERROR) {
		error = APP_ERROR;
	}
	if (error == APP_OK) {
		if (Led_Off(CARS_RED_LED_PORT, CARS_RED_LED_PIN) == LED_ERROR) {
			error = APP_ERROR;
		}
	}
	return error;
}

static App_ErrorType Traffic_Green_Or_Yellow_Handler(void) {
	App_ErrorType error = APP_OK;
	/* Turn on yellow of both traffic lights for 5 seconds */
	if (Cars_Pedestrains_Ready() == APP_ERROR) {
		error = APP_ERROR;
	}
	/* Turn on green of pedestrians traffic and red of cars traffic */
	if (error == APP_OK) {
		if (Pedstrians_Go() == APP_ERROR) {
			error = APP_ERROR;
		}
	}
	if (error == APP_OK) {
		if (Cars_Stop() == APP_ERROR) {
			error = APP_ERROR;
		}
	}
	/* Turn off both traffic lights */
	if (error == APP_OK) {
		if (Pedstrians_Done() == APP_ERROR) {
			error = APP_ERROR;
		}
	}
	return error;
}

static App_ErrorType Traffic_Red_Handler(void) {
	App_ErrorType error = APP_OK;
	/* Turn on green of pedestrians traffic and red of cars traffic */
	if (Pedstrians_Go() == APP_ERROR) {
		error = APP_ERROR;
	}
	if (error == APP_OK) {
		if (Cars_Stop() == APP_ERROR) {
			error = APP_ERROR;
		}
	}

	/* Turn off both traffic lights */
	if (error == APP_OK) {
		if (Pedstrians_Done() == APP_ERROR) {
			error = APP_ERROR;
		}
	}
	return error;
}

static App_ErrorType Pedestrian_Mode(void) {
	App_ErrorType error = APP_OK;
	if ((trafficState == TRAFFIC_GREEN)) {
		if (Traffic_Green_Or_Yellow_Handler() == APP_ERROR) {
			error = APP_ERROR;
		}

		if (error == APP_OK) {
			if (Cars_Pedestrains_Ready() == APP_ERROR) {
				error = APP_ERROR;
			}
		}
		if (error == APP_OK) {
			if (Led_On(CARS_GREEN_LED_PORT, CARS_GREEN_LED_PIN) == LED_ERROR) {
				error = APP_ERROR;
			}
		}
		trafficState = TRAFFIC_GREEN;
	} else if (trafficState == TRAFFIC_YELLOW) {
		if (Traffic_Green_Or_Yellow_Handler() == APP_ERROR) {
			error = APP_ERROR;
		}

		if (error == APP_OK) {
			if (Cars_Pedestrains_Ready() == APP_ERROR) {
				error = APP_ERROR;
			}
		}
		if (error == APP_OK) {
			if (Led_On(CARS_YELLOW_LED_PORT, CARS_YELLOW_LED_PIN)
					== LED_ERROR) {
				error = APP_ERROR;
			}
		}
		trafficState = TRAFFIC_YELLOW;
	} else if (trafficState == TRAFFIC_RED) {
		if (Traffic_Red_Handler() == APP_ERROR) {
			error = APP_ERROR;
		}

		if (error == APP_OK) {
			if (Cars_Pedestrains_Ready() == APP_ERROR) {
				error = APP_ERROR;
			}
		}
		if (error == APP_OK) {
			if (Led_On(CARS_RED_LED_PORT, CARS_RED_LED_PIN) == LED_ERROR) {
				error = APP_ERROR;
			}
		}
		trafficState = TRAFFIC_RED;
	}
	return error;
}

App_ErrorType App_Init(void) {
	App_ErrorType error = APP_OK;

	if (Leds_Init() == LED_ERROR) {
		error = APP_ERROR;
	}
	if (error == APP_OK) {
		if (INT0_init(INT0_INT1_risingEdge, INT0_CallBack) == INT_ERROR) {
			error = APP_ERROR;
		}
	}
	return error;
}

App_ErrorType App_Start(void) {
	App_ErrorType error = APP_OK;
	if(Normal_Mode() == APP_ERROR){
		error = APP_ERROR;
	}
	return error;
}
