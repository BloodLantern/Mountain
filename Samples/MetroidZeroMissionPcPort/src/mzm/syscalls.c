#include "mzm/syscalls.h"
#include <stdint.h>
#include <stdio.h>

void CpuFastSet(void *src, void *dst, u16 size)
{

}

void CpuSet(void *src, void *dst, u32 size)
{

}

s32 DivarmDiv(s32 number, s32 denom)
{
    return number / denom;
}

s32 DivarmMod(s32 denom, s32 number)
{
    return number % denom;
}

void LZ77UncompVRAM(const void *src, void *dst)
{
    s32 remaining = *(const u32*)src >> 8;
	src = (const u8*)src + 4;
	s32 blocksRemaining = 0;
	u8* disp;
	s32 bytes;
	s32 byte;
	s32 halfword = 0;
	int blockheader = 0;
    s32 width = 2;

	while (remaining > 0) {
		if (blocksRemaining) {
			if (blockheader & 0x80) {
				// Compressed
				int block = ((u8*)src)[1] | (((u8*)src)[0] << 8);
				src = (const u8*)src + 2;
				disp = (u8*)dst - (block & 0x0FFF) - 1;
				bytes = (block >> 12) + 3;
				while (bytes--) {
					if (remaining) {
						--remaining;
					} else {
						printf("Corrupted LZ77 data\n");
					}
					if (width == 2) {
                        u16* dstAligned = (u16*)((size_t)disp & ~1);
						byte = *dstAligned;
						if ((size_t)dst & 1) {
							byte >>= ((size_t)disp & 1) * 8;
							halfword |= byte << 8;
                            *(u16*)((size_t)dst ^ 1) = halfword;
						} else {
							byte >>= ((size_t)disp & 1) * 8;
							halfword = byte & 0xFF;
						}
					} else {
						byte = *disp;
                        *(u8*)dst = byte;
					}
					++disp;
					dst = (u8*)dst + 1;
				}
			} else {
				// Uncompressed
				byte = *(const u8*)src;
				src = (const u8*)src + 1;
				if (width == 2) {
					if ((size_t)dst & 1) {
						halfword |= byte << 8;

                        void* dstAligned = (void*)((size_t)dst ^ 1);
						*(u16*)dstAligned = halfword;
					} else {
						halfword = byte;
					}
				} else {
					*(u8*)dst = byte;
				}
				dst = (u8*)dst + 1;
				--remaining;
			}
			blockheader <<= 1;
			--blocksRemaining;
		} else {
			blockheader = *(const u8*)src;
			src = (const u8*)src + 1;
			blocksRemaining = 8;
		}
	}
}

void LZ77UncompWRAM(const void *src, void *dst)
{
    s32 remaining = *(u32*)src >> 8;
	src = (const u8*)src + 4;
	s32 blocksRemaining = 0;
	u8* disp;
	s32 bytes;
	s32 byte;
	s32 halfword = 0;
	int blockheader = 0;
    s32 width = 1;

	while (remaining > 0) {
		if (blocksRemaining) {
			if (blockheader & 0x80) {
				// Compressed
				int block = ((u8*)src)[1] | (((u8*)src)[0] << 8);
				src = (const u8*)src + 2;
				disp = (u8*)dst - (block & 0x0FFF) - 1;
				bytes = (block >> 12) + 3;
				while (bytes--) {
					if (remaining) {
						--remaining;
					} else {
						printf("Corrupted LZ77 data\n");
					}
					if (width == 2) {
                        u16* dstAligned = (u16*)((size_t)disp & ~1);
						byte = *dstAligned;
						if ((size_t)dst & 1) {
							byte >>= ((size_t)disp & 1) * 8;
							halfword |= byte << 8;
                            *(u16*)((size_t)dst ^ 1) = halfword;
						} else {
							byte >>= ((size_t)disp & 1) * 8;
							halfword = byte & 0xFF;
						}
					} else {
						byte = *disp;
                        *(u8*)dst = byte;
					}
					++disp;
					dst = (u8*)dst + 1;
				}
			} else {
				// Uncompressed
				byte = *(const u8*)src;
				src = (const u8*)src + 1;
				if (width == 2) {
					if ((size_t)dst & 1) {
						halfword |= byte << 8;

                        void* dstAligned = (void*)((size_t)dst ^ 1);
						*(u16*)dstAligned = halfword;
					} else {
						halfword = byte;
					}
				} else {
					*(u8*)dst = byte;
				}
				dst = (u8*)dst + 1;
				--remaining;
			}
			blockheader <<= 1;
			--blocksRemaining;
		} else {
			blockheader = *(const u8*)src;
			src = (const u8*)src + 1;
			blocksRemaining = 8;
		}
	}
}

u32 Midikey2Freq(u32* wd, u8 mk, u8 fp)
{
    return 0;
}

int MultiBoot(void *mbp)
{
    return 0;
}

void SoundBias0(void)
{

}

void SoundBias200(void)
{

}

u16 Sqrt(u32 number)
{
    return 1;
}

void VBlankIntrWait(void)
{

}

