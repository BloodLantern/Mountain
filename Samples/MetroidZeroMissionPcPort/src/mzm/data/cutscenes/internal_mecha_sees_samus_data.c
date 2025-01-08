#include "mzm/data/cutscenes/internal_mecha_sees_samus_data.h"
#include "mzm/cutscenes/mecha_sees_samus.h"
#include "mzm/cutscenes/cutscene_utils.h"
#include "mzm/macros.h"

const struct CutsceneSubroutineData sMechaSeesSamusSubroutineData[3] = {
    {
        .pFunction = MechaRidleySeesSamusInit,
        .oamLength = 2
    },
    {
        .pFunction = MechaRidleySeesSamusEyeOpen,
        .oamLength = 2
    },
    {
        .pFunction = CutsceneEndFunction,
        .oamLength = 2
    }
};
