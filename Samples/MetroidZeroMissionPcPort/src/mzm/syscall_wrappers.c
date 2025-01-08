#include "syscall_wrappers.h"

#include "syscalls.h"

void CallLZ77UncompVram(const void *src, void *dst)
{
    LZ77UncompVRAM(src, dst);
}

void CallLZ77UncompWram(const void *src, void *dst)
{
    LZ77UncompWRAM(src, dst);
}

void TestDivarmSqrt(void)
{
    DivarmDiv(1, 1);
    DivarmMod(1, 1);
    Sqrt(2);
}

void CallSoundbias(void)
{
    SoundBias0();
    SoundBias200();
}

int CallMultiboot(void *mbp)
{
    return MultiBoot(mbp);
}

void CallVBlankIntrWait(void)
{
    VBlankIntrWait();
}
