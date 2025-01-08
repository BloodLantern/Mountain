#include "mzm_game.hpp"

#include "Mountain/window.hpp"
#include "Mountain/rendering/draw.hpp"

#include "mzm/chozodia_escape.h"
#include "mzm/demo.h"
#include "mzm/ending_and_gallery.h"
#include "mzm/funcs.h"
#include "mzm/fusion_gallery.h"
#include "mzm/init_game.h"
#include "mzm/intro.h"
#include "mzm/in_game.h"
#include "mzm/softreset.h"
#include "mzm/softreset_input.h"
#include "mzm/update_input.h"
#include "mzm/constants/game_state.h"
#include "mzm/cutscenes/cutscene_utils.h"
#include "mzm/menus/erase_sram.h"
#include "mzm/menus/file_select.h"
#include "mzm/menus/game_over.h"
#include "mzm/menus/pause_screen.h"
#include "mzm/menus/title_screen.h"
#include "mzm/structs/demo.h"
#include "mzm/structs/game_state.h"

namespace
{
    u8 psf;
}

MzmGame::MzmGame()
    : Game("Metroid: Zero Mission (PC Port)")
{
}

void MzmGame::Initialize()
{
    InitializeGame();

    Game::Initialize();
}

void MzmGame::LoadResources()
{
}

void MzmGame::Update()
{
    gVblankActive = FALSE;
    UpdateAudio();

    if (gResetGame)
    {
        Mountain::Window::SetShouldClose(true);
        return;
    }

    UpdateInput();
    SoftresetCheck();

    gFrameCounter8Bit++;
    gFrameCounter16Bit++;

    switch (gMainGameMode)
    {
        case GM_SOFTRESET:
            if (SoftresetSubroutine())
            {
                gMainGameMode = GM_INGAME;
                gGameModeSub1 = 0;
            }
            break;

        case GM_INTRO:
            if (IntroSubroutine())
            {
                gMainGameMode = GM_TITLE;
                gGameModeSub1 = 0;
            }
            break;

        case GM_TITLE:
            if (TitleScreenSubroutine())
            {
                if (gGameModeSub2 == 1)
                {
                    gMainGameMode = GM_FILESELECT;
                }
                else if (gGameModeSub2 == 2)
                {
                    DemoStart();
                    gMainGameMode = GM_DEMO;
                }
                else
                {
                    gMainGameMode = GM_INTRO;
                }

                gGameModeSub1 = 0;
                gPauseScreenFlag = 0;
                gGameModeSub2 = 0;
            }
            break;

        case GM_FILESELECT:
            if (FileSelectMenuSubroutine())
            {
                if (gGameModeSub2 == 1)
                    gMainGameMode = GM_INGAME;
                else if (gGameModeSub2 == 2)
                    gMainGameMode = GM_INGAME;
                else if (gGameModeSub2 == 4)
                    gMainGameMode = GM_FUSION_GALLERY;
                else if (gGameModeSub2 == 5)
                    gMainGameMode = GM_GALLERY;
                else
                    gMainGameMode = GM_INTRO;

                gGameModeSub1 = 0;
                gGameModeSub3 = 0;
                gGameModeSub2 = 0;
            }
            break;

        case GM_INGAME:
            if (InGameMainLoop())
            {
                if (gPauseScreenFlag == PAUSE_SCREEN_NONE)
                {
                    if (gCurrentCutscene != 0)
                    {
                        gMainGameMode = GM_CUTSCENE;
                    }
                    else if (gTourianEscapeCutsceneStage != 0)
                    {
                        gMainGameMode = GM_TOURIAN_ESCAPE;
                    }
                    else
                    {
                        gMainGameMode = GM_TITLE;
                        gGameModeSub1 = 0;
                    }
                }
                else
                {
                    gMainGameMode = GM_MAP_SCREEN;
                }
            }
            break;

        case GM_MAP_SCREEN:
            if (PauseScreenSubroutine())
            {
                gMainGameMode = gGameModeSub2;
                gGameModeSub2 = 0;

                switch (gPauseScreenFlag)
                {
                    case PAUSE_SCREEN_UNKNOWN_1:
                        gGameModeSub3 = 0;

                    case PAUSE_SCREEN_SUITLESS_ITEMS:
                        gPauseScreenFlag = PAUSE_SCREEN_NONE;
                        break;

                    case PAUSE_SCREEN_UNKNOWN_9:
                        gPauseScreenFlag = PAUSE_SCREEN_NONE;
                        gGameModeSub2 = 1;
                        break;

                    case PAUSE_SCREEN_PAUSE_OR_CUTSCENE:
                    case PAUSE_SCREEN_UNKNOWN_3:
                    case PAUSE_SCREEN_CHOZO_HINT:
                    case PAUSE_SCREEN_MAP_DOWNLOAD:
                    case PAUSE_SCREEN_FULLY_POWERED_SUIT_ITEMS:
                        break;
                }

                gGameModeSub1 = 0;
            }
            break;

        case GM_GAMEOVER:
            if (GameOverSubroutine())
            {
                gMainGameMode = gGameModeSub2;
                gGameModeSub1 = 0;
                gGameModeSub2 = 0;
            }
            break;

        case GM_CHOZODIA_ESCAPE:
            if (ChozodiaEscapeSubroutine())
            {
                gGameModeSub1 = 0;
                gMainGameMode = GM_CREDITS;
            }
            break;

        case GM_CREDITS:
            if (CreditsSubroutine())
            {
                gGameModeSub1 = 0;
                gMainGameMode = GM_INTRO;
            }
            break;

        case GM_TOURIAN_ESCAPE:
            if (TourianEscapeSubroutine())
            {
                gGameModeSub1 = 0;
                gMainGameMode = gGameModeSub2;
            }
            break;

        case GM_CUTSCENE:
            if (CutsceneSubroutine())
            {
                gGameModeSub1 = 0;
                psf = gPauseScreenFlag - 7;
                if (psf <= 1)
                {
                    gMainGameMode = GM_MAP_SCREEN;
                    break;
                }
                gMainGameMode = GM_INGAME;
            }
            break;

        case GM_DEMO:
            if (InGameMainLoop())
            {
                if (gPauseScreenFlag == PAUSE_SCREEN_PAUSE_OR_CUTSCENE)
                {
                    gPauseScreenFlag = PAUSE_SCREEN_NONE;
                    gGameModeSub3 = 0;
                    gGameModeSub1 = 0;
                    if (gDemoState == 0)
                    {
                        gMainGameMode = gGameModeSub2;
                        gGameModeSub2 = gCurrentDemo.endedWithInput;
                    }
                    else {
                        DemoStart();
                        gMainGameMode = GM_DEMO;
                    }
                }
                else
                    gMainGameMode = GM_MAP_SCREEN;
            }
            break;

        case GM_GALLERY:
            if (GallerySubroutine())
            {
                gGameModeSub1 = 0;
                gMainGameMode = GM_FILESELECT;
            }
            break;

        case GM_FUSION_GALLERY:
            if (FusionGallerySubroutine())
            {
                gGameModeSub1 = 0;
                gMainGameMode = GM_FILESELECT;
            }
            break;

        case GM_START_SOFTRESET:
            Softreset();
            break;

        case GM_ERASE_SRAM:
            if (EraseSramSubroutine())
            {
                if (gGameModeSub2 == 1)
                    gResetGame = TRUE;
                else
                    gMainGameMode = GM_SOFTRESET;

                gGameModeSub1 = 0;
                gGameModeSub2 = 0;
            }
            break;

        case GM_DEBUG_MENU:
            for (;;)
            {
                // TODO add debug code
            }

        default: ;
    }

    gVBlankRequestFlag &= ~TRUE;
    gVblankActive = TRUE;
}

void MzmGame::Render()
{
    Mountain::Draw::Clear(Mountain::Color::CornflowerBlue());
}

void MzmGame::Shutdown()
{
    Game::Shutdown();
}
