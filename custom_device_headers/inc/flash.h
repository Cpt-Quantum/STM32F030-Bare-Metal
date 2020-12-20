#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define FLASH_BASE (AHB1_BASE + 0x00002000)

typedef struct
{
	volatile uint32_t       acr;
	volatile uint32_t       keyr;
	volatile uint32_t       optkeyr;
	volatile uint32_t       sr;
	volatile uint32_t       cr;
	volatile const uint32_t ar;
	volatile uint32_t       obr;
	volatile uint32_t       wrpr;
} flash_t;

typedef enum
{
	FLASH_ZERO_WAIT = 0,
	FLASH_ONE_WAIT = 1
} FLASH_LATENCY_E;

typedef enum
{
	FLASH_READ_PROT_0 = 0,
	FLASH_READ_PROT_1 = 1,
	FLASH_READ_PROT_2 = 2
} FLASH_READ_PROT_E;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		FLASH_LATENCY_E latency  :  3;
		const unsigned  res_3    :  1;
		bool            prftbe   :  1;
		const bool      prftbs   :  1;
		const unsigned  res_31_6 : 26;
	};
	uint32_t mask;
} flash_acr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const bool     bsy      :  1;
		const unsigned res_1    :  1;
		bool           pgerr    :  1;
		const unsigned res_3    :  1;
		bool           wrprterr :  1;
		bool           eop      :  1;
		const unsigned res_31_6 : 26;
	};
	uint32_t mask;
} flash_sr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           pg         :  1;
		bool           per        :  1;
		bool           mer        :  1;
		const unsigned res_3      :  1;
		bool           optpg      :  1;
		bool           opter      :  1;
		bool           strt       :  1;
		bool           lock       :  1;
		const unsigned res_8      :  1;
		bool           optwre     :  1;
		bool           errie      :  1;
		const unsigned res_11     :  1;
		bool           eopie      :  1;
		bool           obl_launch :  1;
		const unsigned res_31_14  : 18;
	};
	uint32_t mask;
} flash_cr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		const bool              opterr : 1;
		const FLASH_READ_PROT_E rdprt  : 2;
		const unsigned res_7_3 : 5;
		const bool wdg_sw    : 1;
		const bool nrst_Stop : 1;
		const bool nrst_stby : 1;
		const unsigned res_11 : 1;
		const bool nboot1 : 1;
		const bool vdda_monitor : 1;
		const bool ram_parity_check : 1;
		const unsigned res_15 : 1;
		const unsigned data0 : 8;
		const unsigned data1 : 8;
	};
	uint32_t mask;
} flash_obr_t;

static volatile flash_t * const flash = (volatile flash_t *) FLASH_BASE;

/* Define the macros for reading writing each GPIO port */
#define FLASH_FIELD_READ(index, reg, field) \
	((flash_##reg##_t) flash[index]->reg).field
#define FLASH_FIELD_WRITE(index, reg, field, value) \
	do \
	{ \
		flash_##reg##_t reg = { .mask = flash[index]->reg }; \
		reg.field = value; \
		flash[index]->reg = reg.mask; \
	} while(0) //This allows this macro to be used with/without a ;

#endif //FLASH_H
