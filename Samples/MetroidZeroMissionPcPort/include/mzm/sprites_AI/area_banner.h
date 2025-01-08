#ifndef AREA_BANNER_AI_H
#define AREA_BANNER_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/location_text.h"

#define AREA_BANNER_POSE_SPAWN 0x8
#define AREA_BANNER_POSE_SCROLLING_UP 0x9
#define AREA_BANNER_POSE_STATIC 0x23
#define AREA_BANNER_POSE_REMOVING 0x25

void AreaBannerInit(void);
void AreaBannerSpawn(void);
void AreaBannerScrollingUp(void);
void AreaBannerStatic(void);
void AreaBannerCheckRemovingAnimEnded(void);
void AreaBanner(void);

#ifdef __cplusplus
}
#endif

#endif /* AREA_BANNER_AI_H */
