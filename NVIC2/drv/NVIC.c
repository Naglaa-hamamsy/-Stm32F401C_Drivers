#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"
#include "NVIC_Cfg.h"
#include "NVIC.h"
#define IRQ_MIN 0
#define IRQ_MAX 239
#define REGISTER_SIZE 32

#define SCR_AIRCR *((volatile u32*) 0xE000ED0C)
#define SCR_AIRCR_CLR_MASK 0xFFFF0700


/**************************************TYPES**********************************************/
typedef struct
{
	u32 ISER[8];
	u32 RESERVED0[24];
	u32 ICER[8];
	u32 RESERVED1[24];
	u32 ISPR[8];
	u32 RESERVED2[24];
	u32 ICPR[8];
	u32 RESERVED3[24];
	u32 IABR[8];
	u32 RESERVED4[56];
	u8 IPR[240];
	u32 RESERVED5[644];
	u32 STIR;


}NVIC_t1;

volatile NVIC_t1 * const NVIC = (volatile NVIC_t1 *)0xE000E100;

NVIC_tenuErrorStatus NVIC_enuEnableIRQ(IRQn_t Cpy_u8IRQ)
{
	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;

	if((Cpy_u8IRQ < IRQ_MIN) || (Cpy_u8IRQ > IRQ_MAX))
	{
		Local_enuErrorStatus = NVIC_enuNOK;
	}
	else
	{
		/* Register is IRQ/32 , Bit is IRQ %32 */
		NVIC->ISER[Cpy_u8IRQ >> 5] |= 1<< (Cpy_u8IRQ % REGISTER_SIZE);
		Local_enuErrorStatus = NVIC_enuOK;

	}
	return Local_enuErrorStatus;
}

NVIC_tenuErrorStatus NVIC_enuDisableIRQ(IRQn_t Cpy_u8IRQ)
{
	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;

	if((Cpy_u8IRQ < IRQ_MIN) || (Cpy_u8IRQ > IRQ_MAX))
	{
		Local_enuErrorStatus = NVIC_enuNOK;
	}
	else
	{
		/* Register is IRQ/32 , Bit is IRQ %32 */
		NVIC->ICER[Cpy_u8IRQ >> 5] |=( 1<< (Cpy_u8IRQ % REGISTER_SIZE));
		Local_enuErrorStatus = NVIC_enuOK;

	}
	return Local_enuErrorStatus;
}
NVIC_tenuErrorStatus NVIC_enuSetPending(IRQn_t Cpy_u8IRQ)
{
	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;

		if((Cpy_u8IRQ < IRQ_MIN) || (Cpy_u8IRQ > IRQ_MAX))
		{
			Local_enuErrorStatus = NVIC_enuNOK;
		}
		else
		{
			/* Register is IRQ/32 , Bit is IRQ %32 */
			NVIC->ISPR[Cpy_u8IRQ >> 5] |= 1<< (Cpy_u8IRQ % REGISTER_SIZE);
			Local_enuErrorStatus = NVIC_enuOK;

		}
		return Local_enuErrorStatus;
}
NVIC_tenuErrorStatus NVIC_enuClearPending(IRQn_t Cpy_u8IRQ)
{
	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;

		if((Cpy_u8IRQ < IRQ_MIN) || (Cpy_u8IRQ > IRQ_MAX))
		{
			Local_enuErrorStatus = NVIC_enuNOK;
		}
		else
		{
			/* Register is IRQ/32 , Bit is IRQ %32 */
			NVIC->ICPR[Cpy_u8IRQ >> 5] |=( 1<< (Cpy_u8IRQ % REGISTER_SIZE));
			Local_enuErrorStatus = NVIC_enuOK;

		}
		return Local_enuErrorStatus;
}
NVIC_tenuErrorStatus NVIC_enuGetActiveStatus(IRQn_t Cpy_u8IRQ , ActiveStatus_t *Add_penuActiveStatus)
{

	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;

			if((Cpy_u8IRQ < IRQ_MIN) || (Cpy_u8IRQ > IRQ_MAX))
			{
				Local_enuErrorStatus = NVIC_enuNOK;
			}
			else if(Add_penuActiveStatus == NULL)
			{
				Local_enuErrorStatus = NVIC_enuNullPtr;
			}

			else
			{
				/* Register is IRQ/32 , Bit is IRQ %32 */
				*Add_penuActiveStatus =	GET_BIT(NVIC->IABR[Cpy_u8IRQ >> 5] , (Cpy_u8IRQ % REGISTER_SIZE));
				Local_enuErrorStatus = NVIC_enuOK;

			}
			return Local_enuErrorStatus;
}
NVIC_tenuErrorStatus NVIC_enuSetPriority(IRQn_t Cpy_enuIRQ,Priorities_t Cpy_u8Priority)
{
	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;

	 if((Cpy_u8Priority < 0) || (Cpy_u8Priority >15))
	{
		Local_enuErrorStatus = NVIC_enuNOK;
	}
	 /*Handling External Interrupts of STM only*/
	 else if((Cpy_enuIRQ < IRQ_MIN) || (Cpy_enuIRQ > IRQ_MAX))
	{
	 Local_enuErrorStatus = NVIC_enuNOK;

	}
	else
		{
			NVIC->IPR[Cpy_enuIRQ] = Cpy_u8Priority<<4;
		}
	return Local_enuErrorStatus;

}
NVIC_tenuErrorStatus NVIC_enusetPriorityGrouping(u32 Cpy_u8priorityGrouping)
{
	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;
	u32 Local_Reg = 0;
	if((Cpy_u8priorityGrouping == NVIC_16G_0S ) ||(Cpy_u8priorityGrouping == NVIC_4G_4S)
			|| (Cpy_u8priorityGrouping == NVIC_2G_8S) || (Cpy_u8priorityGrouping == NVIC_0G_16S))
	{
		Local_Reg =	SCR_AIRCR;
		Local_Reg &= ~ (SCR_AIRCR_CLR_MASK);

		Local_Reg |= Cpy_u8priorityGrouping;
		SCR_AIRCR = Local_Reg;
	}
	else
	{
		Local_enuErrorStatus = NVIC_enuNOK;
	}
	return Local_enuErrorStatus;
}
/*void NVIC_vidSetPriMask(void)
{
	__asm__("MOVS R0, #1");
	__asm__("MSR PRIMASK, R0");
}
void NVIC_vidSetFaultMask(void)
{
	__asm__("MOVS R0, #1");
	__asm__("MSR FAULTMASK, R0");
}
NVIC_tenuErrorStatus NVIC_vidSetBasePri(Priorities_t Cpy_u8Priority)
{
	NVIC_tenuErrorStatus Local_enuErrorStatus = NVIC_enuOK;

		 if((Cpy_u8Priority < 0) || (Cpy_u8Priority >15))
		 {
			Local_enuErrorStatus = NVIC_enuNOK;
		 }
		 else
		 {
			__asm__(MOVS R0, Cpy_u8Priority );
			__asm__(MSR BASEPRI, R0);
		 }

  return Local_enuErrorStatus;

}
*/
