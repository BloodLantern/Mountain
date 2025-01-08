#ifndef WAVER_AI_H
#define WAVER_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define WAVER_POSE_MOVING 0x9

void WaverInit(void);
void WaverMove(void);
void Waver(void);

#ifdef __cplusplus
}
#endif

#endif /* WAVER_AI_H */
