#ifndef SRAM_SRAM_H
#define SRAM_SRAM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void SramWriteUnchecked(u8* src, u8* dest, u32 size);
void SramWrite(u8* src, u8* dest, u32 size);
u8* SramCheck(u8* src, u8* dest, u32 size);
u8* SramWriteChecked(u8* src, u8* dest, u32 size);

#ifdef __cplusplus
}
#endif

#endif /* SRAM_SRAM_H */
