/*
 * SWITCH_Cfg.c
 *
 *  Created on: 23 Feb 2023
 *      Author: naglaaa
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "SWITCH_Cfg.h"
#include "SWITCH.h"


/******************MODE OPTIONS**************************
			1)SWITCH_MODE_INTERNAL_PULLUP
			2)SWITCH_MODE_INTERNAL_PULLDOWN
			3)SWITCH_MODE_EXTERNAL_PULLUP
			4)SWITCH_MODE_EXTERNAL_PULLDOWN
*********************************************************/
const SWITCH_Cfg_t SWITCH_Cfg[SWITCHES_NUMBER] = {

	[SWITCH_START] =
	{
	    .Port = GPIO_enuPORTB,
	    .Pin = GPIO_enuPin0,
	    .Mode = SWITCH_MODE_INTERNAL_PULLUP,
		.Speed = GPIO_enuSpeed_VeryHigh

	},
/*
	[SWITCH_STOP] =
	{

		.Port = GPIO_enuPORTB,
		.Pin = GPIO_enuPin1,
		.Mode = SWITCH_MODE_INTERNAL_PULLDOWN,
		.Speed = GPIO_enuSpeed_VeryHigh
	},
*/
};

