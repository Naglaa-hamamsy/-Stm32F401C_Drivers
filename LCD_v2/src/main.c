#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
#include "GPIO.h"
#include "LCD_cfg.h"
#include "LCD.h"

int main()
{
	RCC_enuSetAHB1PerClock(RCC_enuGPIOA_EN,RCC_enuPerEnable);
	RCC_enuSetAHB1PerClock(RCC_enuGPIOB_EN,RCC_enuPerEnable);
	LCD_vidInit();
	voidInitStm();

	while(1)
	{

	}
}
