#include "mzm/sprites_AI/elevator_statue.h"
#include "mzm/macros.h"
#include "mzm/sprite_util.h"

#include "mzm/data/sprites/elevator_statue.h"

#include "mzm/constants/clipdata.h"
#include "mzm/constants/sprite.h"
#include "mzm/constants/event.h"
#include "mzm/constants/samus.h"

#include "mzm/structs/sprite.h"
#include "mzm/structs/samus.h"
#include "mzm/structs/clipdata.h"

/**
 * @brief 47ebc | 50 | Updates the clipdata of the statue debris on the ground
 * 
 * @param caa Clipdata Affecting Action
 */
void ElevatorStatueChangeTwoGroundCCAA(u8 caa)
{
    u16 yPosition;
    u16 xPosition;

    yPosition = gCurrentSprite.yPosition - HALF_BLOCK_SIZE;
    xPosition = gCurrentSprite.xPosition - BLOCK_SIZE;

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition, xPosition - BLOCK_SIZE); // Right block
    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition, xPosition - (BLOCK_SIZE * 2)); // Left block
}

/**
 * @brief 47f0c | 64 | Updates the clipdata of the Kraid elevator statue
 * 
 * @param caa Clipdata Affecting Action
 */
void KraidElevatorStatueChangeCAA(u8 caa)
{
    u16 yPosition;
    u16 xPosition;

    yPosition = gCurrentSprite.yPosition - HALF_BLOCK_SIZE;
    xPosition = gCurrentSprite.xPosition - BLOCK_SIZE;
    
    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 2), xPosition - BLOCK_SIZE); // Head block

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 3), xPosition); // Bottom

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 4), xPosition); // Middle

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 5), xPosition); // Top
}

/**
 * @brief 47f70 | 4c | Initializes a Kraid elevator statue to be fallen
 * 
 */
void KraidElevatorStatueFallenInit(void)
{
    gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 2);
    gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE + HALF_BLOCK_SIZE);

    gCurrentSprite.hitboxTopOffset = -(QUARTER_BLOCK_SIZE * 3 + PIXEL_SIZE * 3); // Hitbox even though there's no samus collision?
    gCurrentSprite.hitboxBottomOffset = 0;
    gCurrentSprite.hitboxLeftOffset = -(BLOCK_SIZE * 4);
    gCurrentSprite.hitboxRightOffset = BLOCK_SIZE + HALF_BLOCK_SIZE;

    gCurrentSprite.pOam = sKraidElevatorStatueOAM_Fallen;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.animationDurationCounter = 0;

    gCurrentSprite.pose = ELEVATOR_STATUE_POSE_IDLE;
    ElevatorStatueChangeTwoGroundCCAA(CAA_MAKE_NON_POWER_GRIP);
}

/**
 * @brief 47fbc | 8c | Initializes a Kraid elevator statue sprite
 * 
 */
void KraidElevatorStatueInit(void)
{
    gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 5);
    gCurrentSprite.bgPriority = 1;
    gCurrentSprite.drawOrder = 2;

    gCurrentSprite.properties |= (SP_ALWAYS_ACTIVE | SP_SOLID_FOR_PROJECTILES);
    gCurrentSprite.samusCollision = SSC_NONE;

    if (EventFunction(EVENT_ACTION_CHECKING, EVENT_KRAID_ELEVATOR_STATUE_DESTROYED))
    {
        KraidElevatorStatueFallenInit();
        return;
    }

    gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 6);
    gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(0);

    gCurrentSprite.hitboxTopOffset = -(BLOCK_SIZE * 6); // Hitbox even though there's no samus collision?
    gCurrentSprite.hitboxBottomOffset = 0;
    gCurrentSprite.hitboxLeftOffset = -BLOCK_SIZE;
    gCurrentSprite.hitboxRightOffset = BLOCK_SIZE;

    gCurrentSprite.pOam = sKraidElevatorStatueOAM_Idle;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.animationDurationCounter = 0;

    gCurrentSprite.pose = ELEVATOR_STATUE_POSE_CHECK_FALL;

    KraidElevatorStatueChangeCAA(CAA_MAKE_NON_POWER_GRIP); // Set collision
}

/**
 * @brief 48048 | 34 | Checks if the Kraid elevator statue should fall
 * 
 */
void KraidElevatorStatueCheckShouldFall(void)
{
    // Samus not using the elevator and kraid dead
    if (gSamusData.pose != SPOSE_USING_AN_ELEVATOR && EventFunction(EVENT_ACTION_CHECKING, EVENT_KRAID_KILLED))
    {
        // Set falling behavior
        gCurrentSprite.pose = ELEVATOR_STATUE_POSE_DELAY_BEFORE_FALLING;
        gCurrentSprite.timer = 16; // Delay before falling
    }
}

/**
 * @brief 4807c | 54 | Handles the delay before the Kraid elevator statue starts falling
 * 
 */
void KraidElevatorStatueDelayBeforeFalling(void)
{
    gCurrentSprite.timer--;
    if (gCurrentSprite.timer == 0)
    {
        // Set falling behavior
        gCurrentSprite.pOam = sKraidElevatorStatueOAM_Falling;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.animationDurationCounter = 0;

        gCurrentSprite.pose = ELEVATOR_STATUE_POSE_FALLING;

        // Set event
        EventFunction(EVENT_ACTION_SETTING, EVENT_KRAID_ELEVATOR_STATUE_DESTROYED);

        // Remove collison
        KraidElevatorStatueChangeCAA(CAA_REMOVE_SOLID);

        // Play effects
        ScreenShakeStartHorizontal(10, 0x80 | 1);
        SoundPlay(0x11E);
    }
}

/**
 * @brief 480d0 | a4 | Handles the Kraid elevator statue falling
 * 
 */
void KraidElevatorStatueFalling(void)
{
    switch (gCurrentSprite.currentAnimationFrame)
    {
        case 1:
            if (gCurrentSprite.animationDurationCounter == 3)
            {
                // Spawn kraid debris
                SpriteSpawnSecondary(SSPRITE_ELEVATOR_STATUE_DEBRIS, ELEVATOR_STATUE_DEBRIS_PART_KRAID,
                    gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                    gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            }
            break;

        case 4:
            // Update draw distance
            gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 4);
            gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
            break;

        case 6:
            // Update draw distance
            gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 3);
            gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE + HALF_BLOCK_SIZE);

            if (gCurrentSprite.animationDurationCounter == 2)
            {
                // Start screen shake and spawn dust debris
                ScreenShakeStartVertical(20, 0x80 | 1);

                SpriteSpawnSecondary(SSPRITE_ELEVATOR_STATUE_DEBRIS, ELEVATOR_STATUE_DEBRIS_PART_DUST,
                    0, gCurrentSprite.primarySpriteRamSlot,
                    gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            }
    }

    // Check set fallen
    if (SpriteUtilCheckEndCurrentSpriteAnim())
        KraidElevatorStatueFallenInit();
}

/**
 * @brief 48174 | 64 | Updates the clipdata of the Ridley elevator statue
 * 
 * @param caa Clipdata Affecting Action
 */
void RidleyElevatorStatueChangeCCAA(u8 caa)
{
    u16 yPosition;
    u16 xPosition;

    yPosition = gCurrentSprite.yPosition - HALF_BLOCK_SIZE;
    xPosition = gCurrentSprite.xPosition - (BLOCK_SIZE * 2);

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 2), xPosition); // Bottom block

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 3), xPosition); // Middle bottom block

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 4), xPosition); // Middle top block

    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE * 5), xPosition); // Top block
}

/**
 * @brief 481d8 | 4c | Initializes the Ridley elevator statue to be fallen
 * 
 */
void RidleyElevatorStatueFallenInit(void)
{
    gCurrentSprite.drawDistanceTopOffset = HALF_BLOCK_SIZE + PIXEL_SIZE * 2;
    gCurrentSprite.drawDistanceBottomOffset = QUARTER_BLOCK_SIZE + PIXEL_SIZE * 2;

    gCurrentSprite.hitboxTopOffset = -(QUARTER_BLOCK_SIZE * 3 + PIXEL_SIZE * 3); // Hitbox even though there's no samus collision?
    gCurrentSprite.hitboxBottomOffset = 0;
    gCurrentSprite.hitboxLeftOffset = -(BLOCK_SIZE * 4);
    gCurrentSprite.hitboxRightOffset = BLOCK_SIZE + HALF_BLOCK_SIZE;

    gCurrentSprite.pOam = sRidleyElevatorStatueOAM_Fallen;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.animationDurationCounter = 0;

    gCurrentSprite.pose = ELEVATOR_STATUE_POSE_IDLE;
    ElevatorStatueChangeTwoGroundCCAA(CAA_MAKE_NON_POWER_GRIP);
}

/**
 * @brief 48224 | 8c | Initializes the Ridley elevator sprite
 * 
 */
void RidleyElevatorStatueInit(void)
{
    gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 5);

    gCurrentSprite.bgPriority = 1;
    gCurrentSprite.drawOrder = 2;

    gCurrentSprite.properties |= (SP_ALWAYS_ACTIVE | SP_SOLID_FOR_PROJECTILES);
    gCurrentSprite.samusCollision = SSC_NONE;

    if (EventFunction(EVENT_ACTION_CHECKING, EVENT_RIDLEY_ELEVATOR_STATUE_DESTROYED))
    {
        RidleyElevatorStatueFallenInit();
        return;
    }

    gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 6);
    gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(0);

    gCurrentSprite.hitboxTopOffset = -(BLOCK_SIZE * 6); // Hitbox even though there's no samus collision?
    gCurrentSprite.hitboxBottomOffset = 0;
    gCurrentSprite.hitboxLeftOffset = -BLOCK_SIZE;
    gCurrentSprite.hitboxRightOffset = BLOCK_SIZE;

    gCurrentSprite.pOam = sRidleyElevatorStatueOAM_Idle;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.animationDurationCounter = 0;

    gCurrentSprite.pose = ELEVATOR_STATUE_POSE_CHECK_FALL;
    RidleyElevatorStatueChangeCCAA(CAA_MAKE_NON_POWER_GRIP); // Set collision
}

/**
 * @brief 482b0 | 34 | Checks if the Ridley elevator statue should fall
 * 
 */
void RidleyElevatorStatueCheckShouldFall(void)
{
    // Samus not using the elevator and ridley dead
    if (gSamusData.pose != SPOSE_USING_AN_ELEVATOR && EventFunction(EVENT_ACTION_CHECKING, EVENT_RIDLEY_KILLED))
    {
        // Set falling behavior
        gCurrentSprite.pose = ELEVATOR_STATUE_POSE_DELAY_BEFORE_FALLING;
        gCurrentSprite.timer = 16; // Timer before falling
    }
}

/**
 * @brief 482e4 | 54 | Handles the delay before the Ridley elevator statue starts falling
 * 
 */
void RidleyElevatorStatueDelayBeforeFalling(void)
{
    gCurrentSprite.timer--;
    if (gCurrentSprite.timer == 0)
    {
        // Set falling behavior
        gCurrentSprite.pOam = sRidleyElevatorStatueOAM_Falling;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.animationDurationCounter = 0;

        gCurrentSprite.pose = ELEVATOR_STATUE_POSE_FALLING;

        // Set event
        EventFunction(EVENT_ACTION_SETTING, EVENT_RIDLEY_ELEVATOR_STATUE_DESTROYED);

        // Remove collision
        RidleyElevatorStatueChangeCCAA(CAA_REMOVE_SOLID);

        // Play effects
        ScreenShakeStartHorizontal(10, 0x80 | 1);
        SoundPlay(0x11F);
    }
}

/**
 * @brief 48338 | b8 | Handles the Ridley elevator statue falling
 * 
 */
void RidleyElevatorStatueFalling(void)
{
    switch (gCurrentSprite.currentAnimationFrame)
    {
        case 1:
            if (gCurrentSprite.animationDurationCounter == 3)
            {
                // Spawn ridley debris
                SpriteSpawnSecondary(SSPRITE_ELEVATOR_STATUE_DEBRIS, ELEVATOR_STATUE_DEBRIS_PART_RIDLEY,
                    gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                    gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            }
            break;

        case 4:
            // Update draw distance
            gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 5 + HALF_BLOCK_SIZE);
            gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(HALF_BLOCK_SIZE);
            break;

        case 5:
            gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 5);
            gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
            break;

        case 0x6:
            // Update draw distance
            gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 4 + HALF_BLOCK_SIZE);
            gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE + HALF_BLOCK_SIZE);

            if (gCurrentSprite.animationDurationCounter == 2)
            {
                // Start screen shake and spawn dust debris
                ScreenShakeStartVertical(20, 0x80 | 1);

                SpriteSpawnSecondary(SSPRITE_ELEVATOR_STATUE_DEBRIS, ELEVATOR_STATUE_DEBRIS_PART_DUST,
                    0, gCurrentSprite.primarySpriteRamSlot,
                    gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            }
    }

    // Check set fallen
    if (SpriteUtilCheckEndCurrentSpriteAnim())
        RidleyElevatorStatueFallenInit();
}

/**
 * @brief 483f0 | 48 | Kraid elevator statue AI
 * 
 */
void KraidElevatorStatue(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            KraidElevatorStatueInit();
            break;

        case ELEVATOR_STATUE_POSE_CHECK_FALL:
            KraidElevatorStatueCheckShouldFall();
            break;

        case ELEVATOR_STATUE_POSE_DELAY_BEFORE_FALLING:
            KraidElevatorStatueDelayBeforeFalling();
            break;

        case ELEVATOR_STATUE_POSE_FALLING:
            KraidElevatorStatueFalling();
    }
}

/**
 * @brief 48438 | 48 | Ridley elevator statue AI
 * 
 */
void RidleyElevatorStatue(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            RidleyElevatorStatueInit();
            break;

        case ELEVATOR_STATUE_POSE_CHECK_FALL:
            RidleyElevatorStatueCheckShouldFall();
            break;

        case ELEVATOR_STATUE_POSE_DELAY_BEFORE_FALLING:
            RidleyElevatorStatueDelayBeforeFalling();
            break;

        case ELEVATOR_STATUE_POSE_FALLING:
            RidleyElevatorStatueFalling();
    }
}

/**
 * @brief 48480 | cc | Elevator status debris AI
 * 
 */
void ElevatorStatueDebris(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
            gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;

            gCurrentSprite.hitboxTopOffset = 0;
            gCurrentSprite.hitboxBottomOffset = 0;
            gCurrentSprite.hitboxLeftOffset = 0;
            gCurrentSprite.hitboxRightOffset = 0;

            gCurrentSprite.pose = ELEVATOR_STATUE_DEBRIS_POSE_IDLE;
            gCurrentSprite.samusCollision = SSC_NONE;
            gCurrentSprite.bgPriority = 1;

            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;

            // Set data depending on part
            if (gCurrentSprite.roomSlot == ELEVATOR_STATUE_DEBRIS_PART_DUST)
            {
                gCurrentSprite.drawOrder = 1;

                gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 3 + HALF_BLOCK_SIZE);
                gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
                gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 5);

                gCurrentSprite.pOam = sElevatorStatueDebrisOAM_Dust;
            }
            else
            {
                gCurrentSprite.drawOrder = 5;

                gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 6);
                gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(HALF_BLOCK_SIZE);
                gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 2);

                if (gCurrentSprite.roomSlot == ELEVATOR_STATUE_DEBRIS_PART_KRAID)
                    gCurrentSprite.pOam = sElevatorStatueDebrisOAM_Kraid;
                else
                    gCurrentSprite.pOam = sElevatorStatueDebrisOAM_Ridley;
            }
            break;

        case ELEVATOR_STATUE_DEBRIS_POSE_IDLE:
            // Kill if animation ended
            if (SpriteUtilCheckEndCurrentSpriteAnim())
                gCurrentSprite.status = 0;
    }
}
