#ifndef SAMUS_IN_BLUE_SHIP_DATA_H
#define SAMUS_IN_BLUE_SHIP_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/macros.h"
#include "mzm/types.h"

#include "mzm/structs/cutscene.h"

extern const struct CutscenePageData sSamusInBlueShipPageData[1];
extern const struct OamArray sSamusInBlueShipOam[3];

extern const u16 sSamusInBlueShipPAL[9 * 16];
extern const u32 sSamusInBlueShipSamusGfx[3641];
extern const u32 sSamusInBlueShipControlsGfx[1642];
extern const u32 sSamusInBlueShipSamusTileTable[368];

#ifdef __cplusplus
}
#endif

#endif /* SAMUS_IN_BLUE_SHIP_DATA_H */
