#include "mzm/sprites_AI/area_banner.h"
#include "mzm/sprite_util.h"
#include "mzm/macros.h"

#include "mzm/data/sprites/area_banner.h"

#include "mzm/constants/sprite.h"

#include "mzm/structs/sprite.h"

/**
 * @brief 3c704 | a4 | Initializes an area banner sprite
 * 
 */
void AreaBannerInit(void)
{
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;

    gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
    gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
    gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 8);

    gCurrentSprite.hitboxTopOffset = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottomOffset = PIXEL_SIZE;
    gCurrentSprite.hitboxLeftOffset = -PIXEL_SIZE;
    gCurrentSprite.hitboxRightOffset = PIXEL_SIZE;

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.pose = AREA_BANNER_POSE_SPAWN;

    if (gCurrentSprite.roomSlot < LT_MOTHERSHIP)
    {
        // Area name, spawn at bottom
        gCurrentSprite.pOam = sAreaBannerOam_SpawnBottom;
        gCurrentSprite.workVariable = TRUE;
        gCurrentSprite.yPosition = 0x98;
        gCurrentSprite.xPosition = SCREEN_SIZE_X / 2;
    }
    else if ((gCurrentSprite.roomSlot == LT_SAVE_ROOM || gCurrentSprite.roomSlot == LT_MAP_ROOM) && gAlarmTimer != 0)
    {
        gCurrentSprite.status = 0; // Don't spawn save/map if alarm is active
    }
    else
    {
        // Spawn in middle
        gCurrentSprite.pOam = sAreaBannerOam_SpawnMiddle;
        gCurrentSprite.workVariable = FALSE;
        gCurrentSprite.yPosition = 0x36;
        gCurrentSprite.xPosition = SCREEN_SIZE_X / 2;
    }
}

/**
 * @brief 3c7a8 | 20 | Handles the area banner spawning
 * 
 */
void AreaBannerSpawn(void)
{
    gCurrentSprite.animationDurationCounter--;
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN; // Remove not drawn
    gCurrentSprite.pose = AREA_BANNER_POSE_SCROLLING_UP;
}

/**
 * @brief 3c7c8 | 60 | Handles the area banner scrolling up, determines the static behavior
 * 
 */
void AreaBannerScrollingUp(void)
{
    if (SpriteUtilCheckEndCurrentSpriteAnim())
    {
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.pose = AREA_BANNER_POSE_STATIC;

        // Set OAM and timer for how long the message stays
        if (gCurrentSprite.workVariable) // Position flag, 1 = on bottom, 0 = in middle
        {
            gCurrentSprite.pOam = sAreaBannerOam_StaticBottom;
            gCurrentSprite.timer = 120;
        }
        else
        {
            gCurrentSprite.pOam = sAreaBannerOam_StaticMiddle;
            if (gCurrentSprite.roomSlot == LT_SAVE_ROOM || gCurrentSprite.roomSlot == LT_MAP_ROOM)
                gCurrentSprite.timer = 50;
            else
                gCurrentSprite.timer = 90;
        }
    }
}

/**
 * @brief 3c828 | 44 | Handles the area banner being static
 * 
 */
void AreaBannerStatic(void)
{
    gCurrentSprite.timer--; // Timer for how long it stays
    if (gCurrentSprite.timer == 0)
    {
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.pose = AREA_BANNER_POSE_REMOVING;

        // Set OAM
        if (gCurrentSprite.workVariable)
            gCurrentSprite.pOam = sAreaBannerOam_RemovingBottom;
        else
            gCurrentSprite.pOam = sAreaBannerOam_RemovingMiddle;
    }
}

/**
 * @brief 3c86c | 18 | Checks if the removing anim ended
 * 
 */
void AreaBannerCheckRemovingAnimEnded(void)
{
    if (SpriteUtilCheckEndCurrentSpriteAnim())
        gCurrentSprite.status = 0; // Kill sprite
}

/**
 * @brief 3c884 | e0 | Area banner AI
 * 
 */
void AreaBanner(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            AreaBannerInit();
            break;

        case AREA_BANNER_POSE_SPAWN:
            AreaBannerSpawn();
            break;
        
        case AREA_BANNER_POSE_SCROLLING_UP:
            AreaBannerScrollingUp();
            break;

        case AREA_BANNER_POSE_STATIC:
            AreaBannerStatic();
            break;

        case AREA_BANNER_POSE_REMOVING:
            AreaBannerCheckRemovingAnimEnded();
            break;
    }
}
