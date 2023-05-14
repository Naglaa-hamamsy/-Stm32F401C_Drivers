/*
 * UART.h
 *
 *  Created on: 28 Mar 2023
 *      Author: naglaaa
 */

#ifndef UART_H_
#define UART_H_
/*****************************************DEFINES*******************************************/
	/*Configure Data Bits Number*/
#define UART_DATABITS_8BIT 0x00000000
#define UART_DATABITS_9BIT 0x00001000
	/*Configure Parity*/
#define UART_PARITY_DISABLED 0x00000000
#define UART_PARITY_EVEN 0x00000400
#define UART_PARITY_ODD 0x00000600
	/*Configure Stop Bits*/
#define UART_STOPBITS_1 0x00000000
#define UART_STOPBITS_2 0x00002000
	/*Configure Over Sampling*/
//#define UART_OVERSAMPLING_8  0x00000000
//#define UART_OVERSAMPLING_16 0x00008000
#define UART_OVERSAMPLING_8 1
#define UART_OVERSAMPLING_16 0
	/*Configure CPU Frequency*/
#define F_CPU 25000000






/*****************************************TYPES********************************************/
typedef void(*CBF_t)(void);

typedef enum
{
	UART_enuOK,
	UART_enuNOK,
	UART_enuBUSY,
	UART_enuNullPtr
}UART_tenuErrorStatus;
typedef enum
{
	UART_1,
	UART_2,
	UART_6
}UART_Channels_t;

typedef struct
	{
		GPIO_Cfg_t Tx;
		GPIO_Cfg_t Rx;
	}UART_Pins_t;

/*typedef struct
{
	u32 TransmissionComplete = 0x00000040;
}UART_Flags_t;
*/
typedef struct
{

 UART_Channels_t Channel;
 u32 DataLength;
 u32 Parity;
 u32 StopBits;
 u32 OverSampling;
 u32 BaudRate;
 UART_Pins_t UART_Pins;

 /*typedef struct
 	{
 		GPIO_Cfg_t Tx;
 		GPIO_Cfg_t Rx;
 	}UART_Pins_t;
 */

}UART_Cfg_t;
typedef struct
{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;

}UART_Registers_t;

extern volatile UART_Registers_t * const UART[3];
/***********************************PROTOTYPES***************************************/
UART_tenuErrorStatus UART_enuInit(UART_Cfg_t const * Cpy_Cfg);
UART_tenuErrorStatus UART_enuSendAsynchZeroCpy(UART_Channels_t Cpy_Channel, u8 * Cpy_u8Buffer , u32 Cpy_u32Size , CBF_t Cpy_CBF);
UART_tenuErrorStatus UART_enuReceiveAsynch(UART_Channels_t Cpy_Channel, u8 *  Cpy_u8Buffer , u32 Cpy_u32Size , CBF_t Cpy_CBF);


#endif /* UART_H_ */
