#ifndef GBA_INTERRUPT_H
#define GBA_INTERRUPT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/memory.h"
#include "mzm/types.h"

#define REG_IME (gRegBuffer + 0x208)
#define REG_IE (gRegBuffer + 0x200)
#define REG_IF (gRegBuffer + 0x202)
#define REG_VCOUNT (gRegBuffer + 0x006)

#define IF_VBLANK (1 << 0)
#define IF_HBLANK (1 << 1)
#define IF_VCOUNT (1 << 2)
#define IF_TIMER0 (1 << 3)
#define IF_TIMER1 (1 << 4)
#define IF_TIMER2 (1 << 5)
#define IF_TIMER3 (1 << 6)
#define IF_SERIAL (1 << 7)
#define IF_DMA0 (1 << 8)
#define IF_DMA1 (1 << 9)
#define IF_DMA2 (1 << 10)
#define IF_DMA3 (1 << 11)
#define IF_KEYPAD (1 << 12)
#define IF_GAMEPAK (1 << 13)

#ifdef __cplusplus
}
#endif

#endif /* GBA_INTERRUPT_H */
