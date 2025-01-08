#include "mzm/data/cutscenes/internal_ridley_landing_data.h"
#include "mzm/cutscenes/ridley_landing.h"
#include "mzm/cutscenes/cutscene_utils.h"
#include "mzm/macros.h"

const struct CutsceneSubroutineData sRidleyLandingSubroutineData[5] = {
    {
        .pFunction = RidleyLandingInit,
        .oamLength = 1
    },
    {
        .pFunction = RidleyLandingShipInSpace,
        .oamLength = 1
    },
    {
        .pFunction = RidleyLandingShipLanding,
        .oamLength = 9
    },
    {
        .pFunction = RidleyLandingRidleyFlying,
        .oamLength = 2
    },
    {
        .pFunction = CutsceneEndFunction,
        .oamLength = 2
    }
};