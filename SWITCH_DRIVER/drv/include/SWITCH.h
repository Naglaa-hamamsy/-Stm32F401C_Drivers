/*
 * SWITCH.h
 *
 *  Created on: 23 Feb 2023
 *      Author: naglaaa
 */

#ifndef SWITCH_H_
#define SWITCH_H_
/*******************************TYPES****************************/
#define SWITCH_MODE_INTERNAL_PULLUP 0
#define SWITCH_MODE_INTERNAL_PULLDOWN 1
#define SWITCH_MODE_EXTERNAL_PULLUP 0
#define SWITCH_MODE_EXTERNAL_PULLDOWN 1
typedef enum
{
	SWITCH_enuOK,
	SWITCH_enuNOK,
	SWITCH_enuNullPtr
}SWITCH_tenuErrorStatus;

typedef enum
{
	SWITCH_enuPressed = 0,
	SWITCH_enuReleased,
	SWITCH_enuFloat

}SWITCH_States_t;

/*
typedef enum
{
	SWITCH_enuModeInternalPullUp = 0,
	SWITCH_enuModeInternalPullDown,
	SWITCH_enuModeExternalPullUp,
	SWITCH_enuModeExternalPullDown
}SWITCH_Modes_t;
*/
typedef struct
{
      GPIO_PORTS_t Port;
      GPIO_PINS_t Pin;
      GPIO_SPEEDS_t	Speed;
     u8 Mode;



}SWITCH_Cfg_t;

/*************************FUNCTION PROTOTYPES***************************/

/*****************************************
Description: Switch Initialization Function
Input: Void
Output: Switch Error Status
****************************************/
SWITCH_tenuErrorStatus SWITCH_enuInit(void);
/*****************************************
Description: Get Switch State Function
Input: Switch Pin , Pointer to hold the State of Switch

 **************** SWITCH PIN OPTIONS***************
             1) SWITCH_START
             2) SWITCH_STOP
 **************** SWITCH STATE OPTIONS***************
 	 	 	 1) SWITCH_enuPressed
             2) SWITCH_enuReleased

Output: Switch Error Status
****************************************/
SWITCH_tenuErrorStatus SWITCH_enuGetSwitchState(SWITCH_Pins_t Cpy_enuSwitch, SWITCH_States_t *Add_penuSwitchState);

/*****************************************
Description: Runnable To Handle Switch Debouncing
Input: Void
Output: Void
****************************************/
void Runnable_vidSwitchDebouncingHandling(void);
/*Array of struct SWITCH_Cfg_t*/
extern const SWITCH_Cfg_t SWITCH_Cfg[SWITCHES_NUMBER];

#endif /* SWITCH_H_ */
