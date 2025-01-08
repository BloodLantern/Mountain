#ifndef COMPLEX_OAM_H
#define COMPLEX_OAM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

u8 ProcessComplexOam(u32 oamSlot, s16 xPosition, s16 yPosition, u16 rotation, s16 scaling, u8 doubleSize, u8 flipSize);
void CalculateOamPart4(u16 rotation, s16 scaling, u8 oamSlot);

#ifdef __cplusplus
}
#endif

#endif /* COMPLEX_OAM_H */
