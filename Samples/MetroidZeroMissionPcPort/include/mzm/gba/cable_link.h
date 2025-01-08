#ifndef GBA_CABLE_LINK_H
#define GBA_CABLE_LINK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/memory.h"
#include "mzm/types.h"

#define REG_TM0CNT_L (gRegBuffer + 0x100)
#define REG_TM0CNT_H (gRegBuffer + 0x102)

#define REG_TM3CNT_L (gRegBuffer + 0x10C)
#define REG_TM3CNT_H (gRegBuffer + 0x10E)

#define REG_SIO_MULTI (gRegBuffer + 0x120)
#define REG_SIO (gRegBuffer + 0x128)
#define REG_SIO_DATA8 (gRegBuffer + 0x12A)
#define REG_RNCT (gRegBuffer + 0x134)

#define SIO_SHIFT_INTERNAL_CLOCK_FLAG (1 << 0)
#define SIO_SHIFT_INTERNAL_CLOCK_2MHZ (1 << 1)
#define SIO_STATE_HIGH_OR_NONE (1 << 2)
#define SIO_HIGH_DURING_INACTIVITY (1 << 3)
#define SIO_START_BIT_ACTIVE (1 << 7)
#define SIO_32BIT_TRANSFER (1 << 12)
#define SIO_NON_NORMAL_MODE (1 << 13)
#define SIO_IRQ_ENABLE (1 << 14)

#define TIMER_CONTROL_IRQ_ENABLE (1 << 6)
#define TIMER_CONTROL_ACTIVE (1 << 7)

#ifdef __cplusplus
}
#endif

#endif /* GBA_CABLE_LINK_H */
