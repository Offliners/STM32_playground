#ifndef _GPIO_COMMON_H_
#define _GPIO_COMMON_H_

#include "memorymap.h"

#define GPIOA_OFFSET    (0x00000000)
#define GPIOA           GET_ADDR(PERIPHERAL_AHB1_BASE + GPIOA_OFFSET)

#define GPIO_OSPEED_2MHZ		0x0
#define GPIO_OSPEED_25MHZ		0x1
#define GPIO_OSPEED_50MHZ		0x2
#define GPIO_OSPEED_100MHZ		0x3

#endif