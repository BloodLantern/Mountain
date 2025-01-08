#include "mzm/data/internal_save_file_data.h"
#include "mzm/constants/connection.h"
#include "mzm/constants/samus.h"
#include "mzm/constants/game_state.h"

const struct SaveFileInfo sSaveFileInfo_Empty = {
    .exists = FALSE,
    .corruptionFlag = 0,
    .currentArea = AREA_BRINSTAR,
    .currentEnergy = 0,
    .maxEnergy = 0,
    .currentMissiles = 0,
    .maxMissiles = 0,
    .suitType = SUIT_NORMAL,
    .igtHours = 0,
    .igtMinutes = 0,
    .igtSconds = 0,
    .hasSaved = FALSE,
    .completedGame = FALSE,
    .introPlayed = FALSE,
    .language = LANGUAGE_JAPANESE,
    .difficulty = DIFF_NORMAL,
    .timeAttack = FALSE,
};
