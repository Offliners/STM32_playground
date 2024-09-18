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
    [RCC_GPIOA]      = 0x0,
    [RCC_GPIOB]      = 0x1,
    [RCC_GPIOC]      = 0x2,
    [RCC_GPIOD]      = 0x3,
    [RCC_GPIOE]      = 0x4,
    [RCC_GPIOF]      = 0x5,
    [RCC_GPIOG]      = 0x6,
    [RCC_GPIOH]      = 0x7,
    [RCC_CRC]        = 0x12,
    [RCC_BKP_SRAM]   = 0x18,
    [RCC_DMA1]       = 0x21,
    [RCC_DMA2]       = 0x22,
    [RCC_OTGHS]      = 0x29,
    [RCC_OTGHS_ULPI] = 0x30
};

#define RCC_AHB1_ENABLE(clken)     WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) | (CLK_ENABLE << RCC_AHB1_TABLE[clken]))
#define RCC_AHB1_DISABLE(clken)    WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) & (~(CLK_ENABLE << RCC_AHB1_TABLE[clken])))

#endif