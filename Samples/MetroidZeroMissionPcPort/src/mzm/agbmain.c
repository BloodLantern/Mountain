#include "mzm/gba.h"
#include "mzm/demo.h"

#include "mzm/structs/game_state.h"

#include "mzm/menus/file_select.h"

struct GameCompletion gGameCompletion;
struct FileScreenOptionsUnlocked gFileScreenOptionsUnlocked;
struct ButtonAssignments gButtonAssignments;
s8 gTourianEscapeCutsceneStage;
vu16 gVBlankRequestFlag;
u8 gDisableSoftreset;
u8 gDebugFlag;
u8 gSramErrorFlag;
s8 gDisablePause;
u8 gShipLandingFlag;
u8 gTimeAttackFlag;
u16 gButtonInput;
u16 gPreviousButtonInput;
u16 gChangedInput;
s8 gIsLoadingFile;
s8 gPauseScreenFlag;
s8 gVblankActive;
u8 gFrameCounter8Bit;
u16 gFrameCounter16Bit;
u8 gDifficulty;
s8 gLanguage;
u8 gResetGame;
u8 gNotPressingUp;
u8 gEndingFlags;

s16 gMainGameMode;
s16 gGameModeSub1;
s8 gGameModeSub2;
s8 gGameModeSub3;
u8 gSubGameModeStage;

u8 gHasSaved;
s8 gMostRecentSaveFile;
u8 gCompletedGameFlagCopy;

u8 gEwramBuffer[EWRAM_SIZE];
u8 gIwramBuffer[IWRAM_SIZE];
u8 gRegBuffer[0x3FE];
u16 gPalramBuffer[PALRAM_SIZE / sizeof(u16)];
u8 gVramBuffer[VRAM_SIZE];
u8 gOamBuffer[OAM_SIZE];
u8 gSramBuffer[sizeof(struct Sram)];
