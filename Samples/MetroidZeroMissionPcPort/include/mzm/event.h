#ifndef EVENT_H
#define EVENT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

extern u32 gEventsTriggered[8];

u32 EventFunction(u8 action, u8 event);

#ifdef __cplusplus
}
#endif

#endif /* EVENT_H */
