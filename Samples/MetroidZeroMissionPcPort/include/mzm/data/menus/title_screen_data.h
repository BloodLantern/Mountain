#ifndef TITLE_SCREEN_DATA_H
#define TITLE_SCREEN_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"
#include "mzm/structs/menus/title_screen.h"
#include "mzm/structs/menu.h"

extern const u16 sTitleScreenPal[15 * 16];
extern const u16 sTitleScreenPromptPAL[5 * 16];

extern const u32 sTitleScreenTitleGfx[1095];
extern const u32 sTitleScreenSparklesGfx[256];
extern const u32 sTitleScreenSpaceBackgroundGfx[3203];
extern const u32 sTitleScreenSpaceBackgroundDecorationGfx[797];
extern const u32 sTitleScreenSpaceAndGroundBackgroundGfx[1920];
extern const u32 sTitleScreenTitleTileTable[199];
extern const u32 sTitleScreenSpaceBackgroundTileTable[702];

extern const u8 sTitleScreenRomInfoPosition[4];
extern const u8 sTitleScreenRomInfoTime[12];
extern const u8 sTitleScreenRomInfoRegionUSA[4];
extern const u8 sTitleScreenRomInfoRegionEUR[4];
extern const u8 sTitleScreenRomInfoRegionJPN[4];

extern const struct TitleScreenPageData sTitleScreenPageData[2];

extern const struct MenuOamData sTitleScreenTopSparkleBaseOam;
extern const struct MenuOamData sTitleScreenBottomSparkleBaseOam;

extern const struct OamArray sTitleScreenOam[7];

#ifdef __cplusplus
}
#endif

#endif /* TITLE_SCREEN_DATA_H */
