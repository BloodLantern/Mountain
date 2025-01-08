#ifndef GBA_AUDIO_H
#define GBA_AUDIO_H

#include "memory.h"

#define REG_SOUND1CNT_L (gRegBuffer + 0x60)
#define REG_SOUND1CNT_H (gRegBuffer + 0x62)
#define REG_SOUND1CNT_X (gRegBuffer + 0x64)

#define REG_SOUND2CNT_L (gRegBuffer + 0x68)
#define REG_SOUND2CNT_H (gRegBuffer + 0x6C)

#define REG_SOUND3CNT_L (gRegBuffer + 0x70)
#define REG_SOUND3CNT_H (gRegBuffer + 0x72)
#define REG_SOUND3CNT_X (gRegBuffer + 0x74)

#define REG_SOUND4CNT_L (gRegBuffer + 0x78)
#define REG_SOUND4CNT_H (gRegBuffer + 0x7C)

#define REG_SOUNDCNT_L (gRegBuffer + 0x80)
#define REG_SOUNDCNT_H (gRegBuffer + 0x82)

#define REG_SOUNDCNT_X (gRegBuffer + 0x84)
#define REG_SOUNDBIAS (gRegBuffer + 0x88)

#define REG_FIFO_A (gRegBuffer + 0xA0)
#define REG_FIFO_B (gRegBuffer + 0xA4)

#define SOUNDCNT_RESTART_SOUND (1 << 15)

#endif /* GBA_AUDIO_H */