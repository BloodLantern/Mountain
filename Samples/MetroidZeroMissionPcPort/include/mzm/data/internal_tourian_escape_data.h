#ifndef INTERNAL_TOURIAN_ESCAPE_DATA_H
#define INTERNAL_TOURIAN_ESCAPE_DATA_H

#include "mzm/types.h"
#include "mzm/macros.h"

typedef u8 (*TourianEscapeFunc_T)(void);

extern const TourianEscapeFunc_T sTourianEscapeSubroutinePointers[12];

#endif /* INTERNAL_TOURIAN_ESCAPE_DATA_H */