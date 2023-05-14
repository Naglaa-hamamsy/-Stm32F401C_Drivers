/*
 * RCC2.c
 *
 *  Created on: 7 Feb 2023
 *      Author: naglaaa
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
/**************************DEFINES*************************/
#define READY 1
#define NOT_READY 0
#define TIME_OUT 1000
#define SWS_MASK 0x0000000c
#define SW_MASK 0x00000003
#define HSE_ON 16
#define HSI_ON 0
#define PLL_ON 24
#define HSE_RDY 17
#define HSI_RDY 1
#define PLL_RDY 25
#define M_LOWER 2
#define M_UPPER 63
#define N_LOWER 192
#define N_UPPER 432
#define P_LOWER 0
#define P_UPPER 3
#define Q_LOWER 2
#define Q_UPPER 15
#define PLLSRC_PIN 22
#define PLL_Q_PIN 24
#define PLL_M_PIN 0
#define PLL_N_PIN 6
#define PLL_P_PIN 16
/**************************VARIABLES*************************/
volatile RCC_t *const RCC=(volatile RCC_t*)0x40023800;
static RCC_tenuRCCErrorStatus RCC_enuCheckReady_Static(RCC_tenuSystemClocks Cpy_u8SysClock);
static u8 RCC_enuGetSysClock_Static(u8 *Add_pu8SysClock);

RCC_tenuRCCErrorStatus RCC_enuEnable_HSE(void)
{
	RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
	RCC->CR|=1<<HSE_ON;
	if(RCC_enuCheckReady_Static(RCC_enuClock_HSE)==RCC_enuReady)
	{
		Local_enuErrorStatus=RCC_enuOK;
	}
	else
	{
		Local_enuErrorStatus=RCC_enuNOK;
	}
	return Local_enuErrorStatus;
}

RCC_tenuRCCErrorStatus RCC_enuEnable_HSI(void)
{
	RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
		RCC->CR|=1<<HSI_ON;
		if(RCC_enuCheckReady_Static(RCC_enuClock_HSI)==RCC_enuReady)
		{
			Local_enuErrorStatus=RCC_enuOK;
		}
		else
		{
			Local_enuErrorStatus=RCC_enuNOK;
		}
		return Local_enuErrorStatus;
}
RCC_tenuRCCErrorStatus RCC_enuEnable_PLL(void)
{
	RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
			RCC->CR|=1<<PLL_ON;
			if(RCC_enuCheckReady_Static(RCC_enuClock_PLL)==RCC_enuReady)
			{
				Local_enuErrorStatus=RCC_enuOK;
			}
			else
			{
				Local_enuErrorStatus=RCC_enuNOK;
			}
			return Local_enuErrorStatus;
}



RCC_tenuRCCErrorStatus RCC_enuCheckReady(RCC_tenuSystemClocks Cpy_u8SysClock)
{

	u16 Local_u16TimeOutCounter=0;
	u8 Local_u8ErrorStatus=RCC_enuReady;
	switch(Cpy_u8SysClock)
	{
	case RCC_enuClock_HSI:
		while((GET_BIT(RCC->CR , HSI_RDY)== NOT_READY) && (Local_u16TimeOutCounter<TIME_OUT))
			{
				Local_u16TimeOutCounter++;
			}
		if(GET_BIT(RCC->CR,HSI_RDY)==READY)
			{
				Local_u8ErrorStatus=RCC_enuReady;
			}
		else
			{
				Local_u8ErrorStatus=RCC_enuNotReady;
			}
			break;
	case RCC_enuClock_HSE:
			while((GET_BIT(RCC->CR,HSE_RDY)==NOT_READY) && (Local_u16TimeOutCounter<TIME_OUT))
				{
					Local_u16TimeOutCounter++;
				}
			if(GET_BIT(RCC->CR,HSE_RDY)==READY)
				{
					Local_u8ErrorStatus=RCC_enuReady;
				}
			else
				{
					Local_u8ErrorStatus=RCC_enuNotReady;
				}
				break;
	case RCC_enuClock_PLL:
			while((GET_BIT(RCC->CR,PLL_RDY)==NOT_READY) && (Local_u16TimeOutCounter<TIME_OUT))
				{
					Local_u16TimeOutCounter++;
				}
			if(GET_BIT(RCC->CR,PLL_RDY)==READY)
				{
					Local_u8ErrorStatus=RCC_enuReady;
				}
			else
				{
					Local_u8ErrorStatus=RCC_enuNotReady;
				}
				break;

	}

	return Local_u8ErrorStatus;
}


RCC_tenuRCCErrorStatus RCC_enuDisable_HSE(void)
{
	RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
	u8 Return_System_Clock=0;
	RCC_enuGetSysClock_Static(&Return_System_Clock);
	if(Return_System_Clock==RCC_enuClock_HSE)
	{
		Local_enuErrorStatus=RCC_enuNOK;
	}
	else
	{
	/*Clear ON pin*/
		RCC->CR&= ~(1<<HSE_ON);


	}
	return Local_enuErrorStatus;
}

RCC_tenuRCCErrorStatus RCC_enuDisable_PLL(void)
{
	RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
	u8 Return_System_Clock=0;
		RCC_enuGetSysClock_Static(&Return_System_Clock);
		if(Return_System_Clock==RCC_enuClock_PLL)
		{
			Local_enuErrorStatus=RCC_enuNOK;
		}
		else
		{
	/*Clear ON pin*/
		RCC->CR&= ~(1<<PLL_ON);

		}
		return Local_enuErrorStatus;
}

RCC_tenuRCCErrorStatus RCC_enuGetSysClock(u8 *Add_pu8SysClock)
{
	RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
	u32 Local_u32Reg=0;
	if (Add_pu8SysClock == NULL)
		{
		Local_enuErrorStatus =RCC_enuNullPtr;
		}
	else
	{
		/*Take the register into temporary register*/
		Local_u32Reg=RCC->CFGR;
		/*Clearing all register except the SWS two bits*/
		Local_u32Reg&=SWS_MASK;
		/*Shift the register by 2 to get the SWS value*/
		*Add_pu8SysClock=(Local_u32Reg>>2);

	}
	return Local_enuErrorStatus;
}

RCC_tenuRCCErrorStatus RCC_enuSetPLLConfig(RCC_tenu_PLLSource Cpy_enuPLLSource,u8 Cpy_u8DivFacMainPLL_M,u16 Cpy_u16MulFacVCO_N,RCC_tenuPLLPValues Cpy_u8DivFacVCO_P ,u8 Cpy_u8DivFacVCO_USB_Q)
 {

	 RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
	 u32 Local_u32TempRegister=0;
	 if(GET_BIT(RCC->CR,PLL_ON))
	 {
		 Local_enuErrorStatus=RCC_enuNOK;
	 }

	 else if(!((Cpy_enuPLLSource == RCC_enuSRC_HSI) || (Cpy_enuPLLSource == RCC_enuSRC_HSE)))
	 {
		 Local_enuErrorStatus = RCC_enuNOK;
	 }

	 else if((Cpy_u8DivFacMainPLL_M < M_LOWER) || (Cpy_u8DivFacMainPLL_M > M_UPPER))
	 {
		 Local_enuErrorStatus = RCC_enuNOK;
	 }

	 else if((Cpy_u16MulFacVCO_N < N_LOWER) || (Cpy_u16MulFacVCO_N > N_UPPER))
	 {
		 Local_enuErrorStatus = RCC_enuNOK;
	 }

	 else if ((Cpy_u8DivFacVCO_P < P_LOWER) || (Cpy_u8DivFacVCO_P > P_UPPER))
	 {
		 Local_enuErrorStatus = RCC_enuNOK;
	 }

	 else if ((Cpy_u8DivFacVCO_USB_Q < Q_LOWER) && (Cpy_u8DivFacVCO_USB_Q > Q_UPPER))
	 {
		 Local_enuErrorStatus = RCC_enuNOK;
	 }

	 else
	 {


		/*Set source pin in PLLSRC_PIN as HSE or HSI*/

		RCC->PLLCFGR|= (Cpy_enuPLLSource << PLLSRC_PIN);

		/*Set configurations to temporary register*/
		Local_u32TempRegister = RCC->PLLCFGR;
		Local_u32TempRegister|= (Cpy_u8DivFacMainPLL_M << PLL_M_PIN);
		Local_u32TempRegister|= (Cpy_u16MulFacVCO_N << PLL_N_PIN);
		Local_u32TempRegister|= (Cpy_u8DivFacVCO_USB_Q << PLL_Q_PIN);
		Local_u32TempRegister|= (Cpy_u8DivFacVCO_P << PLL_P_PIN);

		/*then copy it into CFGR*/
		RCC->PLLCFGR=Local_u32TempRegister;

		}

	 return Local_enuErrorStatus;
 }
RCC_tenuRCCErrorStatus RCC_enuSelectSystemClock(RCC_tenuSystemClocks  Cpy_enuSystemClock)
{
	RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
	u32 Local_u32TempRegister=5;
	u32 Return_SystemClock=5;
	volatile u32 LOC_ERROR = 0 ;
		    /*Taking the register into a temp register*/

			 Local_u32TempRegister=RCC->CFGR;
			/*Clearing the first two bits first then, applying the corresponding mode by orring it with
				 * the register*/
			 Local_u32TempRegister&=~(SW_MASK);
			 Local_u32TempRegister|=Cpy_enuSystemClock;
			 RCC->CFGR=Local_u32TempRegister;

			 LOC_ERROR=  RCC_enuGetSysClock(&Return_SystemClock);

				 if(Return_SystemClock == Cpy_enuSystemClock)
				 {
					 Local_enuErrorStatus=RCC_enuOK;
				 }
				 else if(Return_SystemClock != Cpy_enuSystemClock)
				 {
					 Local_enuErrorStatus=RCC_enuNOK;

				 }


	 return Local_enuErrorStatus;
}

  u8 RCC_enuGetSysClock_Static(u8 *Add_pu8SysClock)
{
	  RCC_tenuRCCErrorStatus Local_enuErrorStatus=RCC_enuOK;
	  	u32 Local_u32Reg=0;
	  	if (Add_pu8SysClock == NULL)
	  		{
	  		Local_enuErrorStatus =RCC_enuNullPtr;
	  		}
	  	else
	  	{
	  		/*Take the register into temporary register*/
	  		Local_u32Reg=RCC->CFGR;
	  		/*Clearing all register except the SWS two bits*/
	  		Local_u32Reg&=SWS_MASK;
	  		/*Shift the register by 2 to get the SWS value*/
	  		*Add_pu8SysClock=(Local_u32Reg>>2);

	  	}
	  	return Local_enuErrorStatus;
}
 static RCC_tenuRCCErrorStatus RCC_enuCheckReady_Static(RCC_tenuSystemClocks Cpy_u8SysClock)
{

	u16 Local_u16TimeOutCounter=0;
	u8 Local_u8ErrorStatus=RCC_enuReady;
	switch(Cpy_u8SysClock)
	{
	case RCC_enuClock_HSI:
		while((GET_BIT(RCC->CR,HSI_RDY)==NOT_READY) && (Local_u16TimeOutCounter<TIME_OUT))
			{
				Local_u16TimeOutCounter++;
			}
		if(GET_BIT(RCC->CR,HSI_RDY)==READY)
			{
				Local_u8ErrorStatus=RCC_enuReady;
			}
		else
			{
				Local_u8ErrorStatus=RCC_enuNotReady;
			}
			break;
	case RCC_enuClock_HSE:
			while((GET_BIT(RCC->CR,HSE_RDY)==NOT_READY) && (Local_u16TimeOutCounter<TIME_OUT))
				{
					Local_u16TimeOutCounter++;
				}
			if(GET_BIT(RCC->CR,HSE_RDY)==READY)
				{
					Local_u8ErrorStatus=RCC_enuReady;
				}
			else
				{
					Local_u8ErrorStatus=RCC_enuNotReady;
				}
				break;
	case RCC_enuClock_PLL:
			while((GET_BIT(RCC->CR,PLL_RDY)==NOT_READY) && (Local_u16TimeOutCounter<TIME_OUT))
				{
					Local_u16TimeOutCounter++;
				}
			if(GET_BIT(RCC->CR,PLL_RDY)==READY)
				{
					Local_u8ErrorStatus=RCC_enuReady;
				}
			else
				{
					Local_u8ErrorStatus=RCC_enuNotReady;
				}
				break;

	}

	return Local_u8ErrorStatus;
}


 RCC_tenuRCCErrorStatus RCC_enuSetPrescaler_AHB(u32 Cpy_u8AHBPrescaler)
 {
	 RCC_tenuRCCErrorStatus Local_enuErrorStatus = RCC_enuOK;
	 u32 Local_u32Reg=0;
	 if((Cpy_u8AHBPrescaler < AHB_PRESCALER_2) || (Cpy_u8AHBPrescaler > AHB_PRESCALER_512))
			 {
		 	 	 Local_enuErrorStatus = RCC_enuNOK;
			 }
	 else
	 {
		 Local_u32Reg = RCC->CFGR;
		 Local_u32Reg&=~ AHB_PRESCALER_MASK;
		 Local_u32Reg |= Cpy_u8AHBPrescaler;
		 RCC->CFGR = Local_u32Reg;
		 Local_enuErrorStatus = RCC_enuOK;
	 }
	 return Local_enuErrorStatus;
 }

 RCC_tenuRCCErrorStatus RCC_enuSetPrescaler_APB1(u32 Cpy_u8APB1Prescaler)
 {
	 RCC_tenuRCCErrorStatus Local_enuErrorStatus = RCC_enuOK;
		 u32 Local_u32Reg=0;
		 if((Cpy_u8APB1Prescaler < APB1_PRESCALER_2) || (Cpy_u8APB1Prescaler > APB1_PRESCALER_16))
				 {
			 	 	 Local_enuErrorStatus = RCC_enuNOK;
				 }
		 else
		 {
			 Local_u32Reg = RCC->CFGR;
			 Local_u32Reg&=~ APB1_PRESCALER_MASK;
			 Local_u32Reg |= Cpy_u8APB1Prescaler;
			 RCC->CFGR = Local_u32Reg;
			 Local_enuErrorStatus = RCC_enuOK;
		 }
		 return Local_enuErrorStatus;
 }
 RCC_tenuRCCErrorStatus RCC_enuSetPrescaler_APB2(u32 Cpy_u8APB2Prescaler)
 {

	 RCC_tenuRCCErrorStatus Local_enuErrorStatus = RCC_enuOK;
			 u32 Local_u32Reg=0;
			 if((Cpy_u8APB2Prescaler < APB2_PRESCALER_2) || (Cpy_u8APB2Prescaler > APB2_PRESCALER_16))
					 {
				 	 	 Local_enuErrorStatus = RCC_enuNOK;
					 }
			 else
			 {
				 Local_u32Reg = RCC->CFGR;
				 Local_u32Reg&=~ APB1_PRESCALER_MASK;
				 Local_u32Reg |= Cpy_u8APB2Prescaler;
				 RCC->CFGR = Local_u32Reg;
				 Local_enuErrorStatus = RCC_enuOK;
			 }
			 return Local_enuErrorStatus;
 }
 /*RCC_tenuRCCErrorStatus  RCC_enuSetPeripheral_AHB1(u32 Cpy_u32AHB1Peripheral, u8 Status)
 {
	 RCC_tenuRCCErrorStatus Local_enuErrorStatus = RCC_enuOK;
	 u32 Local_u32Reg = 0;
	 if((Cpy_u32AHB1Peripheral & 0x00800000) != 0x00800000)
	 {
		 Local_enuErrorStatus = RCC_enuNOK;
	 }

	 else
	 {

		switch(Status)
		{
		case Enable:
			Local_u32Reg = RCC->AHB1ENR;
			Local_u32Reg &=~( Cpy_u32AHB1Peripheral);
			Local_u32Reg |=(Cpy_u32AHB1Peripheral & 0x007fffff);
			RCC->AHB1ENR = Local_u32Reg;
			break;
		case Disable:
			Local_u32Reg = RCC->AHB1ENR;
			Local_u32Reg &=~Cpy_u32AHB1Peripheral ;
			RCC->AHB1ENR = Local_u32Reg;
			break;
		}
		Local_enuErrorStatus = RCC_enuOK;
	 }
	 return Local_enuErrorStatus;
 }*/

  RCC_tenuRCCErrorStatus RCC_enuSetAHB1PerClock(RCC_tenuAHB1Peripherals Cpy_enuAHB1Peripheral,RCC_tenuPeripheralStatus Cpy_enuPeripheralStatus)
 {
	 RCC_tenuRCCErrorStatus Local_u8ErrorStatus=RCC_enuOK;

	 if((Cpy_enuAHB1Peripheral < RCC_enuGPIOA_EN) || (Cpy_enuAHB1Peripheral > RCC_enuDMA2_EN))
	 {
		 Local_u8ErrorStatus=RCC_enuNOK;
	 }
	 else
	 {
		if(Cpy_enuPeripheralStatus == RCC_enuPerEnable)
		{
		RCC->AHB1ENR|=(1<<Cpy_enuAHB1Peripheral);
		 Local_u8ErrorStatus=RCC_enuOK;

		}
		else
		{
			 RCC->AHB1ENR&=~Cpy_enuAHB1Peripheral;
			 Local_u8ErrorStatus=RCC_enuOK;
		}


	 }

	 return Local_u8ErrorStatus;
 }


 RCC_tenuRCCErrorStatus RCC_enuSetAHB2PerClock(RCC_tenuAHB2Peripherals Cpy_enuAHB2Peripheral,RCC_tenuPeripheralStatus Cpy_enuPeripheralStatus)
 {
	 RCC_tenuRCCErrorStatus Local_u8ErrorStatus=RCC_enuOK;

	 if(Cpy_enuAHB2Peripheral != RCC_OTGFS_EN)
	 {
		 Local_u8ErrorStatus=RCC_enuNOK;
	 }
	 else
	 {
		if(Cpy_enuPeripheralStatus == RCC_enuPerEnable)
		{
		 SET_BIT(RCC->AHB2ENR,Cpy_enuAHB2Peripheral);
		 Local_u8ErrorStatus=RCC_enuOK;

		}
		else
		{
			 CLR_BIT(RCC->AHB2ENR,Cpy_enuAHB2Peripheral);
			 Local_u8ErrorStatus=RCC_enuOK;
		}


	 }

	 return Local_u8ErrorStatus;
 }

 RCC_tenuRCCErrorStatus RCC_enuSetAPB1PerClock(RCC_tenuAPB1Peripherals Cpy_enuAPB1Peripheral,RCC_tenuPeripheralStatus Cpy_enuPeripheralStatus)
 {
	 RCC_tenuRCCErrorStatus Local_u8ErrorStatus=RCC_enuOK;

	 if((Cpy_enuAPB1Peripheral < RCC_enuTIM2_EN) || (Cpy_enuAPB1Peripheral > RCC_enuPWR_EN))
	 {
		 Local_u8ErrorStatus=RCC_enuNOK;
	 }
	 else
	 {
		if(Cpy_enuPeripheralStatus == RCC_enuPerEnable)
		{
		 SET_BIT(RCC->APB1ENR,Cpy_enuAPB1Peripheral);
		 Local_u8ErrorStatus=RCC_enuOK;

		}
		else
		{
			 CLR_BIT(RCC->APB1ENR,Cpy_enuAPB1Peripheral);
			 Local_u8ErrorStatus=RCC_enuOK;
		}


	 }

	 return Local_u8ErrorStatus;
 }

 RCC_tenuRCCErrorStatus RCC_enuSetAPB2PerClock(RCC_tenuAPB2Peripherals Cpy_enuAPB2Peripheral,RCC_tenuPeripheralStatus Cpy_enuPeripheralStatus)
 {
	 RCC_tenuRCCErrorStatus Local_u8ErrorStatus=RCC_enuOK;

	 if((Cpy_enuAPB2Peripheral < RCC_enuTIM1_EN) || (Cpy_enuAPB2Peripheral > RCC_enuTIM11_EN))
	 {
		 Local_u8ErrorStatus=RCC_enuNOK;
	 }
	 else
	 {
		if(Cpy_enuPeripheralStatus == RCC_enuPerEnable)
		{
		 SET_BIT(RCC->APB2ENR,Cpy_enuAPB2Peripheral);
		 Local_u8ErrorStatus=RCC_enuOK;

		}
		else
		{
			 CLR_BIT(RCC->APB2ENR,Cpy_enuAPB2Peripheral);
			 Local_u8ErrorStatus=RCC_enuOK;
		}


	 }

	 return Local_u8ErrorStatus;
 }
