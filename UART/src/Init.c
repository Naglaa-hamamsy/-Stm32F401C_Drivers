/*
 * Init.c
 *
 *  Created on: 30 Mar 2023
 *      Author: naglaaa
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include "RCC2.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART_Cfg.h"
#include "UART.h"
void AppInit (void)
{
#define UART_1_ENABLE_IRQ 37
#define UART_2_ENABLE_IRQ 38
#define UART_6_ENABLE_IRQ 71
	RCC_enuEnable_HSE();
RCC_enuSelectSystemClock(RCC_enuClock_HSE);
	RCC_enuSetAPB2PerClock(RCC_enuUSART1_EN,RCC_enuPerEnable);
	RCC_enuSetAHB1PerClock(RCC_enuGPIOA_EN,RCC_enuPerEnable);
	RCC_enuSetAPB2PerClock(RCC_enuUSART6_EN,RCC_enuPerEnable);

	// RCC_enuSetAHB1PerClock(RCC_enuGPIOC_EN,RCC_enuPerEnable);
	 /*First UART Config*/

	UART_Cfg_t cfg;
	cfg.BaudRate = 9600;
	cfg.Channel= UART_6;
	cfg.DataLength = UART_DATABITS_8BIT;
	cfg.OverSampling = UART_OVERSAMPLING_8;
	cfg.Parity = UART_PARITY_DISABLED;
	cfg.StopBits = UART_STOPBITS_1;


			cfg.UART_Pins.Tx.Port=GPIO_enuPORTA;
		 	cfg.UART_Pins.Tx.Pin=GPIO_enuPin11;
		 	cfg.UART_Pins.Tx.Mode=GPIO_enuMode_AF_PushPull;
		 	cfg.UART_Pins.Tx.Speed=GPIO_enuSpeed_VeryHigh;
		 	cfg.UART_Pins.Rx.Port=GPIO_enuPORTA;
		 	cfg.UART_Pins.Rx.Pin=GPIO_enuPin12;
		 cfg.UART_Pins.Rx.Mode=GPIO_enuMode_AF_PushPull;
		 	cfg.UART_Pins.Rx.Speed=GPIO_enuSpeed_VeryHigh;
			 GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin11,GPIO_enuAF8);
				 GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin12,GPIO_enuAF8);
				 GPIO_enuInit(&(cfg.UART_Pins.Tx));
					 	GPIO_enuInit(&(cfg.UART_Pins.Rx));
					 	UART_enuInit(&cfg);

				 /*cfg.UART_Pins.Tx.Port=GPIO_enuPORTC;
			 	cfg.UART_Pins.Tx.Pin=GPIO_enuPin6;
			 	//cfg.UART_Pins.Tx.Mode=GPIO_enuMode_AF_PushPull;
			 	cfg.UART_Pins.Tx.Speed=GPIO_enuSpeed_VeryHigh;
			 	cfg.UART_Pins.Rx.Port=GPIO_enuPORTC;
			 	cfg.UART_Pins.Rx.Pin=GPIO_enuPin7;
			 	//cfg.UART_Pins.Rx.Mode=GPIO_enuMode_Input_Floating;
			 	cfg.UART_Pins.Rx.Speed=GPIO_enuSpeed_VeryHigh;
				 GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin6,GPIO_enuAF8);
					 GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin7,GPIO_enuAF8);

*/
					 	/*Second UART1 Config*/

						UART_Cfg_t cfg2;
						cfg2.BaudRate = 9600;
						cfg2.Channel= UART_1;
						cfg2.DataLength = UART_DATABITS_8BIT;
						cfg2.OverSampling = UART_OVERSAMPLING_8;
						cfg2.Parity = UART_PARITY_DISABLED;
						cfg2.StopBits = UART_STOPBITS_1;

					 		cfg2.UART_Pins.Tx.Port=GPIO_enuPORTA;
					 		cfg2.UART_Pins.Tx.Pin=GPIO_enuPin9;
					 		cfg2.UART_Pins.Tx.Mode=GPIO_enuMode_AF_PushPull;
					 		cfg2.UART_Pins.Tx.Speed=GPIO_enuSpeed_VeryHigh;
					 		cfg2.UART_Pins.Rx.Port=GPIO_enuPORTA;
					 		cfg2.UART_Pins.Rx.Pin=GPIO_enuPin10;
					 		cfg2.UART_Pins.Rx.Mode=GPIO_enuMode_AF_PushPull;
					 		cfg2.UART_Pins.Rx.Speed=GPIO_enuSpeed_VeryHigh;
					 		 GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin9,GPIO_enuAF7);
					 					 GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin10,GPIO_enuAF7);
					 			 GPIO_enuInit(&(cfg2.UART_Pins.Tx));
					 						 	GPIO_enuInit(&(cfg2.UART_Pins.Rx));
					 				 	UART_enuInit(&cfg2);

	NVIC_enuEnableIRQ(UART_6_ENABLE_IRQ);
	NVIC_enuEnableIRQ(UART_1_ENABLE_IRQ);
	//NVIC_enuEnableIRQ(UART_2_ENABLE_IRQ);
	// GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin9,GPIO_enuAF7);
	 //GPIO_enuSelectAF(GPIO_enuPORTA,GPIO_enuPin10,GPIO_enuAF7);
	 //


	// UART[UART_1]->SR = 0;

}



