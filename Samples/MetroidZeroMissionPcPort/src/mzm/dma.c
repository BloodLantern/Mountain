#include "funcs.h"
#include "globals.h"
#include "gba.h"

#include <string.h>

void DmaTransfer(u8 channel, void *src, void *dst, u32 len, u8 bitSize)
{
    memcpy(dst, src, len);
}

void BitFill(u8 channel, s32 value, void* dst, u32 len, u8 bitSize)
{
    memset(dst, value, len);
}
