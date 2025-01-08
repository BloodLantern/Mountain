#ifndef INTERNAL_TITLE_SCREEN_DATA_H
#define INTERNAL_TITLE_SCREEN_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/menus/title_screen.h"

extern const struct TitleScreenAnimatedPalette sTitleScreenAnimatedPaletteTemplates[4];
extern const u8 sTitleScreenCometsFlags[2][2];

extern const u8 sTitleScreenSkyDecorationsPaletteRows[6];
extern const u8 sTitleScreenTitlePaletteRows[14];
extern const u8 sTitleScreenPromptPaletteRows[7];

#ifdef __cplusplus
}
#endif

#endif /* INTERNAL_TITLE_SCREEN_DATA_H */
