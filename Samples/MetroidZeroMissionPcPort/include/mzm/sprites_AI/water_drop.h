#ifndef WATER_DROP_AI_H
#define WATER_DROP_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define WATER_DROP_POSE_CHECK_SPAWNING_ENDED 0x9
#define WATER_DROP_POSE_SPLASHING_INIT 0xE
#define WATER_DROP_POSE_SPLASHING 0xF
#define WATER_DROP_POSE_SPAWNING 0x11
#define WATER_DROP_POSE_FALLING 0x1F

void WaterDropInit(void);
void WaterDrop(void);

#ifdef __cplusplus
}
#endif

#endif /* WATER_DROP_AI_H */
