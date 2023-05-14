
#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
#include "GPIO.h"

int main(void)
{

	 GPIO_Cfg_t x;
	 u8 y;
	 u16 z;
		RCC_enuSelectSystemClock(RCC_enuClock_HSE);
		 RCC_enuSetAHB1PerClock(RCC_enuGPIOA_EN,RCC_enuPerEnable);
	 x.Port = GPIO_enuPORTA;
	 x.Pin =1;
	 x.Mode=GPIO_enuMode_Input_PullDown;
	 x.Speed=GPIO_enuSpeed_VeryHigh;
	 GPIO_enuInit(&x);
	// GPIO_enuSelectAF(GPIO_enuPORTA, GPIO_enuPin9, GPIO_enuAF1);
	 //GPIO_enuSetPortValue( GPIO_enuPORTA , 0b1111000011110000);
	 GPIO_enuWritePinValue(GPIO_enuPORTA , GPIO_enuPin3 , 1);

	 GPIO_enuGetPinValue( GPIO_enuPORTA, 1 , &y);
	 //GPIO_enuGetPortValue( GPIO_enuPORTA, &z);
	//u8 x;

		RCC_enuEnable_HSE();
		//  RCC_enuEnable_PLL();
		//  RCC_enuSetPLLConfig(RCC_enuSRC_HSE,50,200,2,10);
	  	 // RCC_enuEnable_PLL();
	  //RCC_enuSetPrescaler_AHB(AHB_PRESCALER_16);

		 // RCC_enuDisable_HSE();
	 //RCC_enuSelectSystemClock(RCC_enuClock_HSE);
		 // RCC_enuEnable_PLL();
		//  RCC_enuGetSysClock(&x);

	while(1)
		{

		}
}
