#ifndef GAME_OVER_H
#define GAME_OVER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

u32 GameOverSubroutine(void);
u32 GameOverProcessInput(void);
void GameOverUpdateTextGfx(void);
void GameOverInit(void);
void GameOverInit_Unused(void);
void GameOverVBlank(void);
void GameOverVBlank_Empty(void);
void GameOverUpdateLettersPalette(void);
void GameOverUpdateSamusHead(u8 action);
void GameOverProcessOAM(void);

#ifdef __cplusplus
}
#endif

#endif /* GAME_OVER_H */
