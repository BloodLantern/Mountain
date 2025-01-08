#ifndef STATUE_OPENING_CUTSCENE
#define STATUE_OPENING_CUTSCENE

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"
#include "mzm/structs/cutscene.h"

#define STATUE_OPENING_OAM_ID_KRAID_IDLE 1
#define STATUE_OPENING_OAM_ID_KRAID_ACTIVATING 2
#define STATUE_OPENING_OAM_ID_KRAID_ACTIVATED 3
#define STATUE_OPENING_OAM_ID_KRAID_OPENED 4
#define STATUE_OPENING_OAM_ID_RIDLEY_IDLE 5
#define STATUE_OPENING_OAM_ID_RIDLEY_ACTIVATING 6
#define STATUE_OPENING_OAM_ID_RIDLEY_ACTIVATED 7
#define STATUE_OPENING_OAM_ID_RIDLEY_OPENED 8

u8 StatueOpeningOpening(void);
u8 StatueOpeningInit(void);
u8 StatueOpeningSubroutine(void);
void StatueOpeningProcessOAM(void);

#ifdef __cplusplus
}
#endif

#endif /* STATUE_OPENING_CUTSCENE */
