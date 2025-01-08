#include "mzm/sprites_AI/security_gate.h"
#include "mzm/sprite_util.h"

#include "mzm/data/sprites/security_gate.h"

#include "mzm/constants/clipdata.h"
#include "mzm/constants/sprite.h"
#include "mzm/constants/sprite_util.h"
#include "mzm/constants/particle.h"

#include "mzm/structs/clipdata.h"
#include "mzm/structs/sprite.h"

/**
 * @brief 2eaf8 | 50 | Updates the clipdata of the security gate
 * 
 * @param caa Clipdata affecting action
 */
void SecurityGateChangeCCAA(u8 caa)
{
    u16 yPosition;
    u16 xPosition;

    yPosition = gCurrentSprite.yPosition;
    xPosition = gCurrentSprite.xPosition;

    // Bottom
    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (HALF_BLOCK_SIZE), xPosition);
    // Middle bottom
    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE), xPosition);
    // Middle top
    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - ((BLOCK_SIZE * 2) + HALF_BLOCK_SIZE), xPosition);
    // Top
    gCurrentClipdataAffectingAction = caa;
    ClipdataProcess(yPosition - ((BLOCK_SIZE * 3) + HALF_BLOCK_SIZE), xPosition);
}

/**
 * 2eb48 | 40 | Opens the gate
 * 
 */
void SecurityGateOpen(void)
{
    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
    gCurrentSprite.pOam = sSceurityGateOAM_Opened;
    gCurrentSprite.animationDurationCounter = 0x0;
    gCurrentSprite.currentAnimationFrame = 0x0;
    gCurrentSprite.pose = 0x27;
    SecurityGateChangeCCAA(CAA_REMOVE_SOLID); // Remove collision
    SoundPlayNotAlreadyPlaying(0x225);
}

/**
 * 2eb88 | 38 | Starts the closing of the gate
 * 
 */
void SecurityGateStartClosing(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;
    gCurrentSprite.pOam = sSecurityGateOAM_Closing;
    gCurrentSprite.animationDurationCounter = 0x0;
    gCurrentSprite.currentAnimationFrame = 0x0;
    gCurrentSprite.pose = 0x23;
    SoundPlayNotAlreadyPlaying(0x109);
}

/**
 * 2ebc0 | a8 | Initializes a security gate default open sprite
 * 
 */
void SecurityGateDefaultOpenInit(void)
{
    if (gAlarmTimer != 0x0) // Check if should be closed or open
    {
        gCurrentSprite.pOam = sSecurityGateOAM_Closed;
        gCurrentSprite.pose = 0x25;
        gCurrentSprite.timer = 0x1;
        SecurityGateChangeCCAA(CAA_MAKE_NON_POWER_GRIP); // Set collision
    }
    else
    {
        gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
        gCurrentSprite.pOam = sSecurityGateOAM_Opened;
        gCurrentSprite.pose = 0x9;
    }

    gCurrentSprite.hitboxTopOffset = -0x100;
    gCurrentSprite.hitboxBottomOffset = 0x0;
    gCurrentSprite.hitboxLeftOffset = -0x18;
    gCurrentSprite.hitboxRightOffset = 0x18;
    gCurrentSprite.drawDistanceTopOffset = 0x40;
    gCurrentSprite.drawDistanceBottomOffset = 0x8;
    gCurrentSprite.drawDistanceHorizontalOffset = 0x8;
    gCurrentSprite.animationDurationCounter = 0x0;
    gCurrentSprite.currentAnimationFrame = 0x0;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.health = 0x1;
    gCurrentSprite.drawOrder = 0x3;
    gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;
}

/**
 * 2ec68 | 18 | Checks if the alarm timer is different than 0, if yes closes the gate
 * 
 */
void SecurityGateDefaultOpenCheckAlarm(void)
{
    if (gAlarmTimer != 0x0)
        SecurityGateStartClosing();
}

/**
 * 2ec80 | 38 | Checks if the closing animation has ended
 * 
 */
void SecurityGateCheckClosingAnimEnded(void)
{
    if (SpriteUtilCheckEndCurrentSpriteAnim())
    {
        gCurrentSprite.pOam = sSecurityGateOAM_Closed;
        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;
        gCurrentSprite.pose = 0x25;
        gCurrentSprite.timer = 0x0;
        gCurrentSprite.arrayOffset = 0x0;
    }
}

/**
 * 2ecb8 | 60 | Called after the alarm is done, opens the gate if necessary
 * 
 */
void SecurityGateDefaultOpenOpenAfterAlarm(void)
{
    if (gCurrentSprite.timer == 0x0 && !SpriteCheckCollidingWithSamusDrawing()) // ?
    {
        SecurityGateChangeCCAA(CAA_MAKE_NON_POWER_GRIP);
        gCurrentSprite.timer++;
    }

    if (gAlarmTimer == 0x0)
    {
        gCurrentSprite.arrayOffset++;
        if (gCurrentSprite.arrayOffset > 0x28)
            SecurityGateOpen();
    }
    else
        gCurrentSprite.arrayOffset = 0x0;
}

/**
 * 2ed18 | 28 | Checks if the opening animation has ended
 * 
 */
void SecurityGateCheckOpeningAnimEnded(void)
{
    if (SpriteUtilCheckEndCurrentSpriteAnim())
    {
        gCurrentSprite.pOam = sSecurityGateOAM_Opened;
        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;
        gCurrentSprite.pose = 0x9;
    }
}

/**
 * 2ed40 | 40 | Handles the death of the security gate, unused
 * 
 */
void SecurityGateDeath(void)
{
    u16 yPosition;
    u16 xPosition;

    SecurityGateChangeCCAA(CAA_REMOVE_SOLID);
    yPosition = gCurrentSprite.yPosition - 0x40;
    xPosition = gCurrentSprite.xPosition;
    ParticleSet(yPosition, xPosition, PE_SPRITE_EXPLOSION_HUGE);
    SpriteUtilSpriteDeath(DEATH_NORMAL, yPosition - 0x60, xPosition, TRUE, PE_SPRITE_EXPLOSION_BIG);
}

/**
 * 2ed80 | a4 | Initializes a security gate default closed sprite
 * 
 */
void SecurityGateDefaultClosedInit(void)
{
    if (gAlarmTimer != 0x0)
    {
        gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
        gCurrentSprite.pOam = sSecurityGateOAM_Opened;
        gCurrentSprite.pose = 0x9;
    }
    else
    {
        gCurrentSprite.pOam = sSecurityGateOAM_Closed;
        gCurrentSprite.pose = 0x25;
        gCurrentSprite.timer = 0x1;
        SecurityGateChangeCCAA(CAA_MAKE_NON_POWER_GRIP);
    }

    gCurrentSprite.hitboxTopOffset = -0x100;
    gCurrentSprite.hitboxBottomOffset = 0x0;
    gCurrentSprite.hitboxLeftOffset = -0x18;
    gCurrentSprite.hitboxRightOffset = 0x18;
    gCurrentSprite.drawDistanceTopOffset = 0x40;
    gCurrentSprite.drawDistanceBottomOffset = 0x8;
    gCurrentSprite.drawDistanceHorizontalOffset = 0x8;
    gCurrentSprite.animationDurationCounter = 0x0;
    gCurrentSprite.currentAnimationFrame = 0x0;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.health = 0x1;
    gCurrentSprite.drawOrder = 0x3;
    gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;
}

/**
 * 2ee24 | 18 | Checks if the alarm timer is 0, if yes closes the gate
 * 
 */
void SecurityGateDefaultClosedCheckAlarm(void)
{
    if (gAlarmTimer == 0x0)
        SecurityGateStartClosing();
}

/**
 * 2ee3c | 3c | Checks if the alarm timer isn't 0, if yes calls SecurityGateOpen
 * 
 */
void SecurityGateDefaultClosedCloseAfterAlarm(void)
{
    if (gCurrentSprite.timer == 0x0 && !SpriteCheckCollidingWithSamusDrawing())
    {
        SecurityGateChangeCCAA(CAA_MAKE_NON_POWER_GRIP);
        gCurrentSprite.timer++;
    }

    if (gAlarmTimer != 0x0)
        SecurityGateOpen();
}

/**
 * 2ee78 | f0 | Security Gate Default Open AI
 * 
 */
void SecurityGateDefaultOpen(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 0x1;
    switch (gCurrentSprite.pose)
    {
        case 0x0:
            SecurityGateDefaultOpenInit();
            break;
        case 0x9:
            SecurityGateDefaultOpenCheckAlarm();
            break;
        case 0x23:
            SecurityGateCheckClosingAnimEnded();
            break;
        case 0x25:
            SecurityGateDefaultOpenOpenAfterAlarm();
            break;
        case 0x27:
            SecurityGateCheckOpeningAnimEnded();
            break;
        default:
            SecurityGateDeath();
    }
}

/**
 * 2ef68 | f0 | Security Gate Default Closed AI
 * 
 */
void SecurityGateDefaultClosed(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 0x1;
    switch (gCurrentSprite.pose)
    {
        case 0x0:
            SecurityGateDefaultClosedInit();
            break;
        case 0x9:
            SecurityGateDefaultClosedCheckAlarm();
            break;
        case 0x23:
            SecurityGateCheckClosingAnimEnded();
            break;
        case 0x25:
            SecurityGateDefaultClosedCloseAfterAlarm();
            break;
        case 0x27:
            SecurityGateCheckOpeningAnimEnded();
            break;
        default:
            SecurityGateDeath();
    }
}