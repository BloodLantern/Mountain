#ifndef POWER_GRIP_AI_H
#define POWER_GRIP_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define POWER_GRIP_POSE_IDLE 0x9
#define POWER_GRIP_POSE_BEING_ACQUIRED 0x23

void PowerGrip(void);
void PowerGripGlow(void);

#ifdef __cplusplus
}
#endif

#endif /* POWER_GRIP_AI_H */
