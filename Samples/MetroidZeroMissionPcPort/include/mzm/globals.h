#ifndef GLOBALS_H
#define GLOBALS_H

#include "callbacks.h"
#include "types.h"
#include "sprite_debris.h"
#include "room.h"
#include "particle.h"
#include "oam.h"
#include "screen_shake.h"
#include "display.h"
#include "samus.h"
#include "gba/keys.h"
#include "projectile.h"

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

#endif /* GLOBALS_H */
