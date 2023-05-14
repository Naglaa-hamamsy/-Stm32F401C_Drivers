/*
 * RCC2.h
 *
 *  Created on: 7 Feb 2023
 *      Author: naglaaa
 */

#ifndef RCC2_H_
#define RCC2_H_

/**********************************DEFINES***************************************/
#define PLLQ_2	2
#define PLLQ_3	3
#define PLLQ_4	4
#define PLLQ_5	5
#define PLLQ_6	6
#define PLLQ_7	7
#define PLLQ_8	8
#define PLLQ_9	9
#define PLLQ_10	10
#define PLLQ_11	11
#define PLLQ_12	12
#define PLLQ_13	13
#define PLLQ_14	14
#define PLLQ_15	15
#define APB2_PRESCALER_MASK 0xE000
#define APB2_PRESCALER_2 0x00008000
#define APB2_PRESCALER_4 0x0000A000
#define APB2_PRESCALER_8 0x0000C000
#define APB2_PRESCALER_16 0x0000E000

#define APB1_PRESCALER_MASK 0x00001C00
#define APB1_PRESCALER_2 0x00001000
#define APB1_PRESCALER_4 0x00001400
#define APB1_PRESCALER_8 0x00001800
#define APB1_PRESCALER_16 0x00001C00

#define AHB_PRESCALER_MASK 0x000000f0
#define AHB_PRESCALER_2 0x00000080
#define AHB_PRESCALER_4 0x00000090
#define AHB_PRESCALER_8 0x000000A0
#define AHB_PRESCALER_16 0x000000B0
#define AHB_PRESCALER_64 0x000000C0
#define AHB_PRESCALER_128 0x000000D0
#define AHB_PRESCALER_256 0x000000E0
#define AHB_PRESCALER_512 0x000000f0

#define GPIOA_EN_AHB1 0x00800001
#define GPIOB_EN_AHB1 0x00800002
#define GPIOC_EN_AHB1 0x00800004
#define GPIOD_EN_AHB1 0x00800008
#define GPIOE_EN_AHB1 0x00800010
#define GPIOH_EN_AHB1 0x00800080
#define CRC_EN_AHB1 0x00801000
#define DMA1_EN_AHB1 0x00A00000
#define DMA2_EN_AHB1 0x00C00000

#define Enable 1
#define Disable 0







/**********************************TYPES***************************************/
typedef struct
{
	u32 CR;
	u32	PLLCFGR;
	u32	CFGR;
	u32	CIR;
	u32	AHB1RSTR;
	u32	AHB2RSTR;

	u32 Reserved1;
	u32 Reserved2;

	u32	APB1RSTR;
	u32	APB2RSTR;

	u32 Reserved3;
	u32 Reserved4;

	u32	AHB1ENR;
	u32	AHB2ENR;

	u32 Reserved5;
	u32 Reserved6;

	u32	APB1ENR;
	u32	APB2ENR;

	u32 Reserved7;
	u32 Reserved8;

	u32	AHB1LPENR;
	u32	AHB2LPENR;

	u32 Reserved9;
	u32 Resered10;

	u32	APB1LPENR;
	u32	APB2LPENR;

	u32 Reserved11;
	u32 Resered12;

	u32	BDCR;
	u32	CSR;

	u32 Reserved13;
	u32 Resered14;

	u32	SSCGR;
	u32	PLLI2SCFGR;

	u32 Reserved15;
	u32	DCKCFGR;


}RCC_t;

extern volatile RCC_t *const RCC;
/* Enum for RCC Error status */
/* It could be OK, NOK*/
typedef enum
{
  RCC_enuOK,
  RCC_enuNOK,
  RCC_enuReady,
  RCC_enuNotReady,
  RCC_enuNullPtr

}RCC_tenuRCCErrorStatus;

/* System Clocks*/
typedef enum
{
RCC_enuClock_HSI,
RCC_enuClock_HSE,
RCC_enuClock_PLL
}RCC_tenuSystemClocks;
/* PLL SOURCE*/
typedef enum
{
	RCC_enuSRC_HSI,
	RCC_enuSRC_HSE,
}RCC_tenu_PLLSource;

/*PLL P values*/
typedef enum
{
	RCC_PLLP2,
	RCC_PLLP4,
	RCC_PLLP6,
	RCC_PLLP8
}RCC_tenuPLLPValues;


typedef enum
{
	RCC_enuGPIOA_EN,
	RCC_enuGPIOB_EN,
	RCC_enuGPIOC_EN,
	RCC_enuGPIOD_EN,
	RCC_enuGPIOE_EN,
	RCC_enuGPIOH_EN=7,
	RCC_enuCRC_EN=12,
	RCC_enuDMA1_EN=21,
	RCC_enuDMA2_EN,
	RCC_enuAHB1MaxPeriNumber=23
}RCC_tenuAHB1Peripherals;

typedef enum
{
	RCC_OTGFS_EN=7
}RCC_tenuAHB2Peripherals;

typedef enum
{	RCC_enuTIM2_EN,
	RCC_enuTIM3_EN,
	RCC_enuTIM4_EN,
	RCC_enuTIM5_EN,
	RCC_enuWWDG_EN=11,
	RCC_enuSPI2_EN=14,
	RCC_enuSPI3_EN,
	RCC_enuUSART2_EN=17,
	RCC_enuI2C1_EN=21,
	RCC_enuI2C2_EN,
	RCC_enuI2C3_EN,
	RCC_enuPWR_EN=28,
	RCC_enuAPB1MaxPeriNumber=29

}RCC_tenuAPB1Peripherals;

typedef enum
{
	RCC_enuTIM1_EN,
	RCC_enuUSART1_EN=4,
	RCC_enuUSART6_EN,
	RCC_enuADC1_EN=8,
	RCC_enuSDIO_EN=11,
	RCC_enuSP11_EN,
	RCC_enuSPI4_EN,
	RCC_enuSYSCFG_EN,
	RCC_enuTIM9_EN=16,
	RCC_enuTIM10_EN,
	RCC_enuTIM11_EN,
    RCC_enuAPB2MaxPeriNumber=19

}RCC_tenuAPB2Peripherals;

typedef enum
{
	RCC_enuPerEnable,
	RCC_enuPerDisable

}RCC_tenuPeripheralStatus;
/************************************APIS***************************************/
/* **************************************** */
/* Enable HSE Clock
 Input: Void
 Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
 /* ***************************************** */

RCC_tenuRCCErrorStatus RCC_enuEnable_HSE(void);
/* **************************************** */
/* Disable HSE Clock
 Input: Void
 Output: RCC_tenuRCCErrorStatus */
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuDisable_HSE(void);
/* **************************************** */
/* Enable HSI Clock
 Input: Void
 Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuEnable_HSI(void);
/* **************************************** */
/* Disable HSI Clock
 Input: Void
 Output: RCC_tenuRCCErrorStatus*/
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuEnable_PLL(void);
/* **************************************** */
/* Disable PLL Clock
 Input: Void
 Output: RCC_tenuRCCErrorStatus*/
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuDisable_PLL(void);

/* **************************************** */
/* RCC Check if the clock is ready or not
 Input: clock
************ OPTIONS:***********
1)RCC_enuClock_HSI,
2)RCC_enuClock_HSE,
3)RCC_enuClock_PLL
 Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuCheckReady(RCC_tenuSystemClocks Cpy_u8SysClock);
/* RCC Get system clock Function
 Input: pointer to u8
 Output: RCC_tenuRCCErrorStatus to report error*/
/* there's a pointer as input , to return the value of current clock*/
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuGetSysClock(u8 *Add_pu8SysClock);


/* **************************************** */
/* RCC Set PLL Configuration
 Input: PLL Source , Configuration of PLL (M/N/P/Q)
  ******PLL SOURCE OPTIONS:*********
	 1) RCC_enuSRC_HSI
	 2)RCC_enuSRC_HSE

  ******CONFIGURATION OPTIONS:*********
  1) Q Values==> From 2 to 15
  2) P Values==> From 2 to 8
  3) M Values==> From 2 to 63
  4) N Values==> From 192 to 432

  Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
 /* ***************************************** */

RCC_tenuRCCErrorStatus RCC_enuSetPLLConfig(RCC_tenu_PLLSource Cpy_enuPLLSource,u8 Cpy_u8DivFacMainPLL_M,u16 Cpy_u16MulFacVCO_N,RCC_tenuPLLPValues Cpy_u8DivFacVCO_P ,u8 Cpy_u8DivFacVCO_USB_Q);
/* **************************************** */
/* RCC Select System Clock
 Input:Clock
 ************ OPTIONS:***********
1)RCC_enuClock_HSI,
2)RCC_enuClock_HSE,
3)RCC_enuClock_PLL
  Output: RCC_tenuRCCErrorStatus to report if the clock became the system clock or not*/
 /* ***************************************** */

RCC_tenuRCCErrorStatus RCC_enuSelectSystemClock(RCC_tenuSystemClocks  Cpy_enuSystemClock);

RCC_tenuRCCErrorStatus RCC_enuSetPrescaler_AHB(u32 Cpy_u8AHBPrescaler);
RCC_tenuRCCErrorStatus RCC_enuSetPrescaler_APB1(u32 Cpy_u8APB1Prescaler);
RCC_tenuRCCErrorStatus RCC_enuSetPrescaler_APB2(u32 Cpy_u8APB1Prescaler);
/*

*//* Set AHB1 Peripherals (Enable/Disable) function
 Input:
 1) Peripheral wanted to be enabled/disabled
 2) Status (Enabled/Disabled)
      *****INPUT OPTIONS****
  1.RCC_enuGPIOA_EN,
  2.RCC_enuGPIOB_EN,
  3.RCC_enuGPIOC_EN,
  4.RCC_enuGPIOD_EN,
  5.RCC_enuGPIOE_EN,
  6.RCC_enuGPIOH_EN=7,
  7.RCC_enuCRC_EN=12,
  8.RCC_enuDMA1_EN=21,
  9.RCC_enuDMA2_EN,

    ***MAKE SURE THAT YOU AVOID RESERVED BITS***

 Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
RCC_tenuRCCErrorStatus RCC_enuSetAHB1PerClock(RCC_tenuAHB1Peripherals,RCC_tenuPeripheralStatus);
/* **************************************** */
/* Set AHB2 Peripherals (Enable/Disable) function
 Input:
 1) Peripheral wanted to be enabled/disabled
 2) Status (Enabled/Disabled)
      *****INPUT OPTIONS****
 	1) RCC_OTGFS_EN
    ***MAKE SURE THAT YOU AVOID RESERVED BITS***

 Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
/*
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuSetAHB2PerClock(RCC_tenuAHB2Peripherals,RCC_tenuPeripheralStatus);
/* **************************************** */
/* Set APB1 Peripherals (Enable/Disable) function
 Input:
 1) Peripheral wanted to be enabled/disabled
 2) Status (Enabled/Disabled)
      *****INPUT OPTIONS****
 	1.RCC_enuTIM2_EN
	2.RCC_enuTIM3_EN
	3.RCC_enuTIM4_EN
	4.RCC_enuTIM5_EN
	5.RCC_enuWWDG_EN
	6.RCC_enuSPI2_EN
	7.RCC_enuSPI3_EN
	8.RCC_enuUSART2_EN
	9.RCC_enuI2C1_EN
	10.RCC_enuI2C2_EN
	11.RCC_enuI2C3_EN
	12.RCC_enuPWR_EN

    ***MAKE SURE THAT YOU AVOID RESERVED BITS***

 Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
/*
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuSetAPB1PerClock(RCC_tenuAPB1Peripherals,RCC_tenuPeripheralStatus);
/* **************************************** */
/* Set APB1 Peripherals (Enable/Disable) function
 Input:
 1) Peripheral wanted to be enabled/disabled
 2) Status (Enabled/Disabled)
      *****INPUT OPTIONS****
 	1.RCC_enuTIM1_EN,
	2.RCC_enuUSART1_EN=4,
	3.RCC_enuUSART6_EN,
	4.RCC_enuADC1_EN=8,
	5.RCC_enuSDIO_EN=11,
	6.RCC_enuSP11_EN,
	7.RCC_enuSPI4_EN,
	8.RCC_enuSYSCFG_EN,
	9.RCC_enuTIM9_EN=16,
	10.RCC_enuTIM10_EN,
	11.RCC_enuTIM11_EN,


    ***MAKE SURE THAT YOU AVOID RESERVED BITS***

 Output: RCC_tenuRCCErrorStatus to report if the clock is ready or not*/
/*
 /* ***************************************** */
RCC_tenuRCCErrorStatus RCC_enuSetAPB2PerClock(RCC_tenuAHB2Peripherals,RCC_tenuPeripheralStatus);


//RCC_tenuRCCErrorStatus  RCC_enuSetPeripheral_AHB1(u32 Cpy_u32AHB1Peripheral, u8 Status); // reserved test

#endif /* RCC2_H_ */
