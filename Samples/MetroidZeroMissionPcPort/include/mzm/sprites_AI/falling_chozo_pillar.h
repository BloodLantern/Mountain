#ifndef FALLING_CHOZO_PILLAR_AI_H
#define FALLING_CHOZO_PILLAR_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define FALLING_CHOZO_PILLAR_POSE_CHECK_SUIT_ANIM_ENDED 0x9
#define FALLING_CHOZO_PILLAR_POSE_CHECK_ON_SCREEN 0x23
#define FALLING_CHOZO_PILLAR_POSE_FALLING 0x25
#define FALLING_CHOZO_PILLAR_POSE_FALLEN 0x27
#define FALLING_CHOZO_PILLAR_POSE_IDLE 0x29

void FallingChozoPillar(void);

#ifdef __cplusplus
}
#endif

#endif /* FALLING_CHOZO_PILLAR_AI_H */
