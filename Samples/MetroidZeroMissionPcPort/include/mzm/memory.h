#ifndef MEMORY_H
#define MEMORY_H

#include "mzm/gba.h"
#include "mzm/types.h"

void DmaTransfer(u8 channel, void *src, void *dst, u32 len, u8 bitSize);
void BitFill(int dma_channel, u32 value, void *dst, u32 len, u8 bit_size);

#endif /* MEMORY_H */
