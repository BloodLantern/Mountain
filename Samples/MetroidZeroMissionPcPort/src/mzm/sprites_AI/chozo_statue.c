#include "mzm/sprites_AI/chozo_statue.h"
#include "mzm/sprites_AI/unknown_item_chozo_statue.h"
#include "mzm/sprite_util.h"

#include "mzm/data/frame_data_pointers.h"
#include "mzm/data/sprites/chozo_statue.h"

#include "mzm/constants/audio.h"
#include "mzm/constants/in_game_cutscene.h"
#include "mzm/constants/clipdata.h"
#include "mzm/constants/game_state.h"
#include "mzm/constants/sprite.h"
#include "mzm/constants/event.h"
#include "mzm/constants/samus.h"
#include "mzm/constants/text.h"

#include "mzm/structs/audio.h"
#include "mzm/structs/game_state.h"
#include "mzm/structs/hud.h"
#include "mzm/structs/sprite.h"
#include "mzm/structs/samus.h"
#include "mzm/structs/scroll.h"

/**
 * @brief 13850 | 88 | Synchronize the sub sprites of a chozo statue
 * 
 */
void ChozoStatueSyncSubSprites(void)
{
    u16 (*pData)[3];
    u32 offset;

    pData = (u16(*)[3])gSubSpriteData1.pMultiOam[gSubSpriteData1.currentAnimationFrame].pFrame;
    offset = pData[gCurrentSprite.roomSlot][0];
    
    if (gCurrentSprite.pOam != sChozoStatueFrameDataPointers[offset])
    {
        gCurrentSprite.pOam = sChozoStatueFrameDataPointers[offset];
        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;
    }

    gCurrentSprite.yPosition = gSubSpriteData1.yPosition + pData[gCurrentSprite.roomSlot][1];

    if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
        gCurrentSprite.xPosition = gSubSpriteData1.xPosition - pData[gCurrentSprite.roomSlot][2];
    else
        gCurrentSprite.xPosition = gSubSpriteData1.xPosition + pData[gCurrentSprite.roomSlot][2];
}

/**
 * @brief 138d8 | 30c | Registers a chozo statue item/hint
 * 
 * @param spriteId Chozo statue sprite ID
 */
void ChozoStatueRegisterItem(u8 spriteId)
{
    switch (spriteId)
    {
        case PSPRITE_CHOZO_STATUE_LONG:
            gEquipment.beamBombs |= BBF_LONG_BEAM;

        case PSPRITE_CHOZO_STATUE_LONG_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_LONG_BEAM_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_ICE:
            gEquipment.beamBombs |= BBF_ICE_BEAM;

        case PSPRITE_CHOZO_STATUE_ICE_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_ICE_BEAM_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_WAVE:
            gEquipment.beamBombs |= BBF_WAVE_BEAM;

        case PSPRITE_CHOZO_STATUE_WAVE_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_WAVE_BEAM_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_BOMB:
            gEquipment.beamBombs |= BBF_BOMBS;

        case PSPRITE_CHOZO_STATUE_BOMB_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_BOMBS_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER:
            gEquipment.suitMisc |= SMF_SPEEDBOOSTER;

        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_SPEEDBOOSTER_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_HIGH_JUMP:
            gEquipment.suitMisc |= SMF_HIGH_JUMP;
            EventFunction(EVENT_ACTION_SETTING, EVENT_HIGH_JUMP_OBTAINED);

        case PSPRITE_CHOZO_STATUE_HIGH_JUMP_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_HIGH_JUMP_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_SCREW:
            gEquipment.suitMisc |= SMF_SCREW_ATTACK;
            EventFunction(EVENT_ACTION_SETTING, EVENT_SCREW_ATTACK_OBTAINED);

        case PSPRITE_CHOZO_STATUE_SCREW_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_SCREW_ATTACK_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_VARIA:
            gEquipment.suitMisc |= SMF_VARIA_SUIT;
            EventFunction(EVENT_ACTION_SETTING, EVENT_VARIA_SUIT_OBTAINED);

        case PSPRITE_CHOZO_STATUE_VARIA_HINT:
            EventFunction(EVENT_ACTION_SETTING, EVENT_STATUE_VARIA_SUIT_GRABBED);
            break;

        case PSPRITE_CHOZO_STATUE_SPACE_JUMP:
            gEquipment.suitMisc |= SMF_SPACE_JUMP;
            EventFunction(EVENT_ACTION_SETTING, EVENT_SPACE_JUMP_OBTAINED);
            break;

        case PSPRITE_CHOZO_STATUE_GRAVITY:
            gEquipment.suitMisc |= SMF_GRAVITY_SUIT;
            EventFunction(EVENT_ACTION_SETTING, EVENT_GRAVITY_SUIT_OBTAINED);
            break;

        case PSPRITE_CHOZO_STATUE_PLASMA_BEAM:
            gEquipment.beamBombs |= BBF_PLASMA_BEAM;
            EventFunction(EVENT_ACTION_SETTING, EVENT_PLASMA_BEAM_OBTAINED);
            break;
    }
}

/**
 * @brief 13be4 | 1fc | Sets the direction of a chozo statue
 * 
 */
void ChozoStatueSetDirection(void)
{
    switch (gCurrentSprite.spriteId)
    {
        case PSPRITE_CHOZO_STATUE_LONG:
        case PSPRITE_CHOZO_STATUE_ICE_HINT:
        case PSPRITE_CHOZO_STATUE_ICE:
        case PSPRITE_CHOZO_STATUE_WAVE_HINT:
        case PSPRITE_CHOZO_STATUE_WAVE:
        case PSPRITE_CHOZO_STATUE_BOMB:
        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER:
        case PSPRITE_CHOZO_STATUE_HIGH_JUMP:
        case PSPRITE_CHOZO_STATUE_SCREW:
        case PSPRITE_CHOZO_STATUE_VARIA_HINT:
        case PSPRITE_CHOZO_STATUE_VARIA:
        case PSPRITE_CHOZO_STATUE_GRAVITY:
            gCurrentSprite.status |= SPRITE_STATUS_XFLIP;
            break;

        case PSPRITE_CHOZO_STATUE_LONG_HINT:
        case PSPRITE_CHOZO_STATUE_BOMB_HINT:
        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER_HINT:
        case PSPRITE_CHOZO_STATUE_HIGH_JUMP_HINT:
        case PSPRITE_CHOZO_STATUE_SCREW_HINT:
        case PSPRITE_CHOZO_STATUE_SPACE_JUMP:
        case PSPRITE_CHOZO_STATUE_PLASMA_BEAM:
            break;
    }
}

/**
 * @brief 13de0 | 2bc | Gets the behavior of the chozo statue with the ID in parameter
 * 
 * @param spriteId Chozo statue sprite ID
 * @return u8 Behavior
 */
u8 ChozoStatueGetBehavior(u8 spriteId)
{
    u8 behavior;

    behavior = CHOZO_STATUE_BEHAVIOR_ITEM;

    switch (spriteId)
    {
        case PSPRITE_CHOZO_STATUE_LONG_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_LONG_BEAM_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_ICE_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_ICE_BEAM_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_WAVE_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_WAVE_BEAM_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_BOMB_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_BOMBS_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_SPEEDBOOSTER_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_HIGH_JUMP_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_HIGH_JUMP_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_SCREW_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_SCREW_ATTACK_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_VARIA_HINT:
            if (EventFunction(EVENT_ACTION_CHECKING, EVENT_STATUE_VARIA_SUIT_GRABBED))
                behavior = CHOZO_STATUE_BEHAVIOR_HINT_TAKEN;
            else
                behavior = CHOZO_STATUE_BEHAVIOR_HINT;
            break;

        case PSPRITE_CHOZO_STATUE_LONG:
            if (gEquipment.beamBombs & BBF_LONG_BEAM)
                behavior++;
            break;
        
        case PSPRITE_CHOZO_STATUE_ICE:
            if (gEquipment.beamBombs & BBF_ICE_BEAM)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_WAVE:
            if (gEquipment.beamBombs & BBF_WAVE_BEAM)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_PLASMA_BEAM:
            if (gEquipment.beamBombs & BBF_PLASMA_BEAM)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_BOMB:
            if (gEquipment.beamBombs & BBF_BOMBS)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_SPEEDBOOSTER:
            if (gEquipment.suitMisc & SMF_SPEEDBOOSTER)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_HIGH_JUMP:
            if (gEquipment.suitMisc & SMF_HIGH_JUMP)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_SCREW:
            if (gEquipment.suitMisc & SMF_SCREW_ATTACK)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_VARIA:
            if (gEquipment.suitMisc & SMF_VARIA_SUIT)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_SPACE_JUMP:
            if (gEquipment.suitMisc & SMF_SPACE_JUMP)
                behavior++;
            break;

        case PSPRITE_CHOZO_STATUE_GRAVITY:
            if (gEquipment.suitMisc & SMF_GRAVITY_SUIT)
                behavior++;
            break;
    }

    return behavior;
}

/**
 * @brief 1409c | 1f8 | Initializes a Chozo statue sprite
 * 
 */
void ChozoStatueInit(void)
{
    u8 behavior;
    struct SpriteGraphics* gfxSlot;
    u8 ramSlot;
    u16 yPosition;
    u16 xPosition;
    u8 newRamSlot;

    gCurrentSprite.properties |= (SP_ALWAYS_ACTIVE | SP_SOLID_FOR_PROJECTILES);

    ChozoStatueSetDirection();
    if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
        gSubSpriteData1.xPosition = gCurrentSprite.xPosition + HALF_BLOCK_SIZE;
    else
        gSubSpriteData1.xPosition = gCurrentSprite.xPosition - HALF_BLOCK_SIZE;

    gSubSpriteData1.yPosition = gCurrentSprite.yPosition;

    gCurrentSprite.drawDistanceTopOffset = 0x20;
    gCurrentSprite.drawDistanceBottomOffset = 0x20;
    gCurrentSprite.drawDistanceHorizontalOffset = 0x18;

    gCurrentSprite.hitboxTopOffset = 0x4;
    gCurrentSprite.hitboxBottomOffset = 0x4;
    gCurrentSprite.hitboxLeftOffset = 0x4;
    gCurrentSprite.hitboxRightOffset = 0x4;

    gCurrentSprite.drawOrder = 0x3;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.health = 0x1;

    gSubSpriteData1.animationDurationCounter = 0x0;
    gSubSpriteData1.currentAnimationFrame = 0x0;
    gSubSpriteData1.workVariable2 = 0x0;
    gSubSpriteData1.workVariable3 = FALSE;

    behavior = ChozoStatueGetBehavior(gCurrentSprite.spriteId);
    if (behavior > CHOZO_STATUE_BEHAVIOR_REFILL)
    {
        // Is hint
        gCurrentSprite.pose = CHOZO_STATUE_POSE_IDLE;
        if (behavior == CHOZO_STATUE_BEHAVIOR_HINT_TAKEN)
        {
            // Set seated
            gSubSpriteData1.pMultiOam = sChozoStatueMultiSpriteData_Seated;
            ChozoStatueSeatedChangeCCAA(CAA_MAKE_NON_POWER_GRIP);
        }
        else
        {
            // Set standing
            gSubSpriteData1.workVariable3 = TRUE;
            gSubSpriteData1.pMultiOam = sChozoStatueMultiSpriteData_Standing;
            ChozoStatueStandingChangeCCAA(CAA_MAKE_NON_POWER_GRIP, CAA_MAKE_SOLID_GRIPPABLE);
        }
    }
    else
    {
        // Is item
        gSubSpriteData1.pMultiOam = sChozoStatueMultiSpriteData_Seated;
        ChozoStatueSeatedChangeCCAA(CAA_MAKE_NON_POWER_GRIP);

        if (behavior == CHOZO_STATUE_BEHAVIOR_ITEM)
        {
            // Item
            gCurrentSprite.pose = CHOZO_STATUE_POSE_WAIT_FOR_ITEM_TO_BE_COLLECTED;

            // Spawn chozo ball
            if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
            {
                SpriteSpawnSecondary(SSPRITE_CHOZO_BALL, 0x0, gCurrentSprite.spritesetGfxSlot,
                    gCurrentSprite.primarySpriteRamSlot, gSubSpriteData1.yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE),
                    gSubSpriteData1.xPosition + 0x38, 0x0);
            }
            else
            {
                SpriteSpawnSecondary(SSPRITE_CHOZO_BALL, 0x0, gCurrentSprite.spritesetGfxSlot,
                    gCurrentSprite.primarySpriteRamSlot, gSubSpriteData1.yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE),
                    gSubSpriteData1.xPosition - 0x38, 0x0);
            }
        }
        else
            gCurrentSprite.pose = CHOZO_STATUE_POSE_IDLE; // Refill
    }

    gCurrentSprite.roomSlot = CHOZO_STATUE_PART_HEAD;

    yPosition = gSubSpriteData1.yPosition;
    xPosition = gSubSpriteData1.xPosition;
    gfxSlot = gCurrentSprite.spritesetGfxSlot;
    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    // Spawn eye
    gCurrentSprite.workVariable = SpriteSpawnSecondary(SSPRITE_CHOZO_STATUE_PART, CHOZO_STATUE_PART_EYE,
        gfxSlot, ramSlot, yPosition, xPosition, gCurrentSprite.status & SPRITE_STATUS_XFLIP);

    // Spawn arm
    behavior = SpriteSpawnSecondary(SSPRITE_CHOZO_STATUE_PART, CHOZO_STATUE_PART_ARM,
        gfxSlot, ramSlot, yPosition, xPosition, gCurrentSprite.status & SPRITE_STATUS_XFLIP);

    // Spawn leg
    SpriteSpawnSecondary(SSPRITE_CHOZO_STATUE_PART, CHOZO_STATUE_PART_LEG, gfxSlot, ramSlot,
        yPosition, xPosition, gCurrentSprite.status & SPRITE_STATUS_XFLIP);

    // Spawn glow
    newRamSlot = SpriteSpawnSecondary(SSPRITE_CHOZO_STATUE_PART, CHOZO_STATUE_PART_GLOW, gfxSlot,
        ramSlot, yPosition, xPosition, gCurrentSprite.status & SPRITE_STATUS_XFLIP);
    gSpriteData[newRamSlot].workVariable = behavior;
}

/**
 * @brief 14294 | 4 | Empty function
 * 
 */
void ChozoStatue_Empty(void)
{
    return;
}

/**
 * @brief 14298 | 64 | Registers the hint
 * 
 */
void ChozoStatueRegisterHint(void)
{
    u8 eyeSlot;

    // Open eye
    eyeSlot = gCurrentSprite.workVariable;
    gSpriteData[eyeSlot].pose = CHOZO_STATUE_PART_POSE_EYE_OPENING_INIT;

    gCurrentSprite.pose = CHOZO_STATUE_POSE_HINT_FLASHING;
    gCurrentSprite.timer = 0x78;
    gCurrentSprite.workVariable2 = 0xC;
    gCurrentSprite.arrayOffset = 0x0;

    if (gCurrentSprite.spriteId == PSPRITE_CHOZO_STATUE_LONG_HINT)
    {
        MakeBackgroundFlash(BG_FLASH_CHOZO_LONG_TRANSPARENCY);
        gCurrentSprite.timer += 0x28;
    }

    // Register hint
    ChozoStatueRegisterItem(gCurrentSprite.spriteId);
    FadeMusic(0x3C);
}

/**
 * @brief 142fc | bc | Handles the flashing before a chozo statue hint
 * 
 */
void ChozoStatueHintFlashing(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.workVariable;

    if (gSpriteData[ramSlot].pose == 0x61)
    {
        gCurrentSprite.timer--;
        if (gCurrentSprite.timer == 0x0)
        {
            gCurrentSprite.pose = CHOZO_STATUE_POSE_SITTING_INIT;
            gCurrentSprite.paletteRow = 0x0;

            // Start hint
            gPauseScreenFlag = PAUSE_SCREEN_CHOZO_HINT;

            PlayMusic(MUSIC_CHOZO_STATUE_HINT, 0x0);
        }
        else
        {
            if (gCurrentSprite.timer == 0x77)
            {
                MakeBackgroundFlash(BG_FLASH_SLIGHT_YELLOW);
                SoundPlay(0x11B); // Chozo hint
            }
            else if (gCurrentSprite.timer > 0x77)
                return;

            // Update palette
            gCurrentSprite.workVariable2--;
            if (gCurrentSprite.workVariable2 == 0x0)
            {
                // Reset delay
                gCurrentSprite.workVariable2 = 0xC;
                // Change row
                gCurrentSprite.paletteRow = sChozoStatueFlashingPaletteRows[gCurrentSprite.arrayOffset];
                
                // Update offset
                if (gCurrentSprite.arrayOffset > 0x2)
                    gCurrentSprite.arrayOffset = 0x0;
                else
                    gCurrentSprite.arrayOffset++;
            }
        }
    }
}

/**
 * @brief 143b8 | 40 | Initializes a Chozo statue to be sitting
 * 
 */
void ChozoStatueSittingInit(void)
{
    gCurrentSprite.pose = CHOZO_STATUE_POSE_SITTING;

    gSubSpriteData1.pMultiOam = sChozoStatueMultiSpriteData_Sitting;
    gSubSpriteData1.animationDurationCounter = 0x0;
    gSubSpriteData1.currentAnimationFrame = 0x0;

    ChozoStatueStandingChangeCCAA(CAA_REMOVE_SOLID, CAA_REMOVE_SOLID);
    SoundPlay(0x11C);

    gSlowScrollingTimer = 0x3C;
}

/**
 * @brief 143f8 | 4c | Handles a chozo statue sitting
 * 
 */
void ChozoStatueSitting(void)
{
    SpriteUtilUpdateSubSprite1Timer();
    if (gSubSpriteData1.workVariable2 != 0x0)
        SpawnChozoStatueMovement(gSubSpriteData1.workVariable2);

    if (SpriteUtilCheckEndSubSprite1Anim())
    {
        gSubSpriteData1.pMultiOam = sChozoStatueMultiSpriteData_Seated;
        gSubSpriteData1.animationDurationCounter = 0x0;
        gSubSpriteData1.currentAnimationFrame = 0x0;

        gCurrentSprite.pose = CHOZO_STATUE_POSE_DELAY_AFTER_SITTING;
        gCurrentSprite.timer = 0x1E;

        ChozoStatueSeatedChangeCCAA(CAA_MAKE_NON_POWER_GRIP);
    }
}

/**
 * @brief 14444 | 24 | Handles the delay before the refill after the statue sat down
 * 
 */
void ChozoStatueDelayBeforeRefillAfterHint(void)
{
    gCurrentSprite.timer--;
    if (gCurrentSprite.timer == 0x0)
        gCurrentSprite.pose = CHOZO_STATUE_POSE_IDLE;   
}

/**
 * @brief 14468 | 2c | Waits for the item to be grabbed
 * 
 */
void ChozoStatueWaitForItemToBeCollected(void)
{
    // Check behavior
    if (ChozoStatueGetBehavior(gCurrentSprite.spriteId) == CHOZO_STATUE_BEHAVIOR_REFILL)
    {
        // Hint behavior, thus item was took
        gCurrentSprite.pose = CHOZO_STATUE_POSE_TIMER_AFTER_ITEM;
        gCurrentSprite.timer = 0x28;
    }
}

/**
 * @brief 14494 | 24 | Timer after the item is grabbed, unknown purpose
 * 
 */
void ChozoStatueTimerAfterItemGrabbed(void)
{
    gCurrentSprite.timer--;
    if (gCurrentSprite.timer == 0x0)
        gCurrentSprite.pose = CHOZO_STATUE_POSE_IDLE;
}

/**
 * @brief 144b8 | 48 | Initializes a chozo statue for a refill
 * 
 */
void ChozoStatueRefillInit(void)
{
    gCurrentSprite.pose = CHOZO_STATUE_POSE_REFILL;
    gCurrentSprite.workVariable2 = 0x4;
    gCurrentSprite.arrayOffset = 0x0;

    SpriteSpawnSecondary(SSPRITE_CHOZO_STATUE_REFILL, 0x0, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gSamusData.yPosition - 0x18, gSamusData.xPosition, 0x0);
}

/**
 * @brief 14500 | 4c | Handles a chozo statue refilling Samus
 * 
 */
void ChozoStatueRefillSamus(void)
{
    // Update palette
    gCurrentSprite.workVariable2--;
    if (gCurrentSprite.workVariable2 == 0x0)
    {
        // Reset delay
        gCurrentSprite.workVariable2 = 0x4;
        // Change row
        gCurrentSprite.paletteRow = sChozoStatueFlashingPaletteRows[gCurrentSprite.arrayOffset];
        
        // Update offset
        if (gCurrentSprite.arrayOffset > 0x2)
            gCurrentSprite.arrayOffset = 0x0;
        else
            gCurrentSprite.arrayOffset++;
    }
}

/**
 * @brief 1454c | 20 | Initializes a chozos statue to be sleeping
 * 
 */
void ChozoStatueSleepingInit(void)
{
    gCurrentSprite.pose = CHOZO_STATUE_POSE_SLEEPING;
    gCurrentSprite.paletteRow = 0x0;
    gCurrentSprite.timer = 0x46;
}

/**
 * @brief 1456c | 58 | Handles a chozo statue going to sleep
 * 
 */
void ChozoStatueSleeping(void)
{
    u8 ramSlot;

    gCurrentSprite.timer--;
    if (gCurrentSprite.timer == 0x0)
    {
        // Close eye
        ramSlot = gCurrentSprite.workVariable;
        gSpriteData[ramSlot].pose = CHOZO_STATUE_PART_POSE_EYE_CLOSING_INIT;

        gCurrentSprite.pose = CHOZO_STATUE_POSE_DO_NOTHING;

        // Replay room music if hint
        if (gSubSpriteData1.workVariable3)
            PlayMusic(gMusicTrackInfo.currentRoomTrack, 0x0);
    }
}

/**
 * @brief 145c4 | 174 | Initializes a chozo statue part sprite
 * 
 */
void ChozoStatuePartInit(void)
{
    u8 ramSlot;
    u8 behavior;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;
    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;

    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.drawOrder = 0x2;
    
    gCurrentSprite.hitboxTopOffset = 0x4;
    gCurrentSprite.hitboxBottomOffset = 0x4;
    gCurrentSprite.hitboxLeftOffset = 0x4;
    gCurrentSprite.hitboxRightOffset = 0x4;

    behavior = ChozoStatueGetBehavior(gSpriteData[ramSlot].spriteId);

    switch (gCurrentSprite.roomSlot)
    {
        case CHOZO_STATUE_PART_ARM:
            gCurrentSprite.drawDistanceTopOffset = 0x10;
            gCurrentSprite.drawDistanceBottomOffset = 0x10;
            gCurrentSprite.drawDistanceHorizontalOffset = 0x1E;

            gCurrentSprite.animationDurationCounter = 0x0;
            gCurrentSprite.currentAnimationFrame = 0x0;

            if (behavior == CHOZO_STATUE_BEHAVIOR_HINT)
                gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_CHECK_GRAB_SAMUS_HINT;
            else
                gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_CHECK_GRAB_SAMUS_REFILL;

            if (behavior == CHOZO_STATUE_BEHAVIOR_ITEM)
                gCurrentSprite.pOam = sChozoStatuePartOAM_ArmIdle;
            else
                gCurrentSprite.pOam = sChozoStatuePartOAM_ArmGlow;
            break;
    
        case CHOZO_STATUE_PART_LEG:
            gCurrentSprite.drawDistanceTopOffset = 0x30;
            gCurrentSprite.drawDistanceBottomOffset = 0x0;
            gCurrentSprite.drawDistanceHorizontalOffset = 0x20;

            if (behavior == CHOZO_STATUE_BEHAVIOR_HINT)
                gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_LEG_IDLE;
            else
                gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_DO_NOTHING;
            break;

        case CHOZO_STATUE_PART_EYE:
            gCurrentSprite.drawDistanceTopOffset = 0x8;
            gCurrentSprite.drawDistanceBottomOffset = 0x8;
            gCurrentSprite.drawDistanceHorizontalOffset = 0x8;

            gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_DO_NOTHING;
            gCurrentSprite.animationDurationCounter = 0x0;
            gCurrentSprite.currentAnimationFrame = 0x0;

            if (behavior == CHOZO_STATUE_BEHAVIOR_HINT)
                gCurrentSprite.pOam = sChozoStatuePartOAM_EyeClosed;
            else
                gCurrentSprite.pOam = sChozoStatuePartOAM_EyeOpened;
            break;

        case CHOZO_STATUE_PART_GLOW:
            gCurrentSprite.drawDistanceTopOffset = 0x10;
            gCurrentSprite.drawDistanceBottomOffset = 0x1;
            gCurrentSprite.drawDistanceHorizontalOffset = 0xC;

            gCurrentSprite.pOam = sChozoStatuePartOAM_GlowIdle;
            gCurrentSprite.animationDurationCounter = 0x0;
            gCurrentSprite.currentAnimationFrame = 0x0;

            gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_GLOW_IDLE;
            gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
            break;

        default:
            gCurrentSprite.status = 0x0;
    }
}

/**
 * @brief 14738 | 5c | Handles the glow being idle
 * 
 */
void ChozoStatuePartGlowIdle(void)
{
    u8 ramSlot;

    // Arm part slot
    ramSlot = gCurrentSprite.workVariable;

    if (gSpriteData[ramSlot].pOam == sChozoStatuePartOAM_ArmGlow)
    {
        // Display if arm has glow
        if (gCurrentSprite.status & SPRITE_STATUS_NOT_DRAWN)
        {
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            gCurrentSprite.animationDurationCounter = 0x0;
            gCurrentSprite.currentAnimationFrame = 0x0;
        }
    }
    else if (!(gCurrentSprite.status & SPRITE_STATUS_NOT_DRAWN))
        gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
}

/**
 * @brief 14794 | a0 | Detects if Samus in in the hand (for a hint)
 * 
 */
void ChozoStatuePartArmCheckGrabSamusHint(void)
{
    u8 ramSlot;
    u16 xPosition;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;
    xPosition = gCurrentSprite.xPosition;

    // Get X offset
    if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
        xPosition += CHOZO_STATUE_HAND_X_OFFSET;
    else
        xPosition -= CHOZO_STATUE_HAND_X_OFFSET;

    // In range, chozo statue is idle, either morph ball or rolling
    if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_IDLE &&
        gSamusData.yPosition == gCurrentSprite.yPosition - CHOZO_STATUE_HAND_Y_OFFSET &&
        gSamusData.xPosition > xPosition - QUARTER_BLOCK_SIZE && gSamusData.xPosition < xPosition + QUARTER_BLOCK_SIZE &&
        (u8)(gSamusData.pose - SPOSE_MORPH_BALL) < (SPOSE_UNMORPHING - SPOSE_MORPH_BALL))
    {
        // Set pose
        SamusSetPose(SPOSE_GRABBED_BY_CHOZO_STATUE);
        
        // Update statue
        gSpriteData[ramSlot].pose = CHOZO_STATUE_POSE_REGISTER_HINT;
        
        gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_SITTING;

        // Set samus grabbed
        gCurrentSprite.pOam = sChozoStatuePartOAM_ArmSamusGrabbed;
        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;

        gDisablePause = TRUE;
    }
}

/**
 * @brief 14834 | 30 | Synchronizes Samus' position with the hand position
 * 
 */
void ChozoStatuePartSyncSamusPosition(void)
{
    gSamusData.yPosition = gCurrentSprite.yPosition - CHOZO_STATUE_HAND_Y_OFFSET;

    if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
        gSamusData.xPosition = gCurrentSprite.xPosition + CHOZO_STATUE_HAND_X_OFFSET;
    else
        gSamusData.xPosition = gCurrentSprite.xPosition - CHOZO_STATUE_HAND_X_OFFSET;
}

/**
 * @brief 14864 | 44 | Handles the arm part sitting
 * 
 */
void ChozoStatuePartArmSitting(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    // Check set seated
    if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_DELAY_AFTER_SITTING)
        gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_SEATED;

    ChozoStatuePartSyncSamusPosition();

    // Spawn echo
    if (gSubSpriteData1.workVariable2)
        SpawnChozoStatueMovement(gSubSpriteData1.workVariable2);
}

/**
 * @brief 148a8 | 40 | Handles the arm part being seated
 * 
 */
void ChozoStatuePartArmSeated(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    ChozoStatuePartSyncSamusPosition();

    if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_IDLE)
    {
        gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_CHECK_GRAB_SAMUS_REFILL;
        gDisablePause = FALSE;
    }
}

/**
 * @brief 148e8 | fc | Detects if Samus in in the hand (for a refill)
 * 
 */
void ChozoStatuePartArmCheckGrabSamusRefill(void)
{
    u8 ramSlot;
    u8 isGrabbed;
    u16 xPosition;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    // Update OAM
    if (gCurrentSprite.pOam == sChozoStatuePartOAM_ArmIdle && gPreventMovementTimer == 0x0 &&
        ChozoStatueGetBehavior(gSpriteData[ramSlot].spriteId) != CHOZO_STATUE_BEHAVIOR_ITEM)
        gCurrentSprite.pOam = sChozoStatuePartOAM_ArmGlow;

    isGrabbed = FALSE;
    xPosition = gCurrentSprite.xPosition;

    // Get X offset
    if (gCurrentSprite.status & SPRITE_STATUS_XFLIP)
        xPosition += CHOZO_STATUE_HAND_X_OFFSET;
    else
        xPosition -= CHOZO_STATUE_HAND_X_OFFSET;

    // In range, chozo statue is idle
    if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_IDLE &&
        gSamusData.yPosition == gCurrentSprite.yPosition - CHOZO_STATUE_HAND_Y_OFFSET &&
        gSamusData.xPosition > xPosition - QUARTER_BLOCK_SIZE && gSamusData.xPosition < xPosition + QUARTER_BLOCK_SIZE)
    {
        if (gSamusData.pose == SPOSE_MORPH_BALL)
        {
            // Set grabbed
            SamusSetPose(SPOSE_GRABBED_BY_CHOZO_STATUE);
            isGrabbed++;
        }
        else if (gSamusData.pose == SPOSE_GRABBED_BY_CHOZO_STATUE)
            isGrabbed++; // Already grabbed

        if (isGrabbed)
        {
            gSpriteData[ramSlot].pose = CHOZO_STATUE_POSE_REFILL_INIT;
            gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_REFILL;

            ChozoStatuePartSyncSamusPosition();

            gCurrentSprite.pOam = sChozoStatuePartOAM_ArmSamusGrabbed;
            gCurrentSprite.animationDurationCounter = 0x0;
            gCurrentSprite.currentAnimationFrame = 0x0;

            gCurrentSprite.timer = 0x1E;
        }
    }
}

/**
 * @brief 149e4 | 140 | Refills Samus
 * 
 */
void ChozoStatuePartArmRefill(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_REFILL)
    {
        if (gCurrentSprite.timer == 0x1E)
        {
            // Refill energy
            if (!SpriteUtilRefillEnergy())
            {
                gCurrentSprite.timer--;
                gEnergyRefillAnimation = 0xD;
            }
        }
        else if (gCurrentSprite.timer == 0x1D)
        {
            // Refill missiles
            if (gEnergyRefillAnimation != 0x0)
                gEnergyRefillAnimation--;
            else if (!SpriteUtilRefillMissiles())
            {
                gCurrentSprite.timer--;
                gMissileRefillAnimation = 0xD;
            }
        }
        else if (gCurrentSprite.timer == 0x1C)
        {
            // Refill super missiles
            if (gMissileRefillAnimation != 0x0)
                gMissileRefillAnimation--;
            else if (!SpriteUtilRefillSuperMissiles())
            {
                gCurrentSprite.timer--;
                gSuperMissileRefillAnimation = 0xD;
            }
        }
        else if (gCurrentSprite.timer == 0x1B)
        {
            // Refill power bombs
            if (gSuperMissileRefillAnimation != 0x0)
                gSuperMissileRefillAnimation--;
            else if (!SpriteUtilRefillPowerBombs())
            {
                gCurrentSprite.timer--;
                gPowerBombRefillAnimation = 0xD;
            }
        }
        else
        {
            // Check refill anim ended
            if (gPowerBombRefillAnimation != 0x0)
                gPowerBombRefillAnimation--;
            else if (gCurrentSprite.timer != 0x0)
                gCurrentSprite.timer--; // Update timer
            else
            {
                // Set sleeping
                gSpriteData[ramSlot].pose = CHOZO_STATUE_POSE_SLEEPING_INIT;
                gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_SLEEPING_INIT;

                // Spawn refill correct ended message
                if (gEquipment.maxMissiles == 0x0 && gEquipment.maxSuperMissiles == 0x0 && gEquipment.maxPowerBombs == 0x0)
                {
                    // Only energy
                    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, MESSAGE_ENERGY_TANK_RECHARGE_COMPLETE, 0x6,
                        gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0x0);
                }
                else
                {
                    // Energy and weapons
                    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, MESSAGE_WEAPONS_AND_ENERGY_RESTORED, 0x6,
                        gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0x0);
                }
            }
        }
    }
}

/**
 * @brief 14b24 | 4 | Empty function
 * 
 */
void ChozoStatuePart_Empty(void)
{
    return;
}

/**
 * @brief 14b28 | 30 | Initializes the arm part to be sleeping
 * 
 */
void ChozoStatuePartSleepingInit(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_SLEEPING)
        gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_ARM_SLEEPING;
}

/**
 * @brief 14b58 | 38 | Handles the arm part sleeping
 * 
 */
void ChozoStatuePartArmSleeping(void)
{
    // Check release samus
    if (gPreventMovementTimer == 0x0 && gCurrentSprite.pOam == sChozoStatuePartOAM_ArmSamusGrabbed)
    {
        // Release samus
        gCurrentSprite.pOam = sChozoStatuePartOAM_ArmIdle;
        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;

        SamusSetPose(SPOSE_MORPH_BALL);
    }
}

/**
 * @brief 14b90 | 20 | Initializes the eye part to be opening
 * 
 */
void ChozoStatuePartEyeOpeningInit(void)
{
    gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_EYE_OPENING;

    gCurrentSprite.pOam = sChozoStatuePartOAM_EyeOpening;
    gCurrentSprite.animationDurationCounter = 0x0;
    gCurrentSprite.currentAnimationFrame = 0x0;
}

/**
 * @brief 14bb0 | 2c | Handles the eye part opening
 * 
 */
void ChozoStatuePartEyeOpening(void)
{
    if (SpriteUtilCheckEndCurrentSpriteAnim())
    {
        gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_DO_NOTHING;

        // Set opened
        gCurrentSprite.pOam = sChozoStatuePartOAM_EyeOpened;
        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;
    }
}

/**
 * @brief 14bdc | 20 | Initializes the eye part to be closing
 * 
 */
void ChozoStatuePartEyeClosingInit(void)
{
    gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_EYE_CLOSING;

    gCurrentSprite.pOam = sChozoStatuePartOAM_EyeClosing;
    gCurrentSprite.animationDurationCounter = 0x0;
    gCurrentSprite.currentAnimationFrame = 0x0;
}

/**
 * @brief 14bfc | 2c | Handles the eye part closing
 * 
 */
void ChozoStatuePartEyeClosing(void)
{
    if (SpriteUtilCheckEndCurrentSpriteAnim())
    {
        gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_DO_NOTHING;

        // Set closed
        gCurrentSprite.pOam = sChozoStatuePartOAM_EyeClosed;
        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;
    }
}

/**
 * @brief 14c28 | 48 | Handles the leg part being idle
 * 
 */
void ChozoStatuePartLegIdle(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_SITTING)
    {
        // Spawn echo
        if (gSubSpriteData1.workVariable2 != 0x0)
            SpawnChozoStatueMovement(gSubSpriteData1.workVariable2);
    }
    else if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_DELAY_AFTER_SITTING)
        gCurrentSprite.pose = CHOZO_STATUE_PART_POSE_DO_NOTHING;
}

/**
 * @brief 14c70 | 148 | Chozo statue AI
 * 
 */
void ChozoStatue(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 0x1;

    switch (gCurrentSprite.pose)
    {
        case 0x0:
            ChozoStatueInit();
            break;

        case CHOZO_STATUE_POSE_IDLE:
            ChozoStatue_Empty();
            break;

        case CHOZO_STATUE_POSE_REGISTER_HINT:
            ChozoStatueRegisterHint();
            break;

        case CHOZO_STATUE_POSE_HINT_FLASHING:
            ChozoStatueHintFlashing();
            break;

        case CHOZO_STATUE_POSE_SITTING_INIT:
            ChozoStatueSittingInit();
            break;

        case CHOZO_STATUE_POSE_SITTING:
            ChozoStatueSitting();
            break;

        case CHOZO_STATUE_POSE_DELAY_AFTER_SITTING:
            ChozoStatueDelayBeforeRefillAfterHint();
            break;

        case CHOZO_STATUE_POSE_WAIT_FOR_ITEM_TO_BE_COLLECTED:
            ChozoStatueWaitForItemToBeCollected();
            break;

        case CHOZO_STATUE_POSE_TIMER_AFTER_ITEM:
            ChozoStatueTimerAfterItemGrabbed();
            break;

        case CHOZO_STATUE_POSE_REFILL_INIT:
            ChozoStatueRefillInit();
            break;

        case CHOZO_STATUE_POSE_REFILL:
            ChozoStatueRefillSamus();
            break;

        case CHOZO_STATUE_POSE_SLEEPING_INIT:
            ChozoStatueSleepingInit();
            break;

        case CHOZO_STATUE_POSE_SLEEPING:
            ChozoStatueSleeping();
    }

    SpriteUtilUpdateSubSprite1Anim();
    ChozoStatueSyncSubSprites();
}

/**
 * @brief 14db8 | 248 | Chozo statue part AI
 * 
 */
void ChozoStatuePart(void)
{
    u8 ramSlot;

    gCurrentSprite.ignoreSamusCollisionTimer = 0x1;
    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    switch (gCurrentSprite.pose)
    {
        case 0x0:
            ChozoStatuePartInit();
            break;

        case CHOZO_STATUE_PART_POSE_ARM_CHECK_GRAB_SAMUS_HINT:
            ChozoStatuePartArmCheckGrabSamusHint();
            break;

        case CHOZO_STATUE_PART_POSE_ARM_SITTING:
            ChozoStatuePartArmSitting();
            break;

        case CHOZO_STATUE_PART_POSE_ARM_SEATED:
            ChozoStatuePartArmSeated();
            break;

        case CHOZO_STATUE_PART_POSE_ARM_CHECK_GRAB_SAMUS_REFILL:
            ChozoStatuePartArmCheckGrabSamusRefill();
            break;

        case CHOZO_STATUE_PART_POSE_ARM_REFILL:
            ChozoStatuePartArmRefill();
            ChozoStatuePart_Empty();
            break;

        case CHOZO_STATUE_PART_POSE_ARM_SLEEPING_INIT:
            ChozoStatuePartSleepingInit();
            break;

        case CHOZO_STATUE_PART_POSE_ARM_SLEEPING:
            ChozoStatuePartArmSleeping();
            break;

        case CHOZO_STATUE_PART_POSE_EYE_OPENING_INIT:
            ChozoStatuePartEyeOpeningInit();
            break;

        case CHOZO_STATUE_PART_POSE_EYE_OPENING:
            ChozoStatuePartEyeOpening();
            break;

        case CHOZO_STATUE_PART_POSE_EYE_CLOSING_INIT:
            ChozoStatuePartEyeClosingInit();
            break;

        case CHOZO_STATUE_PART_POSE_EYE_CLOSING:
            ChozoStatuePartEyeClosing();
            break;

        case CHOZO_STATUE_PART_POSE_LEG_IDLE:
            ChozoStatuePartLegIdle();
            break;

        case CHOZO_STATUE_PART_POSE_GLOW_IDLE:
            ChozoStatuePartGlowIdle();

        case CHOZO_STATUE_PART_POSE_DO_NOTHING:
            break;
    }

    if (gCurrentSprite.roomSlot == CHOZO_STATUE_PART_LEG)
        ChozoStatueSyncSubSprites();
    else
        SpriteUtilSyncCurrentSpritePositionWithSubSpriteData1PositionAndOAM();

    gCurrentSprite.paletteRow = gSpriteData[ramSlot].paletteRow;
}

/**
 * @brief 15000 | a8 | Chozo statue refill AI
 * 
 */
void ChozoStatueRefill(void)
{
    u8 ramSlot;

    gCurrentSprite.ignoreSamusCollisionTimer = 0x1;
    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gCurrentSprite.pose == 0x0)
    {
        gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
        gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;

        gCurrentSprite.samusCollision = SSC_NONE;
        gCurrentSprite.drawOrder = 0x1;

        gCurrentSprite.drawDistanceTopOffset = 0x10;
        gCurrentSprite.drawDistanceBottomOffset = 0x10;
        gCurrentSprite.drawDistanceHorizontalOffset = 0x10;
        
        gCurrentSprite.hitboxTopOffset = 0x4;
        gCurrentSprite.hitboxBottomOffset = 0x4;
        gCurrentSprite.hitboxLeftOffset = 0x4;
        gCurrentSprite.hitboxRightOffset = 0x4;

        gCurrentSprite.pose = 0x9;

        gCurrentSprite.animationDurationCounter = 0x0;
        gCurrentSprite.currentAnimationFrame = 0x0;
        gCurrentSprite.pOam = sChozoStatueRefillOAM;

        SoundPlay(0x10F); // Chozo statue refill
    }
    else if (gSpriteData[ramSlot].pose == CHOZO_STATUE_POSE_SLEEPING)
    {
        gCurrentSprite.status = 0x0;
        SoundFade(0x10F, 0x1E); // Chozo statue refill
    }
}
