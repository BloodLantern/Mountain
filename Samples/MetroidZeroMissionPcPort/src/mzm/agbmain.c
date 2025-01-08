#include "mzm/glad/glad.h"

#include "mzm/syscalls.h"
#include "mzm/gba.h"
#include "mzm/demo.h"
#include "mzm/update_input.h"
#include "mzm/softreset_input.h"
#include "mzm/softreset.h"
#include "mzm/intro.h"
#include "mzm/in_game.h"
#include "mzm/chozodia_escape.h"
#include "mzm/ending_and_gallery.h"
#include "mzm/fusion_gallery.h"
#include "mzm/init_game.h"

#include "mzm/cutscenes/cutscene_utils.h"

#include "mzm/data/generic_data.h"

#include "mzm/constants/game_state.h"
#include "mzm/constants/samus.h"
#include "mzm/constants/sprite.h"

#include "mzm/structs/cutscene.h"
#include "mzm/structs/demo.h"
#include "mzm/structs/game_state.h"
#include "mzm/structs/samus.h"
#include "mzm/structs/sprite.h"

#include "mzm/modern/audio.h"
#include "mzm/modern/debug.h"

#include "mzm/menus/title_screen.h"
#include "mzm/menus/file_select.h"
#include "mzm/menus/pause_screen.h"
#include "mzm/menus/game_over.h"
#include "mzm/menus/erase_sram.h"

#include "mzm/audio/track_internal.h"

#include <stdio.h>
#include <windows.h>

#include "mzm/openal/al.h"
#include "mzm/openal/alc.h"

#include "mzm/GLFW/glfw3.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "mzm/imgui/cimgui.h"

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

GLFWwindow* gWindow;

u8 gTargetFps = 60;

int main(int argc, char** argv)
{
    {
        if (!glfwInit())
        {
            const char* error; glfwGetError(&error);
            fprintf(stderr, "glfwInit() failed: %s\n", error);
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        gWindow = glfwCreateWindow(SCREEN_SIZE_X_SUB_PIXEL, SCREEN_SIZE_Y_SUB_PIXEL, "MZM", NULL, NULL);
        if (!gWindow)
        {
            const char* error; glfwGetError(&error);
            fprintf(stderr, "glfwCreateWindow() failed: %s\n", error);
        }
        glfwMakeContextCurrent(gWindow);
        glfwSwapInterval(0);
    }

    gladLoadGL();
    // Setup Dear ImGui context
	ImGuiContext* ctx = igCreateContext(NULL);

	ImGuiIO* io = igGetIO();
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable viewports

    igStyleColorsDark(NULL);
	ImGui_ImplGlfw_InitForOpenGL(gWindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");

    u8 psf;
    
    SpriteRendererInitBuffers();

    InitAudio();

    //SoundPlay(1, 0);
    InitializeGame();

    glClearColor(0, 0, 0, 1);

    // Init windows timer for custom FPS
    TIMECAPS timeInfo;
    timeGetDevCaps(&timeInfo, sizeof(timeInfo));
    timeBeginPeriod(timeInfo.wPeriodMin);

    while (!glfwWindowShouldClose(gWindow))
    {
        DWORD frameStart = timeGetTime();

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        gVblankActive = FALSE;
        UpdateAudio();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        igNewFrame();

        PrintDebug_Samus();
        PrintDebug_Sprites();
        PrintDebug_GameInfo();
        PrintDebug_Hitboxes();

        if (gResetGame)
        {
            break;
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
        }

        gVBlankRequestFlag &= ~TRUE;
        gVblankActive = TRUE;

        igRender();

        ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
		GLFWwindow* ctxBackup = glfwGetCurrentContext();
        igUpdatePlatformWindows();
		igRenderPlatformWindowsDefault(NULL, NULL);
		glfwMakeContextCurrent(ctxBackup);

        DWORD diff = timeGetTime() - frameStart;
        // Compute the frame duration again each frame in case its value changed
        DWORD frameDuration = 1000 / gTargetFps;

        if (diff < frameDuration)
            Sleep(frameDuration - diff);

        glfwSwapBuffers(gWindow);
    }

    timeEndPeriod(timeInfo.wPeriodMin);

    ShutdownAudio();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igDestroyContext(ctx);

    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}
