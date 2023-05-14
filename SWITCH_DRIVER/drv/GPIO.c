/*
 * GPIO.c
 *
 *  Created on: 15 Feb 2023
 *      Author: naglaaa
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
 /**********************************************DEFINES************************************************************/
#define MODE_INPUT 0b00
#define MODE_OUTPUT 0b01
#define MODE_AF 0b10
#define MODE_ANALOG 0b11

#define OTYPE_PUSH_PULL 0
#define OTYPE_OPEN_DRAIN 1

#define PUPDR_NO 0b00
#define PUPDR_PULL_UP 0b01
#define PUPDR_PULL_DOWN 0b10

#define AF_CLEAR_MASK 0x0000000f





volatile GPIO_t * const GPIO[6] =
{   [GPIO_enuPORTA] = (volatile GPIO_t *)0x40020000,
	[GPIO_enuPORTB] =(volatile GPIO_t *)0x40020400,
	[GPIO_enuPORTC]=(volatile GPIO_t *)0x40020800,
	[GPIO_enuPORTD]= (volatile GPIO_t *)0x40020C00,
	[GPIO_enuPORTE]=(volatile GPIO_t *)0x40021000,
	[GPIO_enuPORTH]=  (volatile GPIO_t *)0x40021C00
};

/*****************************************************STATIC FUNCTIONS PROTOTYPES***************************************/

static void Input(GPIO_PORTS_t Port, GPIO_PINS_t Pin);
static void Output(GPIO_PORTS_t Port, GPIO_PINS_t Pin);
static void Analog(GPIO_PORTS_t Port,GPIO_PINS_t Pin);
static void AF(GPIO_PORTS_t Port,GPIO_PINS_t Pin);
static void OpenDrain(GPIO_PORTS_t Port,GPIO_PINS_t Pin);
static void PushPull(GPIO_PORTS_t Port,GPIO_PINS_t Pinr);
static void PullUp(GPIO_PORTS_t Port,GPIO_PINS_t Pin);
static void PullDown(GPIO_PORTS_t Port,GPIO_PINS_t Pin);
static void Speed(GPIO_PORTS_t Port,GPIO_PINS_t Pin, GPIO_SPEEDS_t Speed);

/**************************************************FUNCTIONS IMPLEMENTATION*************************************************/

GPIO_tenuErrorStatus GPIO_enuWritePinValue( GPIO_PORTS_t Cpy_enuPortNumber, GPIO_PINS_t Cpy_enuPinNumber , GPIO_PIN_VALUE_t Cpy_enuPinValue)
{
	GPIO_tenuErrorStatus Local_enuErrorStatus = GPIO_enuOK;
			if( (Cpy_enuPortNumber < GPIO_enuPORTA) || (Cpy_enuPortNumber > GPIO_enuPORTH ))
			{
				Local_enuErrorStatus = GPIO_enuNOK;
			}
			else if(( Cpy_enuPinNumber < GPIO_enuPin0) || (Cpy_enuPinNumber > GPIO_enuPin15))
			{
				Local_enuErrorStatus = GPIO_enuNOK;
			}
			else if ((Cpy_enuPinValue != GPIO_enuPin_LOW) && (Cpy_enuPinValue != GPIO_enuPin_HIGH))
			{
				Local_enuErrorStatus = GPIO_enuNOK;
			}
			else
			{
				if( Cpy_enuPinValue == GPIO_enuPin_LOW)
				{ /*Reset Register*/
					GPIO[Cpy_enuPortNumber]->GPIO_BSRR |= 1<<(Cpy_enuPinNumber+16);
					Local_enuErrorStatus = GPIO_enuOK;
				}
				else if(Cpy_enuPinValue == GPIO_enuPin_HIGH)
				{
					/*Set Register*/
					GPIO[Cpy_enuPortNumber]->GPIO_BSRR = 1<<Cpy_enuPinNumber;
					Local_enuErrorStatus = GPIO_enuOK;
				}
			}
	return Local_enuErrorStatus;
}

GPIO_tenuErrorStatus GPIO_enuSetPortValue( GPIO_PORTS_t Cpy_enuPortNumber, u16 Cpy_enuPortValue)
{
	GPIO_tenuErrorStatus Local_enuErrorStatus = GPIO_enuOK;
		if( (Cpy_enuPortNumber < GPIO_enuPORTA) || (Cpy_enuPortNumber > GPIO_enuPORTH ))
		{
			Local_enuErrorStatus = GPIO_enuNOK;
		}
		else if( (Cpy_enuPortValue < GPIO_enuPort_LOW) || (Cpy_enuPortValue > GPIO_enuPort_HIGH))
		{
			Local_enuErrorStatus = GPIO_enuNOK;
		}
		else
		{
					GPIO[Cpy_enuPortNumber]->GPIO_ODR = Cpy_enuPortValue;
					Local_enuErrorStatus = GPIO_enuOK;
		}
	return Local_enuErrorStatus;
}
GPIO_tenuErrorStatus GPIO_enuGetPinValue( GPIO_PORTS_t Cpy_enuPortNumber, GPIO_PINS_t Cpy_enuPinNumber , GPIO_PIN_VALUE_t * Add_penuPinValue)
{
	GPIO_tenuErrorStatus Local_enuErrorStatus = GPIO_enuOK;

	   if( (Cpy_enuPortNumber < GPIO_enuPORTA) || (Cpy_enuPortNumber > GPIO_enuPORTH ))
		{
			Local_enuErrorStatus = GPIO_enuNOK;
		}
		else if(( Cpy_enuPinNumber < GPIO_enuPin0) || (Cpy_enuPinNumber > GPIO_enuPin15))
		{
			Local_enuErrorStatus = GPIO_enuNOK;
		}
		else
		{
			*Add_penuPinValue = GET_BIT(GPIO[Cpy_enuPortNumber]->GPIO_IDR,Cpy_enuPinNumber);
			Local_enuErrorStatus = GPIO_enuOK;
		}
	return Local_enuErrorStatus;
}

GPIO_tenuErrorStatus GPIO_enuGetPortValue( GPIO_PORTS_t Cpy_enuPortNumber, GPIO_PORT_VALUE_t * Add_penuPortValue)
{

	GPIO_tenuErrorStatus Local_enuErrorStatus = GPIO_enuOK;

		if( (Cpy_enuPortNumber < GPIO_enuPORTA) || (Cpy_enuPortNumber > GPIO_enuPORTH ))
		{
				Local_enuErrorStatus = GPIO_enuNOK;
		}
		else
		{
			*Add_penuPortValue = GPIO[Cpy_enuPortNumber]->GPIO_IDR;
			Local_enuErrorStatus = GPIO_enuOK;
		}
	return Local_enuErrorStatus;
}
GPIO_tenuErrorStatus GPIO_enuInit(GPIO_Cfg_t * GPIO_Cfg)
{
	u32 Local_ClearMask = 0x00000003;
	u32 Local_u32TempReg=0;
	GPIO_tenuErrorStatus Local_enuErrorStatus = GPIO_enuOK;

	switch(GPIO_Cfg->Mode )
	{
							/***************************************************************************************************
							********************************************* INPUT CASES******************************************
							****************************************************************************************************/

		case GPIO_enuMode_Input_Floating :
		/*****Configure Input ****/
		Input(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_Input_PullUp :
		/*****Configure Input ****/
		Input(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Up*******/
		PullUp(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_Input_PullDown :
		/*****Configure Input ****/
		Input(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Down*******/
		PullDown(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

						/***************************************************************************************************
						********************************************* OUTPUT CASES******************************************
						**-**************************************************************************************************/

		case GPIO_enuMode_Output_OpenDrain :
		/*****Configure Output******/
		Output(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/*******Configure OpenDrain*****/
		OpenDrain(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;


		case GPIO_enuMode_Output_PushPull :
			/*****Configure Output******/

				Output(GPIO_Cfg->Port,GPIO_Cfg->Pin);
				/*******Configure PushPull*****/
				PushPull(GPIO_Cfg->Port,GPIO_Cfg->Pin);
				break;

		case GPIO_enuMode_Output_OpenDrain_PullUp:
		/*****Configure Output******/
		Output(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/*******Configure OpenDrain*****/
		OpenDrain(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Up*******/
		PullUp(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_Output_OpenDrain_PullDown:
		/*****Configure Output******/
		Output(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/*******Configure OpenDrain*****/
		OpenDrain(GPIO_Cfg->Port,GPIO_Cfg->Pin);

		/******Configure Pull Down*******/
		PullDown(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;


		case GPIO_enuMode_Output_PushPull_PullUp :
		/*****Configure Output******/
		Output(GPIO_Cfg->Port,GPIO_Cfg->Pin);

		/*******Configure PushPull*****/
		PushPull(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Up*******/
		PullUp(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;



		case GPIO_enuMode_Output_PushPull_PullDown :
		/*****Configure Output******/

		Output(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/*******Configure PushPull*****/
		PushPull(GPIO_Cfg->Port,GPIO_Cfg->Pin);

		/******Configure Pull Down*******/

		PullDown(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

								/***************************************************************************************************
								*********************************************ANALOG*************************************************
								****************************************************************************************************/

		case GPIO_enuMode_Analog:
		/*********Configure Analog***********/
		Analog(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;
								/***************************************************************************************************
								*********************************************ALTERNATE FUNCTION CASES*******************************
								****************************************************************************************************/

		case GPIO_enuMode_AF_OpenDrain:
		/********Configure AF*******/
		AF(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/*******Configure OpenDrain*****/

		OpenDrain(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_AF_OpenDrain_PullUp:
		/********Configure AF*******/
		AF(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/*******Configure OpenDrain*****/

		OpenDrain(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Up*******/

		PullUp(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_AF_OpenDrain_PullDown:
		/********Configure AF*******/
		AF(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/*******Configure OpenDrain*****/
		OpenDrain(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Down*******/
		PullDown(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_AF_PushPull:

		/********Configure AF*******/
		AF(GPIO_Cfg->Port,GPIO_Cfg->Pin);

		/*******Configure PushPull*****/
		PushPull(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_AF_PushPull_PullUp:
		/********Configure AF*******/
		AF(GPIO_Cfg->Port,GPIO_Cfg->Pin);

		/*******Configure PushPull*****/
		PushPull(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Up*******/

		PullUp(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;

		case GPIO_enuMode_AF_PushPull_PullDown:
		/********Configure AF*******/
		AF(GPIO_Cfg->Port,GPIO_Cfg->Pin);

		/*******Configure PushPull*****/
		PushPull(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		/******Configure Pull Down*******/

		PullDown(GPIO_Cfg->Port,GPIO_Cfg->Pin);
		break;
		default:Local_enuErrorStatus = GPIO_enuNOK;break;

	}

	/*****Set The Needed Speed*******/

		Speed(GPIO_Cfg->Port,GPIO_Cfg->Pin,GPIO_Cfg->Speed);
		return Local_enuErrorStatus;
}
/****************************************** STATIC FUNCTIONS IMPLEMENTATION****************************************/

static void Input(GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{

		u32 Local_ClearMask = 0x00000003;
		u32 Local_u32TempReg=0;
		/*Take GPIO_MODERS In Local Register*/
		Local_u32TempReg = GPIO[Port]->GPIO_MODER;
		/* Clear The Needed Two Bits*/
		Local_u32TempReg &=~(Local_ClearMask << (Pin *2));
		/* Set The Needed Mode*/
		Local_u32TempReg |= ((MODE_INPUT) << (Pin *2));
		/* Return The Local Register Into GPIO MODER Again*/
		GPIO[Port]->GPIO_MODER = Local_u32TempReg;
}
static void PullUp(GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{
	u32 Local_ClearMask = 0x00000003;
		u32 Local_u32TempReg=0;


		/*Take GPIO_PUPDR In Local Register*/
		 Local_u32TempReg = GPIO[Port]->GPIO_PUPDR;
		/* Clear The Needed Two Bits*/
		Local_u32TempReg &=~(Local_ClearMask << (Pin *2));
		/* Set The Needed Mode*/
		Local_u32TempReg |= ((PUPDR_PULL_UP) << (Pin *2));
		/* Return The Local Register Into GPIO PUPDR Again*/
		GPIO[Port]->GPIO_PUPDR= Local_u32TempReg;
}
static void PullDown(GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{
	u32 Local_ClearMask = 0x00000003;
			u32 Local_u32TempReg=0;
		/*Take GPIO_PUPDR In Local Register*/
		 Local_u32TempReg = GPIO[Port]->GPIO_PUPDR;
		/* Clear The Needed Two Bits*/
		Local_u32TempReg &=~(Local_ClearMask << (Pin *2));
		/* Set The Needed Mode*/
		Local_u32TempReg |= ((PUPDR_PULL_DOWN) << (Pin *2));
		/* Return The Local Register Into GPIO PUPDR Again*/
		GPIO[Port]->GPIO_PUPDR= Local_u32TempReg;
}
static void Output(GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{

	u32 Local_ClearMask = 0x00000003;
	u32 Local_u32TempReg=0;
		/*Take GPIO_MODERS In Local Register*/
		Local_u32TempReg = GPIO[Port]->GPIO_MODER;
		/* Clear The Needed Two Bits*/
		Local_u32TempReg &=~(Local_ClearMask << (Pin *2));
		/* Set The Needed Mode*/
		Local_u32TempReg |= ((MODE_OUTPUT) << (Pin *2));
		/* Return The Local Register Into GPIO MODER Again*/
		GPIO[Port]->GPIO_MODER = Local_u32TempReg;
}
static void OpenDrain(GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{
GPIO[Port]->GPIO_OTYPER |= (OTYPE_OPEN_DRAIN<< Pin);
}
static void PushPull(GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{
	GPIO[Port]->GPIO_OTYPER &=~ (1<< Pin);
}
static void Analog (GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{ u32 Local_ClearMask = 0x00000003;
	u32 Local_u32TempReg=0;
	/*Take GPIO_MODERS In Local Register*/
	Local_u32TempReg = GPIO[Port]->GPIO_MODER;
	/* Clear The Needed Two Bits*/
	Local_u32TempReg &=~(Local_ClearMask << (Pin *2));
	/* Set The Needed Mode*/
	Local_u32TempReg|= ((MODE_ANALOG) << (Pin *2));
	/* Return The Local Register Into GPIO MODER Again*/
	GPIO[Port]->GPIO_MODER = Local_u32TempReg;
}
static void AF (GPIO_PORTS_t Port, GPIO_PINS_t Pin)
{
	u32 Local_ClearMask = 0x00000003;
	u32 Local_u32TempReg=0;
	/*Take GPIO_MODERS In Local Register*/
	Local_u32TempReg = GPIO[Port]->GPIO_MODER;
	/* Clear The Needed Two Bits*/
	Local_u32TempReg &=~(Local_ClearMask << (Pin *2));
	/* Set The Needed Mode*/
	Local_u32TempReg |= ((MODE_AF) << (Pin *2));
	/* Return The Local Register Into GPIO MODER Again*/
	GPIO[Port]->GPIO_MODER = Local_u32TempReg;
}
static void Speed(GPIO_PORTS_t Port,GPIO_PINS_t Pin, GPIO_SPEEDS_t Speed)
{
	u32 Local_ClearMask = 0x00000003;
		u32 Local_u32TempReg=0;
	/*Take GPIO_OSPEEDR In Local Register*/
	Local_u32TempReg = GPIO[Port]->GPIO_OPSPEEDR;
	/* Clear The Needed Two Bits*/
	Local_u32TempReg &=~(Local_ClearMask << (Pin *2));
	/* Set The Needed Mode*/
	Local_u32TempReg |= (Speed << (Pin *2));
	/* Return The Local Register Into GPIO PUPDR Again*/
	GPIO[Port]->GPIO_OPSPEEDR= Local_u32TempReg;
}
GPIO_tenuErrorStatus GPIO_enuSelectAF(GPIO_PORT_VALUE_t Cpy_enuPortNumber, GPIO_PINS_t Cpy_enuPinNumber ,GPIO_AF_t Cpy_enuAF)
{
	u32 Local_u32Register=0;
	GPIO_tenuErrorStatus Local_enuErrorStatus = GPIO_enuOK;
	/*AFRL Range*/
	if( (Cpy_enuPortNumber < GPIO_enuPORTA) || (Cpy_enuPortNumber > GPIO_enuPORTH ))
	{
		Local_enuErrorStatus = GPIO_enuNOK;
	}
	/*AFRH Range*/
	else if(( Cpy_enuPinNumber < GPIO_enuPin0) || (Cpy_enuPinNumber > GPIO_enuPin15))
	{
		Local_enuErrorStatus = GPIO_enuNOK;
	}

	else
	{
		if ( Cpy_enuPinNumber <= 7)
		{
			Local_u32Register = GPIO[Cpy_enuPortNumber]->GPIO_AFRL;
			Local_u32Register &=~ (AF_CLEAR_MASK << (Cpy_enuPinNumber * 4));
			Local_u32Register |= (Cpy_enuAF << (Cpy_enuPinNumber * 4));
			GPIO[Cpy_enuPortNumber]->GPIO_AFRL = Local_u32Register;
		}

		else if ((Cpy_enuPinNumber >=8) || (Cpy_enuPinNumber <= 25))
		{
			Local_u32Register = GPIO[Cpy_enuPortNumber]->GPIO_AFRH;
			Local_u32Register &=~ (AF_CLEAR_MASK << ((Cpy_enuPinNumber-8) * 4));
			Local_u32Register |= (Cpy_enuAF << ((Cpy_enuPinNumber-8) * 4));
			GPIO[Cpy_enuPortNumber]->GPIO_AFRH = Local_u32Register;
		}
		Local_enuErrorStatus = GPIO_enuOK;
	}
	return Local_enuErrorStatus;
}
