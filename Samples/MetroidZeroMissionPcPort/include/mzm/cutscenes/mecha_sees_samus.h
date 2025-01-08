#ifndef MECHA_SEES_SAMUS_CUTSCENE
#define MECHA_SEES_SAMUS_CUTSCENE

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"

u8 MechaRidleySeesSamusEyeOpen(void);
u8 MechaRidleySeesSamusInit(void);
u8 MechaRidleySeesSamusSubroutine(void);
void MechaRidleySeesSamusProcessOAM(void);

#ifdef __cplusplus
}
#endif

#endif
