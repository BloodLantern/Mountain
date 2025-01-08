#ifndef ROOM_H
#define ROOM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void RoomLoad(void);
void RoomLoadTileset(void);
void RoomLoadEntry(void);
void RoomLoadBackgrounds(void);
void RoomRemoveNeverReformBlocksAndCollectedTanks(void);
void RoomReset(void);
void RoomSetBackgroundScrolling(void);
void RoomSetInitialTilemap(u8 bgNumber);
u32 RoomRleDecompress(u8 isBG, const u8* src, u8* dst);
void RoomUpdateGfxInfo(void);
void RoomUpdateAnimatedGraphicsAndPalettes(void);
void RoomUpdateHatchFlashingAnimation(void);
void RoomUpdate(void);
void RoomUpdateBackgroundsPosition(void);
void RoomUpdateVerticalTilemap(s32 offset);
void RoomUpdateHorizontalTilemap(s32 offset);
void RoomCheckDMA3Ended(void);

#ifdef __cplusplus
}
#endif

#endif /* ROOM_H */
