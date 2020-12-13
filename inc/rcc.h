#ifndef RCC_H
#define RCC_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define RCC_BASE (AHB1_BASE + 0x00001000)

typedef struct
{
	volatile uint32_t cr;
	volatile uint32_t cfgr;
	volatile uint32_t cir;
	volatile uint32_t apb2rstr;
	volatile uint32_t apb1rstr;
	volatile uint32_t ahbenr;
	volatile uint32_t apb2enr;
	volatile uint32_t apb1enr;
	volatile uint32_t bdcr;
	volatile uint32_t csr;
	volatile uint32_t ahbrstr;
	volatile uint32_t cfgr2;
	volatile uint32_t cfgr3;
	volatile uint32_t cr2;
} rcc_t;

/* Type to describe the options for clock division on the APB clock */
typedef enum
{
	PCLK_DIV_NO = 0,
	PCLK_DIV_2  = 4,
	PCLK_DIV_4  = 5,
	PCLK_DIV_8  = 6,
	PCLK_DIV_16 = 7
} PCLK_PRESCALER_E;

/* Type to describe the options for clock division used on the AHB clock */
typedef enum
{
	HCLK_DIV_NO  = 0,
	HCLK_DIV_2   = 8,
	HCLK_DIV_4   = 9,
	HCLK_DIV_8   = 10,
	HCLK_DIV_16  = 11,
	HCLK_DIV_64  = 12,
	HCLK_DIV_128 = 13,
	HCLK_DIV_256 = 14,
	HCLK_DIV_512 = 15
} HCLK_PRESCALER_E;

/* Type for describing clock source options for the system clock */
typedef enum
{
	SYSCLK_SW_HSI = 0,
	SYSCLK_SW_HSE = 1,
	SYSCLK_SW_PLL = 2,
} SYSCLK_SW_E;

/* Type describing options on the internal PLL */
typedef enum
{
	PLL_MULT_X2  =  0,
	PLL_MULT_X3  =  1,
	PLL_MULT_X4  =  2,
	PLL_MULT_X5  =  3,
	PLL_MULT_X6  =  4,
	PLL_MULT_X7  =  5,
	PLL_MULT_X8  =  6,
	PLL_MULT_X9  =  7,
	PLL_MULT_X10 =  8,
	PLL_MULT_X11 =  9,
	PLL_MULT_X12 = 10,
	PLL_MULT_X13 = 11,
	PLL_MULT_X14 = 12,
	PLL_MULT_X15 = 13,
	PLL_MULT_X16 = 14
} PLL_MULT_E;

/* Type describing options for the microcontroller output clock pin source */
typedef enum
{
	MCO_DISABLE   = 0,
	MCO_HSI_14MHZ = 1,
	MCO_LSI       = 2,
	MCO_LSE       = 3,
	MCO_SYSCLK    = 4,
	MCO_HSI_8MHZ  = 5,
	MCO_HSE       = 6,
	MCO_PLL       = 7
} MCO_E;

/* Type describing options for dividing the microcontroller output clock source */
typedef enum
{
	MCO_DIV_1   = 0,
	MCO_DIV_2   = 1,
	MCO_DIV_4   = 2,
	MCO_DIV_8   = 3,
	MCO_DIV_16  = 4,
	MCO_DIV_32  = 5,
	MCO_DIV_64  = 6,
	MCO_DIV_128 = 7
} MCO_PRESCALER_E;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           hsion     : 1;
		const bool     hsirdy    : 1;
		const unsigned res_2     : 1;
		unsigned       hsitrim   : 5;
		const uint8_t  hsical    : 8;
		bool           hseon     : 1;
		const bool     hserdy    : 1;
		bool           hsebyp    : 1;
		bool           cssson    : 1;
		const unsigned res_23_20 : 4;
		bool           pllon     : 1;
		const bool     pllrdy    : 1;
		const unsigned res_31_26 : 6;
	};
	uint32_t mask;
} rcc_cr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		SYSCLK_SW_E       sw        : 2;
		const SYSCLK_SW_E sws       : 2;
		HCLK_PRESCALER_E  hpre      : 4;
		PCLK_PRESCALER_E  ppre      : 3;
		const unsigned    res_13_11 : 3;
		bool              adcpre    : 1;	// Note that the datasheet mentions this is obsolete
		bool              res_15    : 1;
		unsigned          pllsrc    : 1;
		bool              pllxtpre  : 1;
		PLL_MULT_E        pllmul    : 4;
		const unsigned    res_23_22 : 2;
		MCO_E             mco       : 4;
		MCO_PRESCALER_E   mcopre    : 3;
		bool              pllnodiv  : 1;
	};
	uint32_t mask;
} rcc_cfgr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		/* Ready flags for each clock */
		const bool     lsirdyf    : 1;
		const bool     lserdyf    : 1;
		const bool     hsirdyf    : 1;
		const bool     hserdyf    : 1;
		const bool     pllrdyf    : 1;
		const bool     hsi14rdyf  : 1;
		const unsigned res_6      : 1;
		const bool     cssf       : 1;
		/* Interrupt enables for each clock ready signal */
		bool           lsirdyie   : 1;
		bool           lserdyie   : 1;
		bool           hsirdyie   : 1;
		bool           hserdyie   : 1;
		bool           pllrdyie   : 1;
		bool           hsi14rdyie : 1;
		const unsigned res_15_14  : 2;
		/* Interrupt clear flags */
		unsigned       lsirdyc    : 1;
		unsigned       lserdyc    : 1;
		unsigned       hsirdyc    : 1;
		unsigned       hserdyc    : 1;
		unsigned       pllrdyc    : 1;
		unsigned       hsi14rdyc  : 1;
		const unsigned res_22     : 1;
		unsigned       cssc       : 1;
		const unsigned res_31_24  : 8;
	};
	uint32_t mask;
} rcc_cir_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           syscfgrst : 1;
		const unsigned res_4_1   : 4;
		bool           usart6rst : 1;
		const unsigned res_8_6   : 3;
		bool           adcrst    : 1;
		const unsigned res_10    : 1;
		bool           tim1rst   : 1;
		bool           spi1rst   : 1;
		const unsigned res_13    : 1;
		bool           usart1rst : 1;
		const unsigned res_15    : 1;
		bool           tim15rst  : 1;
		bool           tim16rst  : 1;
		bool           tim17rst  : 1;
		const unsigned res_21_19 : 3;
		bool           dbgmcurst : 1;
		const unsigned res_31_23 : 9;
	};
	uint32_t mask;
} rcc_apb2rstr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const unsigned res_0     : 1;
		bool           tim3rst   : 1;
		const unsigned res_3_2   : 2;
		bool           tim6rst   : 1;
		bool           tim7rst   : 1;
		const unsigned res_7_6   : 2;
		bool           tim14rst  : 1;
		const unsigned res_10_9  : 2;
		bool           wwdgrst   : 1;
		const unsigned res_13_12 : 2;
		bool           spi2rst   : 1;
		const unsigned res_16_15 : 2;
		bool           usart2rst : 1;
		bool           usart3rst : 1;
		bool           usart4rst : 1;
		bool           usart5rst : 1;
		bool           i2c1rst   : 1;
		bool           i2c2rst   : 1;
		bool           usbrst    : 1;
		const unsigned res_27_24 : 4;
		bool           pwrrst    : 1;
		const unsigned res_31_29 : 3;
	};
	uint32_t mask;
} rcc_apb1rstr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           dmaen     :  1;
		const unsigned res_1     :  1;
		bool           sramen    :  1;
		const unsigned res_3     :  1;
		bool           flitfen   :  1;
		const unsigned res_5     :  1;
		bool           crcen     :  1;
		const unsigned res_16_7  : 10;
		bool           iopaen    :  1;
		bool           iopben    :  1;
		bool           iopcen    :  1;
		bool           iopden    :  1;
		const unsigned res_21    :  1;
		bool           iopfen    :  1;
		const unsigned res_31_23 :  9;
	};
	uint32_t mask;
} rcc_ahbenr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           syscfgen  : 1;
		const unsigned res_4_1   : 4;
		bool           usart6en  : 1;
		const unsigned res_8_6   : 3;
		bool           adcen     : 1;
		const unsigned res_10    : 1;
		bool           tim1en    : 1;
		bool           spi1en    : 1;
		const unsigned res_13    : 1;
		bool           usart1en  : 1;
		const unsigned res_15    : 1;
		bool           tim15en   : 1;
		bool           tim16en   : 1;
		bool           tim17en   : 1;
		const unsigned res_21_19 : 3;
		bool           dbgmcuen  : 1;
		const unsigned res_31_23 : 9;
	};
	uint32_t mask;
} rcc_apb2enr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const unsigned res_0     : 1;
		bool           tim3en    : 1;
		const unsigned res_3_2   : 2;
		bool           tim6en    : 1;
		bool           tim7en    : 1;
		const unsigned res_7_6   : 2;
		bool           tim14en   : 1;
		const unsigned res_10_9  : 2;
		bool           wwdgen    : 1;
		const unsigned res_13_12 : 2;
		bool           spi2en    : 1;
		const unsigned res_16_15 : 2;
		bool           usart2en  : 1;
		bool           usart3en  : 1;
		bool           usart4en  : 1;
		bool           usart5en  : 1;
		bool           i2c1en    : 1;
		bool           i2c2en    : 1;
		bool           usben     : 1;
		const unsigned res_27_24 : 4;
		bool           pwren     : 1;
		const unsigned res_31_29 : 3;
	};
	uint32_t mask;
} rcc_apb1enr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           lseon     :  1;
		const bool     lserdy    :  1;
		bool           lsebyp    :  1;
		unsigned       lsedrv    :  2;
		const unsigned res_7_5   :  3;
		unsigned       rtcsel    :  2;
		const unsigned res_14_10 :  5;
		bool           rtcen     :  1;
		bool           bdrst     :  1;
		const unsigned res_31_17 : 15;
	};
	uint32_t mask;
} rcc_bdcr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           lsion       :  1;
		const bool     lsirdy      :  1;
		const unsigned res_22_2    : 21;
		const unsigned v18pwerrstf :  1;
		unsigned       rmvf        :  1;
		const unsigned oblrstf     :  1;
		const unsigned pinrstf     :  1;
		const unsigned porrstf     :  1;
		const unsigned sftrstf     :  1;
		const unsigned iwdgrstf    :  1;
		const unsigned wwdgrstf    :  1;
		const unsigned lpwrrstf    :  1;
	};
	uint32_t mask;
} rcc_csr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const unsigned res_16_0   : 17;
		unsigned       ioparst    :  1;
		unsigned       iopbrst    :  1;
		unsigned       iopcrst    :  1;
		unsigned       iopdrst    :  1;
		const unsigned res_21     :  1;
		unsigned       iopfrst    :  1;
		const unsigned res_31_23  :  9;
	};
	uint32_t mask;
} rcc_ahbrstr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       prediv   :  4;
		const unsigned res_31_4 : 28;
	};
	uint32_t mask;
} rcc_cfgr2_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       usart1sw :  2;
		const unsigned res_3_2  :  2;
		unsigned       i2c1sw   :  1;
		const unsigned res_6_5  :  2;
		unsigned       usbsw    :  1;
		unsigned       adcsw    :  1;	//Marked as obselete in the datasheet
		const unsigned res_31_9 : 23;
	};
	uint32_t mask;
} rcc_cfgr3_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           hsi14on   :  1;
		const bool     hsi14rdy  :  1;
		bool           hsi14dis  :  1;
		unsigned       hsi14trim :  5;
		const unsigned hsi14cal  :  8;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} rcc_cr2_t;

static volatile rcc_t * const rcc = (volatile rcc_t *) RCC_BASE;

#define RCC_FIELD_READ(reg, field) ((rcc_##reg##_t)rcc->reg).field
#define RCC_FIELD_WRITE(reg, field, value) \
	do {	\
		rcc_##reg##_t reg = { .mask = rcc->reg}; \
		reg.field = value;	\
		rcc->reg = reg.mask;	\
	} while (0)	//The do while just allows this macro to used with/without a ;

#endif //RCC_H
