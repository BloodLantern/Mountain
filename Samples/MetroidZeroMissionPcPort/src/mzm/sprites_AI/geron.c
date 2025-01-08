#include "mzm/sprites_AI/geron.h"
#include "mzm/sprites_AI/parasite.h"
#include "mzm/macros.h"
#include "mzm/sprite_util.h"

#include "mzm/data/sprites/geron.h"

#include "mzm/constants/sprite.h"
#include "mzm/constants/event.h"
#include "mzm/constants/clipdata.h"

#include "mzm/structs/sprite.h"
#include "mzm/structs/clipdata.h"

/**
 * @brief 448e0 | 344 | Geron AI 
 * 
 */
void Geron(void)
{
    u32 destroyed;
    u8 caa;
    u16 yPosition;
    u16 xPosition;
    u16 spriteTop;
    u16 spriteBottom;
    u16 spriteLeft;
    u16 spriteRight;
    u32 eventCheck;
    struct SpriteData* pSprite;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            destroyed = FALSE;
            // Check is destroyed
            if (gCurrentSprite.spriteId == PSPRITE_GERON_BRINSTAR_ROOM_15)
            {
                if (!EventFunction(EVENT_ACTION_CHECKING, EVENT_PLANT_DESTROYED_LAVA))
                    destroyed = FALSE;
                else
                    destroyed = TRUE;
            }
            else if (gCurrentSprite.spriteId == PSPRITE_GERON_BRINSTAR_ROOM_1C)
            {
                if (!EventFunction(EVENT_ACTION_CHECKING, EVENT_HIGH_JUMP_OBTAINED))
                {
                    gCurrentSprite.status = 0;
                    break;
                }

                if (EventFunction(EVENT_ACTION_CHECKING, EVENT_PLANT_DESTROYED_POST_VARIA))
                    destroyed = TRUE;
            }
            else if (gCurrentSprite.spriteId == PSPRITE_GERON_VARIA1)
            {
                if (EventFunction(EVENT_ACTION_CHECKING, EVENT_PLANT_DESTROYED_VARIA2))
                    destroyed = TRUE;
            }
            else if (gCurrentSprite.spriteId == PSPRITE_GERON_VARIA2)
            {
                if (EventFunction(EVENT_ACTION_CHECKING, EVENT_PLANT_DESTROYED_VARIA3))
                    destroyed = TRUE;
            }
            else if (gCurrentSprite.spriteId == PSPRITE_GERON_VARIA3)
            {
                if (EventFunction(EVENT_ACTION_CHECKING, EVENT_PLANT_DESTROYED_VARIA1))
                    destroyed = TRUE;
            }
            else
            {
                gCurrentSprite.status = 0;
                break;
            }

            gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 3);
            gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(0);
            gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE + QUARTER_BLOCK_SIZE);

            gCurrentSprite.hitboxTopOffset = -(BLOCK_SIZE * 3);
            gCurrentSprite.hitboxBottomOffset = 0;
            gCurrentSprite.hitboxLeftOffset = -(QUARTER_BLOCK_SIZE * 3);
            gCurrentSprite.hitboxRightOffset = (QUARTER_BLOCK_SIZE * 3);

            gCurrentSprite.drawOrder = 5;
            gCurrentSprite.currentAnimationFrame = 0;
            gCurrentSprite.animationDurationCounter = 0;

            gCurrentSprite.samusCollision = SSC_NONE;
            gCurrentSprite.arrayOffset = 0;

            if (destroyed)
            {
                // Set destroyed
                gCurrentSprite.pose = GERON_POSE_DESTROYED;
                gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
                gCurrentSprite.pOam = sGeronOAM_Destroyed;
            }
            else
            {
                // Set idle
                gCurrentSprite.pose = GERON_POSE_IDLE;
                gCurrentSprite.health = 1;
                gCurrentSprite.pOam = sGeronOAM_Idle;

                yPosition = gCurrentSprite.yPosition - (HALF_BLOCK_SIZE);
                xPosition = gCurrentSprite.xPosition;

                // Set collision
                caa = CAA_MAKE_NON_POWER_GRIP;

                gCurrentClipdataAffectingAction = caa;
                ClipdataProcess(yPosition, xPosition);

                gCurrentClipdataAffectingAction = caa;
                ClipdataProcess(yPosition - BLOCK_SIZE, xPosition);

                gCurrentClipdataAffectingAction = caa;
                ClipdataProcess(yPosition - (BLOCK_SIZE * 2), xPosition);
            }
            break;

        case GERON_POSE_IDLE:
            spriteTop = gCurrentSprite.yPosition + gCurrentSprite.hitboxTopOffset;
            spriteBottom = gCurrentSprite.yPosition + PIXEL_SIZE * 2;
            spriteLeft = gCurrentSprite.xPosition + gCurrentSprite.hitboxLeftOffset;
            spriteRight = gCurrentSprite.xPosition + gCurrentSprite.hitboxRightOffset;

            // Check make parasites grab geron
            for (pSprite = gSpriteData; pSprite < gSpriteData + MAX_AMOUNT_OF_SPRITES; pSprite++)
            {
                // Check not already grabbed
                if (pSprite->status & SPRITE_STATUS_EXISTS && pSprite->samusCollision == SSC_BUG)
                {
                    yPosition = pSprite->yPosition;
                    xPosition = pSprite->xPosition;

                    // Check colliding
                    if (spriteBottom > yPosition && spriteTop < yPosition && spriteRight > xPosition && spriteLeft < xPosition)
                    {
                        // Assign geron
                        pSprite->workVariable = gCurrentSprite.primarySpriteRamSlot;

                        // Set grabbed behavior
                        pSprite->pose = PARASITE_POSE_GERON_GRABBED_INIT;
                        pSprite->status |= SPRITE_STATUS_IGNORE_PROJECTILES;

                        // Set no collision to prevent being counted twice
                        pSprite->samusCollision = SSC_NONE;

                        // Increase amount of parasites
                        gCurrentSprite.arrayOffset++;
                    }
                }
            }

            if (gCurrentSprite.arrayOffset >= 4)
            {
                // Set getting destroyed
                gCurrentSprite.pose = GERON_POSE_GETTING_DESTROYED;

                gCurrentSprite.pOam = sGeronOAM_GettingDestroyed;
                gCurrentSprite.currentAnimationFrame = 0;
                gCurrentSprite.animationDurationCounter = 0;

                gCurrentSprite.timer = 200;
                SoundPlayNotAlreadyPlaying(0x26C);
            }
            else
            {
                // Check should shake 
                if (SPRITE_HAS_ISFT(gCurrentSprite))
                {
                    if (SPRITE_HAS_ISFT(gCurrentSprite) == 0x2)
                    {
                        // Set shaking
                        gCurrentSprite.pOam = sGeronOAM_Shaking;
                        gCurrentSprite.currentAnimationFrame = 0;
                        gCurrentSprite.animationDurationCounter = 0;
                        SoundPlayNotAlreadyPlaying(0x26B);
                    }
                }
                else
                {
                    if (gCurrentSprite.pOam == sGeronOAM_Shaking && SpriteUtilCheckEndCurrentSpriteAnim())
                    {
                        // Set idle
                        gCurrentSprite.pOam = sGeronOAM_Idle;
                        gCurrentSprite.currentAnimationFrame = 0;
                        gCurrentSprite.animationDurationCounter = 0;
                    }
                }
            }
            break;
        
        case GERON_POSE_GETTING_DESTROYED:
            gCurrentSprite.timer--;
            if (gCurrentSprite.timer == 0)
            {
                gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
                gCurrentSprite.pose = GERON_POSE_DELAY_BEFORE_DESTROYED;

                yPosition = gCurrentSprite.yPosition - HALF_BLOCK_SIZE;
                xPosition = gCurrentSprite.xPosition;

                // Remove collision
                gCurrentClipdataAffectingAction = CAA_REMOVE_SOLID;
                ClipdataProcess(yPosition, xPosition);

                gCurrentClipdataAffectingAction = CAA_REMOVE_SOLID;
                ClipdataProcess(yPosition - BLOCK_SIZE, xPosition);

                gCurrentClipdataAffectingAction = CAA_REMOVE_SOLID;
                ClipdataProcess(yPosition - (BLOCK_SIZE * 2), xPosition);

                // Set event
                if (gCurrentSprite.spriteId == PSPRITE_GERON_BRINSTAR_ROOM_15)
                    EventFunction(EVENT_ACTION_SETTING, EVENT_PLANT_DESTROYED_LAVA);
                else if (gCurrentSprite.spriteId == PSPRITE_GERON_BRINSTAR_ROOM_1C)
                    EventFunction(EVENT_ACTION_SETTING, EVENT_PLANT_DESTROYED_POST_VARIA);
                else if (gCurrentSprite.spriteId == PSPRITE_GERON_VARIA1)
                    EventFunction(EVENT_ACTION_SETTING, EVENT_PLANT_DESTROYED_VARIA2);
                else if (gCurrentSprite.spriteId == PSPRITE_GERON_VARIA2)
                    EventFunction(EVENT_ACTION_SETTING, EVENT_PLANT_DESTROYED_VARIA3);
                else if (gCurrentSprite.spriteId == PSPRITE_GERON_VARIA3)
                    EventFunction(EVENT_ACTION_SETTING, EVENT_PLANT_DESTROYED_VARIA1);
            }
            break;

        case GERON_POSE_DELAY_BEFORE_DESTROYED:
            if (SpriteUtilCheckEndCurrentSpriteAnim())
            {
                // Set destroyed
                gCurrentSprite.pose = GERON_POSE_DESTROYED;
                gCurrentSprite.pOam = sGeronOAM_Destroyed;
                gCurrentSprite.currentAnimationFrame = 0;
                gCurrentSprite.animationDurationCounter = 0;
            }
            break;
    }
}
