

#include <stdio.h>
#include <stdlib.h>
#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"


int main(void)
{
  // At this stage the system clock should have already been configured
  // at high speed.

  // Infinite loop
	RCC_enuSelectSystemClock(RCC_enuClock_HSE);
	RCC_enuSetAHB1PerClock(RCC_enuGPIOC_EN,RCC_enuPerEnable);
	LED_enuInit();

	//LED_enuSetLedState(LED_Alarm,STATE_LED_ON);
	//LED_enuSetLedState(LED_Alarm,STATE_LED_OFF);

  while (1)
    {
       // Add your code here.
    }
}



// ----------------------------------------------------------------------------
