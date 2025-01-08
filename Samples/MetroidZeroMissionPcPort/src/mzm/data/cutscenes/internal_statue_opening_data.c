#include "mzm/data/cutscenes/internal_statue_opening_data.h"
#include "mzm/cutscenes/statue_opening.h"
#include "mzm/cutscenes/cutscene_utils.h"

const struct CutsceneSubroutineData sStatueOpeningSubroutineData[3] = {
    [0] = {
        .pFunction = StatueOpeningInit,
        .oamLength = 2
    },
    [1] = {
        .pFunction = StatueOpeningOpening,
        .oamLength = 2
    },
    [2] = {
        .pFunction = CutsceneEndFunction,
        .oamLength = 2
    }
};
