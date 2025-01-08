#ifndef STATUS_SCREEN_MENU_STRUCT_H
#define STATUS_SCREEN_MENU_STRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "mzm/types.h"

struct StatusScreenItemData {
    u8 group;
    u8 abilityOffset;
    u8 row;
    u8 unk_3;
};

struct StatusScreenItemAcquisitionData {
    u8 unk_0;
    u8 group;
    u8 abilityOffset;
    u8 unk_3;
};

#ifdef __cplusplus
}
#endif

#endif /* STATUS_SCREEN_MENU_STRUCT_H */
