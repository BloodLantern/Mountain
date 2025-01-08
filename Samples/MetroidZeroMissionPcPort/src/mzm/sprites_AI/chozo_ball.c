#include "mzm/sprites_AI/chozo_ball.h"
#include "mzm/sprites_AI/chozo_statue.h"
#include "mzm/macros.h"
#include "mzm/sprite_util.h"

#include "mzm/data/sprites/chozo_statue.h"
#include "mzm/data/sprites/unknown_item_chozo_statue.h"

#include "mzm/constants/samus.h"
#include "mzm/constants/sprite.h"
#include "mzm/constants/text.h"

#include "mzm/structs/sprite.h"
#include "mzm/structs/samus.h"

/**
 * 162b0 | 94 | Spawns an item banner depending on the chozo statue sprite ID
 * 
 * @param spriteId Chozo statue sprite ID
 */
void ChozoBallSpawnItemBanner(u8 spriteId)
{
    u8 text;

    switch (spriteId)
    {
        case PSPRITE_CHOZO_STATUE_LONG:
            text = MESSAGE_LONG_BEAM;
            break;

        case PSPRITE_CHOZO_STATUE_ICE:
            text = MESSAGE_ICE_BEAM;
            break;

        case PSPRITE_CHOZO_STATUE_WAVE:
            text = MESSAGE_WAVE_BEAM;
            break;

        case PSPRITE_CHOZO_STATUE_PLASMA_BEAM:
            text = MESSAGE_UKNOWN_ITEM_PLASMA;
            break;

        case PSPRITE_CHOZO_STATUE_BOMB:
            text = MESSAGE_BOMB;
            break;

        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER:
            text = MESSAGE_SPEED_BOOSTER;
            break;

        case PSPRITE_CHOZO_STATUE_HIGH_JUMP:
            text = MESSAGE_HIGH_JUMP;
            break;

        case PSPRITE_CHOZO_STATUE_SCREW:
            text = MESSAGE_SCREW_ATTACK;
            break;

        case PSPRITE_CHOZO_STATUE_VARIA:
            text = MESSAGE_VARIA_SUIT;
            break;

        case PSPRITE_CHOZO_STATUE_SPACE_JUMP:
            text = MESSAGE_UNKNOWN_ITEM_SPACE_JUMP;
            break;

        case PSPRITE_CHOZO_STATUE_GRAVITY:
            text = MESSAGE_UNKNOWN_ITEM_GRAVITY;
            break;
    }

    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, text, 6, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
}

/**
 * @brief 16344 | 64 | Sets the closed OAM of a chozo ball based on the sprite ID
 * 
 * @param spriteId Chozo statue sprite ID
 */
void ChozoBallSetClosedOAM(u8 spriteId)
{
    switch (spriteId)
    {
        case PSPRITE_CHOZO_STATUE_PLASMA_BEAM:
            gCurrentSprite.pOam = sChozoBallOam_UnknownClosed;
            break;
        
        case PSPRITE_CHOZO_STATUE_SPACE_JUMP:
            gCurrentSprite.pOam = sChozoBallOam_UnknownClosed;
            break;

        case PSPRITE_CHOZO_STATUE_GRAVITY:
            gCurrentSprite.pOam = sChozoBallOam_UnknownClosed;
            break;
        
        case PSPRITE_CHOZO_STATUE_LONG:
        case PSPRITE_CHOZO_STATUE_ICE:
        case PSPRITE_CHOZO_STATUE_WAVE:
        case PSPRITE_CHOZO_STATUE_BOMB:
        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER:
        case PSPRITE_CHOZO_STATUE_HIGH_JUMP:
        case PSPRITE_CHOZO_STATUE_SCREW:
        case PSPRITE_CHOZO_STATUE_VARIA:
            gCurrentSprite.pOam = sChozoBallOam_NormalClosed;
            break;

        default:
            gCurrentSprite.pOam = sChozoBallOam_NormalClosed;
    }
}

/**
 * @brief 163a8 | 64 | Sets the revealing OAM of a chozo ball based on the sprite ID
 * 
 * @param spriteId Chozo statue sprite ID
 */
void ChozoBallSetRevealingOAM(u8 spriteId)
{
    switch (spriteId)
    {
        case PSPRITE_CHOZO_STATUE_PLASMA_BEAM:
            gCurrentSprite.pOam = sChozoBallOam_UnknownRevealing;
            break;

        case PSPRITE_CHOZO_STATUE_SPACE_JUMP:
            gCurrentSprite.pOam = sChozoBallOam_UnknownRevealing;
            break;

        case PSPRITE_CHOZO_STATUE_GRAVITY:
            gCurrentSprite.pOam = sChozoBallOam_UnknownRevealing;
            break;

        case PSPRITE_CHOZO_STATUE_LONG:
        case PSPRITE_CHOZO_STATUE_ICE:
        case PSPRITE_CHOZO_STATUE_WAVE:
        case PSPRITE_CHOZO_STATUE_BOMB:
        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER:
        case PSPRITE_CHOZO_STATUE_HIGH_JUMP:
        case PSPRITE_CHOZO_STATUE_SCREW:
        case PSPRITE_CHOZO_STATUE_VARIA:
            gCurrentSprite.pOam = sChozoBallOam_NormalRevealing;
            break;

        default:
            gCurrentSprite.pOam = sChozoBallOam_NormalRevealing;
    }
}

/**
 * @brief 1640c | 64 | Sets the revealed OAM of a chozo ball based on the sprite ID
 * 
 * @param spriteId Chozo statue sprite ID
 */
void ChozoBallSetRevealedOAM(u8 spriteId)
{
    switch (spriteId)
    {
        case PSPRITE_CHOZO_STATUE_PLASMA_BEAM:
            gCurrentSprite.pOam = sChozoBallOam_UnknownRevealed;
            break;

        case PSPRITE_CHOZO_STATUE_SPACE_JUMP:
            gCurrentSprite.pOam = sChozoBallOam_UnknownRevealed;
            break;

        case PSPRITE_CHOZO_STATUE_GRAVITY:
            gCurrentSprite.pOam = sChozoBallOam_UnknownRevealed;
            break;

        case PSPRITE_CHOZO_STATUE_LONG:
        case PSPRITE_CHOZO_STATUE_ICE:
        case PSPRITE_CHOZO_STATUE_WAVE:
        case PSPRITE_CHOZO_STATUE_BOMB:
        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER:
        case PSPRITE_CHOZO_STATUE_HIGH_JUMP:
        case PSPRITE_CHOZO_STATUE_SCREW:
        case PSPRITE_CHOZO_STATUE_VARIA:
            gCurrentSprite.pOam = sChozoBallOam_NormalRevealed;
            break;

        default:
            gCurrentSprite.pOam = sChozoBallOam_NormalRevealed;
    }
}

/**
 * 16470 | 74 | Initializes a chozo ball sprite
 * 
 */
void ChozoBallInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;

    gCurrentSprite.hitboxTopOffset = -(QUARTER_BLOCK_SIZE + PIXEL_SIZE * 3);
    gCurrentSprite.hitboxBottomOffset = (QUARTER_BLOCK_SIZE + PIXEL_SIZE * 3);
    gCurrentSprite.hitboxLeftOffset = -(QUARTER_BLOCK_SIZE + PIXEL_SIZE * 3);
    gCurrentSprite.hitboxRightOffset = (QUARTER_BLOCK_SIZE + PIXEL_SIZE * 3);

    gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(QUARTER_BLOCK_SIZE * 3);
    gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(QUARTER_BLOCK_SIZE * 3);
    gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(QUARTER_BLOCK_SIZE * 3);

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.samusCollision = SSC_SOLID;
    gCurrentSprite.health = 1;
    gCurrentSprite.pose = CHOZO_BALL_POSE_DO_NOTHING;

    ChozoBallSetClosedOAM(gSpriteData[gCurrentSprite.primarySpriteRamSlot].spriteId);
}

/**
 * 164e4 | 4 | Empty function
 * 
 */
void ChozoBallEmpty(void)
{
    return;
}

/**
 * 164e8 | 70 | Initializes a chozo ball to be revealing
 * 
 */
void ChozoBallRevealingInit(void)
{
    gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;
    gCurrentSprite.health = 1;
    gCurrentSprite.samusCollision = SSC_ABILITY_LASER_SEARCHLIGHT;
    gCurrentSprite.pose = CHOZO_BALL_POSE_REVEALING;

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.paletteRow = gCurrentSprite.absolutePaletteRow;
    SPRITE_CLEAR_ISFT(gCurrentSprite);

    ChozoBallSetRevealingOAM(gSpriteData[gCurrentSprite.primarySpriteRamSlot].spriteId);
    SoundPlay(0x11D);
}

/**
 * 16558 | 3c | Checks if the revealing animation has ended
 * 
 */
void ChozoBallCheckRevealingAnimEnded(void)
{
    if (SpriteUtilCheckEndCurrentSpriteAnim())
    {
        gCurrentSprite.pose = CHOZO_BALL_POSE_IDLE;

        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        ChozoBallSetRevealedOAM(gSpriteData[gCurrentSprite.primarySpriteRamSlot].spriteId);
    }
}

/**
 * 16594 | 1c | Registers the item grabbed and calls ChozoBallSpawnItemBanner
 * 
 */
void ChozoBallRegisterItem(void)
{
    u8 spriteId;

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_COLLIDING)
    {
        gPreventMovementTimer = SAMUS_ITEM_PMT;
        gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;
        gCurrentSprite.ignoreSamusCollisionTimer = 1;

        gCurrentSprite.pose = CHOZO_BALL_POSE_GETTING;
        gCurrentSprite.timer = 0;

        spriteId = gSpriteData[gCurrentSprite.primarySpriteRamSlot].spriteId;
        ChozoStatueRegisterItem(spriteId);
        ChozoBallSpawnItemBanner(spriteId);
    }
}

/**
 * 16600 | 3c | Handles the flashing animation when the item gets grabbed 
 * 
 */
void ChozoBallFlashAnimation(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (MOD_AND(gCurrentSprite.timer, 2) == 0)
        gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;
        
    if (gPreventMovementTimer < SAMUS_ITEM_PMT - 1)
        gCurrentSprite.status = 0;
}

/**
 * 1663c | 58 | Chozo ball AI
 * 
 */
void ChozoBall(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            ChozoBallInit();
            break;

        case CHOZO_BALL_POSE_DO_NOTHING:
            ChozoBallEmpty();
            break;

        case CHOZO_BALL_POSE_REVEALING:
            ChozoBallCheckRevealingAnimEnded();
            break;

        case CHOZO_BALL_POSE_IDLE:
            ChozoBallRegisterItem();
            break;

        case CHOZO_BALL_POSE_GETTING:
            ChozoBallFlashAnimation();
            break;

        default:
            ChozoBallRevealingInit();
    }
}
