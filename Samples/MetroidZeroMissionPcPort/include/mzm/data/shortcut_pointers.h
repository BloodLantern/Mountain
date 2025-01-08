#ifndef SHORTCUT_POINTERS_H
#define SHORTCUT_POINTERS_H

#include "mzm/types.h"
#include "mzm/temp_globals.h"
#include "mzm/structs/save_file.h"

extern union EwramData* sEwramPointer;
extern u16* sBgPalramPointer;
extern u16* sObjPalramPointer;
extern u32* sVisitedMinimapTilesPointer;
extern union NonGameplayRAM* sNonGameplayRamPointer;
extern struct Sram* sSramEwramPointer;
extern struct Sram* sSramFlashPointer;

#endif /* SHORTCUT_POINTERS_H */
