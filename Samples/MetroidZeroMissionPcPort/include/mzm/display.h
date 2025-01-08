#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

// Globals


// Structs


// Functions

void IoWriteRegisters(void);
void IoWriteRegistersDuringTransition(void);
void IoUpdateDISPCNT(u8 operation, u16 value);

#ifdef __cplusplus
}
#endif

#endif /* DISPLAY_H */
