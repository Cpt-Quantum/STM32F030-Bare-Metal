#include "inc/stm32f030x6.h"

#include <stdint.h>
#include <stdbool.h>

#define LED_PIN 4

typedef enum {
	GPIO_INPUT = 0,
	GPIO_OUTPUT = 1,
	GPIO_ALT_MODE = 2,
	GPIO_ANALOGUE = 3,
	GPIO_MODER_MAX = 3
} GPIO_MODER_E;

typedef enum {
	PLL_MULT_X2  = RCC_CFGR_PLLMUL2,
	PLL_MULT_X3  = RCC_CFGR_PLLMUL3,
	PLL_MULT_X4  = RCC_CFGR_PLLMUL4,
	PLL_MULT_X5  = RCC_CFGR_PLLMUL5,
	PLL_MULT_X6  = RCC_CFGR_PLLMUL6,
	PLL_MULT_X7  = RCC_CFGR_PLLMUL7,
	PLL_MULT_X8  = RCC_CFGR_PLLMUL8,
	PLL_MULT_X9  = RCC_CFGR_PLLMUL9,
	PLL_MULT_X10 = RCC_CFGR_PLLMUL10,
	PLL_MULT_X11 = RCC_CFGR_PLLMUL11,
	PLL_MULT_X12 = RCC_CFGR_PLLMUL12,
	PLL_MULT_X13 = RCC_CFGR_PLLMUL13,
	PLL_MULT_X14 = RCC_CFGR_PLLMUL14,
	PLL_MULT_X15 = RCC_CFGR_PLLMUL15,
	PLL_MULT_X16 = RCC_CFGR_PLLMUL16
} PLL_MULT_E;

void start_timer(TIM_TypeDef *TIMx, uint16_t prescale, uint16_t count)
{
	/* Make sure the timer is disabled before starting initialisation */
	TIMx->CR1 &= ~(TIM_CR1_CEN);

	/* Reset and start the timer */
	if (TIMx == TIM1)
	{
		RCC->APB2RSTR |=   RCC_APB2RSTR_TIM1RST;
		RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM1RST);
	}
	else if (TIMx == TIM16)
	{
		RCC->APB2RSTR |=   RCC_APB2RSTR_TIM16RST;
		RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM16RST);
	}
	else if (TIMx == TIM17)
	{
		RCC->APB2RSTR |=   RCC_APB2RSTR_TIM17RST;
		RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM17RST);
	}
	else if (TIMx == TIM3)
	{
		RCC->APB1RSTR |=   RCC_APB1RSTR_TIM3RST;
		RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST);
	}
	else if (TIMx == TIM14)
	{
		RCC->APB1RSTR |=   RCC_APB1RSTR_TIM14RST;
		RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM14RST);
	}

	/* Set the prescaler */
	TIMx->PSC = prescale;
	/* Set the value to count to */
	TIMx->ARR = count;
	/* Set the update event to generate an update of its registers and reset it */
	TIMx->EGR |= TIM_EGR_UG;
	/* Setup timer to trigger a hardware interrupt upon reaching the count */
	TIMx->DIER |= TIM_DIER_UIE;
	/* Now enable the timer */
	TIMx->CR1 |= TIM_CR1_CEN;
}

void clock_setup(bool external_clk, bool use_pll, PLL_MULT_E pll_mult)
{
	/* Enable the selected clock and wait for it to be ready */
	if (external_clk == true)
	{
		RCC->CR |= RCC_CR_HSEON;
		while(!(RCC->CR & RCC_CR_HSERDY)){};
	}
	else
	{
		RCC->CR |= RCC_CR_HSION;
		while(!(RCC->CR & RCC_CR_HSIRDY)){};
	}

	/* Now enable the PLL if needed */
	if (use_pll == true)
	{
		if (external_clk == true)
		{
			RCC->CFGR &= ~(RCC_CFGR_PLLMUL |
						   RCC_CFGR_PLLSRC);
			RCC->CFGR |= (RCC_CFGR_PLLSRC_HSE_PREDIV |
						  pll_mult);
		}
		else
		{
			RCC->CFGR &= ~(RCC_CFGR_PLLMUL |
						   RCC_CFGR_PLLSRC);
			RCC->CFGR |= (RCC_CFGR_PLLSRC_HSI_DIV2 |
						  pll_mult);
		}

		/* Turn on the PLL and wait for the hardware to set the ready flag */
		RCC->CR |= RCC_CR_PLLON;
		while(!(RCC->CR & RCC_CR_PLLRDY)){};
	}

	/* Now set the clock source of the system clock */
	if (use_pll == true)
	{
		RCC->CFGR &= ~(RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)){};
	}
	else if (external_clk == true)
	{
		RCC->CFGR &= ~(RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_SW_HSE;
		while(!(RCC->CFGR & RCC_CFGR_SWS_HSE)){};
	}
	else if (external_clk == false)
	{
		RCC->CFGR &= ~(RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_SW_HSI;
		while(!(RCC->CFGR & RCC_CFGR_SWS_HSI)){};
	}
}

int main(void)
{
	/* Setup flash wait cycles */
	FLASH->ACR &= ~(0x00000017);
	FLASH->ACR |= (FLASH_ACR_LATENCY | FLASH_ACR_PRFTBE);

	/* Initialise system clock */
	clock_setup(false, true, PLL_MULT_X12);

	/* Enable the clock for timer 3 */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	NVIC_SetPriority(TIM3_IRQn, 0x03);
	NVIC_EnableIRQ(TIM3_IRQn);

	/* Enable Port A GPIO clock */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	/* Set PA4 to output and set high */
	/* First clear the associated part of the MODER register for the LED pin */
	GPIOA->MODER &= ~(GPIO_MODER_MAX << (LED_PIN * 2));
	/* Now set the pin to be an output */
	GPIOA->MODER |= (GPIO_OUTPUT << (LED_PIN * 2));
	/* Finally set the pin high */
	GPIOA->ODR &= (1 << LED_PIN);

	/* Initialise the timer */
	start_timer(TIM3, 48000, 1000);
	
	/* Loop forever */
	while(1)
	{
	};
}

void TIM3_IRQHandler(void)
{
	/* Check the cause of the interrupt */
	if (TIM3->SR & TIM_SR_UIF)
	{
		/* First clear the interrupt flag */
		TIM3->SR &= ~(TIM_SR_UIF);

		/* Toggle the LED pin */
		GPIOA->ODR ^= (1 << LED_PIN);
	}
}
