#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define TIM1_BASE  (APB_BASE + 0x12C00)
#define TIM3_BASE  (APB_BASE + 0x0400)
#define TIM6_BASE  (APB_BASE + 0x1000)
#define TIM7_BASE  (APB_BASE + 0x1400)
#define TIM14_BASE (APB_BASE + 0x2000)
#define TIM15_BASE (APB_BASE + 0x14000)
#define TIM16_BASE (APB_BASE + 0x14400)
#define TIM17_BASE (APB_BASE + 0x14800)

typedef enum {
	TIM1_INDEX  = 0,
	TIM3_INDEX  = 1,
	TIM6_INDEX  = 2,
	TIM7_INDEX  = 3,
	TIM14_INDEX = 4,
	TIM15_INDEX = 5,
	TIM16_INDEX = 6,
	TIM17_INDEX = 7
} timer_index_t;

/* NB: Not all of the registers will be present for a specific timer */
typedef struct
{
	volatile uint32_t cr1;
	volatile uint32_t cr2;
	volatile uint32_t smcr;
	volatile uint32_t dier;
	volatile uint32_t sr;
	volatile uint32_t egr;
	volatile uint32_t ccmr1;
	volatile uint32_t ccmr2;
	volatile uint32_t ccer;
	volatile uint32_t cnt;
	volatile uint32_t psc;
	volatile uint32_t arr;
	volatile uint32_t rcr;
	volatile uint32_t ccr1;
	volatile uint32_t ccr2;
	volatile uint32_t ccr3;
	volatile uint32_t ccr4;
	volatile uint32_t bdtr;
	volatile uint32_t dcr;
	volatile uint32_t dmar;
	volatile uint32_t _or;
} timer_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           cen       :  1;
		bool           udis      :  1;
		unsigned       urs       :  1;
		bool           opm       :  1;
		const unsigned res_6_4   :  3;
		bool           arpe      :  1;
		unsigned       ckd       :  2;
		const unsigned res_15_10 :  6;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_cr1_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           ccpc      :  1;
		const unsigned res_1     :  1;
		unsigned       ccus      :  1;
		unsigned       ccds      :  1;
		const unsigned res_7_4   :  4;
		unsigned       ois1      :  1;
		unsigned       ois1n     :  1;
		const unsigned res_15_10 :  6;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_cr2_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       sms       :  3;
		const unsigned res_3     :  1;
		unsigned       ts        :  3;
		unsigned       msm       :  1;
		const unsigned res_15_8  :  8;
		const unsigned res_31_16 : 16;
	};
} timer_smcr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           uie       :  1;
		bool           cc1ie     :  1;
		const unsigned res_4_2   :  3;
		bool           comie     :  1;
		const unsigned res_6     :  1;
		bool           bie       :  1;
		bool           ude       :  1;
		bool           cc1de     :  1;
		const unsigned res_13_10 :  4;
		const unsigned res_14    :  1;
		const unsigned res_15    :  1;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_dier_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           uif       :  1;
		bool           cc1if     :  1;
		const unsigned res_4_2   :  3;
		bool           comif     :  1;
		const unsigned res_6     :  1;
		bool           bif       :  1;
		const unsigned res_8     :  1;
		bool           cc1of     :  1;
		const unsigned res_15_10 :  6;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_sr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       ug        :  1;
		unsigned       cc1g      :  1;
		const unsigned res_4_2   :  3;
		unsigned       comg      :  1;
		const unsigned res_6     :  1;
		unsigned       bg        :  1;
		const unsigned res_15_8  :  8;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_egr_t;

/* There are two potential register layouts for ccmr1 depending on whether */
/* it is configured for input capture or output compare mode. There are    */
/* therefore two different types declared here to cover both layouts.      */
typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       cc1s      :  2;
		unsigned       ic1psc    :  2;
		unsigned       ic1f      :  4;
		const unsigned res_15_8  :  8;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_ccmr1_capture_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       cc1s      :  2;
		bool           oc1fe     :  1;
		bool           oc1pe     :  1;
		unsigned       oc1m      :  3;
		const unsigned res_15_7  :  9;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_ccmr1_compare_t;


typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           cc1e      :  1;
		unsigned       cc1p      :  1;
		bool           cc1ne     :  1;
		unsigned       cc1np     :  1;
		const unsigned res_15_4  : 12;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_ccer_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint16_t       cnt       : 16;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_cnt_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint16_t       psc       : 16;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_psc_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint16_t       arr       : 16;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_arr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint8_t        rep       :  8;
		const unsigned res_15_8  :  8;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_rcr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint16_t       ccr1      : 16;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_ccr1_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint16_t       ccr2      : 16;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_ccr2_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint8_t        dtg       :  8;
		unsigned       lock      :  2;
		unsigned       ossi      :  1;
		unsigned       ossr      :  1;
		bool           bke       :  1;
		unsigned       bkp       :  1;
		bool           aoe       :  1;
		bool           moe       :  1;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_bdtr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       dba       :  4;
		const unsigned res_7_5   :  3;
		unsigned       dbl       :  4;
		const unsigned res_15_13 :  3;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_dcr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint16_t       dmab      : 16;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_dmar_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       ti1_rmp   :  2;
		const unsigned res_15_2  : 14;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} timer_or_t;

static volatile timer_t * const timer[] = {
	(volatile timer_t *) TIM1_BASE,
	(volatile timer_t *) TIM3_BASE,
	(volatile timer_t *) TIM6_BASE,
	(volatile timer_t *) TIM7_BASE,
	(volatile timer_t *) TIM14_BASE,
	(volatile timer_t *) TIM15_BASE,
	(volatile timer_t *) TIM16_BASE,
	(volatile timer_t *) TIM17_BASE
};

/* Define the macros for reading writing each GPIO port */
#define TIMER_FIELD_READ(index, reg, field) \
	((timer_##reg##_t) timer[index]->reg).field
#define TIMER_FIELD_WRITE(index, reg, field, value) \
	do \
	{ \
		timer_##reg##_t reg = { .mask = timer[index]->reg }; \
		reg.field = value; \
		timer[index]->reg = reg.mask; \
	} while(0) //This allows this macro to be used with/without a ;

#endif //TIMERS_H
