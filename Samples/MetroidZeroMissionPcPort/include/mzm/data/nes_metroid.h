#ifndef NES_METROID_DATA_H
#define NES_METROID_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

typedef void (*NesEmuFunc_T)(void*);

extern const NesEmuFunc_T sNesEmuBootLoader;

extern const u8 sNesMetroidData_Text[18];
extern const u8 sNesMetroidData[];

#ifdef __cplusplus
}
#endif

#endif /* NES_METROID_DATA_H */

