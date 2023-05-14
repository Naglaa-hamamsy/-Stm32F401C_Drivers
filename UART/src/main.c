
#include "STD_Types.h"
#include "BIT_Math.h"

#include "RCC2.h"
#include "GPIO.h"
#include "Systick_Cfg.h"
#include "Systick.h"
#include "LED_Cfg.h"
#include "LED.h"
#include "NVIC.h"
#include "UART_Cfg.h"
#include "UART.h"

extern void AppInit(void);


void SendDone(void)
{
	LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
}
void ReceiveDone(void)
{
	LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
}
void Systick_Func(void)
{
	static u8 data[7] = "naglaa";
	static u8 counter = 0;
	counter ++;
	if(counter % 1000 == 0)
	{
	UART_enuSendAsynchZeroCpy(UART_6, data , 7, SendDone);
	}

}
int main()
{


	//u8 data[7] = "naglaa";
u8 dataS[1] ={'a'};
u8 dataR[1] = {'k'};
	AppInit();
	LED_enuInit();
	//STK_enuSetCallBackFunction(Systick_Func);
	 //STK_vidEnableStkInterrupt();
	 //STK_enuSetStkClockSource(STK_CLOCK_AHB);
	 //STK_vidStop();
	 //STK_enuSetPeriodMilliSec(1);
	 //STK_vidStart();

	//UART_enuSendAsynchZeroCpy(UART_2, data , 1, NULL);


	//LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
	/*
	u8 k = 0;
		for(u8 i = 97;i<=124;i++)
		{
			data[k++] = i;
		}
*/

		//UART_enuSendAsynchZeroCpy(UART_6, data , 7, SendDone);
	//UART_enuReceiveAsynch(UART_6, data, 7, NULL);

while(1)
{
	//UART_enuSendAsynchZeroCpy(UART_2, data , 2, NULL);
	//UART_enuSendAsynchZeroCpy(UART_1 , data , 1 , NULL);

	UART_enuSendAsynchZeroCpy(UART_6, dataS ,1, NULL);


	UART_enuReceiveAsynch(UART_1, dataR, 1, NULL);
		if(dataR[0] == 'a')
			{
				LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
				}
		else if(dataR[0] == 'b')
		{
			LED_enuSetLedState(LED_Ledo,STATE_LED_OFF);
		}

	//UART_enuSendAsynchZeroCpy(UART_1, data , 1, NULL);
	//UART_enuReceiveAsynch(UART_2, data, 1, NULL);
	//if(data[0] == 'b')
		//{
			//LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
		//}
	/*UART_enuReceiveAsynch(UART_2, data, 1, NULL);
			if(data[0] == 'a')
				{
						LED_enuSetLedState(LED_Ledo,STATE_LED_ON);
					}
*/
	//UART_enuSendAsynchZeroCpy(UART_6, data , 1, NULL);


	//	UART_enuSendAsynchZeroCpy(UART_6, data ,7, NULL);
	//UART_enuSendAsynchZeroCpy(UART_6, data , 7, NULL);
}
}
