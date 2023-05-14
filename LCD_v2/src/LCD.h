#ifndef LCD_H
#define LCD_H
/*********************************DEFINES***********************************/
#define ROWS_NUM 1
#define COLS_NUM 15
/*LCD Config*/

#define FUNCTION_SET(LINES,FONT) (LINES|FONT)
#define DISPLAY_CONTROL(CURSOR,DISPLAY,BLINK) (CURSOR|DISPLAY|BLINK)
#define DISPLAY_CLEAR 0x01


/********************************TYPES**************************************/

typedef enum
{
	LCD_enuOneLine = 0b00110000,
	LCD_enuTwoLines = 0b00111000,
}LCD_Lines_t;
typedef enum
{
	LCD_enuCursorDisable = 0b00001000,
	LCD_enuCursorEnable = 0b00001010,
}LCD_Cursor_Enable_t;

typedef enum
{
	LCD_enuCursorBlinking = 0b00001001,
	LCD_enuCursorNoBlinking = 0b00001000,
}LCD_Cursor_Blink_t;
typedef enum
{
	LCD_enuSmallFont = 0b00110000,
	LCD_enuLargeFont = 0b00110100,
}LCD_Font_t;
typedef enum
{
	LCD_enuDisplayOn = 0b00001100,
	LCD_enuDisplayOff = 0b00001000,
}LCD_Display_t;
typedef enum
{
	LCD_enuOK,
	LCD_enuNOK,
	LCD_enuBusy,
	LCD_enuNotInitialized,
	LCD_enuBufferFull
}LCD_enuErrorStatus;


void LCD_vidInit(void);
//LCD_enuErrorStatus LCD_enuSendChar(u8 Cpy_u8Data);
LCD_enuErrorStatus LCD_enuSendStringAsynch(char Add_pcString[] , u8 Cpy_u8Length ,u8 Cpy_u8XPos, u8 Cpy_u8YPos);
LCD_enuErrorStatus LCD_enuClearScreenAsynch(void);
//LCD_enuErrorStatus LCD_enuGoToXY(u8 Cpy_u8XPos, u8 Cpy_u8YPos);
//LCD_enuErrorStatus LCD_enuSendInteger(u16 Cpy_u32Integer);
//LCD_enuErrorStatus LCD_enuWriteSpecialChar(u8 Add_pu8Pattern[], u8 Cpy_u8BlockNum,u8 Cpy_u8XPos, u8 Cpy_u8YPos);



#endif
