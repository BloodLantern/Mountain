#ifndef SEARCHLIGHT_DATA_H
#define SEARCHLIGHT_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/oam.h"

extern const u32 sSearchlightGfx[172];
extern const u16 sSearchlightPAL[16];

extern const u16 sSearchlightOAM_Moving_Frame0[25];

extern const u16 sSearchlightOAM_Moving_Frame1[25];

extern const u16 sSearchlightOAM_Moving_Frame2[25];

extern const u16 sSearchlightOAM_Moving_Frame3[25];

extern const struct FrameData sSearchlightOAM_Moving[7];

extern const struct FrameData sSearchlightOAM_Unused[5];

#ifdef __cplusplus
}
#endif

#endif
