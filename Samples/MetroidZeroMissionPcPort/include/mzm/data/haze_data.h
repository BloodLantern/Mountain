#ifndef HAZE_DATA_H
#define HAZE_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/haze.h"

extern const u8 sHaze_345ff8[132];

extern const s8 sHaze_Bg3_StrongEffect[48];

// ...

extern const s16* const sHaze_PowerBomb_WindowValuesPointers[161];

extern const s8 sHaze_Bg3Bg2Bg1[9][32];

extern const s8 sHaze_Bg3_WeakOutside[16];

extern const s8 sHaze_Bg_WeakOutside[32];

extern const struct HazeLoop sHazeLoop_Empty;

#ifdef __cplusplus
}
#endif

#endif /* HAZE_DATA_H */
