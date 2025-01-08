#include "mzm/sprites_AI/multiviola.h"
#include "mzm/macros.h"
#include "mzm/sprite_util.h"

#include "mzm/data/sprites/multiviola.h"
#include "mzm/data/sprite_data.h"

#include "mzm/constants/particle.h"
#include "mzm/constants/clipdata.h"
#include "mzm/constants/sprite.h"
#include "mzm/constants/sprite_util.h"

#include "mzm/structs/sprite.h"

/**
 * @brief 1e854 | 70 | Initializes a multiviola sprite
 * 
 */
void MultiviolaInit(void)
{
    gCurrentSprite.drawDistanceTopOffset = 0x20;
    gCurrentSprite.drawDistanceBottomOffset = 0xC;
    gCurrentSprite.drawDistanceHorizontalOffset = 0x10;

    gCurrentSprite.hitboxTopOffset = -0x20;
    gCurrentSprite.hitboxBottomOffset = 0x20;
    gCurrentSprite.hitboxLeftOffset = -0x20;
    gCurrentSprite.hitboxRightOffset = 0x20;

    gCurrentSprite.pOam = sMultiviolaOAM_Moving;
    gCurrentSprite.animationDurationCounter = 0x0;
    gCurrentSprite.currentAnimationFrame = gCurrentSprite.primarySpriteRamSlot * 2;

    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    SpriteUtilMakeSpriteFaceSamusXFlip();
    gCurrentSprite.pose = MULTIVIOLA_POSE_MOVING;
}

/**
 * @brief 1e8c4 | 110 | Handles a multiviola moving
 * 
 */
void MultiviolaMove(void)
{
    u8 isBouncing;
    u16 yMovement;

    isBouncing = FALSE;
    yMovement = 0x3;

    if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
    {
        // Move right
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + gCurrentSprite.hitboxRightOffset);
        if (gPreviousCollisionCheck == COLLISION_AIR)
            gCurrentSprite.xPosition += 0x3;
        else
        {
            // Bounce X
            gCurrentSprite.status &= ~SPRITE_STATUS_XFLIP;
            isBouncing++;
        }
    }
    else
    {
        // Move left
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + gCurrentSprite.hitboxLeftOffset);
        if (gPreviousCollisionCheck == COLLISION_AIR)
            gCurrentSprite.xPosition -= 0x3;
        else
        {
            // Bounce X
            gCurrentSprite.status |= SPRITE_STATUS_XFLIP;
            isBouncing++;
        }
    }

    if (gCurrentSprite.status & SPRITE_STATUS_UNKNOWN_400)
    {
        // Move up
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxTopOffset, gCurrentSprite.xPosition);
        if (gPreviousCollisionCheck == COLLISION_AIR)
            gCurrentSprite.yPosition -= yMovement;
        else
        {
            // Bounce Y
            gCurrentSprite.status &= ~SPRITE_STATUS_UNKNOWN_400;
            isBouncing++;
        }
    }
    else
    {
        // Move down
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxBottomOffset, gCurrentSprite.xPosition);
        if (gPreviousCollisionCheck == COLLISION_AIR)
            gCurrentSprite.yPosition += yMovement;
        else
        {
            // Bounce Y
            gCurrentSprite.status |= SPRITE_STATUS_UNKNOWN_400;
            isBouncing++;
        }
    }

    if (isBouncing && gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
        SoundPlayNotAlreadyPlaying(0x152);
}

/**
 * @brief 1e9cc | 4 | Unused multiviola sprite function
 * 
 */
void MultivioaUnused_Empty1(void)
{
    return;
}


/**
 * @brief 1e9d0 | 4 | Unused multiviola sprite function
 * 
 */
void MultivioaUnused_Empty2(void)
{
    return;
}

/**
 * @brief 1e9d4 | 90 | Multiviola AI
 * 
 */
void Multiviola(void)
{
    if (gCurrentSprite.properties & SP_DAMAGED)
    {
        gCurrentSprite.properties &= ~SP_DAMAGED;
        if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
            SoundPlayNotAlreadyPlaying(0x153);
    }

    if (gCurrentSprite.freezeTimer != 0x0)
    {
        SpriteUtilUpdateFreezeTimer();
        SpriteUtilUpdateSecondarySpriteFreezeTimerOfCurrent(SSPRITE_MULTIVIOLA_UNUSED, gCurrentSprite.primarySpriteRamSlot);
    }
    else
    {
        if (SpriteUtilIsSpriteStunned())
            return;

        switch (gCurrentSprite.pose)
        {
            default:
                SpriteUtilSpriteDeath(DEATH_NORMAL, gCurrentSprite.yPosition, gCurrentSprite.xPosition, TRUE, PE_SPRITE_EXPLOSION_BIG);
                break;
                
            case 0x0:
                MultiviolaInit();
                break;

            case MULTIVIOLA_POSE_MOVING:
                MultiviolaMove();
        }
    }
}

/**
 * @brief 1ea64 | 4 | Unused multiviola sprite AI
 * 
 */
void MultiviolaUnused(void)
{
    return;
}