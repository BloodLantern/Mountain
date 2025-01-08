#ifndef GBA_INPUT_H
#define GBA_INPUT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

struct ButtonAssignments {
    u16 armWeapon;
    u16 diagonalAim;
    u16 pause;
    u16 swapMissiles;
};

#ifdef __cplusplus
}
#endif

#endif /* GBA_INPUT_H */
