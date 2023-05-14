#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"

const LED_CFG_t LED_CFG[LEDS_NUMBER] =
{
	[LED_Alarm] =
	{
			.Port =GPIO_enuPORTA,
			.Pin =GPIO_enuPin0,
			.Mode =LED_enuActiveHigh,
			.Speed = GPIO_enuSpeed_VeryHigh

		},
/*
	[LED_Warning] =
		{
			.Port =GPIO_enuPORTA,
			.Pin =GPIO_enuPin1,
			.Speed = GPIO_enuSpeed_VeryHigh

		},
/*
	[LED_Start] =
		{
			.Port =GPIO_enuPORTA,
			.Pin =GPIO_enuPin2,
			.Mode =LED_enuActiveLow,
			.Speed = GPIO_enuSpeed_VeryHigh

		},

	[LED_Stop] =
		{
			.Port =GPIO_enuPORTA,
			.Pin =GPIO_enuPin3,
			.Mode =LED_enuActiveLow,
			.Speed = GPIO_enuSpeed_VeryHigh

		}
		*/
};
