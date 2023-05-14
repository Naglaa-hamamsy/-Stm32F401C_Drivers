#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"
#include "SWITCH_Cfg.h"
#include "SWITCH.h"
int main(void)
{ u8 ret=3,ret2=3;
  // At this stage the system clock should have already been configured
  // at high speed.

  // Infinite loop
	RCC_enuSelectSystemClock(RCC_enuClock_HSE);
	RCC_enuSetAHB1PerClock(RCC_enuGPIOB_EN,RCC_enuPerEnable);
	RCC_enuSetAHB1PerClock(RCC_enuGPIOA_EN,RCC_enuPerEnable);
	LED_enuInit();
	SWITCH_enuInit();

	//LED_enuSetLedState(LED_Warning,STATE_LED_ON);

	/*SWITCH_enuGetSwitchState(SWITCH_STOP,&ret2);
	if(ret2==SWITCH_enuPressed)
	{
		LED_enuSetLedState(LED_Warning,STATE_LED_OFF);
	}
	*/

//	LED_enuSetLedState(LED_Alarm,STATE_LED_ON);
	//LED_enuSetLedState(LED_Alarm,STATE_LED_OFF);

  while (1)
    {
		Runnable_vidSwitchDebouncingHandling();

	  SWITCH_enuGetSwitchState(SWITCH_START,&ret);
	  	if(ret==SWITCH_enuPressed)
	  	{
	  		LED_enuSetLedState(LED_Alarm,STATE_LED_ON);
	  	}
	  	else if(ret==SWITCH_enuReleased)
		  	{
		  		LED_enuSetLedState(LED_Alarm,STATE_LED_OFF);
		  	}
    }
}



// ----------------------------------------------------------------------------
