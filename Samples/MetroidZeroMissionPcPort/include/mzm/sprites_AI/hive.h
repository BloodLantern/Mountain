#ifndef HIVE_AI_H
#define HIVE_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/sprite.h"

void HiveSpawnParticle(void);
void HiveInit(void);
u8 HiveCountMellows(void);
void HivePhase1(void);
void HivePhase2(void);
void HivePhase3(void);
void HiveDying(void);
void HiveIgnoreSamusCollision(void);
void HiveRootsInit(void);
void HiveRootsMove(void);
void MellowInit(struct SpriteData* pSprite);
void MellowIdle(struct SpriteData* pSprite);
void MellowFleeing(struct SpriteData* pSprite);
void MellowSamusDetectedInit(struct SpriteData* pSprite);
void MellowMove(struct SpriteData* pSprite);
void Hive(void);
void HiveRoots(void);
void Mellow(void);
void MellowSwarm(void);

#ifdef __cplusplus
}
#endif

#endif /* HIVE_AI_H */
