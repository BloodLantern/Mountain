#ifndef IN_GAME_H
#define IN_GAME_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/samus.h"

u32 InGameMainLoop(void);
void SetVBlankCodeInGame(void);
void TransferSamusGraphics(u32 updatePalette, struct SamusPhysics* pPhysics);
void VBlankCodeInGameLoad(void);
void unk_c9ec(void);
void VBlankCodeInGame(void);
void VBlankInGame_Empty(void);
void InitAndLoadGenerics(void);
void UpdateFreeMovement_Debug(void);

#ifdef __cplusplus
}
#endif

#endif /* IN_GAME_H */
