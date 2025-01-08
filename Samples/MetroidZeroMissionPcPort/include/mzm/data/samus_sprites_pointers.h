#ifndef SAMUS_SPRITES_POINTERS_H
#define SAMUS_SPRITES_POINTERS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#include "mzm/constants/samus.h"
#include "mzm/constants/sprite.h"

#include "mzm/structs/connection.h"
#include "mzm/structs/samus.h"
#include "mzm/structs/particle.h"
#include "mzm/structs/projectile.h"

#define MAX_AMOUNT_OF_SPRITESET 114

extern const SamusFunc_T sSamusPoseFunctionPointers[SPOSE_END];

extern const SamusFunc_T sSamusPoseGfxFunctionPointers[SPOSE_END];

extern const Func_T sPrimarySpritesAIPointers[PSPRITE_END];

extern const char* const sSpritesGraphicsFilePointers[PSPRITE_END];
extern const char* const sSpritesPalettesFilePointers[PSPRITE_END];

extern const u32* const sSpritesGraphicsPointers[PSPRITE_END - 16];

extern const u16* const sSpritesPalettePointers[PSPRITE_END - 16];

extern const Func_T sSecondarySpritesAIPointers[SSPRITE_END];

extern const u8* const sSpritesetPointers[MAX_AMOUNT_OF_SPRITESET];

#ifdef __cplusplus
}
#endif

#endif /* SAMUS_SPRITES_POINTERS_H */
