#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define USART1_BASE (APB_BASE + 0x00013800UL)
#define USART2_BASE (APB_BASE + 0x00004400UL)
#define USART3_BASE (APB_BASE + 0x00004800UL)
#define USART4_BASE (APB_BASE + 0x00004C00UL)
#define USART5_BASE (APB_BASE + 0x00005000UL)
#define USART6_BASE (APB_BASE + 0x00011400UL)

typedef struct
{
	volatile uint32_t cr1;
	volatile uint32_t cr2;
	volatile uint32_t cr3;
	volatile uint32_t brr;
	volatile const uint32_t res_4;
	volatile uint32_t rtor;
	volatile uint32_t ror;
	volatile uint32_t isr;
	volatile uint32_t icr;
	volatile uint32_t rdr;
	volatile uint32_t tdr;
} usart_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           ue        : 1;
		const unsigned res_1     : 1;
		bool           re        : 1;
		bool           te        : 1;
		bool           idleie    : 1;
		bool           rxneie    : 1;
		bool           tcie      : 1;
		bool           txeie     : 1;
		bool           peie      : 1;
		unsigned       ps        : 1;
		bool           pce       : 1;
		unsigned       wake      : 1;
		unsigned       m0        : 1;
		bool           mme       : 1;
		bool           cmie      : 1;
		unsigned       over8     : 1;
		unsigned       dedt      : 5;
		unsigned       deat      : 5;
		bool           rtoie     : 1;
		const unsigned res_27    : 1;
		unsigned       m1        : 1;
		const unsigned res_31_29 : 3;
	};
	uint32_t mask;
} usart_cr1_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const unsigned res_3_0  : 4;
		unsigned       addm7 i  : 1;
		const unsigned res_7_5  : 3;
		unsigned       lbcl     : 1;
		unsigned       cpha     : 1;
		unsigned       cpol     : 1;
		bool           clken    : 1;
		unsigned       stop     : 2;
		const unsigned res_14   : 1;
		bool           swap     : 1;
		bool           rxinv    : 1;
		bool           txinv    : 1;
		bool           datainv  : 1;
		bool           msbfirst : 1;
		bool           abren    : 1;
		unsigned       abrmod   : 2;
		bool           rtoen    : 1;
		uint8_t        add      : 8;
	};
	uint32_t mask;
} usart_cr2_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           eie       : 1;
		const unsigned res_2_1   : 2;
		bool           hdsel     : 1;
		const unsigned res_5_4   : 2;
		bool           dmar      : 1;
		bool           dmat      : 1;
		bool           rtse      : 1;
		bool           ctse      : 1;
		bool           ctsie     : 1;
		bool           onebit    : 1;
		bool           ovrdis    : 1;
		bool           ddre      : 1;
		bool           dem       : 1;
		unsigned       dep       : 1;
		const unsigned res_16    : 1;
		const unsigned res_19_17 : 3;
		const unsigned res_23    : 1;
		const unsigned res_24    : 1;
		const unsigned res_31_25 : 7;
	};
	uint32_t mask;
} usart_cr3_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint16_t       brr       : 16;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} usart_brr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       rto       : 24;
		const unsigned res_31_24 :  8;
	};
	uint32_t mask;
} usart_rtor_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       abrrq    :  1;
		unsigned       sbkrq    :  1;
		unsigned       mmrq     :  1;
		unsigned       rxfrq    :  1;
		const unsigned res_31_4 : 28;
	};
	uint32_t mask;
} usart_rqr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const bool pe            : 1;
		const bool fe            : 1;
		const bool nf            : 1;
		const bool ore           : 1;
		const bool idle          : 1;
		const bool rxne          : 1;
		const bool tc            : 1;
		const bool txe           : 1;
		const unsigned res_8     : 1;
		const bool ctsif         : 1;
		const bool cts           : 1;
		const bool rtof          : 1;
		const unsigned rtof      : 2;
		const bool abre          : 1;
		const bool abrf          : 1;
		const bool busy          : 1;
		const bool cmf           : 1;
		const bool sbkf          : 1;
		const bool rwu           : 1;
		const unsigned res_20    : 1;
		const unsigned res_21    : 1;
		const unsigned res_24_22 : 3;
		const unsigned res_31_25 : 7;
	};
	uint32_t mask;
} usart_isr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool pecf                :  1;
		bool fecf                :  1;
		bool ncf                 :  1;
		bool orecf               :  1;
		bool idlecf              :  1;
		const unsigned res_5     :  1;
		bool tccf                :  1;
		const unsigned res_7     :  1;
		const unsigned res_8     :  1;
		bool ctscf               :  1;
		const unsigned res_10    :  1;
		bool rtocf               :  1;
		const unsigned res_16_12 :  5;
		bool cmcf                :  1;
		const unsigned res_19_18 :  2;
		const unsigned res_31_20 : 12;
	};
	uint32_t mask;
} usart_icr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint8_t        rdr      : 8;
		const unsigned res_31_9 : 24;
	};
	uint32_t mask;
} usart_rdr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		uint8_t        tdr      :  8;
		const unsigned res_31_9 : 24;
	};
	uint32_t mask;
} usart_tdr_t;

static volatile usart_t * const usart[] = {
	volatile (usart_t *) USART1_BASE,
	volatile (usart_t *) USART2_BASE,
	volatile (usart_t *) USART3_BASE,
	volatile (usart_t *) USART4_BASE,
	volatile (usart_t *) USART5_BASE,
	volatile (usart_t *) USART6_BASE
};

/* Define the macros for reading/writing to each set of USART registers */
#define USART_FIELD_READ(index, reg, field) \
	((usart_##reg##_t) usart[index]->reg).field
#define USART_FIELD_WRITE(index, reg, field, value) \
	do \
	{ \
		usart_##reg##_t reg = { .mask = usart[index]->reg }; \
		reg.field = value; \
		usart[index]->reg = reg.mask; \
	} while(0) //This allows this macro to be used with/without a ;

#endif //UART_H
