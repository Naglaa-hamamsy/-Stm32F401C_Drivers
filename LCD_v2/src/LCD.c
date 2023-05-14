/*
 * LCD.c
 *
 *  Created on: 3 Apr 2023
 *      Author: naglaaa
 */

#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "LCD_cfg.h"
#include "LCD.h"
/********************************DEFINES************************************/
#define BUFFER_SIZE 4
#define BUSY 0
#define IDLE 1
#define LCD_ENABLE_LOW 0
#define LCD_ENABLE_HIGH 1
#define LCD_ENABLE_FLOAT 2
/***************************TYPES*************************************/
typedef enum
{
	FunctionSetStart,
	FunctionSetEnd,
	DisplayControlStart,
	DisplayControlEnd,
	DisplayClearStart,
	DisplayClearEnd,
	EndState,
	InitDone,
}Init_States_t;

typedef enum
{
	Req_Write,
	Req_Clear,
	NoReq
}Req_Type_t;

typedef enum
{
	Write_SetPositionStart,
	Write_SetPositionEnd,
	Write_SetChar,
	Write_Done,

}Write_States_t;

typedef struct
{
	char *String;
	u8 StringLength;
	u8 PosX;
	u8 PosY;
	u8 Idx;
}UserBuffer_t;

static UserBuffer_t UserBuffer={NULL};
/* Global State For State Machine Initialization States*/
static Init_States_t Init_State =FunctionSetStart;
static Req_Type_t Req_Type = NoReq;
static u8 LCD_State = IDLE;
static u8 Buffer_Available = BUFFER_SIZE;
static u8 Buffer_Next = 0;
static u8 Buffer_Current = 0;
static Write_States_t Write_State = Write_SetPositionStart;
static u8 LCD_Enable = LCD_ENABLE_LOW;
/*************************STATIC PROTOTYPES**************************/
static void voidInitStm(void);
static void voidSendCommand(u8 Cpy_u8Command);
static void voidSendChar(u8 Cpy_u8Char);
void voidLCD_Task(void);
static void voidWriteProcess(void);
static void voidClearProcess(void);
/*************************IMPLEMENTATION****************************/
void LCD_vidInit(void)
{
	GPIO_Cfg_t cfg;
	/*Enable Pin*/
	cfg.Port =LCD_Cfg.LCD_Pins_t.Enable_Pin.Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);
	/*Rs Pin*/
	cfg.Port =LCD_Cfg.LCD_Pins_t.RS_Pin.Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.RS_Pin.Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);
	/*Rw Pin*/
	cfg.Port =LCD_Cfg.LCD_Pins_t.RW_Pin.Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.RW_Pin.Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);
	/*Data Pins*/
	cfg.Port =LCD_Cfg.LCD_Pins_t.data[0].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[0].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);

	cfg.Port =LCD_Cfg.LCD_Pins_t.data[1].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[1].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);

	cfg.Port =LCD_Cfg.LCD_Pins_t.data[2].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[2].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);

	cfg.Port =LCD_Cfg.LCD_Pins_t.data[3].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[3].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);

	cfg.Port =LCD_Cfg.LCD_Pins_t.data[4].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[4].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);


	cfg.Port =LCD_Cfg.LCD_Pins_t.data[5].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[5].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);

	cfg.Port =LCD_Cfg.LCD_Pins_t.data[6].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[6].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);

	cfg.Port =LCD_Cfg.LCD_Pins_t.data[7].Port;
	cfg.Pin = LCD_Cfg.LCD_Pins_t.data[7].Pin;
	cfg.Mode = GPIO_enuMode_Output_PushPull;
	cfg.Speed = GPIO_enuSpeed_VeryHigh;
	GPIO_enuInit(&cfg);


}
LCD_enuErrorStatus LCD_enuSendStringAsych(char Add_pcString[] , u8 Cpy_u8Length ,u8 Cpy_u8XPos, u8 Cpy_u8YPos)
{
	LCD_enuErrorStatus LocalErrorStatus = LCD_enuOK;

	if(Init_State != InitDone)
	{
		LocalErrorStatus = LCD_enuNotInitialized;
	}
	if(LCD_State == BUSY)
	{
		LocalErrorStatus = LCD_enuBusy;
	}
	else
	{
		if((Cpy_u8XPos >ROWS_NUM) || (Cpy_u8YPos >COLS_NUM))
				{
					LocalErrorStatus = LCD_enuNOK;
				}
		else
		{
			LCD_State = BUSY;
			Req_Type = Req_Write;

				/*Put User Data Into Buffer*/

				UserBuffer.String = Add_pcString;
				UserBuffer.StringLength =Cpy_u8Length;
				UserBuffer.PosX = Cpy_u8XPos;
				UserBuffer.PosY = Cpy_u8YPos;



		}
	}
	return LocalErrorStatus;
}
 void voidInitStm(void)
{
	/*Start Delay Of This Function Is 35ms*/
		switch(Init_State)
		{
		case FunctionSetStart:

			voidSendCommand(FUNCTION_SET(LCD_Cfg.LCD_Operation_t.No_Of_Lines,LCD_Cfg.LCD_Operation_t.Font));
			GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_HIGH);
			Init_State = FunctionSetEnd;
			break;

		case FunctionSetEnd:
			GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_LOW);
			Init_State = DisplayControlStart;
			break;

		case DisplayControlStart:

			voidSendCommand(DISPLAY_CONTROL(LCD_Cfg.LCD_Operation_t.Display_Enable,LCD_Cfg.LCD_Operation_t.Cursor_Enable,LCD_Cfg.LCD_Operation_t.Cursor_Blink));
			GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_HIGH);
			Init_State = DisplayControlEnd;
			break;

		case DisplayControlEnd:
			GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_LOW);
			Init_State = DisplayClearStart;
			break;
		case DisplayClearStart:
			voidSendCommand(DISPLAY_CLEAR);
			GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_HIGH);
			Init_State = DisplayClearEnd;
			break;
		case DisplayClearEnd:
			GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_LOW);
			Init_State = EndState;
			break;
		case EndState: Init_State = InitDone; break;

		}
}



static void voidSendCommand(u8 Cpy_u8Command)
{
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.RS_Pin.Port,LCD_Cfg.LCD_Pins_t.RS_Pin.Pin,GPIO_enuPin_LOW);
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.RW_Pin.Port,LCD_Cfg.LCD_Pins_t.RW_Pin.Pin,GPIO_enuPin_LOW);

	/*Set The LCD Data Port With Command*/
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[0].Port,LCD_Cfg.LCD_Pins_t.data[0].Pin,GET_BIT(Cpy_u8Command,0));
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[1].Port,LCD_Cfg.LCD_Pins_t.data[1].Pin,GET_BIT(Cpy_u8Command,1));
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[2].Port,LCD_Cfg.LCD_Pins_t.data[2].Pin,GET_BIT(Cpy_u8Command,2));
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[3].Port,LCD_Cfg.LCD_Pins_t.data[3].Pin,GET_BIT(Cpy_u8Command,3));
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[4].Port,LCD_Cfg.LCD_Pins_t.data[4].Pin,GET_BIT(Cpy_u8Command,4));
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[5].Port,LCD_Cfg.LCD_Pins_t.data[5].Pin,GET_BIT(Cpy_u8Command,5));
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[6].Port,LCD_Cfg.LCD_Pins_t.data[6].Pin,GET_BIT(Cpy_u8Command,6));
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[7].Port,LCD_Cfg.LCD_Pins_t.data[7].Pin,GET_BIT(Cpy_u8Command,7));


}
static void voidSendChar(u8 Cpy_u8Char)
{
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.RS_Pin.Port,LCD_Cfg.LCD_Pins_t.RS_Pin.Pin,GPIO_enuPin_HIGH);
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.RW_Pin.Port,LCD_Cfg.LCD_Pins_t.RW_Pin.Pin,GPIO_enuPin_LOW);
	/*Set The LCD Data Port With Command*/
	GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[0].Port,LCD_Cfg.LCD_Pins_t.data[0].Pin,GET_BIT(Cpy_u8Char,0));
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[1].Port,LCD_Cfg.LCD_Pins_t.data[1].Pin,GET_BIT(Cpy_u8Char,1));
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[2].Port,LCD_Cfg.LCD_Pins_t.data[2].Pin,GET_BIT(Cpy_u8Char,2));
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[3].Port,LCD_Cfg.LCD_Pins_t.data[3].Pin,GET_BIT(Cpy_u8Char,3));
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[4].Port,LCD_Cfg.LCD_Pins_t.data[4].Pin,GET_BIT(Cpy_u8Char,4));
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[5].Port,LCD_Cfg.LCD_Pins_t.data[5].Pin,GET_BIT(Cpy_u8Char,5));
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[6].Port,LCD_Cfg.LCD_Pins_t.data[6].Pin,GET_BIT(Cpy_u8Char,6));
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.data[7].Port,LCD_Cfg.LCD_Pins_t.data[7].Pin,GET_BIT(Cpy_u8Char,7));

}
/*Every 2 ms*/
 void voidLCD_Task(void)
{
	if(Init_State != InitDone)
	{
		voidInitStm();
	}
	else
	{
		switch(Req_Type)
		{
		case Req_Write:
			voidWriteProcess();
			break;
		case Req_Clear:
			voidClearProcess();
			break;
		case NoReq:
			/*Do Nothing*/
			break;
		}

	}
}


static void voidWriteProcess(void)
{
	static u8 LCD_CurrentPos=0;
	LCD_Enable = LCD_ENABLE_LOW;
	switch(Write_State)
	{
	case Write_SetPositionStart:
		switch(UserBuffer.PosX)
				{
					case 0: voidSendCommand(0x80 + UserBuffer.PosY);break;
					case 1: voidSendCommand(0xC0 + UserBuffer.PosY);break;
				}
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_HIGH);
		break;
	case Write_SetPositionEnd:
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_LOW);
					break;
	case Write_SetChar:
		if(LCD_Enable == LCD_ENABLE_LOW)
		{
			if(LCD_CurrentPos < UserBuffer.StringLength)
					{
						voidSendChar(UserBuffer.String[LCD_CurrentPos]);
						LCD_CurrentPos++;
						GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_HIGH);
						LCD_Enable = LCD_ENABLE_HIGH;
					}
			else
					{
						LCD_State = IDLE;break;
					}
		}
		else
		{
				/*3shan el state ele ablha*/
			GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_LOW);
				LCD_Enable = LCD_ENABLE_LOW;
		}

	}

}
static void voidClearProcess(void)
{
	LCD_Enable = LCD_ENABLE_LOW;
	if(LCD_Enable == LCD_ENABLE_LOW)
			{
				voidSendCommand(DISPLAY_CLEAR);
				GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_HIGH);
				LCD_Enable = LCD_ENABLE_HIGH;

			}
	else
			{
				/*3shan el state ele ablha*/
		GPIO_enuWritePinValue(LCD_Cfg.LCD_Pins_t.Enable_Pin.Port,LCD_Cfg.LCD_Pins_t.Enable_Pin.Pin,GPIO_enuPin_LOW);
				LCD_Enable = LCD_ENABLE_LOW;
				LCD_State = IDLE;
			}

}
LCD_enuErrorStatus LCD_enuClearScreenAsynch(void)
{
	LCD_enuErrorStatus LocalErrorStatus = LCD_enuOK;

		if(LCD_State == BUSY)
		{
			LocalErrorStatus = LCD_enuBusy;
		}
		else if(Init_State != InitDone)
		{
			LocalErrorStatus = LCD_enuNotInitialized;
		}
		else
			/*IDLE STATE*/
		{
			LCD_State = BUSY;
			Req_Type = Req_Clear;
		}

	return LocalErrorStatus;
}



