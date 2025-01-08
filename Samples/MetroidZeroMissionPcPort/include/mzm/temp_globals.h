#ifndef TEMP_GLOBALS_H
#define TEMP_GLOBALS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/gba.h"
#include "mzm/types.h"

#include "mzm/structs/cutscene.h"
#include "mzm/structs/intro.h"
#include "mzm/structs/menus/game_over.h"
#include "mzm/structs/ending_and_gallery.h"
#include "mzm/structs/menus/pause_screen.h"
#include "mzm/structs/menus/title_screen.h"
#include "mzm/structs/menus/erase_sram.h"
#include "mzm/structs/menus/file_select.h"
#include "mzm/structs/fusion_gallery.h"
#include "mzm/structs/chozodia_escape.h"
#include "mzm/structs/tourian_escape.h"
#include "mzm/cutscenes/kraid_rising.h"


union NonGameplayRAM {
    struct CutsceneData cutscene;
    struct IntroData intro;
    struct GameOverData gameOver;
    struct EndingData ending;
    struct PauseScreenData pauseScreen;
    struct TitleScreenData titleScreen;
    struct EraseSramData eraseSram;
    struct FileSelectData fileSelect;
    struct FusionGalleryData fusionGallery;
    struct ChozodiaEscapeData chozodiaEscape;
    struct TourianEscapeData tourianEscape;
    u8 inGame[1576];
};

union EwramData {
    struct PauseScreenEwramData pauseScreen;
    struct FileSelectEwramData fileSelect;
    struct KraidRisingEwramData kraidRising;
};

extern u16 unk_02035400;

extern u8 gUnk_03004fc9;
extern union NonGameplayRAM gNonGameplayRAM;

extern u16 gBg0HOFS_NonGameplay;
extern u16 gBg0VOFS_NonGameplay;
extern u16 gBg1HOFS_NonGameplay;
extern u16 gBg1VOFS_NonGameplay;
extern u16 gBg2HOFS_NonGameplay;
extern u16 gBg2VOFS_NonGameplay;
extern u16 gBg3HOFS_NonGameplay;
extern u16 gBg3VOFS_NonGameplay;

extern u16 gCurrentOamRotation;
extern u16 gCurrentOamScaling;

#ifdef __cplusplus
}
#endif

#endif
