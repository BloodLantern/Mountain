#ifndef CALLBACKS_H
#define CALLBACKS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

// Globals

extern Func_T gVBlankCallback;
extern Func_T gHBlankCallback;
extern Func_T gVCountCallback;
extern Func_T gSerialCommunicationCallback;
extern Func_T gTimer3Callback;

// Functions

void CallbackCallVblank(void);
void CallbackSetVBlank(Func_T callback);
void CallbackCallHBlank(void);
void CallbackSetHBlank(Func_T callback);
void CallbackCallVCount(void);
void CallbackSetVCount(Func_T callback);
void CallbackCallSerialCommunication(void);
void CallbackSetSerialCommunication(Func_T callback);
void CallbackCallTimer3(void);
void CallbackSetTimer3(Func_T callback);
void Callback_Empty(void);

#ifdef __cplusplus
}
#endif

#endif /* CALLBACKS_H */
