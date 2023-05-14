#ifndef LED_H
#define LED_H
/**************************************************DEFINES****************************************************************/
#define STATE_LED_ON 1
#define STATE_LED_OFF 0
#define STATE_LED_TOGGLE 2
/*************************************************TYPES*******************************************************************/

typedef enum
{
	LED_enuOK,
	LED_enuNOK
}LED_tenuErrorStatus;
typedef enum
{
	LED_enuActiveHigh,
	LED_enuActiveLow
}LED_MODE_t;


typedef struct
{
	GPIO_PORTS_t Port;
	GPIO_PINS_t Pin;
	LED_MODE_t Mode;
	GPIO_SPEEDS_t Speed;
}LED_CFG_t;

extern const LED_CFG_t LED_CFG[LEDS_NUMBER];

/*************************************************FUNCTION PROTOTYPES*******************************************************************/


/*****************************************
Description: Led Initialization Function
Input: Void
Output: LED Error Status
****************************************/
LED_tenuErrorStatus LED_enuInit(void);
/*****************************************
Description: Led Set Led State Function
Input: Led Pin , State
****************LED PIN OPTIONS************

			1)LED_Alarm
			2)LED_Warning,
			3)LED_Stop,
			4)LED_Start,
			5)LEDS_NUMBER
****************LED STATE OPTIONS************
            1)LED_ON
            2)LED_OFF

Output: LED Error Status
****************************************/
LED_tenuErrorStatus LED_enuSetLedState(LED_PINS_t Cpy_enuLedPin, u8 Cpy_u8State );
#endif
