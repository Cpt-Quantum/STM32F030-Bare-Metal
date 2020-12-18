#include <stdint.h>
#include <stdbool.h>
#include "inc/nvic.h"
#include "inc/rcc.h"
#include "inc/gpio.h"
#include "inc/timers.h"
#include "inc/flash.h"
#include "inc/irq.h"

void start_timer(timer_index_t timer_index, uint16_t prescale, uint16_t count)
{
	/* Make sure the timer is disabled before starting */
	TIMER_FIELD_WRITE(timer_index, cr1, cen, false);

	/* Reset the timer */
	switch(timer_index)
	{
		case TIM1_INDEX:
			RCC_FIELD_WRITE(apb2rstr, tim1rst, true);
			RCC_FIELD_WRITE(apb2rstr, tim1rst, false);
			break;
		case TIM15_INDEX:
			RCC_FIELD_WRITE(apb2rstr, tim15rst, true);
			RCC_FIELD_WRITE(apb2rstr, tim15rst, false);
			break;
		case TIM16_INDEX:
			RCC_FIELD_WRITE(apb2rstr, tim16rst, true);
			RCC_FIELD_WRITE(apb2rstr, tim16rst, false);
			break;
		case TIM17_INDEX:
			RCC_FIELD_WRITE(apb2rstr, tim17rst, true);
			RCC_FIELD_WRITE(apb2rstr, tim17rst, false);
			break;
		case TIM3_INDEX:
			RCC_FIELD_WRITE(apb1rstr, tim3rst, true);
			RCC_FIELD_WRITE(apb1rstr, tim3rst, false);
			break;
		case TIM6_INDEX:
			RCC_FIELD_WRITE(apb1rstr, tim6rst, true);
			RCC_FIELD_WRITE(apb1rstr, tim6rst, false);
			break;
		case TIM7_INDEX:
			RCC_FIELD_WRITE(apb1rstr, tim7rst, true);
			RCC_FIELD_WRITE(apb1rstr, tim7rst, false);
			break;
		case TIM14_INDEX:
			RCC_FIELD_WRITE(apb1rstr, tim14rst, true);
			RCC_FIELD_WRITE(apb1rstr, tim14rst, false);
			break;
	}

	/* Set the prescaler */
	TIMER_FIELD_WRITE(timer_index, psc, psc, prescale);
	/* Set the value to count to */
	TIMER_FIELD_WRITE(timer_index, arr, arr, count);
	/* Send an update event to generate an update of its registers and reset it */
	TIMER_FIELD_WRITE(timer_index, egr, ug, 1);
	/* Setup the timer to trigger a hardware interrupt on reaching the count */
	TIMER_FIELD_WRITE(timer_index, dier, uie, true);
	/* Now enable the timer */
	TIMER_FIELD_WRITE(timer_index, cr1, cen, true);
}

void clock_setup(bool external_clk, bool use_pll, PLL_MULT_E pll_mult)
{
        /* Enable the selected clock and wait for it to be ready */
        if (external_clk == true)
        {
                RCC_FIELD_WRITE(cr, hseon, true);
                while(!(RCC_FIELD_READ(cr, hserdy))) {};
        }
        else
        {
                RCC_FIELD_WRITE(cr, hsion, true);
                while(!(RCC_FIELD_READ(cr, hsirdy))) {};
        }

        /* Now enable the PLL if requested */
        if (use_pll == true)
        {
                rcc_cfgr_t cfgr = { .mask= rcc->cfgr };
                if (external_clk == true)
                {
                        cfgr.pllsrc = 1;
                }
                else
                {
                        cfgr.pllsrc = 0;
                }
                cfgr.pllmul = pll_mult;
                rcc->cfgr = cfgr.mask;

                /* Turn the PLL on and wait for the hardware to set the ready flag */
                RCC_FIELD_WRITE(cr, pllon, true);
                while(!(RCC_FIELD_READ(cr, pllrdy))) {};
        }

        /* Now set the clock source according to the function parameters */
        if (use_pll == true)
        {
                RCC_FIELD_WRITE(cfgr, sw, SYSCLK_SW_PLL);
                /* Check it's set by reading SWS (switch status) */
                while(RCC_FIELD_READ(cfgr, sws) != SYSCLK_SW_PLL) {};
        }
        else if (external_clk == true)
        {
                RCC_FIELD_WRITE(cfgr, sw, SYSCLK_SW_HSE);
                /* Check it's set by reading SWS (switch status) */
                while(RCC_FIELD_READ(cfgr, sws) != SYSCLK_SW_HSE) {};
        }
        else if (external_clk == false)
        {
                RCC_FIELD_WRITE(cfgr, sw, SYSCLK_SW_HSI);
                /* Check it's set by reading SWS (switch status) */
                while(RCC_FIELD_READ(cfgr, sws) != SYSCLK_SW_HSI) {};
        }
}

int main(void)
{
	/* Set up the flash wait states */
	flash_acr_t acr = { .mask = flash->acr };
	acr.latency = FLASH_ONE_WAIT;
	acr.prftbe = true;
	flash->acr = acr.mask;

	/* Clock setup, use the HSE, which is an 8MHz crystal */
	/* Also enable the PLL and set to multiply by 6 */
	/* This will result in a clock with a frequency of 48MHz */
	clock_setup(true, true, PLL_MULT_X6);
	#define CLOCK_FREQ (uint16_t)0x48000000

	/* Enable the clock and NVIC for timer 3 */
	RCC_FIELD_WRITE(apb1enr, tim3en, true);
	NVIC_SetPriority(TIM3_IRQ, 0x03);
	NVIC_EnableIRQ(TIM3_IRQ);

	/* Turn on the clock for port A gpio */
	RCC_FIELD_WRITE(ahbenr, iopaen, true);

	/* Set PA4 to output mode, set speed to low  and set low */
	GPIO_FIELD_WRITE(GPIOA, moder, moder4, GPIO_OUTPUT);
	GPIO_FIELD_WRITE(GPIOA, ospeedr, ospeed4, GPIO_LOW_SPEED);
	GPIO_FIELD_WRITE(GPIOA, odr, odr4, false);

	/* Initialise the timer */
	start_timer(TIM3_INDEX, 48000, 1000);

	while(true)
	{
		__asm__("NOP");
	}
}

/* Function the hardware will jump to when timer 6 triggers an interrupt */
void TIM3_IRQHandler(void)
{
	/* Check the cause of the interrupt */
	if (TIMER_FIELD_READ(TIM3_INDEX, sr, uif))
	{
		/* First clear the interrupt flag */
		TIMER_FIELD_WRITE(TIM3_INDEX, sr, uif, false);

		/* Toggle the LED pin */
		bool current_pin_state = GPIO_FIELD_READ(GPIOA, odr, odr4); 
		GPIO_FIELD_WRITE(GPIOA, odr, odr4, !current_pin_state);
	}
}
