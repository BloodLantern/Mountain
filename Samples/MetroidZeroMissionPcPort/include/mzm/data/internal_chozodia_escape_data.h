#ifndef INTERNAL_CHOZODIA_ESCAPE_DATA
#define INTERNAL_CHOZODIA_ESCAPE_DATA

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

typedef u8 (*ChozodiaEscapeFunc_T)(void);

extern const ChozodiaEscapeFunc_T sChozodiaEscapeFunctionPointers[5];

#ifdef __cplusplus
}
#endif

#endif /* INTERNAL_CHOZODIA_ESCAPE_DATA */
