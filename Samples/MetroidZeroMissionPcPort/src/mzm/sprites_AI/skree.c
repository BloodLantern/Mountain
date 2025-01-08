#include "mzm/sprites_AI/skree.h"
#include "mzm/macros.h"
#include "mzm/sprite_util.h"

#include "mzm/data/sprites/skree.h"
#include "mzm/data/sprite_data.h"

#include "mzm/constants/particle.h"
#include "mzm/constants/clipdata.h"
#include "mzm/constants/sprite.h"
#include "mzm/constants/sprite_util.h"

#include "mzm/structs/display.h"
#include "mzm/structs/sprite.h"
#include "mzm/structs/samus.h"

/**
 * @brief 1c644 | 50 | Initializes a skree sprite
 * 
 */
void SkreeInit(void)
{
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(0);
    gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 2);
    gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);

    gCurrentSprite.hitboxTopOffset = 0;
    gCurrentSprite.hitboxBottomOffset = BLOCK_SIZE + HALF_BLOCK_SIZE;
    gCurrentSprite.hitboxLeftOffset = -(QUARTER_BLOCK_SIZE + PIXEL_SIZE * 2);
    gCurrentSprite.hitboxRightOffset = (QUARTER_BLOCK_SIZE + PIXEL_SIZE * 2);

    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.yPosition -= BLOCK_SIZE;
}

/**
 * @brief 1c694 | 1c | Initializes a skree to be idle
 * 
 */
void SkreeIdleInit(void)
{
    gCurrentSprite.pOam = sSkreeOAM_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pose = SKREE_POSE_DETECTING_SAMUS;
}

/**
 * @brief 1c6b0 | 50 | Checks if samus is in the range of the skree
 * 
 */
void SkreeDetectSamus(void)
{
    if (gSamusData.yPosition <= gCurrentSprite.yPosition)
        return;

    if (gSamusData.yPosition - gCurrentSprite.yPosition >= SKREE_Y_RANGE)
        return;

    if (!(gCurrentSprite.status & SPRITE_STATUS_ONSCREEN))
        return;

    if (gSamusData.xPosition <= gCurrentSprite.xPosition - SKREE_X_RANGE)
        return;

    if (gSamusData.xPosition >= gCurrentSprite.xPosition + SKREE_X_RANGE)
        return;

    // Set spinning
    gCurrentSprite.pose = SKREE_POSE_SPINNING_INIT;
}

/**
 * @brief 1c700 | 1c | Initializes a skree to be spinning
 * 
 */
void SkreeSpinningInit(void)
{
    gCurrentSprite.pOam = sSkreeOAM_Spinning;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pose = SKREE_POSE_SPINNING;
}

/**
 * @brief 1c71c | 1c | Checks if the spin animation ended
 * 
 */
void SkreeCheckSpinAnimEnded(void)
{
    if (SpriteUtilCheckNearEndCurrentSpriteAnim())
        gCurrentSprite.pose = SKREE_POSE_GOING_DOWN_INIT;
}

/**
 * @brief 1c738 | 68 | Initializes a skree to be going down
 * 
 */
void SkreeGoingDownInit(void)
{
    gCurrentSprite.pOam = sSkreeOAM_GoingDown;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.arrayOffset = 0;
    gCurrentSprite.workVariable2 = 0;
    gCurrentSprite.pose = SKREE_POSE_GOING_DOWN;

    if (gCurrentSprite.xPosition > gSamusData.xPosition)
        gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
    else
        gCurrentSprite.status |= SPRITE_STATUS_FACING_RIGHT;

    if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
        SoundPlay(0x141);
}

/**
 * @brief 1c7a0 | fc | Handles a skree going down
 * 
 */
void SkreeGoDown(void)
{
    u32 blockTop;
    u32 xMovement;
    u32 yMovement;
    u32 offset;

    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.hitboxBottomOffset + gCurrentSprite.yPosition,
        gCurrentSprite.xPosition);

    if (gPreviousVerticalCollisionCheck != 0)
    {
        gCurrentSprite.yPosition = blockTop - gCurrentSprite.hitboxBottomOffset;
        gCurrentSprite.pose = SKREE_POSE_CRASHING;
        gCurrentSprite.timer = 0x0;
        if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
            SoundPlay(0x142);
    }
    else
    {
        xMovement = gCurrentSprite.workVariable2 / 4;

        offset = gCurrentSprite.arrayOffset;
        yMovement = sSkreeFallingSpeed[offset];
        if (yMovement == SHORT_MAX)
        {
            yMovement = sSkreeFallingSpeed[offset - 1];
            gCurrentSprite.yPosition += yMovement;
        }
        else
        {
            gCurrentSprite.arrayOffset++;
            gCurrentSprite.yPosition += yMovement;
        }

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition + HALF_BLOCK_SIZE);
            if (gPreviousCollisionCheck == COLLISION_SOLID)
                return;

            gCurrentSprite.xPosition += xMovement;
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition - HALF_BLOCK_SIZE);
            if (gPreviousCollisionCheck == COLLISION_SOLID)
                return;

            gCurrentSprite.xPosition -= xMovement;
        }

        // X speed threshold
        if (xMovement < 16)
            gCurrentSprite.workVariable2++;
    }
}

/**
 * @brief 1c89c | 128 | Handles a skree crashing on the ground
 * 
 */
void SkreeCrashGround(void)
{
    u16 yPosition;
    u16 xPosition;
    struct SpriteGraphics* gfxSlot;
    u8 ramSlot;
    u8 spriteId;

    yPosition = gCurrentSprite.yPosition;
    xPosition = gCurrentSprite.xPosition;

    gCurrentSprite.timer++;

    switch (gCurrentSprite.timer)
    {
        case 1:
            yPosition += 0x48;
            SpriteDebrisInit(0, 17, yPosition - QUARTER_BLOCK_SIZE, xPosition);
            SpriteDebrisInit(0, 18, yPosition, xPosition + (PIXEL_SIZE * 3));

            SpriteDebrisInit(0, 19, yPosition - (HALF_BLOCK_SIZE + PIXEL_SIZE * 2 + PIXEL_SIZE / 2),
                xPosition + (QUARTER_BLOCK_SIZE + PIXEL_SIZE));

            SpriteDebrisInit(0, 4, yPosition - (QUARTER_BLOCK_SIZE + PIXEL_SIZE * 2),
                xPosition - (QUARTER_BLOCK_SIZE + PIXEL_SIZE * 3 + PIXEL_SIZE / 2));
            break;

        case 40:
            gCurrentSprite.pOam = sSkreeOAM_Crashing;
            break;

        case 60:
            gfxSlot = gCurrentSprite.spritesetGfxSlot;
            ramSlot = gCurrentSprite.primarySpriteRamSlot;

            if (gCurrentSprite.spriteId == PSPRITE_SKREE_BLUE)
                spriteId = SSPRITE_BLUE_SKREE_EXPLOSION;
            else
                spriteId = SSPRITE_SKREE_EXPLOSION;
            
            SpriteSpawnSecondary(spriteId, SKREE_EXPLOSION_PART_GOING_UP, gfxSlot, ramSlot,
                yPosition - (PIXEL_SIZE * 2), xPosition, 0);

            SpriteSpawnSecondary(spriteId, SKREE_EXPLOSION_PART_GOING_UP, gfxSlot, ramSlot,
                yPosition - (PIXEL_SIZE * 2), xPosition, SPRITE_STATUS_XFLIP);

            SpriteSpawnSecondary(spriteId, SKREE_EXPLOSION_PART_GOING_DOWN, gfxSlot, ramSlot,
                yPosition + (PIXEL_SIZE * 2), xPosition - (PIXEL_SIZE * 3), 0);

            SpriteSpawnSecondary(spriteId, SKREE_EXPLOSION_PART_GOING_DOWN, gfxSlot, ramSlot,
                yPosition + (PIXEL_SIZE * 2), xPosition + (PIXEL_SIZE * 3), SPRITE_STATUS_XFLIP);

           
            gCurrentSprite.status = 0;

            ParticleSet(yPosition + HALF_BLOCK_SIZE + PIXEL_SIZE, xPosition, PE_SPRITE_EXPLOSION_HUGE);
            SoundPlay(0x134);
    }
}

/**
 * @brief 1c9c4 | b4 | Initializes a skree explosion sprite
 * 
 */
void SkreeExplosionInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
    gCurrentSprite.properties |= SP_KILL_OFF_SCREEN;

    gCurrentSprite.drawDistanceTopOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
    gCurrentSprite.drawDistanceBottomOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
    gCurrentSprite.drawDistanceHorizontalOffset = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);

    gCurrentSprite.hitboxTopOffset = -(PIXEL_SIZE * 3);
    gCurrentSprite.hitboxBottomOffset = (PIXEL_SIZE * 3);
    gCurrentSprite.hitboxLeftOffset = -(PIXEL_SIZE * 3);
    gCurrentSprite.hitboxRightOffset = (PIXEL_SIZE * 3);
    
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    
    gCurrentSprite.pose = SKREE_EXPLOSION_POSE_MOVING;
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    gCurrentSprite.drawOrder = 3;
    gCurrentSprite.bgPriority = MOD_AND(gIoRegistersBackup.BG1CNT, 4);
    
    gCurrentSprite.yPosition += HALF_BLOCK_SIZE + PIXEL_SIZE * 2;
    gCurrentSprite.status |= SPRITE_STATUS_DOUBLE_SIZE | SPRITE_STATUS_ROTATION_SCALING;
    gCurrentSprite.oamScaling = Q_8_8(1.f);
    gCurrentSprite.oamRotation = 0;

    if (gCurrentSprite.roomSlot != SKREE_EXPLOSION_PART_GOING_UP)
        gCurrentSprite.pOam = sSkreeExplosionOAM_GoingDown;
    else
        gCurrentSprite.pOam = sSkreeExplosionOAM_GoingUp;
}

/**
 * @brief 1ca78 | 68 | Handles the movement of a skree explosion sprite
 * 
 */
void SkreeExplosionMove(void)
{
    if (gCurrentSprite.currentAnimationFrame > 1)
        gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
    {
        gCurrentSprite.xPosition += PIXEL_SIZE * 2;
        gCurrentSprite.oamRotation += PI / 4;
    }
    else
    {
        gCurrentSprite.xPosition -= PIXEL_SIZE * 2;
        gCurrentSprite.oamRotation -= PI / 4;
    }

    if (gCurrentSprite.roomSlot != SKREE_EXPLOSION_PART_GOING_UP)
        gCurrentSprite.yPosition += PIXEL_SIZE;
    else
        gCurrentSprite.yPosition -= PIXEL_SIZE;

    if (SpriteUtilCheckEndCurrentSpriteAnim())
        gCurrentSprite.status = 0;
}

/**
 * @brief 1cae0 | 194 | Skree AI
 * 
 */
void Skree(void)
{
    if (gCurrentSprite.properties & SP_DAMAGED)
    {
        gCurrentSprite.properties &= ~SP_DAMAGED;
        if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
            SoundPlayNotAlreadyPlaying(0x143);
    }

    if (gCurrentSprite.freezeTimer != 0)
    {
        SpriteUtilUpdateFreezeTimer();
        return;
    }

    if (SpriteUtilIsSpriteStunned())
        return;
    
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SkreeInit();

        case 0x8:
            SkreeIdleInit();

        case SKREE_POSE_DETECTING_SAMUS:
            SkreeDetectSamus();
            break;

        case SKREE_POSE_SPINNING_INIT:
            SkreeSpinningInit();

        case SKREE_POSE_SPINNING:
            SkreeCheckSpinAnimEnded();
            break;

        case SKREE_POSE_GOING_DOWN_INIT:
            SkreeGoingDownInit();

        case SKREE_POSE_GOING_DOWN:
            SkreeGoDown();
            break;

        case SKREE_POSE_CRASHING:
            SkreeCrashGround();
            break;

        default:
            SpriteUtilSpriteDeath(DEATH_NORMAL, gCurrentSprite.yPosition + (QUARTER_BLOCK_SIZE * 3 + PIXEL_SIZE),
                gCurrentSprite.xPosition, TRUE, PE_SPRITE_EXPLOSION_MEDIUM);
    }
}

/**
 * @brief 1cc74 | 24 | Skree explosion AI
 * 
 */
void SkreeExplosion(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SkreeExplosionInit();

        case SKREE_EXPLOSION_POSE_MOVING:
            SkreeExplosionMove();
    }
}
