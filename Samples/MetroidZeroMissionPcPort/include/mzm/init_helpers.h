#ifndef INIT_HELPERS_H
#define INIT_HELPERS_H

#ifdef __cplusplus
extern "C"
{
#endif

void ClearGfxRam(void);
void LoadInterruptCode(void);
void ResetFreeOam(void);

#ifdef __cplusplus
}
#endif

#endif /* INIT_HELPERS_H */
