#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/callbacks.h"
#include "mzm/types.h"
#include "mzm/sprite_debris.h"
#include "mzm/room.h"
#include "mzm/particle.h"
#include "mzm/oam.h"
#include "mzm/screen_shake.h"
#include "mzm/display.h"
#include "mzm/samus.h"
#include "mzm/gba/keys.h"
#include "mzm/projectile.h"

// IWRAM


union TileData {
    struct {
        u32 tile:10;
        u32 flip:2;
        u32 palette:4;
    } split;

    u16 all;
};

///

extern struct BG2Movement gBg2Movement;
extern u16 gInterruptCode[0x100];

extern void *sp_sys;
extern void *sp_irq;
extern Func_T intr_vector[13];
extern u16 (*gIntrCodePointer)[0x100];

extern u16 gInterruptCheckFlag;

// IO

#ifdef __cplusplus
}
#endif

#endif /* GLOBALS_H */
