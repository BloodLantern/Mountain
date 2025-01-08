#ifndef ZEBBO_AI_H
#define ZEBBO_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define ZEBBO_POSE_IDLE_INIT 0x8
#define ZEBBO_POSE_IDLE 0x9
#define ZEBBO_POSE_GOING_UP 0x23
#define ZEBBO_POSE_MOVING 0x25

void ZebboInit(void);
void ZebboIdleInit(void);
void ZebboIdle(void);
void ZebboGoingUp(void);
void ZebboRespawn(void);
void ZebboMove(void);
void Zebbo(void);

#ifdef __cplusplus
}
#endif

#endif /* ZEBBO_AI_H */
