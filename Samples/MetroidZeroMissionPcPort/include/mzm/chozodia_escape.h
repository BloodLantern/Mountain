#ifndef CHOZODIA_ESCAPE_H
#define CHOZODIA_ESCAPE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void ChozodiaEscapeVBlank(void);
void ChozodiaEscapeHBlank(void);
void ChozodiaEscapeSetHBlank(void);
void ChozodiaEscapeSetupHBlankRegisters(void);
void ChozodiaEscapeUpdateExplosionHaze(void);
u32 ChozodiaEscapeGetItemCountAndEndingNumber(void);
void ChozodiaEscapeProcessOam_1(void);
void ChozodiaEscapeProcessOam_2(void);
void ChozodiaEscapeInit(void);
u8 ChozodiaEscapeShipLeaving(void);
u8 ChozodiaEscapeShipHeatingUp(void);
u8 ChozodiaEscapeShipBlowingUp(void);
u8 ChozodiaEscapeShipLeavingPlanet(void);
u8 ChozodiaEscapeMissionAccomplished(void);
u32 ChozodiaEscapeSubroutine(void);

#ifdef __cplusplus
}
#endif

#endif /* CHOZODIA_ESCAPE_H */
