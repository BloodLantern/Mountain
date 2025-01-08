#include "sram/sram.h"

#include "gba.h"
#include "gbaio.h"

static const char sSramVersion[] = "SRAM_V113";

void SramWriteUnchecked(u8* src, u8* dest, u32 size)
{
    // printf("SramWriteUnchecked : %p ; %p ; %d\n", src, dest, size);
    memcpy(dest, src, size);
}

void SramWrite(u8* src, u8* dest, u32 size)
{
    // printf("SramWrite : %p ; %p ; %d\n", src, dest, size);
    memcpy(dest, src, size);
}

u8* SramCheck(u8* src, u8* dest, u32 size)
{
    // printf("SramCheck : %p ; %p ; %d\n", src, dest, size);
    return NULL;
}

u8* SramWriteChecked(u8* src, u8* dest, u32 size)
{
    // printf("SramWriteChecked : %p ; %p ; %d\n", src, dest, size);
    memcpy(dest, src, size);
    return NULL;
}
