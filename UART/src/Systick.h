/*
 * Systick.h
 *
 *  Created on: 8 Mar 2023
 *      Author: naglaaa
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*********************************DEFINES*************************************/
#define STK_CLOCK_AHB 0x00000004
#define STK_CLOCK_AHB_DIV_8 0x00000000


/*********************************TYPES*************************************/
typedef enum
{
	STK_enuOK,
	STK_enuNOK,
	STK_enuNullPtr,
}STK_tenuErrorStatus;

/* Pointer To Function Type*/
typedef void(*CBF_t)(void);
/*********************************INTERFACES*************************************/

void STK_vidInit(void);
void STK_vidStart(void);
void STK_vidStop(void);
void STK_vidEnableStkInterrupt(void);
void STK_vidDisableStkInterrupt(void);

STK_tenuErrorStatus STK_enuSetCallBackFunction(CBF_t CBF);
STK_tenuErrorStatus STK_enuSetPeriodMilliSec(u16 Cpy_u16RequiredPeriod);
STK_tenuErrorStatus STK_enuSetStkClockSource(u32 Cpy_u32Clock);



#endif /* SYSTICK_H_ */
