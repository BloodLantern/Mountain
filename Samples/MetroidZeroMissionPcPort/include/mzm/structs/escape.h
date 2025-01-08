#ifndef ESCAPE_STRUCT_H
#define ESCAPE_STRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

// Structs

struct EscapeDigits {
    u8 hundredths;
    u8 tenths;
    u8 secondsOnes;
    u8 secondsTens;
    u8 minutesOnes;
    u8 minutesTens;
};

// Globals

extern u8 gCurrentEscapeStatus;
extern u8 gEscapeTimerCounter;
extern struct EscapeDigits gEscapeTimerDigits;

#define CREATE_ESCAPE_TIMER(minutes, seconds, milli)\
{\
    gEscapeTimerDigits.hundredths = (milli) % 10;\
    gEscapeTimerDigits.tenths = (milli) / 10;\
    gEscapeTimerDigits.secondsOnes = (seconds) % 10;\
    gEscapeTimerDigits.secondsTens = (seconds) / 10;\
    gEscapeTimerDigits.minutesOnes = (minutes) % 10;\
    gEscapeTimerDigits.minutesTens = (minutes) / 10;\
}

#ifdef __cplusplus
}
#endif

#endif /* ESCAPE_STRUCT_H */
