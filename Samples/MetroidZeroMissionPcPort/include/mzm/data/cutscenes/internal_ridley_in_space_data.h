#ifndef INTERNAL_RIDLEY_IN_SPACE_DATA_H
#define INTERNAL_RIDLEY_IN_SPACE_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"

extern const struct RawCoordsX sRidleyInSpaceShipLeavingPosition;
extern const struct RawCoordsX sRidleyInSpaceShipsStartPosition[3];

extern const s8 sRidleyInSpaceShipsYMovementOffsets[8];

extern const struct CutsceneSubroutineData sRidleyInSpaceSubroutineData[6];

#ifdef __cplusplus
}
#endif

#endif /* INTERNAL_RIDLEY_IN_SPACE_DATA_H */
