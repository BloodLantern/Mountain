#include "init_game.h"

#include "callbacks.h"
#include "data/save_file_data.h"

#include "gba.h"
#include "gbaio.h"
#include "softreset_input.h"
#include "types.h"

#include "constants/game_state.h"
#include "structs/audio.h"
#include "structs/game_state.h"
#include <stdio.h>

void InitializeGame(void)
{
    write16(REG_DISPCNT, DCNT_BLANK);
    write16(REG_IME, FALSE);
    write16(REG_DISPSTAT, 0);

    dma_fill32(3, 0, gEwramBuffer, EWRAM_SIZE);
    dma_fill32(3, 0, gIwramBuffer, IWRAM_SIZE - 0x200);

    ClearGfxRam();
    LoadInterruptCode();
    CallbackSetVBlank(SoftresetVBlankCallback);
    SramRead_All();
    InitializeAudio();

    write16(REG_IE, IF_VBLANK | IF_DMA2 | IF_GAMEPAK);
    write16(REG_DISPSTAT, DSTAT_IF_VBLANK);
    write16(REG_WAITCNT, WAIT_SRAM_4CYCLES | WAIT_BANK0_3CYCLES
        | WAIT_BANK0_SUBSEQUENT_1CYCLE
        | WAIT_BANK1_3CYCLES | WAIT_BANK1_SUBSEQUENT_1CYCLE
        | WAIT_BANK2_3CYCLES | WAIT_BANK2_SUBSEQUENT_1CYCLE
        | WAIT_GAMEPACK_CGB);

    gGameModeSub1 = 0;
    gGameModeSub2 = 0;
    gDebugFlag = FALSE;

    gButtonInput = KEY_NONE;
    gPreviousButtonInput = KEY_NONE;
    gChangedInput = KEY_NONE;

    UpdateInput();

    if (gChangedInput == (KEY_L | KEY_R))
        gMainGameMode = GM_ERASE_SRAM;
    else
        gMainGameMode = GM_SOFTRESET;

    gButtonInput = 0;
    gPreviousButtonInput = 0;
    gChangedInput = 0;

    gDisableSoftreset = FALSE;
    gStereoFlag = FALSE;

    write16(REG_IF, USHORT_MAX);
    write16(REG_IME, TRUE);
}
