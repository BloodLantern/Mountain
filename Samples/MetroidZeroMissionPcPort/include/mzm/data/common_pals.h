#ifndef DATA_COMMON_PALS_H
#define DATA_COMMON_PALS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

extern const u16 sCommonTilesPal[1 * 16 - 1];
extern const u16 sDoorTransitionPal[15 * 16 + 1];

extern const u16 sCommonTilesMotherShipPal[1 * 16 - 1];
extern const u16 sDoorTransitionMotherShipPal[15 * 16];

extern const u16 sHatchFlashingMotherShipPal[16 * 16];
extern const u16 sHatchFlashingPal[16 * 16];

#ifdef __cplusplus
}
#endif

#endif /* DATA_COMMON_PALS_H */
