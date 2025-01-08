#include "mzm/cutscenes/before_charlie.h"
#include "mzm/cutscenes/cutscene_utils.h"
#include "mzm/gba.h"
#include "mzm/color_effects.h" // Required
#include "mzm/music_wrappers.h"
#include "mzm/syscall_wrappers.h"

#include "mzm/data/shortcut_pointers.h"
#include "mzm/data/cutscenes/before_charlie_data.h"
#include "mzm/data/cutscenes/internal_before_charlie_data.h"

#include "mzm/constants/cutscene.h"
#include "mzm/constants/audio.h"

#include "mzm/structs/display.h"

/**
 * @brief 663c8 | 270 | Handles the close up part
 * 
 * @return u8 FALSE
 */
u8 BeforeCharlieSamusCloseUp(void)
{
    switch (CUTSCENE_DATA.timeInfo.subStage)
    {
        case 0:
            DmaTransfer(3, sBeforeCharlieSamusCloseUpPAL, gPalramBuffer, sizeof(sBeforeCharlieSamusCloseUpPAL), 0x10);
            SET_BACKDROP_COLOR(COLOR_BLACK);

            CallLZ77UncompVram(sBeforeCharlieYoungSamusCloseUpGfx, gVramBuffer + sBeforeCharliePageData[5].graphicsPage * 0x4000);
            CallLZ77UncompVram(sBeforeCharlieSamusCloseUpGfx, gVramBuffer + sBeforeCharliePageData[6].graphicsPage * 0x4000);
            
            CallLZ77UncompVram(sBeforeCharlieYoungSamusCloseUpTileTable, gVramBuffer + sBeforeCharliePageData[5].tiletablePage * 0x800);
            CallLZ77UncompVram(sBeforeCharlieSamusCloseUpEyesClosedTileTable, gVramBuffer + sBeforeCharliePageData[8].tiletablePage * 0x800);
            CallLZ77UncompVram(sBeforeCharlieSamusCloseUpEyesOpenedTileTable, gVramBuffer + sBeforeCharliePageData[7].tiletablePage * 0x800);
            CallLZ77UncompVram(sBeforeCharlieSamusCloseUpOutlineTileTable, gVramBuffer + sBeforeCharliePageData[6].tiletablePage * 0x800);

            CutsceneSetBgcntPageData(sBeforeCharliePageData[5]);
            CutsceneSetBgcntPageData(sBeforeCharliePageData[8]);
            CutsceneSetBgcntPageData(sBeforeCharliePageData[7]);
            CutsceneSetBgcntPageData(sBeforeCharliePageData[6]);

            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS | CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[5].bg, 0x800);
            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS | CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[8].bg, 0x800);
            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS | CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[7].bg, 0x800);
            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS | CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[6].bg, 0x800);
            CutsceneReset();

            CutsceneStartBackgroundFading(10);
            CUTSCENE_DATA.dispcnt = sBeforeCharliePageData[5].bg | sBeforeCharliePageData[8].bg |sBeforeCharliePageData[6].bg ;
            
            CUTSCENE_DATA.timeInfo.timer = 0;
            CUTSCENE_DATA.timeInfo.subStage++;
            break;

        case 1:
            if (CUTSCENE_DATA.timeInfo.timer > 60 * 3)
            {
                CutsceneStartBackgroundEffect(BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG0_SECOND_TARGET_PIXEL | BLDCNT_BG1_SECOND_TARGET_PIXEL | BLDCNT_BG2_SECOND_TARGET_PIXEL |
                    BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL,
                    0, 16, 16, 1);

                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 2:
            if (CUTSCENE_DATA.specialEffect.status & CUTSCENE_SPECIAL_EFFECT_STATUS_BG_ENDED)
            {
                CUTSCENE_DATA.dispcnt ^= sBeforeCharliePageData[5].bg;

                CutsceneStartBackgroundEffect(BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG0_SECOND_TARGET_PIXEL | BLDCNT_BG1_SECOND_TARGET_PIXEL | BLDCNT_BG2_SECOND_TARGET_PIXEL |
                    BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL,
                    0, 16, 1, 16);

                CUTSCENE_DATA.dispcnt |= sBeforeCharliePageData[7].bg;
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 3:
            if (CUTSCENE_DATA.timeInfo.timer > 100)
            {
                CutsceneStartBackgroundEffect(BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG0_SECOND_TARGET_PIXEL | BLDCNT_BG1_SECOND_TARGET_PIXEL | BLDCNT_BG2_SECOND_TARGET_PIXEL |
                    BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL,
                    16, 0, 1, 4);

                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 4:
            if (CUTSCENE_DATA.specialEffect.status & CUTSCENE_SPECIAL_EFFECT_STATUS_BG_ENDED)
            {
                CUTSCENE_DATA.dispcnt ^= sBeforeCharliePageData[8].bg;
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 5:
            if (CUTSCENE_DATA.timeInfo.timer > 140)
            {
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 6:
            if (unk_61f44())
            {
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 7:
            if (CUTSCENE_DATA.timeInfo.timer > 70)
            {
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 8:
            unk_61f28();
            CUTSCENE_DATA.timeInfo.stage++;
            MACRO_CUTSCENE_NEXT_STAGE();
            break;
    }

    return FALSE;
}

/**
 * @brief 66638 | 2d8 | Handles the wall view and the grey voice part
 * 
 * @return u8 FALSE
 */
u8 BeforeCharlieWallAndGreyVoice(void)
{
    switch (CUTSCENE_DATA.timeInfo.subStage)
    {
        case 0:
            DmaTransfer(3, sBeforeCharlieChozoWallPAL, gPalramBuffer, sizeof(sBeforeCharlieChozoWallPAL), 0x10);
            SET_BACKDROP_COLOR(COLOR_BLACK);

            ApplyMonochromeToPalette(sBeforeCharlieChozoWallPAL, (u16*)sEwramPointer + 0x3800, 0);
            DmaTransfer(3, sBeforeCharlieChozoWallPAL, (void*)sEwramPointer, sizeof(sBeforeCharlieChozoWallPAL), 0x10);

            CallLZ77UncompVram(sBeforeCharlieChozoWallBackgroundGfx, gVramBuffer + sBeforeCharliePageData[2].graphicsPage * 0x4000);
            BitFill(3, 0, gVramBuffer + sBeforeCharliePageData[2].tiletablePage * 0x800, 0x800, 0x20);
            BitFill(3, 0, gVramBuffer + sBeforeCharliePageData[3].tiletablePage * 0x800, 0x800, 0x20);

            CallLZ77UncompVram(sBeforeCharlieChozoWallBackgroundTileTable, gVramBuffer + sBeforeCharliePageData[2].tiletablePage * 0x800);
            CallLZ77UncompVram(sBeforeCharlieYoungSamusAndGreyVoiceTileTable, gVramBuffer + sBeforeCharliePageData[3].tiletablePage * 0x800);

            CutsceneSetBgcntPageData(sBeforeCharliePageData[2]);
            CutsceneSetBgcntPageData(sBeforeCharliePageData[3]);

            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS | CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[2].bg, 0x800);
            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS | CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[3].bg, 0x800);

            CallLZ77UncompVram(sBeforeCharlieYoungSamusAndGreyVoiceCloseUpGfx, gVramBuffer + sBeforeCharliePageData[4].graphicsPage * 0x4000);
            CallLZ77UncompVram(sBeforeCharlieYoungSamusAndGreyVoiceCloseuUpTileTable, gVramBuffer + sBeforeCharliePageData[4].tiletablePage * 0x800);

            CutsceneSetBgcntPageData(sBeforeCharliePageData[4]);
            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS, sBeforeCharliePageData[4].bg, 0x940);
            CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[4].bg, 0x800);
            CutsceneReset();

            gWrittenToBLDALPHA_L = 0;
            gWrittenToBLDALPHA_H = 16;

            CUTSCENE_DATA.bldcnt = BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL;
            DmaTransfer(3, &sBeforeCharlieCutsceneGraphicsData, &CUTSCENE_DATA.graphicsData[1], sizeof(CUTSCENE_DATA.graphicsData[1]), 0x10);

            CUTSCENE_DATA.dispcnt = sBeforeCharliePageData[2].bg | sBeforeCharliePageData[4].bg;
            CUTSCENE_DATA.timeInfo.timer = 0;
            CUTSCENE_DATA.timeInfo.subStage++;
            break;

        case 1:
            if (CUTSCENE_DATA.timeInfo.timer > 60 * 2)
            {
                CUTSCENE_DATA.graphicsData[0].active |= TRUE;
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 2:
            if (CUTSCENE_DATA.timeInfo.timer == 200 && !CUTSCENE_DATA.graphicsData[1].active)
            {
                CUTSCENE_DATA.graphicsData[1].active |= TRUE;
            }

            if (CUTSCENE_DATA.timeInfo.timer == 560 && !CUTSCENE_DATA.graphicsData[2].active)
            {
                CutsceneStartBackgroundEffect(CUTSCENE_DATA.bldcnt, 16, 0, 16, 1);
                CUTSCENE_DATA.graphicsData[2].active |= TRUE;
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 3:
            if (!CUTSCENE_DATA.graphicsData[0].active && !CUTSCENE_DATA.graphicsData[1].active && !CUTSCENE_DATA.graphicsData[2].active && CUTSCENE_DATA.specialEffect.status & CUTSCENE_SPECIAL_EFFECT_STATUS_BG_ENDED)
            {
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 4:
            if (CUTSCENE_DATA.timeInfo.timer > 60)
            {
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 5:
            unk_61f28();
            CUTSCENE_DATA.timeInfo.stage++;
            MACRO_CUTSCENE_NEXT_STAGE();
            break;
    }

    BeforeCharlieWallAndGreyVoiceScrollAndLoadYoungSamusGfx(&CUTSCENE_DATA.graphicsData[0]);
    BeforeCharlieWallAndGreyVoiceApplyMonochrome(&CUTSCENE_DATA.graphicsData[1]);
    BeforeCharlieWallAndGreyScrollCloseUp(&CUTSCENE_DATA.graphicsData[2]);

    *CutsceneGetBgVerticalPointer(sBeforeCharliePageData[3].bg) = *CutsceneGetBgVerticalPointer(sBeforeCharliePageData[2].bg);

    return FALSE;
}

/**
 * @brief 66910 | 78 | Handles the scrolling of the wall and loads the young samus and grey voice graphics
 * 
 * @param pGraphics Cutscene graphics data pointer
 */
void BeforeCharlieWallAndGreyVoiceScrollAndLoadYoungSamusGfx(struct CutsceneGraphicsData* pGraphics)
{
    u16* pPosition;

    if (!(pGraphics->active & TRUE))
        return;

    pPosition = CutsceneGetBgVerticalPointer(sBeforeCharliePageData[2].bg);
    (*pPosition)++;

    if (*pPosition >= BLOCK_SIZE * 42)
    {
        *pPosition = BLOCK_SIZE * 42;
        pGraphics->active = FALSE;
    }

    if (!(CUTSCENE_DATA.dispcnt & sBeforeCharliePageData[3].bg) && *pPosition == BLOCK_SIZE * 38)
    {
        CallLZ77UncompVram(sBeforeCharlieYoungSamusAndGreyVoiceGfx, gVramBuffer + sBeforeCharliePageData[3].graphicsPage * 0x4000);
        CUTSCENE_DATA.dispcnt |= sBeforeCharliePageData[3].bg;
    }
}

/**
 * @brief 66988 | 6c | Handles the monochrome palette transition
 * 
 * @param pGraphics Cutscene graphics data pointer
 */
void BeforeCharlieWallAndGreyVoiceApplyMonochrome(struct CutsceneGraphicsData* pGraphics)
{
    if (!(pGraphics->active & TRUE))
        return;

    if (pGraphics->timer != 0)
    {
        pGraphics->timer--;
        return;
    }

    pGraphics->timer = pGraphics->maxTimer;
    pGraphics->paletteStage++;

    ApplySmoothMonochromeToPalette((void*)sEwramPointer, (u16*)sEwramPointer + 0x3800, (u16*)sEwramPointer + 0x400, pGraphics->paletteStage);
    DmaTransfer(3, (u8*)sEwramPointer + 0x400, gPalramBuffer, 0x200, 0x10);

    if (pGraphics->paletteStage == 32)
        pGraphics->active = FALSE;
}

/**
 * @brief 669f4 | 3c | Handles the scrolling of the young samus and grey voice close up
 * 
 * @param pGraphics Cutscene graphics data pointer
 */
void BeforeCharlieWallAndGreyScrollCloseUp(struct CutsceneGraphicsData* pGraphics)
{
    u16* pPosition;

    if (!(pGraphics->active & TRUE))
        return;

    pPosition = CutsceneGetBgHorizontalPointer(sBeforeCharliePageData[4].bg);
    (*pPosition) -= 2;

    if (*pPosition <= BLOCK_SIZE * 32)
    {
        *pPosition = BLOCK_SIZE * 32;
        pGraphics->active = FALSE;
    }
}

/**
 * @brief 66a30 | 70 | Handles the view of the chozo side walls part
 * 
 * @return u8 FALSE
 */
u8 BeforeCharlieChozoWallSides(void)
{
    switch (CUTSCENE_DATA.timeInfo.subStage)
    {
        case 0:
            // Wait
            if (CUTSCENE_DATA.timeInfo.timer > 60 * 2 + 20)
            {
                // Toggle viewed wall
                CUTSCENE_DATA.dispcnt ^= sBeforeCharliePageData[0].bg;
                CUTSCENE_DATA.dispcnt |= sBeforeCharliePageData[1].bg;
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 1:
            // Wait
            if (CUTSCENE_DATA.timeInfo.timer > 60 * 2 + 20)
            {
                CUTSCENE_DATA.timeInfo.timer = 0;
                CUTSCENE_DATA.timeInfo.subStage++;
            }
            break;

        case 2:
            unk_61f0c();
            CUTSCENE_DATA.timeInfo.stage++;
            MACRO_CUTSCENE_NEXT_STAGE();
            break;
    }

    return FALSE;
}

/**
 * @brief 66aa0 | 130 | Initializes the before charlie cutscene
 * 
 * @return u8 FALSE
 */
u8 BeforeCharlieInit(void)
{
    unk_61f0c();

    DmaTransfer(3, sBeforeCharlieChozoWallSidesPAL, gPalramBuffer, sizeof(sBeforeCharlieChozoWallSidesPAL), 0x10);
    BitFill(3, 0, (&gPalramBuffer[sizeof(gPalramBuffer) / 2]), 0x200, 0x20);
    SET_BACKDROP_COLOR(COLOR_BLACK);

    CallLZ77UncompVram(sBeforeCharlieLeftSideOfChozoWallGfx, gVramBuffer + sBeforeCharliePageData[0].graphicsPage * 0x4000);
    CallLZ77UncompVram(sBeforeCharlieRightSideOfChozoWallGfx, gVramBuffer + sBeforeCharliePageData[1].graphicsPage * 0x4000);

    BitFill(3, 0, gVramBuffer + 0x800 + sBeforeCharliePageData[0].tiletablePage * 0x800, 0x800, 0x20);
    BitFill(3, 0, gVramBuffer + sBeforeCharliePageData[1].tiletablePage * 0x800, 0x800, 0x20);

    CallLZ77UncompVram(sBeforeCharlieLeftSideOfChozoWallTileTable, gVramBuffer + sBeforeCharliePageData[0].tiletablePage * 0x800);
    CallLZ77UncompVram(sBeforeCharlieRightSideOfChozoWallTileTable, gVramBuffer + 0x800 + sBeforeCharliePageData[1].tiletablePage * 0x800);

    CutsceneSetBgcntPageData(sBeforeCharliePageData[0]);
    CutsceneSetBgcntPageData(sBeforeCharliePageData[1]);
    CutsceneReset();

    CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS | CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[0].bg, 0x800);
    CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_VOFS, sBeforeCharliePageData[1].bg, 0x800);
    CutsceneSetBackgroundPosition(CUTSCENE_BG_EDIT_HOFS, sBeforeCharliePageData[1].bg, 0xC00);

    PlayMusic(MUSIC_CHOZO_STATUE_HINT_DELAY, 0);

    CUTSCENE_DATA.dispcnt = sBeforeCharliePageData[0].bg;

    CUTSCENE_DATA.timeInfo.timer = 0;
    CUTSCENE_DATA.timeInfo.subStage = 0;
    CUTSCENE_DATA.timeInfo.stage++;

    return FALSE;
}

/**
 * @brief 66bd0 | 30 | Subroutine for the before charlie cutscene
 * 
 * @return u8 bool, ended
 */
u8 BeforeCharlieSubroutine(void)
{
    u8 ended;

    ended = sBeforeCharlieSubroutineData[CUTSCENE_DATA.timeInfo.stage].pFunction();

    CutsceneUpdateBackgroundsPosition(TRUE);
    return ended;
}
