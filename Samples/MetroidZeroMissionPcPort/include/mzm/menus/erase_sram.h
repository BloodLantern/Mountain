#ifndef ERASE_SRAM_MENU_H
#define ERASE_SRAM_MENU_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/menus/erase_sram.h"

u32 EraseSramSubroutine(void);
u32 EraseSramProcessInput(void);
void EraseSramApplyInput(void);
u32 EraseSramCheckForInput(void);
void EraseSramInit(void);
void EraseSramResetOam(void);
void EraseSramUpdateCursorPosition(void);
void EraseSramVBlank(void);
void EraseSramVBlank_Empty(void);
void EraseSramProcessOAM(void);

#ifdef __cplusplus
}
#endif

#endif /* ERASE_SRAM_MENU_H */
