#ifndef DEMO_H
#define DEMO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void DemoVBlank(void);
void DemoStart(void);
void DemoInit(void);
void unk_60cbc(u8 param_1);
void DemoEnd(void);

#ifdef __cplusplus
}
#endif

#endif /* DEMO_H */
