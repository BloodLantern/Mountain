#ifndef FUSION_GALLERY_H
#define FUSION_GALLERY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void FusionGalleryVBlank(void);
void FusionGalleryInit(void);
u32 FusionGalleryDisplay(void);
u32 FusionGallerySubroutine(void);

#ifdef __cplusplus
}
#endif

#endif /* FUSION_GALLERY_H */
