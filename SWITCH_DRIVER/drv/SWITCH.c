/*
 * SWITCH.c
 *
 *  Created on: 23 Feb 2023
 *      Author: naglaaa
 */

#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "SWITCH_Cfg.h"
#include "SWITCH.h"

static u8 TASK_SwitchNumber = 0;
static SWITCH_States_t TASK_SwitchState =SWITCH_enuFloat;

SWITCH_tenuErrorStatus SWITCH_enuInit(void)
{
	u8 Local_u8LoopCounter = 0;
	SWITCH_tenuErrorStatus Local_enuErrorStatus = SWITCH_enuOK;
	GPIO_Cfg_t SwitchCfg;

	/*ITERATE THROUGH ALL THE SWITCHES*/
	for(Local_u8LoopCounter = 0;Local_u8LoopCounter < SWITCHES_NUMBER ;Local_u8LoopCounter++)
	{
		SwitchCfg.Port = SWITCH_Cfg[Local_u8LoopCounter].Port;
		SwitchCfg.Pin = SWITCH_Cfg[Local_u8LoopCounter].Pin;
		SwitchCfg.Speed = SWITCH_Cfg[Local_u8LoopCounter].Speed;

		/*CHECK THE SWITCH MODE*/

		if( SWITCH_Cfg[Local_u8LoopCounter].Mode == SWITCH_MODE_INTERNAL_PULLUP)
		{
			SwitchCfg.Mode = GPIO_enuMode_Input_PullUp;
		}
		else if( SWITCH_Cfg[Local_u8LoopCounter].Mode ==SWITCH_MODE_INTERNAL_PULLDOWN)
		{
			SwitchCfg.Mode = GPIO_enuMode_Input_PullDown;
		}
		/*External Pull up or Pull Down*/
		else
		{
			SwitchCfg.Mode = GPIO_enuMode_Input_Floating;
		}

		GPIO_enuInit(&SwitchCfg);
	}
 return Local_enuErrorStatus;
}

/*SWITCH_tenuErrorStatus SWITCH_enuGetSwitchState(SWITCH_Pins_t Cpy_enuSwitch, SWITCH_States_t *Add_penuSwitchState)
{
	SWITCH_tenuErrorStatus Local_enuErrorStatus = SWITCH_enuOK;
	u8 Temp=2;

	if((Cpy_enuSwitch < 0) || (Cpy_enuSwitch >= SWITCHES_NUMBER))
	{
		Local_enuErrorStatus = SWITCH_enuNOK;
	}
	else if(Add_penuSwitchState == NULL)
	{
		Local_enuErrorStatus = SWITCH_enuNullPtr;

	}
	else
	{

		if(GPIO_enuGetPinValue(SWITCH_Cfg[Cpy_enuSwitch].Port,SWITCH_Cfg[Cpy_enuSwitch].Pin,&Temp) == GPIO_enuOK)
		{
				/*Floating will get the reading as it is

			 /*To abstract the user in application to check pull up &down with pressed and not pressed
				*Add_penuSwitchState = Temp ^ SWITCH_Cfg[Cpy_enuSwitch].Mode;

				Local_enuErrorStatus = SWITCH_enuOK;
		}
		else
		{
			Local_enuErrorStatus = SWITCH_enuNOK;
		}

	}

	return Local_enuErrorStatus;
}
*/
SWITCH_tenuErrorStatus SWITCH_enuGetSwitchState(SWITCH_Pins_t Cpy_enuSwitch, SWITCH_States_t *Add_penuSwitchState)
{
	SWITCH_tenuErrorStatus Local_enuErrorStatus = SWITCH_enuOK;
	if((Cpy_enuSwitch < 0) || (Cpy_enuSwitch >= SWITCHES_NUMBER))
	{
		Local_enuErrorStatus = SWITCH_enuNOK;
	}
	else if(Add_penuSwitchState == NULL)
	{
		Local_enuErrorStatus = SWITCH_enuNullPtr;

	}
	else
	{
		TASK_SwitchNumber = Cpy_enuSwitch;
		 * Add_penuSwitchState = TASK_SwitchState;
	}
}
void Runnable_vidSwitchDebouncingHandling(void)
{
	SWITCH_States_t Temp = SWITCH_enuReleased;
	SWITCH_States_t CurrentState = SWITCH_enuReleased;
	static SWITCH_States_t PreviousState = SWITCH_enuPressed;
	static u8 Counter = 0;

	if(GPIO_enuGetPinValue(SWITCH_Cfg[TASK_SwitchNumber].Port,SWITCH_Cfg[TASK_SwitchNumber].Pin,&Temp) == GPIO_enuOK)
	{
		CurrentState = Temp;
	}
	if(CurrentState == PreviousState)
	{
		Counter++ ;
	}
	else
	{
		Counter = 0;
	}
	if(Counter == 5)
	{
		TASK_SwitchState = CurrentState ^ SWITCH_Cfg[TASK_SwitchNumber].Mode;
		Counter = 0;
	}

		PreviousState = CurrentState;


}
