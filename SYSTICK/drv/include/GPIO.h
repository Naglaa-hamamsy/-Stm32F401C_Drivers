/*
 * GPIO.h
 *
 *  Created on: 15 Feb 2023
 *      Author: naglaaa
 */

#ifndef GPIO_H_
#define GPIO_H_
/***************************TYPES********************************/

typedef enum
{
	GPIO_enuOK,
	GPIO_enuNOK,
	GPIO_enuNullPtr
}GPIO_tenuErrorStatus;

typedef struct
{
  u32 GPIO_MODER;
  u32 GPIO_OTYPER;
  u32 GPIO_OPSPEEDR;
  u32 GPIO_PUPDR;
  u32 GPIO_IDR;
  u32 GPIO_ODR;
  u32 GPIO_BSRR;
  u32 GPIO_LCKR;
  u32 GPIO_AFRL;
  u32 GPIO_AFRH;

}GPIO_t;

 extern volatile GPIO_t * const GPIO[6];

typedef enum
{
	GPIO_enuPORTA,
	GPIO_enuPORTB,
	GPIO_enuPORTC,
	GPIO_enuPORTD,
	GPIO_enuPORTE,
	GPIO_enuPORTH

}GPIO_PORTS_t;

typedef enum
{
	GPIO_enuPin0,
	GPIO_enuPin1,
	GPIO_enuPin2,
	GPIO_enuPin3,
	GPIO_enuPin4,
	GPIO_enuPin5,
	GPIO_enuPin6,
	GPIO_enuPin7,
	GPIO_enuPin8,
	GPIO_enuPin9,
	GPIO_enuPin10,
	GPIO_enuPin11,
	GPIO_enuPin12,
	GPIO_enuPin13,
	GPIO_enuPin14,
	GPIO_enuPin15

}GPIO_PINS_t;

typedef enum
{
	GPIO_enuPin_LOW,
	GPIO_enuPin_HIGH

}GPIO_PIN_VALUE_t;

typedef enum
{
	GPIO_enuPort_LOW,
	GPIO_enuPort_HIGH = 65535

}GPIO_PORT_VALUE_t;

typedef enum
{
	GPIO_enuMode_Input_Floating,
	GPIO_enuMode_Input_PullUp,
	GPIO_enuMode_Input_PullDown,

	GPIO_enuMode_Analog,

	GPIO_enuMode_Output_OpenDrain,
	GPIO_enuMode_Output_OpenDrain_PullUp,
	GPIO_enuMode_Output_OpenDrain_PullDown,
	GPIO_enuMode_Output_PushPull,
	GPIO_enuMode_Output_PushPull_PullUp,
	GPIO_enuMode_Output_PushPull_PullDown,

	GPIO_enuMode_AF_OpenDrain,
	GPIO_enuMode_AF_OpenDrain_PullUp,
	GPIO_enuMode_AF_OpenDrain_PullDown,

	GPIO_enuMode_AF_PushPull,
	GPIO_enuMode_AF_PushPull_PullUp,
	GPIO_enuMode_AF_PushPull_PullDown,


}GPIO_MODES_t;

typedef enum
{
	GPIO_enuSpeed_Low,
	GPIO_enuSpeed_Medium,
	GPIO_enuSpeed_High,
	GPIO_enuSpeed_VeryHigh,

}GPIO_SPEEDS_t;


typedef struct
{
	GPIO_PORTS_t Port;
	GPIO_PINS_t Pin;
	GPIO_MODES_t Mode;
	GPIO_SPEEDS_t Speed;


}GPIO_Cfg_t;

typedef enum
{
	GPIO_enuAF0,
	GPIO_enuAF1,
	GPIO_enuAF2,
	GPIO_enuAF3,
	GPIO_enuAF4,
	GPIO_enuAF5,
	GPIO_enuAF6,
	GPIO_enuAF7,
	GPIO_enuAF8,
	GPIO_enuAF9,
	GPIO_enuAF10,
	GPIO_enuAF11,
	GPIO_enuAF12,
	GPIO_enuAF13,
	GPIO_enuAF14,
	GPIO_enuAF15,


}GPIO_AF_t;
/***************************************INTERFACES****************************************/
/* **************************************** */
/* GPIO Write Pin Value Function
Input: Port Number , Port Value
*************** PORT NUMBER OPTIONS********************
			1) GPIO_enuPORTA
			2) GPIO_enuPORTB
			3) GPIO_enuPORTC
			4) GPIO_enuPORTD
			5) GPIO_enuPORTE
			6) GPIO_enuPORTH
*************** PIN NUMBER OPTIONS********************
			1) GPIO_enuPin0,
			2) GPIO_enuPin1,
			3) GPIO_enuPin2,
			4) GPIO_enuPin3,
			5) GPIO_enuPin4,
			6) GPIO_enuPin5,
			7) GPIO_enuPin6,
			8) GPIO_enuPin7,
			9) GPIO_enuPin8,
			10) GPIO_enuPin9,
			11) GPIO_enuPin10,
			12) GPIO_enuPin11,
			13) GPIO_enuPin12,
			14) GPIO_enuPin13,
			15) GPIO_enuPin14,
			16) GPIO_enuPin15
*************** PIN VALUE OPTIONS********************
            1) GPIO_enuPin_LOW
            2_GPIO_enuPin_HIGH

Output: GPIO Error Status
*/
GPIO_tenuErrorStatus GPIO_enuWritePinValue( GPIO_PORTS_t Cpy_enuPortNumber, GPIO_PINS_t Cpy_enuPinNumber , GPIO_PIN_VALUE_t Cpy_enuPinValue);

/* GPIO Set Port Value Function
Input: Port Number , Port Value
*************** PORT NUMBER OPTIONS********************
			1) GPIO_enuPORTA
			2) GPIO_enuPORTB
			3) GPIO_enuPORTC
			4) GPIO_enuPORTD
			5) GPIO_enuPORTE
			6) GPIO_enuPORTH
*Note that Port Value Range : from 0 to 65535
Output: GPIO Error Status
*/
GPIO_tenuErrorStatus GPIO_enuSetPortValue( GPIO_PORTS_t Cpy_enuPortNumber, u16 Cpy_enuPortValue);


/* GPIO Get Pin Value Function
Input: Port Number , Pin Number , Pointer to hold the value of pin
*************** PORT NUMBER OPTIONS********************
			1) GPIO_enuPORTA
			2) GPIO_enuPORTB
			3) GPIO_enuPORTC
			4) GPIO_enuPORTD
			5) GPIO_enuPORTE
			6) GPIO_enuPORTH
*************** PIN NUMBER OPTIONS********************
			1) GPIO_enuPin0,
			2) GPIO_enuPin1,
			3) GPIO_enuPin2,
			4) GPIO_enuPin3,
			5) GPIO_enuPin4,
			6) GPIO_enuPin5,
			7) GPIO_enuPin6,
			8) GPIO_enuPin7,
			9) GPIO_enuPin8,
			10) GPIO_enuPin9,
			11) GPIO_enuPin10,
			12) GPIO_enuPin11,
			13) GPIO_enuPin12,
			14) GPIO_enuPin13,
			15) GPIO_enuPin14,
			16) GPIO_enuPin15
*
Output: GPIO Error Status
*/
GPIO_tenuErrorStatus GPIO_enuGetPinValue( GPIO_PORTS_t Cpy_enuPortNumber, GPIO_PINS_t Cpy_enuPinNumber , GPIO_PIN_VALUE_t * Add_penuPinValue);
/* **************************************** */
/* GPIO Get Port Value Function
Input: Port Number , Pointer to hold the value of port
*************** PORT NUMBER OPTIONS********************
			1) GPIO_enuPORTA
			2) GPIO_enuPORTB
			3) GPIO_enuPORTC
			4) GPIO_enuPORTD
			5) GPIO_enuPORTE
			6) GPIO_enuPORTH
Output: GPIO Error Status
*/
GPIO_tenuErrorStatus GPIO_enuGetPortValue( GPIO_PORTS_t Cpy_enuPortNumber, GPIO_PORT_VALUE_t * Add_penuPortValue);
GPIO_tenuErrorStatus GPIO_enuInit(GPIO_Cfg_t * GPIO_Cfg);
GPIO_tenuErrorStatus GPIO_enuSelectAF(GPIO_PORT_VALUE_t Cpy_enuPortNumber,GPIO_PINS_t Cpy_enuPinNumber ,GPIO_AF_t Cpy_enuAF);
#endif /* GPIO_H_ */
