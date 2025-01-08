#include "mzm/sprites_AI/elevator_pad.h"
#include "mzm/macros.h"
#include "mzm/sprite_util.h"

#include "mzm/data/sprites/elevator_pad.h"

#include "mzm/constants/sprite.h"
#include "mzm/constants/samus.h"

#include "mzm/structs/sprite.h"
#include "mzm/structs/samus.h"

/**
 * @brief 2872c | b8 | Elevator pad AI
 * 
 */
void ElevatorPad(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.pose == SPRITE_POSE_UNINITIALIZED)
    {
        gCurrentSprite.yPosition -= PIXEL_SIZE * 2;
        gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;
        gCurrentSprite.samusCollision = SSC_NONE;
        gCurrentSprite.pose = 0x9;

        gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(PIXEL_SIZE);
        gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(HALF_BLOCK_SIZE);
        gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);

        gCurrentSprite.hitboxTopOffset = -PIXEL_SIZE;
        gCurrentSprite.hitboxBottomOffset = PIXEL_SIZE;
        gCurrentSprite.hitboxLeftOffset = -PIXEL_SIZE;
        gCurrentSprite.hitboxRightOffset = PIXEL_SIZE;

        gCurrentSprite.pOam = sElevatorPadOAM_Idle;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
    }

    if (gSamusData.pose == SPOSE_USING_AN_ELEVATOR)
    {
        // Sync position
        gCurrentSprite.yPosition = gSamusData.yPosition;
        gCurrentSprite.xPosition = gSamusData.xPosition;

        if (gCurrentSprite.pOam == sElevatorPadOAM_Idle)
        {
            // Set moving
            gCurrentSprite.pOam = sElevatorPadOAM_Moving;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
        }
    }
    else
    {
        if (gCurrentSprite.pOam == sElevatorPadOAM_Moving)
        {
            // Set idle
            gCurrentSprite.pOam = sElevatorPadOAM_Idle;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
        }
    }
}
