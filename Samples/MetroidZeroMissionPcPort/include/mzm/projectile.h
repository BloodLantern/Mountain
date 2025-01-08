#ifndef PROJECTILE_H
#define PROJECTILE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/oam.h"
#include "mzm/structs/projectile.h"
#include "mzm/structs/sprite.h"

void ProjectileProcessNormalBeam(struct ProjectileData* pProj);
void ProjectileProcessLongBeam(struct ProjectileData* pProj);
void ProjectileProcessIceBeam(struct ProjectileData* pProj);
u32 ProjectileCheckWaveBeamHittingBlocks(struct ProjectileData* pProj);
void ProjectileProcessWaveBeam(struct ProjectileData* pProj);
void ProjectileProcessPlasmaBeam(struct ProjectileData* pProj);
void ProjectileProcessPistol(struct ProjectileData* pProj);
void ProjectileProcessChargedNormalBeam(struct ProjectileData* pProj);
void ProjectileProcessChargedLongBeam(struct ProjectileData* pProj);
void ProjectileProcessChargedIceBeam(struct ProjectileData* pProj);
void ProjectileProcessChargedWaveBeam(struct ProjectileData* pProj);
void ProjectileProcessChargedPlasmaBeam(struct ProjectileData* pProj);
void ProjectileProcessChargedPistol(struct ProjectileData* pProj);
void ProjectileDecrementMissileCounter(struct ProjectileData* pProj);
void ProjectileProcessMissile(struct ProjectileData* pProj);
void ProjectileDecrementSuperMissileCounter(struct ProjectileData* pProj);
void ProjectileProcessSuperMissile(struct ProjectileData* pProj);
void ProjectileMorphballLauncherCheckLaunchSamus(struct ProjectileData* pProj);
void ProjectileCheckSamusBombBounce(struct ProjectileData* pProj);
void ProjectileProcessBomb(struct ProjectileData* pProj);
void ProjectileProcess_Empty(struct ProjectileData* pProj);
void ProjectileProcessPowerBomb(struct ProjectileData* pProj);

#ifdef __cplusplus
}
#endif

#endif /* PROJECTILE_H */
