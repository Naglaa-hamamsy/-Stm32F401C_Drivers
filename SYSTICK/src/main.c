#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"
#include "Systick_Cfg.h"
#include "Systick.h"


void Systick_Func(void);
int main(void)
{

	RCC_enuSetAHB1PerClock(RCC_enuGPIOA_EN,RCC_enuPerEnable);
		LED_enuInit();
STK_enuSetCallBackFunction(Systick_Func);
 STK_vidEnableStkInterrupt();
 STK_enuSetStkClockSource(STK_CLOCK_AHB);
 STK_vidStop();
 STK_enuSetPeriodMilliSec(1000);
 STK_vidStart();
// STK_vidStop();


  while (1)
    {
	//	LED_enuSetLedState(LED_Ledo, STATE_LED_TOGGLE);
    }
}
void Systick_Func(void)
{
	/*static u8 counter=0;
	counter++;
	if((counter % 100) ==0)
	{
		LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
	}
		if((counter % 200) ==0)
		{

			LED_enuSetLedState(LED_Ledo,STATE_LED_OFF);

		}
		*/

	LED_enuSetLedState(LED_Ledo, STATE_LED_TOGGLE);
	//LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
}

// ----------------------------------------------------------------------------
