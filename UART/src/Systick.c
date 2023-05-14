/*
 * Systick.c
 *
 *  Created on: 8 Mar 2023
 *      Author: naglaaa
 */

#include "STD_Types.h"
#include "BIT_Math.h"
#include "LED_Cfg.h"
#include "GPIO.h"
#include "LED.h"
#include "Systick_Cfg.h"
#include "Systick.h"

/*********************************DEFINES*************************************/
#define STK_ENABLE 0x00000001
#define STK_ENABLE_INTERRUPT 0x00000002
#define GetTickTime(x) 1/x
#define MAX_COUNTS 16777216
/*********************************TYPES*************************************/
typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}Systick_t;

volatile Systick_t * const STK = (volatile Systick_t*) 0xE000E010;

static CBF_t STK_NotifyFunc = NULL;


/*********************************FUNCTIONS IMPLEMENTATION************************************/
void STK_vidInit(void)
{
	/*Set Clock */
	STK->CTRL |= STK_CLOCK_SRC;
	/*Enable Systick Interrupt*/
	STK->CTRL |=STK_ENABLE_INTERRUPT;
}
void STK_vidStart(void)
{
	STK->CTRL |=STK_ENABLE;
}
void STK_vidStop(void)
{
	STK->CTRL &=~STK_ENABLE;
}
void STK_vidEnableStkInterrupt(void)
{
	STK->CTRL |=STK_ENABLE_INTERRUPT;
}
void STK_vidDisableStkInterrupt(void)
{
	STK->CTRL &= ~STK_ENABLE_INTERRUPT;
}
STK_tenuErrorStatus STK_enuSetCallBackFunction(CBF_t CBF)
{
	STK_tenuErrorStatus Local_enuErrorStatus = STK_enuOK;

	if(CBF == NULL)
	{
		Local_enuErrorStatus = STK_enuNullPtr;
	}
	else
	{
		STK_NotifyFunc = CBF;
	}
	return Local_enuErrorStatus;
}
STK_tenuErrorStatus STK_enuSetPeriodMilliSec(u16 Cpy_u16RequiredPeriod)
{
	STK_tenuErrorStatus Local_enuErrorStatus = STK_enuOK;
	u32 Counts = 0;


	if(STK->CTRL & STK_CLOCK_AHB)
	{
		Counts =((u64)Cpy_u16RequiredPeriod * STK_AHB_FREQ) /1000  ;
	}
	else
	{
		Counts = ((u64)Cpy_u16RequiredPeriod * STK_AHB_FREQ) /8000  ;
	}
	if(Counts <= MAX_COUNTS )
	{
		STK->LOAD = Counts-1;

	}
	else
	{
		Local_enuErrorStatus = STK_enuNOK;
	}
	return Local_enuErrorStatus;
}
STK_tenuErrorStatus STK_enuSetStkClockSource(u32 Cpy_u32Clock)
{
	STK_tenuErrorStatus Local_enuErrorStatus = STK_enuOK;

	if((Cpy_u32Clock == STK_CLOCK_AHB) || (Cpy_u32Clock == STK_CLOCK_AHB_DIV_8))
	{
		STK->CTRL |= Cpy_u32Clock;
	}
	else
	{
		Local_enuErrorStatus = STK_enuNOK;
	}
	return Local_enuErrorStatus;
}

void SysTick_Handler (void)
{
	if(STK_NotifyFunc != NULL)
	{
		STK_NotifyFunc();
	}
}
