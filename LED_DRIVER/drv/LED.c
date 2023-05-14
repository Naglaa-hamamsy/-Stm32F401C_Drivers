#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"
/******************************** FUNCTIONS IMPLEMENTATION***************************************/

LED_tenuErrorStatus LED_enuInit(void)
{
	u8 Local_u8LoopCounter = 0;
	GPIO_Cfg_t GpioCfg;
	for(Local_u8LoopCounter = 0;Local_u8LoopCounter < LEDS_NUMBER; Local_u8LoopCounter++)
	{
		GpioCfg.Port = LED_CFG[Local_u8LoopCounter].Port;
		GpioCfg.Pin = LED_CFG[Local_u8LoopCounter].Pin;
		GpioCfg.Mode = GPIO_enuMode_Output_PushPull;
		GpioCfg.Speed = LED_CFG[Local_u8LoopCounter].Speed;

		GPIO_enuInit(&GpioCfg);

	}
	return LED_enuOK;
}

LED_tenuErrorStatus LED_enuSetLedState(LED_PINS_t Cpy_enuLedPin, u8 Cpy_u8State )
{
	LED_tenuErrorStatus Local_enuErrorStatus = LED_enuOK;
	static State_Toggle = STATE_LED_ON;

	if((Cpy_enuLedPin < 0) || (Cpy_enuLedPin >= LEDS_NUMBER))
	{
		Local_enuErrorStatus = LED_enuNOK;
	}
	else if(Cpy_u8State == STATE_LED_TOGGLE)
	{
		State_Toggle ^= 1;
		if (GPIO_enuWritePinValue(LED_CFG[Cpy_enuLedPin].Port , LED_CFG[Cpy_enuLedPin].Pin, LED_CFG[Cpy_enuLedPin].Mode ^ STATE_LED_TOGGLE) == GPIO_enuOK)
					{
						Local_enuErrorStatus = LED_enuOK;
					}
	}

	else if((Cpy_u8State == STATE_LED_OFF) || (Cpy_u8State == STATE_LED_ON))
	{
		if (GPIO_enuWritePinValue(LED_CFG[Cpy_enuLedPin].Port , LED_CFG[Cpy_enuLedPin].Pin, LED_CFG[Cpy_enuLedPin].Mode ^ Cpy_u8State) == GPIO_enuOK)
				{
					Local_enuErrorStatus = LED_enuOK;
				}

	}
	else
	{
		Local_enuErrorStatus = LED_enuNOK;

	}

	return Local_enuErrorStatus;

}
