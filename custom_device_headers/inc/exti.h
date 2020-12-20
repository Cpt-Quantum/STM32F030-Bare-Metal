#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define EXTI_BASE (APB_BASE + 0x10400)

typedef struct
{
	volatile uint32_t imr;
	volatile uint32_t emr;
	volatile uint32_t rtsr;
	volatile uint32_t ftsr;
	volatile uint32_t swier;
	volatile uint32_t pr;
} exti_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned im0  : 1;
		unsigned im1  : 1;
		unsigned im2  : 1;
		unsigned im3  : 1;
		unsigned im4  : 1;
		unsigned im5  : 1;
		unsigned im6  : 1;
		unsigned im7  : 1;
		unsigned im8  : 1;
		unsigned im9  : 1;
		unsigned im10 : 1;
		unsigned im11 : 1;
		unsigned im12 : 1;
		unsigned im13 : 1;
		unsigned im14 : 1;
		unsigned im15 : 1;
		unsigned im16 : 1;
		unsigned im17 : 1;
		unsigned im18 : 1;
		unsigned im19 : 1;
		unsigned im20 : 1;
		unsigned im21 : 1;
		unsigned im22 : 1;
		unsigned im23 : 1;
		unsigned im24 : 1;
		unsigned im25 : 1;
		unsigned im26 : 1;
		unsigned im27 : 1;
		unsigned im28 : 1;
		unsigned im29 : 1;
		unsigned im30 : 1;
		unsigned im31 : 1;
	};
	uint32_t mask;
} exti_imr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned emr0  : 1;
		unsigned emr1  : 1;
		unsigned emr2  : 1;
		unsigned emr3  : 1;
		unsigned emr4  : 1;
		unsigned emr5  : 1;
		unsigned emr6  : 1;
		unsigned emr7  : 1;
		unsigned emr8  : 1;
		unsigned emr9  : 1;
		unsigned emr10 : 1;
		unsigned emr11 : 1;
		unsigned emr12 : 1;
		unsigned emr13 : 1;
		unsigned emr14 : 1;
		unsigned emr15 : 1;
		unsigned emr16 : 1;
		unsigned emr17 : 1;
		unsigned emr18 : 1;
		unsigned emr19 : 1;
		unsigned emr20 : 1;
		unsigned emr21 : 1;
		unsigned emr22 : 1;
		unsigned emr23 : 1;
		unsigned emr24 : 1;
		unsigned emr25 : 1;
		unsigned emr26 : 1;
		unsigned emr27 : 1;
		unsigned emr28 : 1;
		unsigned emr29 : 1;
		unsigned emr30 : 1;
		unsigned emr31 : 1;
	};
	uint32_t mask;
} exti_emr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           rt0       : 1;
		bool           rt1       : 1;
		bool           rt2       : 1;
		bool           rt3       : 1;
		bool           rt4       : 1;
		bool           rt5       : 1;
		bool           rt6       : 1;
		bool           rt7       : 1;
		bool           rt8       : 1;
		bool           rt9       : 1;
		bool           rt10      : 1;
		bool           rt11      : 1;
		bool           rt12      : 1;
		bool           rt13      : 1;
		bool           rt14      : 1;
		bool           rt15      : 1;
		bool           rt16      : 1;
		bool           rt17      : 1;
		const unsigned res_18    : 1;
		bool           rt19      : 1;
		bool           rt20      : 1;
		bool           rt21      : 1;
		bool           rt22      : 1;
		const unsigned res_30_23 : 8;
		bool           rt31      : 1;
	};
	uint32_t mask;
} exti_rtsr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           ft0       : 1;
		bool           ft1       : 1;
		bool           ft2       : 1;
		bool           ft3       : 1;
		bool           ft4       : 1;
		bool           ft5       : 1;
		bool           ft6       : 1;
		bool           ft7       : 1;
		bool           ft8       : 1;
		bool           ft9       : 1;
		bool           ft10      : 1;
		bool           ft11      : 1;
		bool           ft12      : 1;
		bool           ft13      : 1;
		bool           ft14      : 1;
		bool           ft15      : 1;
		bool           ft16      : 1;
		bool           ft17      : 1;
		const unsigned res_18    : 1;
		bool           ft19      : 1;
		bool           ft20      : 1;
		bool           ft21      : 1;
		bool           ft22      : 1;
		const unsigned res_30_23 : 8;
		bool           ft31      : 1;
	};
	uint32_t mask;
} exti_ftsr_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           swier0    : 1;
		bool           swier1    : 1;
		bool           swier2    : 1;
		bool           swier3    : 1;
		bool           swier4    : 1;
		bool           swier5    : 1;
		bool           swier6    : 1;
		bool           swier7    : 1;
		bool           swier8    : 1;
		bool           swier9    : 1;
		bool           swier10   : 1;
		bool           swier11   : 1;
		bool           swier12   : 1;
		bool           swier13   : 1;
		bool           swier14   : 1;
		bool           swier15   : 1;
		bool           swier16   : 1;
		bool           swier17   : 1;
		const unsigned res_18    : 1;
		bool           swier19   : 1;
		bool           swier20   : 1;
		bool           swier21   : 1;
		bool           swier22   : 1;
		const unsigned res_30_23 : 8;
		bool           swier31   : 1;
	};
	uint32_t mask;
} exti_swier_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           pif0      : 1;
		bool           pif1      : 1;
		bool           pif2      : 1;
		bool           pif3      : 1;
		bool           pif4      : 1;
		bool           pif5      : 1;
		bool           pif6      : 1;
		bool           pif7      : 1;
		bool           pif8      : 1;
		bool           pif9      : 1;
		bool           pif10     : 1;
		bool           pif11     : 1;
		bool           pif12     : 1;
		bool           pif13     : 1;
		bool           pif14     : 1;
		bool           pif15     : 1;
		bool           pif16     : 1;
		bool           pif17     : 1;
		const unsigned res_18    : 1;
		bool           pif19     : 1;
		bool           pif20     : 1;
		bool           pif21     : 1;
		bool           pif22     : 1;
		const unsigned res_30_23 : 8;
		bool           pif31     : 1;
	};
	uint32_t mask;
} exti_pr_t;

static volatile exti_t * const exti = (volatile exti_t *) EXTI_BASE;

#define EXTI_FIELD_READ(reg, field) ((exti_##reg##_t)exti->reg).field
#define EXTI_FIELD_WRITE(reg, field, value) \
	do {	\
		exti_##reg##_t reg = { .mask = exti->reg}; \
		reg.field = value;	\
		exti->reg = reg.mask;	\
	} while (0)	//The do while just allows this macro to used with/without a ;

#endif //EXTI_H
