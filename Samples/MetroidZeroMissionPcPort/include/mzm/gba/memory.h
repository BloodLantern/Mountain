#ifndef GBA_MEMORY_H
#define GBA_MEMORY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/macros.h"
#include "mzm/structs/save_file.h"

#define EWRAM_SIZE (256 * 0x400)
extern u8 gEwramBuffer[EWRAM_SIZE];

#define IWRAM_SIZE (32 * 0x400)
extern u8 gIwramBuffer[IWRAM_SIZE];

extern u8 gRegBuffer[0x3FE];

#define PALRAM_SIZE 0x400
extern u16 gPalramBuffer[PALRAM_SIZE / sizeof(u16)];

#define VRAM_SIZE (96 * 0x400)
extern u8 gVramBuffer[VRAM_SIZE];
#define VRAM_OBJ (gVramBuffer + ARRAY_SIZE(gVramBuffer) / 2)

#define OAM_SIZE 0x400
extern u8 gOamBuffer[OAM_SIZE];

#define ROM_BASE (void *)0x08000000

#ifdef __cplusplus
}
#endif
#define ROM_SIZE (32 * 0x100000)
#endif /* GBA_MEMORY_H */
