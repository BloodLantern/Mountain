#ifndef BEFORE_CHARLIE_CUTSCENE
#define BEFORE_CHARLIE_CUTSCENE

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"

u8 BeforeCharlieSamusCloseUp(void);
u8 BeforeCharlieWallAndGreyVoice(void);
void BeforeCharlieWallAndGreyVoiceScrollAndLoadYoungSamusGfx(struct CutsceneGraphicsData* pGraphics);
void BeforeCharlieWallAndGreyVoiceApplyMonochrome(struct CutsceneGraphicsData* pGraphics);
void BeforeCharlieWallAndGreyScrollCloseUp(struct CutsceneGraphicsData* pGraphics);
u8 BeforeCharlieChozoWallSides(void);
u8 BeforeCharlieInit(void);
u8 BeforeCharlieSubroutine(void);

#ifdef __cplusplus
}
#endif

#endif /* BEFORE_CHARLIE_CUTSCENE */
