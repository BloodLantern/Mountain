#include "mzm/gba.h"
#include "mzm/hud.h"
#include "mzm/hud_generic.h"
#include "mzm/escape.h" // Required

#include "mzm/data/hud_data.h"

#include "mzm/constants/escape.h"
#include "mzm/constants/game_state.h"
#include "mzm/constants/minimap.h"
#include "mzm/constants/particle.h"

#include "mzm/structs/escape.h"
#include "mzm/structs/game_state.h"
#include "mzm/structs/minimap.h"
#include "mzm/structs/hud.h"
#include "mzm/structs/particle.h"

/**
 * @brief 53c68 | 24 | Loads the common sprites graphics
 * 
 */
void HudGenericLoadCommonSpriteGfx(void)
{
    gCommonSpriteGraphics = SpriteRendererLoadGraphics("data/hud/Common.gfx", FALSE);
    gCommonSpritePalette = SpriteRendererLoadPalette("data/hud/Common.pal");
}

/**
 * @brief 53c8c | 24 | Resets the refill animations
 * 
 */
void HudGenericResetRefillAnimations(void)
{
    gEnergyRefillAnimation = 0;
    gMissileRefillAnimation = 0;
    gSuperMissileRefillAnimation = 0;
    gPowerBombRefillAnimation = 0;
}

/**
 * @brief 53cb0 | 120 | Resets the HUD data and the particles
 * 
 */
void HudGenericResetHUDData(void)
{
    struct ParticleEffect* pParticle;

    if (gGameModeSub3 == 0 || gTourianEscapeCutsceneStage != 0)
    {
        for (pParticle = gParticleEffects; pParticle < gParticleEffects + MAX_AMOUNT_OF_PARTICLES; pParticle++)
            pParticle->status = 0;

        gEnergyDigits.ones = 15;
        gEnergyDigits.tens = 15;
        gEnergyDigits.hundreds = 15;
        gEnergyDigits.thousands = 15;

        gMaxEnergyDigits.ones = 15;
        gMaxEnergyDigits.tens = 15;
        gMaxEnergyDigits.hundreds = 15;
        gMaxEnergyDigits.thousands = 15;

        gMissileDigits.ones = 15;
        gMissileDigits.tens = 15;
        gMissileDigits.hundreds = 15;

        gPowerBombDigits.ones = 15;
        gPowerBombDigits.tens = 15;
        gPowerBombDigits.hundreds = 15;

        gSuperMissileDigits.ones = 15;
        gSuperMissileDigits.tens = 15;
        gSuperMissileDigits.hundreds = 15;

        gMissileHighlightStatus = 0;
        gPowerBombHighlightStatus = 0;
        gSuperMissileHighlightStatus = 0;

        gUpdateMinimapFlag = MINIMAP_UPDATE_FLAG_LOWER_LINE;
        gCurrentEscapeStatus = ESCAPE_STATUS_NONE;

        HudGenericResetRefillAnimations();
    }
    else if (gPauseScreenFlag == PAUSE_SCREEN_NONE)
    {
        HudGenericResetRefillAnimations();

        for (pParticle = gParticleEffects; pParticle < gParticleEffects + MAX_AMOUNT_OF_PARTICLES; pParticle++)
        {
            if (pParticle->effect < PE_CHARGING_BEAM)
                pParticle->status = 0;
            else if (pParticle->effect == PE_ESCAPE && EscapeDetermineTimer() == ESCAPE_NONE)
                pParticle->status = 0;
        }
    }
}
