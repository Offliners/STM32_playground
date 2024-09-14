#ifndef _RCC_COMMON_H_
#define _RCC_COMMON_H_

#include "typedef.h"
#include "memorymap.h"

#define RCC_OFFSET      (0x00003800)
#define RCC             GET_ADDR(PERIPHERAL_AHB1_BASE + RCC_OFFSET)

#define RESET_RCC_AHB1ENR_PATTERN   0x00000000
#define RCC_AHB1ENR_OFFSET          0x30
#define GPIOX_DISABLE               0x0
#define GPIOX_ENABLE                0x1

typedef enum {
    RCC_GPIOA,
    RCC_GPIOB,
    RCC_GPIOC,
    RCC_GPIOD,
    RCC_GPIOE,
    RCC_GPIOF,
    RCC_GPIOG,
    RCC_GPIOH,
    RCC_GPIO_END
} RCC_GPIOX;

static const BYTE RCC_GPIOX_TABLE[RCC_GPIO_END] = {
    [RCC_GPIOA] = 0x0,
    [RCC_GPIOB] = 0x1,
    [RCC_GPIOC] = 0x2,
    [RCC_GPIOD] = 0x3,
    [RCC_GPIOE] = 0x4,
    [RCC_GPIOF] = 0x5,
    [RCC_GPIOG] = 0x6,
    [RCC_GPIOH] = 0x7
};

#define RCC_GPIOX_ENABLE(gpiox)     WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) | (GPIOX_ENABLE << RCC_GPIOX_TABLE[gpiox]))
#define RCC_GPIOX_DISABLE(gpiox)    WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) & (~(GPIOX_ENABLE << RCC_GPIOX_TABLE[gpiox])))

#endif