#ifndef SAMUS_IN_BLUE_SHIP_CUTSCENE
#define SAMUS_IN_BLUE_SHIP_CUTSCENE

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"

u8 SamusInBlueShipPoweringUp(void);
void SamusInBlueShipShakeScreen(struct CutsceneGraphicsData* pGraphics);
void SamusInBlueShipUpdateControlPanel(struct CutsceneOamData* pOam);
u8 SamusInBlueShipInit(void);
u8 SamusInBlueShipSubroutine(void);
void SamusInBlueShipProcessOAM(void);

#ifdef __cplusplus
}
#endif

#endif /* SAMUS_IN_BLUE_SHIP_CUTSCENE */
