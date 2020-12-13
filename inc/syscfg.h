#ifndef SYSCFG_H
#define SYSCFG_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define SYSCFG_BASE (APB_BASE + 0x10000)

/* TODO: Check the datasheet against this enum */
typedef enum
{
	EXTI_CFG_PA = 0;
	EXTI_CFG_PB = 1;
	EXTI_CFG_PC = 2;
	EXTI_CFG_PD = 3;
	/* Reserved value of 4 */
	EXTI_CFG_PF = 5;
} EXTI_CFG_E;

typedef struct
{
	volatile uint32_t cfgr1;
	volatile uint32_t res_1;
	volatile uint32_t exticr1;
	volatile uint32_t exticr2;
	volatile uint32_t exticr3;
	volatile uint32_t exticr5;
	volatile uint32_t cfgr2;
} syscfg_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned       mem_mode          : 2;
		const unsigned res_3_2           : 2;
		bool           pa11_pa12_rmp     : 1;
		const unsigned res_7_5           : 3;
		bool           adc_dma_rmp       : 1;
		bool           usart1_tx_dma_rmp : 1;
		bool           usart1_rx_dma_rmp : 1;
		bool           tim16_dma_rmp     : 1;
		bool           tim17_dma_rmp     : 1;
		const unsigned res_15_13         : 3;
		bool           i2c_pb6_fmp       : 1;
		bool           i2c_pb7_fmp       : 1;
		bool           i2c_pb8_fmp       : 1;
		bool           i2c_pb9_fmp       : 1;
		bool           i2c1_fmp          : 1;
		const unsigned res_21            : 1;
		bool           i2c_pa9_fmp       : 1;
		bool           i2c_pa10_fmp      : 1;
		const unsigned res_25_24         : 2;
		bool           usart3_dma_rmp    : 1;
		const unsigned res_31_27         : 5;
	};
	uint32_t mask;
} cfgr1_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		EXTI_CFG_E     exti0     :  4;
		EXTI_CFG_E     exti1     :  4;
		EXTI_CFG_E     exti2     :  4;
		EXTI_CFG_E     exti3     :  4;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} exticr1_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		EXTI_CFG_E     exti4     :  4;
		EXTI_CFG_E     exti5     :  4;
		EXTI_CFG_E     exti6     :  4;
		EXTI_CFG_E     exti7     :  4;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} exticr2_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		EXTI_CFG_E     exti8     :  4;
		EXTI_CFG_E     exti9     :  4;
		EXTI_CFG_E     exti10    :  4;
		EXTI_CFG_E     exti11    :  4;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} exticr3_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		EXTI_CFG_E     exti12    :  4;
		EXTI_CFG_E     exti13    :  4;
		EXTI_CFG_E     exti14    :  4;
		EXTI_CFG_E     exti15    :  4;
		const unsigned res_31_16 : 16;
	};
	uint32_t mask;
} exticr4_t;

typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		bool           lockup_lock      :  1;
		bool           sram_parity_lock :  1;
		const unsigned res_7_2          :  6;
		bool           sram_pef         :  1;
		const unsigned res_31_9         : 23;
	};
	uint32_t mask;
} cfgr2_t;

static volatile syscfg_t * const syscfg = (volatile syscfg_t *) SYSCFG_BASE;

#define SYSCFG_FIELD_READ(reg, field) ((syscfg_##reg##_t)syscfg->reg).field
#define SYSCFG_FIELD_WRITE(reg, field, value) \
	do {	\
		syscfg_##reg##_t reg = { .mask = syscfg->reg}; \
		reg.field = value;	\
		syscfg->reg = reg.mask;	\
	} while (0)	//The do while just allows this macro to used with/without a ;

#endif //SYSCFG_H
