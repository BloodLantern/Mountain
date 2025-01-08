#ifndef GAME_STATE_STRUCT_H
#define GAME_STATE_STRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/input.h"

struct GameCompletion {
    s8 completedGame;
    u8 introPlayed;
    u8 language;
};

extern struct GameCompletion gGameCompletion;

struct FileScreenOptionsUnlocked {
    u16 galleryImages;
    u16 fusionGalleryImages;
    u8 soundTestAndOgMetroid;
    u8 unk_5;
    u8 unk_6;
    u8 unk_7;
    u32 timeAttack;
};

extern struct FileScreenOptionsUnlocked gFileScreenOptionsUnlocked;
extern struct ButtonAssignments gButtonAssignments;
extern s8 gTourianEscapeCutsceneStage;
extern vu16 gVBlankRequestFlag;
extern u8 gDisableSoftreset;
extern u8 gDebugFlag;
extern u8 gSramErrorFlag;
extern s8 gDisablePause;
extern u8 gShipLandingFlag;
extern u8 gTimeAttackFlag;
extern u16 gButtonInput;
extern u16 gPreviousButtonInput;
extern u16 gChangedInput;
extern s8 gIsLoadingFile;
extern s8 gPauseScreenFlag;
extern s8 gVblankActive;
extern u8 gFrameCounter8Bit;
extern u16 gFrameCounter16Bit;
extern u8 gDifficulty;
extern s8 gLanguage;
extern u8 gResetGame;
extern u8 gNotPressingUp;
extern u8 gEndingFlags;

extern s16 gMainGameMode;
extern s16 gGameModeSub1;
extern s8 gGameModeSub2;
extern s8 gGameModeSub3;
extern u8 gSubGameModeStage;

extern u8 gHasSaved;
extern s8 gMostRecentSaveFile;
extern u8 gCompletedGameFlagCopy;

extern u8 gTargetFps;

#ifdef __cplusplus
}
#endif

#endif
