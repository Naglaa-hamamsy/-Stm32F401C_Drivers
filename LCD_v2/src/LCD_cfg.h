#ifndef LCD_CFG_H
#define LCD_CFG_H


typedef enum
{
	LCD_1,
	LCD_2,
	LCDs_NUM
}LCD_t;


typedef struct
{

	struct
	{
		LCD_Lines_t	No_Of_Lines;
		LCD_Cursor_Enable_t	Cursor_Enable;
		LCD_Cursor_Blink_t	Cursor_Blink;
		LCD_Font_t	Font;
		LCD_Display_t Display_Enable;

	}LCD_Operation_t;

	struct{
		GPIO_Cfg_t Enable_Pin;
		GPIO_Cfg_t RS_Pin;
		GPIO_Cfg_t RW_Pin;
		GPIO_Cfg_t data[8];
	}LCD_Pins_t;



}LCD_Cfg_t;

extern const LCD_Cfg_t LCD_Cfg;





#endif
