/*
 * LCD_Cfg.c
 *
 *  Created on: 24 Mar 2023
 *      Author: naglaaa
 */


#include "STD_Types.h"
#include "BIT_Math.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_cfg.h"

const LCD_Cfg_t LCD_Cfg = {


			/*Control Pins*/
			.LCD_Pins_t.Enable_Pin.Port = GPIO_enuPORTA,
			.LCD_Pins_t.Enable_Pin.Pin = GPIO_enuPin0,

			.LCD_Pins_t.RS_Pin.Port =GPIO_enuPORTA,
			.LCD_Pins_t.RS_Pin.Pin = GPIO_enuPin1,

			.LCD_Pins_t.RW_Pin.Port =GPIO_enuPORTA,
			.LCD_Pins_t.RW_Pin.Pin = GPIO_enuPin2,

			/*Data Pins*/
			.LCD_Pins_t.data[0] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin3
			},

			.LCD_Pins_t.data[1] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin4,
			},
			.LCD_Pins_t.data[2] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin5,
			},
			.LCD_Pins_t.data[3] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin6,
			},

			.LCD_Pins_t.data[4] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin7,
			},

			.LCD_Pins_t.data[5] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin8,
			},

			.LCD_Pins_t.data[6] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin9,
			},

			.LCD_Pins_t.data[7] =
			{
			.Port = GPIO_enuPORTA,
			.Pin = GPIO_enuPin10,
			},


			/*Operations*/
		.LCD_Operation_t.No_Of_Lines = LCD_enuTwoLines,
		.LCD_Operation_t.Cursor_Enable = LCD_enuCursorEnable,
		.LCD_Operation_t.Cursor_Blink = LCD_enuCursorNoBlinking,
		.LCD_Operation_t.Font =LCD_enuLargeFont,
		.LCD_Operation_t.Display_Enable =LCD_enuDisplayOn,




};



