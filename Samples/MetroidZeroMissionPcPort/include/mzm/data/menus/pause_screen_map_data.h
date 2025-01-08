#ifndef PAUSE_SCREEN_MAP_DATA_H
#define PAUSE_SCREEN_MAP_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"
#include "mzm/structs/menus/pause_screen.h"
#include "mzm/connection.h"

extern const u8 sMinimapTilesGfx[5120];
extern const u32 sPauseScreen_40f4c4[1792];
extern const u32 sMapScreenAreaNamesGfx[167];
extern const u16 sMinimapTilesPal[5 * 16];

#ifdef __cplusplus
}
#endif

#endif /* PAUSE_SCREEN_MAP_DATA_H */
