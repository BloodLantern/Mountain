#ifndef SYSCALL_WRAPPERS_H
#define SYSCALL_WRAPPERS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void CallLZ77UncompVram(const void *src, void *dst);
void CallLZ77UncompWram(const void *src, void *dst);
void TestDivArm(void);
void CallSoundbias(void);
int CallMultiboot(void *mbp);
void CallVBlankIntrWait(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSCALL_WRAPPERS_H */
