#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"
#include "NVIC_Cfg.h"
#include "NVIC.h"

u8 active = 0;
int
main(int argc, char* argv[])
{

	RCC_enuSetAHB1PerClock(RCC_enuGPIOA_EN,RCC_enuPerEnable);
	RCC_enuSetAHB1PerClock(RCC_enuGPIOB_EN,RCC_enuPerEnable);
  LED_enuInit();
 // NVIC_enuEnableIRQ(IRQn_SPI1);
  //NVIC_enuDisableIRQ(IRQn_SPI1);
  NVIC_enuEnableIRQ(IRQn_EXTI0);
  NVIC_enuEnableIRQ(IRQn_EXTI1);
  NVIC_enuSetPending(IRQn_EXTI0);
  //NVIC_enuDisableIRQ(IRQn_EXTI0);
  //NVIC_enuEnableIRQ(IRQn_EXTI1);
 // NVIC_enuSetPending(IRQn_SPI1);
//  NVIC_enuSetPending(IRQn_EXTI1);
 // NVIC_enuClearPending(IRQn_EXTI0);
  NVIC_enusetPriorityGrouping(NVIC_16G_0S);
  NVIC_enuSetPriority(IRQn_EXTI0 , NVIC_priority_10);
  NVIC_enuSetPriority(IRQn_EXTI1 , NVIC_priority_9);

//  LED_enuSetLedState(LED_Start,STATE_LED_ON);

  while (1)
    {
       // Add your code here.
    }
}

void EXTI0_IRQHandler (void)
{
	LED_enuSetLedState(LED_Start,STATE_LED_ON);

LED_enuSetLedState(LED_Ledo,STATE_LED_ON);

	/*if(active != 0)
		LED_enuSetLedState(LED_Warning,STATE_LED_ON);
		*/

//LED_enuSetLedState(LED_Start,STATE_LED_ON);
	NVIC_enuSetPending(IRQn_EXTI1);
LED_enuSetLedState(LED_Ledo,STATE_LED_OFF);

}
void EXTI1_IRQHandler (void)
{
	//LED_enuSetLedState(LED_Ledo,STATE_LED_OFF);
	LED_enuSetLedState(LED_Warning,STATE_LED_ON);
	//LED_enuSetLedState(LED_Start,STATE_LED_ON);
}

// ----------------------------------------------------------------------------
