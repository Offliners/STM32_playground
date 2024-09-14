#ifndef _MEMORYMAP_H_
#define _MEMORYMAP_H_

#define GET_ADDR(x) (x)
#define READ_REG_BYTE(addr, offset)         (*((volatile BYTE*)GET_ADDR(addr + offset)))
#define WRITE_REG_LWORD(addr, offset, val)   ((*((volatile BYTE*)GET_ADDR(addr + offset)))=(val))
#define READ_REG_WORD(addr, offset)         (*((volatile WORD*)GET_ADDR(addr + offset)))
#define WRITE_REG_WORD(addr, offset, val)   ((*((volatile WORD*)GET_ADDR(addr + offset)))=(val))
#define READ_REG_LWORD(addr, offset)         (*((volatile LWORD*)GET_ADDR(addr + offset)))
#define WRITE_REG_LWORD(addr, offset, val)   ((*((volatile LWORD*)GET_ADDR(addr + offset)))=(val))

#define PERIPHERAL_BASE         (0x40000000)
#define AHB1_OFFSET             (0x00020000)
#define PERIPHERAL_AHB1_BASE    GET_ADDR(PERIPHERAL_BASE + AHB1_OFFSET)

#endif