#ifndef GBA_DMA_H
#define GBA_DMA_H

#include "mzm/memory.h"
#include "mzm/types.h"

#define REG_DMA0 (gRegBuffer + 0x0b0)
#define REG_DMA1 (gRegBuffer + 0x0bc)
#define REG_DMA2 (gRegBuffer + 0x0c8)
#define REG_DMA3 (gRegBuffer + 0x0d4)

#define REG_DMA1_SRC (REG_DMA1 + 0)
#define REG_DMA1_DST (REG_DMA1 + 4)
#define REG_DMA1_CNT (REG_DMA1 + 8)
#define REG_DMA2_SRC (REG_DMA2 + 0)
#define REG_DMA2_DST (REG_DMA2 + 4)
#define REG_DMA2_CNT (REG_DMA2 + 8)

#define DMA_SET(channel, src, dst, cnt) (DmaTransfer(channel, src, dst, ((cnt) & 0xFFFF) * 2, 16))

#define dma_fill(channel, val, dst, size, bit) (memset(dst, val, size))

#define dma_fill16(channel, value, dest, size)                                 \
    dma_fill(channel, value, dest, size, 16)
#define dma_fill32(channel, value, dest, size)                                 \
    dma_fill(channel, value, dest, size, 32)

#define dma_clear(channel, dest, size, bit) ((void)0)

#define dma_clear16(channel, dest, size) dma_clear(channel, dest, size, 16)
#define dma_clear32(channel, dest, size) dma_clear(channel, dest, size, 32)

#define DMA_DEST_INC 0x0000
#define DMA_DEST_DEC (1 << 5)
#define DMA_DEST_FIXED (1 << 6)
#define DMA_DEST_RELOAD (1 << 5 | 1 << 6)
#define DMA_SRC_INC 0x0000
#define DMA_SRC_DEC (1 << 7)
#define DMA_SRC_FIXED (1 << 8)
#define DMA_REPEAT (1 << 9)
#define DMA_16BIT 0x0000
#define DMA_32BIT (1 << 10)
#define DMA_DREQ_ON (1 << 11)
#define DMA_START_NOW 0x0000
#define DMA_START_VBLANK (1 << 12)
#define DMA_START_HBLANK (1 << 13)
#define DMA_START_SPECIAL (1 << 12 | 1 << 13)
#define DMA_START_MASK (1 << 12 | 1 << 13)
#define DMA_INTR_ENABLE (1 << 14)
#define DMA_ENABLE (1 << 15)

#define CPU_SET_SRC_FIXED (1 << 8)
#define CPU_SET_32BIT (1 << 10)

#endif /* GBA_DMA_H */
