#ifndef FUNCS_H
#define FUNCS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

void unk_33dc(void);
void QueueSound(u16 id, u32 unk); /* TODO: unk type */
void StopOrFadeSound(u16 id, u32 unk); /* TODO: unk type */
void UpdateAudio();

#ifdef __cplusplus
}
#endif

#endif /* FUNCS_H */
