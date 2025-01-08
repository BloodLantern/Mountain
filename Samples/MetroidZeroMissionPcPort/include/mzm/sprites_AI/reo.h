#ifndef REO_AI_H
#define REO_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define REO_POSE_IDLE_INIT 0x8
#define REO_POSE_IDLE 0x9
#define REO_POSE_MOVING_INIT 0x22
#define REO_POSE_MOVING 0x23

void ReoInit(void);
void ReoIdleInit(void);
void ReoIdle(void);
void ReoMovingInit(void);
void ReoMove(void);
void Reo(void);

#ifdef __cplusplus
}
#endif

#endif /* REO_AI_H */
