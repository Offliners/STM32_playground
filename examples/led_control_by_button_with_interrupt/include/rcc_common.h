#ifndef _RCC_COMMON_H_
#define _RCC_COMMON_H_

#include "typedef.h"
#include "memorymap.h"

#define CLK_DISABLE               0x0
#define CLK_ENABLE                0x1

// AHB1 peripheral
#define RCC_OFFSET      (0x00003800)
#define RCC             GET_ADDR(PERIPHERAL_AHB1_BASE + RCC_OFFSET)

#define RESET_RCC_AHB1ENR_PATTERN   0x00000000
#define RCC_AHB1ENR_OFFSET          0x30

typedef enum {
    RCC_GPIOA,
    RCC_GPIOB,
    RCC_GPIOC,
    RCC_GPIOD,
    RCC_GPIOE,
    RCC_GPIOF,
    RCC_GPIOG,
    RCC_GPIOH,
    RCC_CRC,
    RCC_BKP_SRAM,
    RCC_DMA1,
    RCC_DMA2,
    RCC_OTGHS,
    RCC_OTGHS_ULPI,
    RCC_AHB1_END
} RCC_AHB1;

static const BYTE RCC_AHB1_TABLE[RCC_AHB1_END] = {
    [RCC_GPIOA]      = 0,
    [RCC_GPIOB]      = 1,
    [RCC_GPIOC]      = 2,
    [RCC_GPIOD]      = 3,
    [RCC_GPIOE]      = 4,
    [RCC_GPIOF]      = 5,
    [RCC_GPIOG]      = 6,
    [RCC_GPIOH]      = 7,
    [RCC_CRC]        = 12,
    [RCC_BKP_SRAM]   = 18,
    [RCC_DMA1]       = 21,
    [RCC_DMA2]       = 22,
    [RCC_OTGHS]      = 29,
    [RCC_OTGHS_ULPI] = 30
};

#define RCC_AHB1_ENABLE(clken)     WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) | (CLK_ENABLE << RCC_AHB1_TABLE[clken]))
#define RCC_AHB1_DISABLE(clken)    WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) & (~(CLK_ENABLE << RCC_AHB1_TABLE[clken])))

// APB2 peripheral
#define RESET_RCC_APB2ENR_PATTERN   0x00000000
#define RCC_APB2ENR_OFFSET          0x44

typedef enum {
    RCC_TIM1,
    RCC_TIM8,
    RCC_USART1,
    RCC_USART6,
    RCC_ADC1,
    RCC_ADC2,
    RCC_ADC3,
    RCC_SDIO,
    RCC_SPI1,
    RCC_SPI4,
    RCC_SYSCFG,
    RCC_TIM9,
    RCC_TIM10,
    RCC_TIM11,
    RCC_SAI1,
    RCC_SAI2,
    RCC_APB2_END
} RCC_APB2;

static const BYTE RCC_APB2_TABLE[RCC_APB2_END] = {
    [RCC_TIM1]   = 0,
    [RCC_TIM8]   = 1,
    [RCC_USART1] = 4,
    [RCC_USART6] = 5,
    [RCC_ADC1]   = 8,
    [RCC_ADC2]   = 9,
    [RCC_ADC3]   = 10,
    [RCC_SDIO]   = 11,
    [RCC_SPI1]   = 12,
    [RCC_SPI4]   = 13,
    [RCC_SYSCFG] = 14,
    [RCC_TIM9]   = 16,
    [RCC_TIM10]  = 17,
    [RCC_TIM11]  = 18,
    [RCC_SAI1]   = 22,
    [RCC_SAI2]   = 23
};

#define RCC_APB2_ENABLE(clken)     WRITE_REG_LWORD(RCC, RCC_APB2ENR_OFFSET, READ_REG_LWORD(RCC, RCC_APB2ENR_OFFSET) | (CLK_ENABLE << RCC_APB2_TABLE[clken]))
#define RCC_APB2_DISABLE(clken)    WRITE_REG_LWORD(RCC, RCC_APB2ENR_OFFSET, READ_REG_LWORD(RCC, RCC_APB2ENR_OFFSET) & (~(CLK_ENABLE << RCC_APB2_TABLE[clken])))        

#endif