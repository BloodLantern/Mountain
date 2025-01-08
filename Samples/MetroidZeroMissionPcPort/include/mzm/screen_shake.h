#ifndef SCREEN_SHAKE_H
#define SCREEN_SHAKE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

u8 ScreenShakeStartVertical(u8 duration, u8 unk);
u8 ScreenShakeStartHorizontal(u8 duration, u8 unk);
u8 ScreenShakeStartHorizontal_Unused(u8 duration);
s32 ScreenShakeUpdateVertical(void);
s32 ScreenShakeUpdateHorizontal(void);

#ifdef __cplusplus
}
#endif

#endif /* SCREEN_SHAKE_H */
