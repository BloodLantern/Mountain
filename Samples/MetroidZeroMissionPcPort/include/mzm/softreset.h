#ifndef SOFTRESET_H
#define SOFTRESET_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

u32 SoftresetSubroutine(void);
void SoftresetInit(void);
void SoftresetVBlank(void);
void SoftresetVBlank_Empty(void);

#ifdef __cplusplus
}
#endif

#endif /* SOFTRESET_H */
