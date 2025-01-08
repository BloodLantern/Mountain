#ifndef OAM_ID_H
#define OAM_ID_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"
#include "mzm/structs/menu.h"

void UpdateMenuOamDataID(struct MenuOamData* pOam, u8 oamId);
void UpdateCutsceneOamDataID(struct CutsceneOamData* pOam, u8 oamId);

#ifdef __cplusplus
}
#endif

#endif /* OAM_ID_H */
