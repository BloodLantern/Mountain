#ifndef PAUSE_SCREEN_MAP_MENU_H
#define PAUSE_SCREEN_MAP_MENU_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/menu.h"
#include "mzm/structs/cutscene.h"

void PauseScreenCountTanksInArea(void);
void PauseScreenDrawIgtAndTanks(u8 param_1, u8 drawTanks);
void PauseScreenInitMapDownload(void);
u32 PauseScreenMapDownloadSubroutine(void);
u32 PauseScreenMapDownloadInstant_Unused(void);
u32 PauseScreenMapDownloadInstantWithLine_Unused(void);
u32 PauseScreenMapDownload(void);
void unk_6db58(u8 param_1);
void PauseScreenMapGetAbsoluteMapBordersPositions(void);
void PauseScreenMapUpdateMapBordersForTargets(void);
void PauseScreenGetAllMinimapData(u8 start);
void PauseScreenMapCheckExploredAreas(void);
void MapScreenSubroutine(void);
void MapScreenTogglehWorldMap(u8 notOpeningWorldMap);
void MapScreenChangeMap(void);

#ifdef __cplusplus
}
#endif

#endif /* PAUSE_SCREEN_MAP_MENU_H */
