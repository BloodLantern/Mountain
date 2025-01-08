#ifndef ENTER_TOURIAN_CUTSCENE
#define ENTER_TOURIAN_CUTSCENE

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"

u8 EnterTourianAnimation(void);
void EnterTourianScrollBackground(void);
void EnterTourianUpdateMetroid(struct CutsceneOamData* pOam, u8 metroidId);
void EnterTourianSwitchMetroidPalette(struct CutscenePaletteData* pPalette, u8 grabbedPal);
void EnterTourianUpdatePirate(struct CutsceneOamData* pOam);
u8 EnterTourianInit(void);
u8 EnterTourianSubroutine(void);
void EnterTourianProcessOAM(void);

#ifdef __cplusplus
}
#endif

#endif /* ENTER_TOURIAN_CUTSCENE */
