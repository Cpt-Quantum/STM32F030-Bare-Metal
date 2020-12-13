#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"
#include "irq.h"

#define NVIC_BASE (SCS_BASE + 0x0100)

#define NVIC_PRIO_BITS 2

typedef struct
{
	volatile uint32_t iser;
	volatile uint32_t res_1_31[31];
	volatile uint32_t icer;
	volatile uint32_t res_33_63[31];
	volatile uint32_t ispr;
	volatile uint32_t res_65_95[31];
	volatile uint32_t icpr;
	volatile uint32_t res_97_127[31];
	volatile uint32_t res_128_192[64];
	volatile uint32_t ipr[8];
} nvic_t;

static volatile nvic_t * const nvic = (volatile nvic_t *) NVIC_BASE;

static inline void NVIC_SetPriority(IRQ_E irq, unsigned priority)
{
	/* The priority configuration registers are broken into 8 bit chunks */
	/* 32 bit register: [ (Prio Byte)(Prio Byte)(Prio Byte)(Prio Byte) ] */
	/* Only part of each priority byte is used, the priority bits are placed */
	/* at the end of the byte as [ (Prio bits) (8 - Prio bits) ]. */
	/* The array index needs to be divided by 4 (>> 2) and the offset within */
	/* the each 32 bit register needs to be accounted for. */
	uint32_t arr_index = irq >> 2U;
	uint32_t offset = (irq & 0x03UL) * 8UL;

	/* New priority value needs to be or-ed with the previous value, minus */
	/* the old byte value for the priority to be set. */
	nvic->ipr[arr_index] = (nvic->ipr[arr_index] & ~(0xFFUL << offset)) |
		( ((priority << (8 - NVIC_PRIO_BITS)) & 0xFFUL) << offset );
}

static inline void NVIC_EnableIRQ(IRQ_E irq)
{
	/* NB: The & with 0x1F is to clip the bit shift at 31 */
	nvic->iser = (uint32_t)(1U << (irq & 0x1FUL));
}

#endif //NVIC_H
