#ifndef EMPTY_DATATYPES_H
#define EMPTY_DATATYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/structs/block.h"
#include "mzm/structs/connection.h"
#include "mzm/structs/transparency.h"
#include "mzm/structs/screen_shake.h"
#include "mzm/structs/scroll.h"
#include "mzm/structs/room.h"
#include "mzm/structs/power_bomb_explosion.h"
#include "mzm/structs/animated_graphics.h"

// 345868

extern const struct HatchData sHatchData_Empty;

extern const struct RawCoordsX sCoordsX_Empty;

extern const struct LockScreen sLockScreen_Empty;

extern const struct BackgroundEffect sBackgroundEffect_Empty;

extern const struct BrokenBlock sBrokenBlock_Empty;

extern const struct BombChain sBombChain_Empty;

extern const struct PowerBomb sPowerBomb_Empty;

extern const struct ScreenShake sScreenShake_Empty;

extern const struct BG0Movement sBg0Movement_Empty;

extern const struct BG3Movement sBg3Movement_Empty;

extern const struct Unused_3005504 sUnusedStruct_3005504_Empty;

extern const struct WaterMovement sWaterMovement_Empty;

extern const struct TransparencyRelated sTransparencyRelated_Empty;

extern const struct LastElevatorUsed sLastElevatorUsed_Empty;

extern const struct BldalphaData sBldalphaData_Empty;

extern const struct BldyData sBldyData_Empty;

extern const struct DefaultTransparency sDefaultTransparency_Empty;

#ifdef __cplusplus
}
#endif

#endif
