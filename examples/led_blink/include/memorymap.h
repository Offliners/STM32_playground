#ifndef _MEMORYMAP_H_
#define _MEMORYMAP_H_

#define GET_ADDR(x) (x)

#define PERIPHERAL_BASE         (0x40000000)
#define AHB1_OFFSET             (0x00020000)
#define PERIPHERAL_AHB1_BASE    GET_ADDR(PERIPHERAL_BASE + AHB1_OFFSET)

#endif