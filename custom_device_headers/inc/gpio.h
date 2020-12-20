#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define GPIOA_BASE (AHB2_BASE + 0x0)
#define GPIOB_BASE (AHB2_BASE + 0x0400)
#define GPIOC_BASE (AHB2_BASE + 0x0800)
#define GPIOD_BASE (AHB2_BASE + 0x0C00)
#define GPIOE_BASE (AHB2_BASE + 0x1000)	//NB: This is actually reserved not GPIOE
#define GPIOF_BASE (AHB2_BASE + 0x1400)

typedef enum
{
	GPIOA = 0,
	GPIOB = 1,
	GPIOC = 2,
	GPIOD = 3,
	GPIOF = 5
} GPIO_PORT;

typedef enum
{
	GPIO_INPUT  = 0,
	GPIO_OUTPUT = 1,
	GPIO_ALT    = 2,
	GPIO_ANALOG = 3
} GPIO_MODER_E;

typedef enum
{
	GPIO_LOW_SPEED  = 0,
	GPIO_MED_SPEED  = 1,
	GPIO_HIGH_SPEED = 3
} GPIO_OSPEEDR_E;

typedef enum
{
	GPIO_NO_PUPD   = 0,
	GPIO_PULL_UP   = 1,
	GPIO_PULL_DOWN = 2
} GPIO_PUPDR_E;

typedef enum
{
	GPIO_AF0 = 0,
	GPIO_AF1 = 1,
	GPIO_AF2 = 2,
	GPIO_AF3 = 3,
	GPIO_AF4 = 4,
	GPIO_AF5 = 5,
	GPIO_AF6 = 6,
	GPIO_AF7 = 7
} GPIO_AFR_E;

typedef struct
{
	volatile uint32_t moder;
	volatile uint32_t otyper;
	volatile uint32_t ospeedr;
	volatile uint32_t pupdr;
	volatile uint32_t idr;
	volatile uint32_t odr;
	volatile uint32_t bsrr;
	volatile uint32_t lckr;
	volatile uint32_t afrl;
	volatile uint32_t afrh;
	volatile uint32_t brr;
} gpio_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		GPIO_MODER_E moder0  : 2;
		GPIO_MODER_E moder1  : 2;
		GPIO_MODER_E moder2  : 2;
		GPIO_MODER_E moder3  : 2;
		GPIO_MODER_E moder4  : 2;
		GPIO_MODER_E moder5  : 2;
		GPIO_MODER_E moder6  : 2;
		GPIO_MODER_E moder7  : 2;
		GPIO_MODER_E moder8  : 2;
		GPIO_MODER_E moder9  : 2;
		GPIO_MODER_E moder10 : 2;
		GPIO_MODER_E moder11 : 2;
		GPIO_MODER_E moder12 : 2;
		GPIO_MODER_E moder13 : 2;
		GPIO_MODER_E moder14 : 2;
		GPIO_MODER_E moder15 : 2;
	};
	uint32_t mask;
} gpio_moder_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       ot0       :  1;
		unsigned       ot1       :  1;
		unsigned       ot2       :  1;
		unsigned       ot3       :  1;
		unsigned       ot4       :  1;
		unsigned       ot5       :  1;
		unsigned       ot6       :  1;
		unsigned       ot7       :  1;
		unsigned       ot8       :  1;
		unsigned       ot9       :  1;
		unsigned       ot10      :  1;
		unsigned       ot11      :  1;
		unsigned       ot12      :  1;
		unsigned       ot13      :  1;
		unsigned       ot14      :  1;
		unsigned       ot15      :  1;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} gpio_otyper_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		GPIO_OSPEEDR_E ospeed0  : 2;
		GPIO_OSPEEDR_E ospeed1  : 2;
		GPIO_OSPEEDR_E ospeed2  : 2;
		GPIO_OSPEEDR_E ospeed3  : 2;
		GPIO_OSPEEDR_E ospeed4  : 2;
		GPIO_OSPEEDR_E ospeed5  : 2;
		GPIO_OSPEEDR_E ospeed6  : 2;
		GPIO_OSPEEDR_E ospeed7  : 2;
		GPIO_OSPEEDR_E ospeed8  : 2;
		GPIO_OSPEEDR_E ospeed9  : 2;
		GPIO_OSPEEDR_E ospeed10 : 2;
		GPIO_OSPEEDR_E ospeed11 : 2;
		GPIO_OSPEEDR_E ospeed12 : 2;
		GPIO_OSPEEDR_E ospeed13 : 2;
		GPIO_OSPEEDR_E ospeed14 : 2;
		GPIO_OSPEEDR_E ospeed15 : 2;
	};
	uint32_t mask;
} gpio_ospeedr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		GPIO_PUPDR_E pupdr0  : 2;
		GPIO_PUPDR_E pupdr1  : 2;
		GPIO_PUPDR_E pupdr2  : 2;
		GPIO_PUPDR_E pupdr3  : 2;
		GPIO_PUPDR_E pupdr4  : 2;
		GPIO_PUPDR_E pupdr5  : 2;
		GPIO_PUPDR_E pupdr6  : 2;
		GPIO_PUPDR_E pupdr7  : 2;
		GPIO_PUPDR_E pupdr8  : 2;
		GPIO_PUPDR_E pupdr9  : 2;
		GPIO_PUPDR_E pupdr10 : 2;
		GPIO_PUPDR_E pupdr11 : 2;
		GPIO_PUPDR_E pupdr12 : 2;
		GPIO_PUPDR_E pupdr13 : 2;
		GPIO_PUPDR_E pupdr14 : 2;
		GPIO_PUPDR_E pupdr15 : 2;
	};
	uint32_t mask;
} gpio_pupdr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const bool     idr0      :  1;
		const bool     idr1      :  1;
		const bool     idr2      :  1;
		const bool     idr3      :  1;
		const bool     idr4      :  1;
		const bool     idr5      :  1;
		const bool     idr6      :  1;
		const bool     idr7      :  1;
		const bool     idr8      :  1;
		const bool     idr9      :  1;
		const bool     idr10     :  1;
		const bool     idr11     :  1;
		const bool     idr12     :  1;
		const bool     idr13     :  1;
		const bool     idr14     :  1;
		const bool     idr15     :  1;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} gpio_idr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           odr0      :  1;
		bool           odr1      :  1;
		bool           odr2      :  1;
		bool           odr3      :  1;
		bool           odr4      :  1;
		bool           odr5      :  1;
		bool           odr6      :  1;
		bool           odr7      :  1;
		bool           odr8      :  1;
		bool           odr9      :  1;
		bool           odr10     :  1;
		bool           odr11     :  1;
		bool           odr12     :  1;
		bool           odr13     :  1;
		bool           odr14     :  1;
		bool           odr15     :  1;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} gpio_odr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned bs0  : 1;
		unsigned bs1  : 1;
		unsigned bs2  : 1;
		unsigned bs3  : 1;
		unsigned bs4  : 1;
		unsigned bs5  : 1;
		unsigned bs6  : 1;
		unsigned bs7  : 1;
		unsigned bs8  : 1;
		unsigned bs9  : 1;
		unsigned bs10 : 1;
		unsigned bs11 : 1;
		unsigned bs12 : 1;
		unsigned bs13 : 1;
		unsigned bs14 : 1;
		unsigned bs15 : 1;
		unsigned br0  : 1;
		unsigned br1  : 1;
		unsigned br2  : 1;
		unsigned br3  : 1;
		unsigned br4  : 1;
		unsigned br5  : 1;
		unsigned br6  : 1;
		unsigned br7  : 1;
		unsigned br8  : 1;
		unsigned br9  : 1;
		unsigned br10 : 1;
		unsigned br11 : 1;
		unsigned br12 : 1;
		unsigned br13 : 1;
		unsigned br14 : 1;
		unsigned br15 : 1;
	};
	uint32_t mask;
} gpio_bsrr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           lck0      :  1;
		bool           lck1      :  1;
		bool           lck2      :  1;
		bool           lck3      :  1;
		bool           lck4      :  1;
		bool           lck5      :  1;
		bool           lck6      :  1;
		bool           lck7      :  1;
		bool           lck8      :  1;
		bool           lck9      :  1;
		bool           lck10     :  1;
		bool           lck11     :  1;
		bool           lck12     :  1;
		bool           lck13     :  1;
		bool           lck14     :  1;
		bool           lck15     :  1;
		bool           lckk      :  1;
		const unsigned res_31_17 : 15;
	};
	uint32_t mask;
} gpio_lckr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		GPIO_AFR_E afsel0 : 4;
		GPIO_AFR_E afsel1 : 4;
		GPIO_AFR_E afsel2 : 4;
		GPIO_AFR_E afsel3 : 4;
		GPIO_AFR_E afsel4 : 4;
		GPIO_AFR_E afsel5 : 4;
		GPIO_AFR_E afsel6 : 4;
		GPIO_AFR_E afsel7 : 4;
	};
	uint32_t mask;
} gpio_afrl_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		GPIO_AFR_E afsel8  : 4;
		GPIO_AFR_E afsel9  : 4;
		GPIO_AFR_E afsel10 : 4;
		GPIO_AFR_E afsel11 : 4;
		GPIO_AFR_E afsel12 : 4;
		GPIO_AFR_E afsel13 : 4;
		GPIO_AFR_E afsel14 : 4;
		GPIO_AFR_E afsel15 : 4;
	};
	uint32_t mask;
} gpio_afrh_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           br0       :  1;
		bool           br1       :  1;
		bool           br2       :  1;
		bool           br3       :  1;
		bool           br4       :  1;
		bool           br5       :  1;
		bool           br6       :  1;
		bool           br7       :  1;
		bool           br8       :  1;
		bool           br9       :  1;
		bool           br10      :  1;
		bool           br11      :  1;
		bool           br12      :  1;
		bool           br13      :  1;
		bool           br14      :  1;
		bool           br15      :  1;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} gpio_brr_t;

static volatile gpio_t * const gpio[] = {
	(volatile gpio_t *) GPIOA_BASE,
	(volatile gpio_t *) GPIOB_BASE,
	(volatile gpio_t *) GPIOC_BASE,
	(volatile gpio_t *) GPIOD_BASE,
	(volatile gpio_t *) GPIOE_BASE,	//This should not be written/read
	(volatile gpio_t *) GPIOF_BASE
};

/* Define the macros for reading writing each GPIO port */
#define GPIO_FIELD_READ(index, reg, field) \
	((gpio_##reg##_t) gpio[index]->reg).field
#define GPIO_FIELD_WRITE(index, reg, field, value) \
	do \
	{ \
		gpio_##reg##_t reg = { .mask = gpio[index]->reg }; \
		reg.field = value; \
		gpio[index]->reg = reg.mask; \
	} while(0) //This allows this macro to be used with/without a ;

#endif //GPIO_H
