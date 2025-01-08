#ifndef ESCAPE_SHIP_SPACE_PIRATE_AI_H
#define ESCAPE_SHIP_SPACE_PIRATE_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

#define ESCAPE_SHIP_SPACE_PIRATE_SPAWN 0x1
#define ESCAPE_SHIP_SPACE_PIRATE_DELAY_BEFORE_JUMPING 0x2

void EscapeShipSpacePirateInit(void);
void EscapeShipSpacePirateSpawn(void);
void EscapeShipSpacePirateDelayBeforeJumping(void);
void EscapeShipSpacePirate(void);

#ifdef __cplusplus
}
#endif

#endif /* ESCAPE_SHIP_SPACE_PIRATE_AI_H */
