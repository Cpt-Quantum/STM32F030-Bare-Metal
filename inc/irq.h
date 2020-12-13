#ifndef IRQ_H
#define IRQ_H

/* Type mapping IRQ number to peripheral, not all peripherals will be         */
/* necessarily available on each chip variant. Check the reference manual for */
/* more information.                                                          */
typedef enum
{
	WWDG_IRQ                =  0,
	RTC_IRQ                 =  2,
	FLASH_IRQ               =  3,
	RCC_IRQ                 =  4,
	EXTI0_1_IRQ             =  5,
	EXTI2_3_IRQ             =  6,
	DMA_CH1_IRQ             =  9,
	DMA_CH2_3_IRQ           = 10,
	DMA_CH4_5_IRQ           = 11,
	ADC_IRQ                 = 12,
	TIM1_BRK_UP_TRG_COM_IRQ = 13,
	TIM1_CC_IRQ             = 14,
	TIM3_IRQ                = 16,
	TIM6_IRQ                = 17,
	TIM14_IRQ               = 19,
	TIM15_IRQ               = 20,
	TIM16_IRQ               = 21,
	TIM17_IRQ               = 22,
	I2C1_IRQ                = 23,
	I2C2_IRQ                = 24,
	SPI1_IRQ                = 25,
	SPI2_IRQ                = 26,
	USART1_IRQ              = 27,
	USART2_IRQ              = 28,
	USART3_4_5_6_IRQ        = 29,
	USB_IRQ                 = 31
} IRQ_E;

#endif //IRQ_H
