#ifndef ESCAPE_H
#define ESCAPE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

// Functions

u8 EscapeDetermineTimer(void);
u8 EscapeCheckHasEscaped(void);
void EscapeUpdateOam(void);
void EscapeCheckReloadGraphics(void);
void EscapeStart(void);
void EscapeSetTimer(void);
void EscaepUpdateTimer(void);

#ifdef __cplusplus
}
#endif

#endif /* ESCAPE_H */
