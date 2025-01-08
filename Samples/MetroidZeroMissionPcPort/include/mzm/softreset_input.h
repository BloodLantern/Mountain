#ifndef SOFTRESET_INPUT_H
#define SOFTRESET_INPUT_H

#ifdef __cplusplus
extern "C"
{
#endif

void SoftresetVBlankCallback(void);
void SoftresetCheck(void);
void Softreset(void);

#ifdef __cplusplus
}
#endif

#endif /* SOFTRESET_INPUT_H */
