#ifndef _MEMORYMAP_H_
#define _MEMORYMAP_H_

#define GET_ADDR(x) (x)
#define READ_REG_BYTE(addr, offset)         (*((volatile BYTE*)GET_ADDR(addr + offset)))
#define WRITE_REG_BYTE(addr, offset, val)   ((*((volatile BYTE*)GET_ADDR(addr + offset)))=(val))
#define READ_REG_WORD(addr, offset)         (*((volatile WORD*)GET_ADDR(addr + offset)))
#define WRITE_REG_WORD(addr, offset, val)   ((*((volatile WORD*)GET_ADDR(addr + offset)))=(val))
#define READ_REG_LWORD(addr, offset)         (*((volatile LWORD*)GET_ADDR(addr + offset)))
#define WRITE_REG_LWORD(addr, offset, val)   ((*((volatile LWORD*)GET_ADDR(addr + offset)))=(val))


// Cortex M4 Internal Peripherals
#define CORTEX_M4_INTERNAL_PERIPHERALS  (0xE0000000)

// NVIC
#define NVIC_OFFSET                     (0x0000E100)
#define NVIC_BASE                       GET_ADDR(CORTEX_M4_INTERNAL_PERIPHERALS + NVIC_OFFSET)


// Peripherals
#define PERIPHERAL_BASE                 (0x40000000)

// AHB1 peripheral
#define AHB1_OFFSET                     (0x00020000)
#define PERIPHERAL_AHB1_BASE            GET_ADDR(PERIPHERAL_BASE + AHB1_OFFSET)

// APB2 peripheral
#define APB2_OFFSET                     (0x00010000)
#define PERIPHERAL_APB2_BASE            GET_ADDR(PERIPHERAL_BASE + APB2_OFFSET)

#endif