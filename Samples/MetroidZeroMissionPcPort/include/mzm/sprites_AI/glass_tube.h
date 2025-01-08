#ifndef GLASS_TUBE_AI_H
#define GLASS_TUBE_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define GLASS_TUBE_POSE_POWER_BOMB_COLLISION 0x9
#define GLASS_TUBE_POSE_IDLE 0xF
#define GLASS_TUBE_POSE_DELAY_BEFORE_CRACKING 0x23
#define GLASS_TUBE_POSE_CRACKING 0x25
#define GLASS_TUBE_POSE_BREAKING 0x27

void GlassTubeChangeCCAA(void);
void GlassTubeInit(void);
void GlassTubeCheckPowerBombCollision(void);
void GlassTubeDelayBeforeBreaking(void);
void GlassTubeCheckCrackingAnimEnded(void);
void GlassTubeCheckBreakingAnimEnded(void);
void GlassTube(void);

#ifdef __cplusplus
}
#endif

#endif /* GLASS_TUBE_AI_H */
