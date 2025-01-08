#ifndef BLACK_SPACE_PIRATE_AI_H
#define BLACK_SPACE_PIRATE_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define BLACK_SPACE_PIRATE_POSE_INACTIVE 0x1

void BlackSpacePirateProjectileCollision(void);
void BlackSpacePirateCollidingWithLaser(void);
void BlackSpacePirateInit(void);
void BlackSpacePirateCheckStartActing(void);
void BlackSpacePirateChargingLaserInit(void);
void BlackSpacePirateChargingLaser(void);
void BlackSpacePirateShootingInit(void);
void BlackSpacePirateShooting(void);
void BlackSpacePirateJumping(void);
void BlackSpacePirateWalkingAlerted(void);
void BlackSpacePirateDeath(u8 playSound);
void BlackSpacePirateHitByLaserInit(void);
void BlackSpacePirateHitByLaser(void);
void BlackSpacePirate(void);

#ifdef __cplusplus
}
#endif

#endif /* BLACK_SPACE_PIRATE_AI_H */
