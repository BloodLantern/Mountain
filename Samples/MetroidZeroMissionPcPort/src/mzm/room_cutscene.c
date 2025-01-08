#include "mzm/animated_graphics.h"
#include "mzm/types.h"
#include "mzm/gba.h"

#include "mzm/transparency.h"
#include "mzm/room.h"
#include "mzm/scroll.h"
#include "mzm/connection.h"

#include "mzm/structs/bg_clip.h"
#include "mzm/structs/display.h"
#include "mzm/structs/room.h"

/**
 * @brief 57d04 | c8 | Loads a room for the escape sequence
 * 
 * @param area Area
 * @param room Room id + 1
 * @param bgX Backgrounds X position
 * @param bgY Backgrounds Y position
 */
void LoadRoomCutscene(u8 area, u8 room, u16 bgX, u16 bgY)
{
    // Set backgrounds position
    gBg0XPosition = bgX;
    gBg0YPosition = bgY;
    gBg1XPosition = bgX;
    gBg1YPosition = bgY;
    gBg2XPosition = bgX;
    gBg2YPosition = bgY;

    // Set area and room
    gCurrentArea = area;
    gCurrentRoom = room - 1;

    // Load room
    RoomLoadEntry();

    // Load room graphics
    RoomLoadTileset();
    RoomLoadBackgrounds();

    // Remove blocks and tanks
    RoomRemoveNeverReformBlocksAndCollectedTanks();

    // Setup transparency
    TransparencySetRoomEffectsTransparency();
    
    // Properly update background 3 position
    ScrollBg3();

    // Check play room effects
    AnimatedGraphicsCheckPlayLightningEffect();

    // Properly 
    RoomUpdateBackgroundsPosition();

    // Load doors
    ConnectionLoadDoors();
    ConnectionCheckHatchLockEvents();

    // Set tilemaps for the background 0, 1 and 2
    RoomSetInitialTilemap(0);
    RoomSetInitialTilemap(1);
    RoomSetInitialTilemap(2);

    // Load animated graphics
    AnimatedGraphicsLoad();

    // Transfer background 3 map
    DmaTransfer(3, gDecompBg3Map, gVramBuffer + 0x3000, sizeof(gDecompBg3Map), 16);

    write16(REG_BG0CNT, gIoRegistersBackup.BG0CNT);
    write16(REG_BG3CNT, gIoRegistersBackup.BG3CNT);
}
