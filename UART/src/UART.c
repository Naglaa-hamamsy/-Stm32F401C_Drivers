/*
 * UART.c
 *
 *  Created on: 28 Mar 2023
 *      Author: naglaaa
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "LED_Cfg.h"
#include "LED.h"
#include "NVIC.h"
#include "UART_Cfg.h"
#include "UART.h"


volatile UART_Registers_t * const UART[3] =
{
		[UART_1] =(volatile UART_Registers_t *) 0x40011000,

		[UART_2] =(volatile UART_Registers_t *) 0x40004400,

		[UART_6] =(volatile UART_Registers_t *) 0x40011400,


};
/*************************************TYPES*******************************************/
typedef enum
{
	TransmissionComplete = 7,
	ReceiveComplete = 5,

}UART_Flags_t;
/*************************************DEFINES****************************************/
#define IDLE 1
#define BUSY 0
#define TRANSMIT_COMPLETE_INTERRUPT_ENABLE 0x00000080
#define RECIVE_COMPLETE_INTERRUPT_ENABLE  0x00000020
#define UART_ENABLE 0x00002000
#define UART_1_ENABLE_IRQ 37
#define UART_2_ENABLE_IRQ 38
#define UART_6_ENABLE_IRQ 71
#define TRANSMITTER_ENABLE 0x00000008
#define RECEIVER_ENABLE 0x00000004
#define OVER_SAMPLING_PIN 15
#define MANTISSA_POS 4
#define FRACTION_MASK 0x0f
#define ENABLE 1
#define DISABLE 0
#define UART_CHANNELS 3
/************************************STATIC VARIABLES******************************/
		/*For Transmitting*/
static u8 UART_TxState[UART_CHANNELS] = {IDLE,IDLE,IDLE};
static u8 * UART_TxBuffer[UART_CHANNELS] = {NULL};
static u32 UART_TxBufferSize[UART_CHANNELS] = {0};
static CBF_t UART_TxCBF[UART_CHANNELS] = {NULL};
static u32 	UART_TxBufferIdx[UART_CHANNELS] = {0};
		/*For Receiving*/
static u8 UART_RxState[UART_CHANNELS] = {IDLE,IDLE,IDLE};
static u8 *	UART_RxBuffer[UART_CHANNELS] = {NULL};
static u32 UART_RxBufferSize[UART_CHANNELS] = {0};
static CBF_t UART_RxCBF[UART_CHANNELS] = {NULL};
static u32 	UART_RxBufferIdx[UART_CHANNELS] = {0};
/************************************STATIC FUNCTIONS******************************/
static void BaudRateCalc(UART_Cfg_t const *Cpy_Cfg);
static void UART_Handler(UART_Channels_t Channel);

/********************************IMPLEMENTATION**************************************/
UART_tenuErrorStatus UART_enuInit(UART_Cfg_t const*  Cpy_Cfg)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;
	if(Cpy_Cfg == NULL)
	{
		LocalErrorStatus = UART_enuNullPtr;
	}
	else
	{
		/*UART INITIALIZATION */


		/*Enable Tx Pin*/
		UART[Cpy_Cfg->Channel]->CR1 |=TRANSMITTER_ENABLE;
		/*Enable Rx Pin*/
		UART[Cpy_Cfg->Channel]->CR1 |=RECEIVER_ENABLE;

		/*USER CONFIGURATION*/
		/*Initialize Data Length*/
		UART[Cpy_Cfg->Channel]->CR1 |= Cpy_Cfg->DataLength;
		/*Initialize Parity*/
		UART[Cpy_Cfg->Channel]->CR1 |= Cpy_Cfg->Parity;
		/*Initialize Over Sampling*/
		if(Cpy_Cfg->OverSampling == UART_OVERSAMPLING_8)
		{
			UART[Cpy_Cfg->Channel]->CR1 |=(1<<15);

		}
		else
		{
			UART[Cpy_Cfg->Channel]->CR1 &=~(1<<15);
		}
		/*Initialize Stop Bits*/
		UART[Cpy_Cfg->Channel]->CR2 |= Cpy_Cfg->StopBits;
		/*Calculating UART DIV Factor -> BaudRate*/
		BaudRateCalc(Cpy_Cfg);

	//	UART[Cpy_Cfg->Channel]->SR = 0;
			/*Enable UART*/
				UART[Cpy_Cfg->Channel]->CR1 |= UART_ENABLE;
	}
	return LocalErrorStatus;
}


UART_tenuErrorStatus UART_enuSendAsynchZeroCpy(UART_Channels_t Cpy_Channel , u8  * Cpy_u8Buffer , u32 Cpy_u32Size , CBF_t Cpy_CBF)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;

	if(UART_TxState[Cpy_Channel] == IDLE)
	{
		if(Cpy_u8Buffer == NULL)
		{
			LocalErrorStatus = UART_enuNullPtr;
		}

		else
		{
			UART_TxBufferIdx[Cpy_Channel] = 0;
			/*Make UART State As Busy*/
			UART_TxState[Cpy_Channel] = BUSY;
			/*Make The Address Of This Buffer Global To Be Seen By Handler*/
			UART_TxBuffer[Cpy_Channel] = Cpy_u8Buffer;
			/*Make Buffer Size Global*/
			UART_TxBufferSize[Cpy_Channel] = Cpy_u32Size;
			/*Make The CBF Global To Be Called In Handler*/
			UART_TxCBF[Cpy_Channel] = Cpy_CBF;
			/*Sending The First Byte*/
			UART[Cpy_Channel]->DR = UART_TxBuffer[Cpy_Channel][UART_TxBufferIdx[Cpy_Channel]];
			UART_TxBufferIdx[Cpy_Channel]++;

			/*Enable Tx Interrupt*/
			UART[Cpy_Channel] ->CR1 |= TRANSMIT_COMPLETE_INTERRUPT_ENABLE;
		}
	}
	else
	{

		LocalErrorStatus = UART_enuBUSY;
	}
	return LocalErrorStatus;
}
UART_tenuErrorStatus UART_enuReceiveAsynch(UART_Channels_t Cpy_Channel, u8 * Cpy_u8Buffer , u32 Cpy_u32Size , CBF_t Cpy_CBF)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;

	if(UART_RxState[Cpy_Channel] == IDLE)
	{
		if(Cpy_u8Buffer == NULL)
		{
			LocalErrorStatus = UART_enuNullPtr;
		}
		else
		{
			UART_RxBufferIdx[Cpy_Channel] = 0;
			/*Make UART State Busy*/
			UART_RxState[Cpy_Channel] = BUSY;
			/*Make Input Arguments Global To Be Seen In Handler*/

			UART_RxBuffer[Cpy_Channel] = Cpy_u8Buffer;
			UART_RxBufferSize[Cpy_Channel] = Cpy_u32Size;
			UART_RxCBF[Cpy_Channel] = Cpy_CBF;
			/*Enable Receive Interrupt*/
			UART[Cpy_Channel]->CR1 |=RECIVE_COMPLETE_INTERRUPT_ENABLE;

		}
	}

	else
	{
		LocalErrorStatus = UART_enuBUSY;
	}
	return LocalErrorStatus;

}
/**********************************STATIC FUNCTIONS IMPLEMENTATION************************/
static void BaudRateCalc(UART_Cfg_t const* Cpy_Cfg)
{
	f32 UART_DIV = 0;
	u32 Mantessa_Part = 0;
	u32 Fraction_Part = 0;
	//Cpy_Cfg->BaudRate
	UART_DIV = ((f32)(F_CPU))/(Cpy_Cfg->BaudRate * (8 * (2-(Cpy_Cfg->OverSampling))));
	/*Extract The Fraction Part & Mantessa Part*/
	Mantessa_Part = (u32)(UART_DIV);
	/*if div by 8 ==> multiply by 8
	 * if div by 16 ==> multiply by 16
	 */
	Fraction_Part = ((UART_DIV - Mantessa_Part)) * 8 *(2-Cpy_Cfg->OverSampling);
	/*Convert each to hexadecimal*/
	UART[Cpy_Cfg->Channel]->BRR  |= ((Mantessa_Part<<MANTISSA_POS) | (Fraction_Part & FRACTION_MASK));

}
static void UART_Handler(UART_Channels_t Cpy_Channel)
{

	/*Reading UART Transmit Complete Flag*/

		if(((UART[Cpy_Channel]->SR >> TransmissionComplete) & 0x1))
		{
			if(UART_TxBufferIdx[Cpy_Channel] < UART_TxBufferSize[Cpy_Channel])
			{
				UART[Cpy_Channel]->DR = UART_TxBuffer[Cpy_Channel][UART_TxBufferIdx[Cpy_Channel]++];
			}
			else
			{
				UART_TxState[Cpy_Channel] = IDLE;
				/*Disable Interrupt*/
				UART[Cpy_Channel]->CR1 &=~TRANSMIT_COMPLETE_INTERRUPT_ENABLE;

				if(UART_TxCBF[Cpy_Channel])
				{
					UART_TxCBF[Cpy_Channel]();
				}
				else
				{
					/*DO NOTHING*/

				}
			}

		}

			/*RECEIVING EVENTS*/
		if(((UART[Cpy_Channel]->SR >> ReceiveComplete) & 0x1) && (UART_RxState[Cpy_Channel] == BUSY))
		{
			if( UART_RxBufferIdx[Cpy_Channel] < UART_RxBufferSize[Cpy_Channel] )
			{
				UART_RxBuffer[Cpy_Channel][UART_RxBufferIdx[Cpy_Channel]++] =  UART[Cpy_Channel]->DR;

			}
			else
			{
				UART_RxState[Cpy_Channel] = IDLE;
				/*Disable Interrupt*/
				UART[Cpy_Channel]->CR1 &=~RECIVE_COMPLETE_INTERRUPT_ENABLE;

				if(UART_RxCBF[Cpy_Channel])
				{
					UART_RxCBF[Cpy_Channel]();
				}
				else
				{
					/*DO NOTHING*/
				}
			}
		}

}




/***************************HANDLERS***************************************/

void USART1_IRQHandler(void)
{
	UART_Handler(UART_1);
}

void USART2_IRQHandler(void)
{
	UART_Handler(UART_2);
}

void USART6_IRQHandler(void)
{
	UART_Handler(UART_6);
}


