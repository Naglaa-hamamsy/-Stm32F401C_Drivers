#ifndef NVIC_H
#define NVIC_H
/******************************************DEFINES***************************************************/

#define NVIC_16G_0S 0x05FA0000  /* ALL IS PREEMPTION*/
#define NVIC_8G_2S 0x05FA0400   /* 3 PREEMPTION & 1 SUBGROUP*/
#define NVIC_4G_4S  0x05FA0500   /* 2 PREEMPTION & 2 SUBGROUP*/
#define NVIC_2G_8S  0x05FA0600 /*1 PREEMPTION & 1 SUBGROUP*/
#define NVIC_0G_16S 0x05FA0700  /*NO PREEMPTION*/
/*******************************************TYPES***************************************************/
typedef enum
{
	NVIC_enuOK,
	NVIC_enuNOK,
	NVIC_enuNullPtr
}NVIC_tenuErrorStatus;


typedef enum
{
	IRQn_NonMaskableInt         = -14,    /*!< 2 Non Maskable Interrupt                                          */
	  IRQn_MemoryManagement       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
	  IRQn_BusFault               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
	  IRQn_UsageFault             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
	  IRQn_SVCall                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
	  IRQn_DebugMonitor           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
	  IRQn_PendSV                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
	  IRQn_SysTick                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
	/******  STM32 specific Interrupt Numbers **********************************************************************/
	  IRQn_WWDG                   = 0,      /*!< Window WatchDog Interrupt                                         */
	  IRQn_PVD                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
	  IRQn_TAMP_STAMP             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
	  IRQn_RTC_WKUP               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
	  IRQn_FLASH                  = 4,      /*!< FLASH global Interrupt                                            */
	  IRQn_RCC                    = 5,      /*!< RCC global Interrupt                                              */
	  IRQn_EXTI0                  = 6,      /*!< EXTI Line0 Interrupt                                              */
	  IRQn_EXTI1                  = 7,      /*!< EXTI Line1 Interrupt                                              */
	  IRQn_EXTI2                  = 8,      /*!< EXTI Line2 Interrupt                                              */
	  IRQn_EXTI3                  = 9,      /*!< EXTI Line3 Interrupt                                              */
	  IRQn_EXTI4                  = 10,     /*!< EXTI Line4 Interrupt                                              */
	  IRQn_DMA1_Stream0           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
	  IRQn_DMA1_Stream1           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
	  IRQn_DMA1_Stream2           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
	  IRQn_DMA1_Stream3           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
	  IRQn_DMA1_Stream4           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
	  IRQn_DMA1_Stream5           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
	  IRQn_DMA1_Stream6           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
	  IRQn_ADC                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
	  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                                     */
	  IRQn_TIM1_BRK_TIM9          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
	  IRQn_TIM1_UP_TIM10          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
	  IRQn_TIM1_TRG_COM_TIM11     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
	  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
	  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                             */
	  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                             */
	  IRQn_TIM4                   = 30,     /*!< TIM4 global Interrupt                                             */
	  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                              */
	  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                              */
	  IRQn_I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                              */
	  IRQn_I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                              */
	  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                             */
	  IRQn_SPI2                   = 36,     /*!< SPI2 global Interrupt                                             */
	  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                                           */
	  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                                           */
	  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                                   */
	  IRQn_RTC_Alarm              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
	  IRQn_OTG_FS_WKUP            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
	  IRQn_DMA1_Stream7           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
	  IRQn_SDIO                   = 49,     /*!< SDIO global Interrupt                                             */
	  IRQn_TIM5                   = 50,     /*!< TIM5 global Interrupt                                             */
	  IRQn_SPI3                   = 51,     /*!< SPI3 global Interrupt                                             */
	  IRQn_DMA2_Stream0           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
	  IRQn_DMA2_Stream1           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
	  IRQn_DMA2_Stream2           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
	  IRQn_DMA2_Stream3           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
	  IRQn_DMA2_Stream4           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
	  IRQn_OTG_FS                 = 67,     /*!< USB OTG FS global Interrupt                                       */
	  IRQn_DMA2_Stream5           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
	  IRQn_DMA2_Stream6           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
	  IRQn_DMA2_Stream7           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
	  IRQn_USART6                 = 71,     /*!< USART6 global interrupt                                           */
	  IRQn_I2C3_EV                = 72,     /*!< I2C3 event interrupt                                              */
	  IRQn_I2C3_ER                = 73,     /*!< I2C3 error interrupt                                              */
	  IRQn_FPU                    = 81,      /*!< FPU global interrupt                                             */
	  IRQn_SPI4
}IRQn_t;

typedef enum
{

	NVIC_priority_0	,
	NVIC_priority_1	,
	NVIC_priority_2	,
	NVIC_priority_3	,
	NVIC_priority_4	,
	NVIC_priority_5	,
	NVIC_priority_6	,
	NVIC_priority_7	,
	NVIC_priority_8	,
	NVIC_priority_9	,
	NVIC_priority_10,
	NVIC_priority_11,
	NVIC_priority_12,
	NVIC_priority_13,
	NVIC_priority_14,
	NVIC_priority_15,

}Priorities_t;

typedef enum
{
	ActiveStatus_enuNotActive,
	ActiveStatus_enuActive,

}ActiveStatus_t;

//extern volatile NVIC_t1 * const NVIC;
/*******************************************FUNCTION PROTOTYPES***************************************************/
NVIC_tenuErrorStatus NVIC_enuSetPriority(IRQn_t,Priorities_t);
NVIC_tenuErrorStatus NVIC_enuEnableIRQ(IRQn_t);
NVIC_tenuErrorStatus NVIC_enuDisableIRQ(IRQn_t);
NVIC_tenuErrorStatus NVIC_enuSetPending(IRQn_t);
NVIC_tenuErrorStatus NVIC_enuClearPending(IRQn_t);
NVIC_tenuErrorStatus NVIC_enuGetActiveStatus(IRQn_t, ActiveStatus_t *);
NVIC_tenuErrorStatus NVIC_enusetPriorityGrouping(u32 Cpy_u8priorityGrouping);
void NVIC_vidSetPriMask(void);
void NVIC_vidSetFaultMask(void);
NVIC_tenuErrorStatus NVIC_vidSetBasePri(Priorities_t);
#endif
