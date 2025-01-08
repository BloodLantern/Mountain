#ifndef DEMO_INPUT_H
#define DEMO_INPUT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void DemoMainLoop(void);
void RecordDemo(void);
void UpdateDemoInput(void);
void CopyDemoInput(void);
void DemoResetInputAndDuration(void);

#ifdef __cplusplus
}
#endif

#endif /* DEMO_INPUT_H */
