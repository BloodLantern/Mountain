#include "modern/debug.h"

#include "constants/clipdata.h"
#include "constants/game_state.h"
#include "constants/samus.h"
#include "constants/sprite.h"
#include "constants/projectile.h"

#include "macros.h"

#include "structs/bg_clip.h"
#include "structs/cutscene.h"
#include "structs/demo.h"
#include "structs/game_state.h"
#include "structs/samus.h"
#include "structs/sprite.h"
#include "structs/projectile.h"

#include <stdio.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "imgui/cimgui.h"

const char* const sPoseNames[SPOSE_END] = {
    [SPOSE_RUNNING] = "RUNNING",
    [SPOSE_STANDING] = "STANDING",
    [SPOSE_TURNING_AROUND] = "TURNING_AROUND",
    [SPOSE_SHOOTING] = "SHOOTING",
    [SPOSE_CROUCHING] = "CROUCHING",
    [SPOSE_TURNING_AROUND_AND_CROUCHING] = "TURNING_AROUND_AND_CROUCHING",
    [SPOSE_SHOOTING_AND_CROUCHING] = "SHOOTING_AND_CROUCHING",
    [SPOSE_SKIDDING] = "SKIDDING",
    [SPOSE_MIDAIR] = "MIDAIR",
    [SPOSE_TURNING_AROUND_MIDAIR] = "TURNING_AROUND_MIDAIR",
    [SPOSE_LANDING] = "LANDING",
    [SPOSE_STARTING_SPIN_JUMP] = "STARTING_SPIN_JUMP",
    [SPOSE_SPINNING] = "SPINNING",
    [SPOSE_STARTING_WALL_JUMP] = "STARTING_WALL_JUMP",
    [SPOSE_SPACE_JUMPING] = "SPACE_JUMPING",
    [SPOSE_SCREW_ATTACKING] = "SCREW_ATTACKING",
    [SPOSE_MORPHING] = "MORPHING",
    [SPOSE_MORPH_BALL] = "MORPH_BALL",
    [SPOSE_ROLLING] = "ROLLING",
    [SPOSE_UNMORPHING] = "UNMORPHING",
    [SPOSE_MORPH_BALL_MIDAIR] = "MORPH_BALL_MIDAIR",
    [SPOSE_HANGING_ON_LEDGE] = "HANGING_ON_LEDGE",
    [SPOSE_TURNING_TO_AIM_WHILE_HANGING] = "TURNING_TO_AIM_WHILE_HANGING",
    [SPOSE_HIDING_ARM_CANNON_WHILE_HANGING] = "HIDING_ARM_CANNON_WHILE_HANGING",
    [SPOSE_AIMING_WHILE_HANGING] = "AIMING_WHILE_HANGING",
    [SPOSE_SHOOTING_WHILE_HANGING] = "SHOOTING_WHILE_HANGING",
    [SPOSE_PULLING_YOURSELF_UP_FROM_HANGING] = "PULLING_YOURSELF_UP_FROM_HANGING",
    [SPOSE_PULLING_YOURSELF_FORWARD_FROM_HANGING] = "PULLING_YOURSELF_FORWARD_FROM_HANGING",
    [SPOSE_PULLING_YOURSELF_INTO_A_MORPH_BALL_TUNNEL] = "PULLING_YOURSELF_INTO_A_MORPH_BALL_TUNNEL",
    [SPOSE_USING_AN_ELEVATOR] = "USING_AN_ELEVATOR",
    [SPOSE_FACING_THE_FOREGROUND] = "FACING_THE_FOREGROUND",
    [SPOSE_TURNING_FROM_FACING_THE_FOREGROUND] = "TURNING_FROM_FACING_THE_FOREGROUND",
    [SPOSE_GRABBED_BY_CHOZO_STATUE] = "GRABBED_BY_CHOZO_STATUE",
    [SPOSE_DELAY_BEFORE_SHINESPARKING] = "DELAY_BEFORE_SHINESPARKING",
    [SPOSE_SHINESPARKING] = "SHINESPARKING",
    [SPOSE_SHINESPARK_COLLISION] = "SHINESPARK_COLLISION",
    [SPOSE_DELAY_AFTER_SHINESPARKING] = "DELAY_AFTER_SHINESPARKING",
    [SPOSE_DELAY_BEFORE_BALLSPARKING] = "DELAY_BEFORE_BALLSPARKING",
    [SPOSE_BALLSPARKING] = "BALLSPARKING",
    [SPOSE_BALLSPARK_COLLISION] = "BALLSPARK_COLLISION",
    [SPOSE_ON_ZIPLINE] = "ON_ZIPLINE",
    [SPOSE_SHOOTING_ON_ZIPLINE] = "SHOOTING_ON_ZIPLINE",
    [SPOSE_TURNING_ON_ZIPLINE] = "TURNING_ON_ZIPLINE",
    [SPOSE_MORPH_BALL_ON_ZIPLINE] = "MORPH_BALL_ON_ZIPLINE",
    [SPOSE_SAVING_LOADING_GAME] = "SAVING_LOADING_GAME",
    [SPOSE_DOWNLOADING_MAP_DATA] = "DOWNLOADING_MAP_DATA",
    [SPOSE_TURNING_AROUND_TO_DOWNLOAD_MAP_DATA] = "TURNING_AROUND_TO_DOWNLOAD_MAP_DATA",
    [SPOSE_GETTING_HURT] = "GETTING_HURT",
    [SPOSE_GETTING_KNOCKED_BACK] = "GETTING_KNOCKED_BACK",
    [SPOSE_GETTING_HURT_IN_MORPH_BALL] = "GETTING_HURT_IN_MORPH_BALL",
    [SPOSE_GETTING_KNOCKED_BACK_IN_MORPH_BALL] = "GETTING_KNOCKED_BACK_IN_MORPH_BALL",
    [SPOSE_DYING] = "DYING",
    [SPOSE_CROUCHING_TO_CRAWL] = "CROUCHING_TO_CRAWL",
    [SPOSE_CRAWLING_STOPPED] = "CRAWLING_STOPPED",
    [SPOSE_STARTING_TO_CRAWL] = "STARTING_TO_CRAWL",
    [SPOSE_CRAWLING] = "CRAWLING",
    [SPOSE_UNCROUCHING_FROM_CRAWLING] = "UNCROUCHING_FROM_CRAWLING",
    [SPOSE_TURNING_AROUND_WHILE_CRAWLING] = "TURNING_AROUND_WHILE_CRAWLING",
    [SPOSE_SHOOTING_WHILE_CRAWLING] = "SHOOTING_WHILE_CRAWLING",
    [SPOSE_UNCROUCHING_SUITLESS] = "UNCROUCHING_SUITLESS",
    [SPOSE_CROUCHING_SUITLESS] = "CROUCHING_SUITLESS",
    [SPOSE_GRABBING_A_LEDGE_SUITLESS] = "GRABBING_A_LEDGE_SUITLESS",
    [SPOSE_FACING_THE_BACKGROUND_SUITLESS] = "FACING_THE_BACKGROUND_SUITLESS",
    [SPOSE_TURNING_FROM_FACING_THE_BACKGROUND_SUITLESS] = "TURNING_FROM_FACING_THE_BACKGROUND_SUITLESS",
    [SPOSE_ACTIVATING_ZIPLINES] = "ACTIVATING_ZIPLINES",
    [SPOSE_IN_ESCAPE_SHIP] = "IN_ESCAPE_SHIP",
    [SPOSE_TURNING_TO_ENTER_ESCAPE_SHIP] = "TURNING_TO_ENTER_ESCAPE_SHIP",
};

const char* const sPrimarySpriteNames[PSPRITE_END] = {
    [PSPRITE_UNUSED0] = "UNUSED0",
    [PSPRITE_UNUSED1] = "UNUSED1",
    [PSPRITE_UNUSED2] = "UNUSED2",
    [PSPRITE_UNUSED3] = "UNUSED3",
    [PSPRITE_UNUSED4] = "UNUSED4",
    [PSPRITE_UNUSED5] = "UNUSED5",
    [PSPRITE_UNUSED6] = "UNUSED6",
    [PSPRITE_UNUSED7] = "UNUSED7",
    [PSPRITE_UNUSED8] = "UNUSED8",
    [PSPRITE_UNUSED9] = "UNUSED9",
    [PSPRITE_UNUSED10] = "UNUSED10",
    [PSPRITE_UNUSED11] = "UNUSED11",
    [PSPRITE_UNUSED12] = "UNUSED12",
    [PSPRITE_UNUSED13] = "UNUSED13",
    [PSPRITE_UNUSED14] = "UNUSED14",
    [PSPRITE_UNUSED15] = "UNUSED15",
    [PSPRITE_UNUSED16] = "UNUSED16",
    [PSPRITE_ITEM_BANNER] = "ITEM_BANNER",
    [PSPRITE_ZOOMER_YELLOW] = "ZOOMER_YELLOW",
    [PSPRITE_ZOOMER_RED] = "ZOOMER_RED",
    [PSPRITE_ZEELA] = "ZEELA",
    [PSPRITE_ZEELA_RED] = "ZEELA_RED",
    [PSPRITE_RIPPER_BROWN] = "RIPPER_BROWN",
    [PSPRITE_RIPPER_PURPLE] = "RIPPER_PURPLE",
    [PSPRITE_ZEB] = "ZEB",
    [PSPRITE_ZEB_BLUE] = "ZEB_BLUE",
    [PSPRITE_LARGE_ENERGY_DROP] = "LARGE_ENERGY_DROP",
    [PSPRITE_SMALL_ENERGY_DROP] = "SMALL_ENERGY_DROP",
    [PSPRITE_MISSILE_DROP] = "MISSILE_DROP",
    [PSPRITE_SUPER_MISSILE_DROP] = "SUPER_MISSILE_DROP",
    [PSPRITE_POWER_BOMB_DROP] = "POWER_BOMB_DROP",
    [PSPRITE_SKREE_GREEN] = "SKREE_GREEN",
    [PSPRITE_SKREE_BLUE] = "SKREE_BLUE",
    [PSPRITE_MORPH_BALL] = "MORPH_BALL",
    [PSPRITE_CHOZO_STATUE_LONG_HINT] = "CHOZO_STATUE_LONG_HINT",
    [PSPRITE_CHOZO_STATUE_LONG] = "CHOZO_STATUE_LONG",
    [PSPRITE_CHOZO_STATUE_ICE_HINT] = "CHOZO_STATUE_ICE_HINT",
    [PSPRITE_CHOZO_STATUE_ICE] = "CHOZO_STATUE_ICE",
    [PSPRITE_CHOZO_STATUE_WAVE_HINT] = "CHOZO_STATUE_WAVE_HINT",
    [PSPRITE_CHOZO_STATUE_WAVE] = "CHOZO_STATUE_WAVE",
    [PSPRITE_CHOZO_STATUE_BOMB_HINT] = "CHOZO_STATUE_BOMB_HINT",
    [PSPRITE_CHOZO_STATUE_BOMB] = "CHOZO_STATUE_BOMB",
    [PSPRITE_CHOZO_STATUE_SPEEDBOOSTER_HINT] = "CHOZO_STATUE_SPEEDBOOSTER_HINT",
    [PSPRITE_CHOZO_STATUE_SPEEDBOOSTER] = "CHOZO_STATUE_SPEEDBOOSTER",
    [PSPRITE_CHOZO_STATUE_HIGH_JUMP_HINT] = "CHOZO_STATUE_HIGH_JUMP_HINT",
    [PSPRITE_CHOZO_STATUE_HIGH_JUMP] = "CHOZO_STATUE_HIGH_JUMP",
    [PSPRITE_CHOZO_STATUE_SCREW_HINT] = "CHOZO_STATUE_SCREW_HINT",
    [PSPRITE_CHOZO_STATUE_SCREW] = "CHOZO_STATUE_SCREW",
    [PSPRITE_CHOZO_STATUE_VARIA_HINT] = "CHOZO_STATUE_VARIA_HINT",
    [PSPRITE_CHOZO_STATUE_VARIA] = "CHOZO_STATUE_VARIA",
    [PSPRITE_SOVA_PURPLE] = "SOVA_PURPLE",
    [PSPRITE_SOVA_ORANGE] = "SOVA_ORANGE",
    [PSPRITE_MULTIVIOLA] = "MULTIVIOLA",
    [PSPRITE_MULTIPLE_LARGE_ENERGY] = "MULTIPLE_LARGE_ENERGY",
    [PSPRITE_GERUTA_RED] = "GERUTA_RED",
    [PSPRITE_GERUTA_GREEN] = "GERUTA_GREEN",
    [PSPRITE_SQUEEPT] = "SQUEEPT",
    [PSPRITE_SQUEEPT_UNUSED] = "SQUEEPT_UNUSED",
    [PSPRITE_MAP_STATION] = "MAP_STATION",
    [PSPRITE_DRAGON] = "DRAGON",
    [PSPRITE_DRAGON_UNUSED] = "DRAGON_UNUSED",
    [PSPRITE_ZIPLINE] = "ZIPLINE",
    [PSPRITE_ZIPLINE_BUTTON] = "ZIPLINE_BUTTON",
    [PSPRITE_REO_GREEN_WINGS] = "REO_GREEN_WINGS",
    [PSPRITE_REO_PURPLE_WINGS] = "REO_PURPLE_WINGS",
    [PSPRITE_GUNSHIP] = "GUNSHIP",
    [PSPRITE_DEOREM] = "DEOREM",
    [PSPRITE_DEOREM_SECOND_LOCATION] = "DEOREM_SECOND_LOCATION",
    [PSPRITE_CHARGE_BEAM] = "CHARGE_BEAM",
    [PSPRITE_SKULTERA] = "SKULTERA",
    [PSPRITE_DESSGEEGA] = "DESSGEEGA",
    [PSPRITE_DESSGEEGA_AFTER_LONG_BEAM] = "DESSGEEGA_AFTER_LONG_BEAM",
    [PSPRITE_WAVER] = "WAVER",
    [PSPRITE_WAVER_UNUSED] = "WAVER_UNUSED",
    [PSPRITE_MELLOW] = "MELLOW",
    [PSPRITE_HIVE] = "HIVE",
    [PSPRITE_POWER_GRIP] = "POWER_GRIP",
    [PSPRITE_IMAGO_LARVA_RIGHT] = "IMAGO_LARVA_RIGHT",
    [PSPRITE_MORPH_BALL_LAUNCHER] = "MORPH_BALL_LAUNCHER",
    [PSPRITE_IMAGO_COCOON] = "IMAGO_COCOON",
    [PSPRITE_ELEVATOR_PAD] = "ELEVATOR_PAD",
    [PSPRITE_SPACE_PIRATE] = "SPACE_PIRATE",
    [PSPRITE_SPACE_PIRATE_WAITING1] = "SPACE_PIRATE_WAITING1",
    [PSPRITE_SPACE_PIRATE_WAITING2] = "SPACE_PIRATE_WAITING2",
    [PSPRITE_SPACE_PIRATE_WAITING3] = "SPACE_PIRATE_WAITING3",
    [PSPRITE_SPACE_PIRATE2] = "SPACE_PIRATE2",
    [PSPRITE_GAMET_BLUE_SINGLE] = "GAMET_BLUE_SINGLE",
    [PSPRITE_GAMET_RED_SINGLE] = "GAMET_RED_SINGLE",
    [PSPRITE_CHOZO_STATUE_GRAVITY] = "CHOZO_STATUE_GRAVITY",
    [PSPRITE_CHOZO_STATUE_SPACE_JUMP] = "CHOZO_STATUE_SPACE_JUMP",
    [PSPRITE_SECURITY_GATE_DEFAULT_OPEN] = "SECURITY_GATE_DEFAULT_OPEN",
    [PSPRITE_ZEBBO_GREEN] = "ZEBBO_GREEN",
    [PSPRITE_ZEBBO_YELLOW] = "ZEBBO_YELLOW",
    [PSPRITE_WORKER_ROBOT] = "WORKER_ROBOT",
    [PSPRITE_PARASITE_MULTIPLE] = "PARASITE_MULTIPLE",
    [PSPRITE_PARASITE] = "PARASITE",
    [PSPRITE_PISTON] = "PISTON",
    [PSPRITE_RIDLEY] = "RIDLEY",
    [PSPRITE_SECURITY_GATE_DEFAULT_CLOSED] = "SECURITY_GATE_DEFAULT_CLOSED",
    [PSPRITE_ZIPLINE_GENERATOR] = "ZIPLINE_GENERATOR",
    [PSPRITE_METROID] = "METROID",
    [PSPRITE_FROZEN_METROID] = "FROZEN_METROID",
    [PSPRITE_RINKA_ORANGE] = "RINKA_ORANGE",
    [PSPRITE_POLYP] = "POLYP",
    [PSPRITE_VIOLA_BLUE] = "VIOLA_BLUE",
    [PSPRITE_VIOLA_ORANGE] = "VIOLA_ORANGE",
    [PSPRITE_GERON_NORFAIR] = "GERON_NORFAIR",
    [PSPRITE_HOLTZ] = "HOLTZ",
    [PSPRITE_GEKITAI_MACHINE] = "GEKITAI_MACHINE",
    [PSPRITE_RUINS_TEST] = "RUINS_TEST",
    [PSPRITE_SAVE_PLATFORM] = "SAVE_PLATFORM",
    [PSPRITE_KRAID] = "KRAID",
    [PSPRITE_IMAGO_COCOON_AFTER_FIGHT] = "IMAGO_COCOON_AFTER_FIGHT",
    [PSPRITE_RIPPERII] = "RIPPERII",
    [PSPRITE_MELLA] = "MELLA",
    [PSPRITE_ATOMIC] = "ATOMIC",
    [PSPRITE_AREA_BANNER] = "AREA_BANNER",
    [PSPRITE_MOTHER_BRAIN] = "MOTHER_BRAIN",
    [PSPRITE_FAKE_POWER_BOMB_EVENT_TRIGGER] = "FAKE_POWER_BOMB_EVENT_TRIGGER",
    [PSPRITE_ACID_WORM] = "ACID_WORM",
    [PSPRITE_ESCAPE_SHIP] = "ESCAPE_SHIP",
    [PSPRITE_SIDEHOPPER] = "SIDEHOPPER",
    [PSPRITE_GEEGA] = "GEEGA",
    [PSPRITE_GEEGA_WHITE] = "GEEGA_WHITE",
    [PSPRITE_RINKA_MOTHER_BRAIN] = "RINKA_MOTHER_BRAIN",
    [PSPRITE_ZEBETITE_ONE_AND_THREE] = "ZEBETITE_ONE_AND_THREE",
    [PSPRITE_CANNON] = "CANNON",
    [PSPRITE_IMAGO_LARVA_RIGHT_SIDE] = "IMAGO_LARVA_RIGHT_SIDE",
    [PSPRITE_TANGLE_VINE_TALL] = "TANGLE_VINE_TALL",
    [PSPRITE_TANGLE_VINE_MEDIUM] = "TANGLE_VINE_MEDIUM",
    [PSPRITE_TANGLE_VINE_CURVED] = "TANGLE_VINE_CURVED",
    [PSPRITE_TANGLE_VINE_SHORT] = "TANGLE_VINE_SHORT",
    [PSPRITE_MELLOW_SWARM] = "MELLOW_SWARM",
    [PSPRITE_MELLOW_SWARM_HEALTH_BASED] = "MELLOW_SWARM_HEALTH_BASED",
    [PSPRITE_IMAGO] = "IMAGO",
    [PSPRITE_ZEBETITE_TWO_AND_FOUR] = "ZEBETITE_TWO_AND_FOUR",
    [PSPRITE_CANNON2] = "CANNON2",
    [PSPRITE_CANNON3] = "CANNON3",
    [PSPRITE_CROCOMIRE] = "CROCOMIRE",
    [PSPRITE_IMAGO_LARVA_LEFT] = "IMAGO_LARVA_LEFT",
    [PSPRITE_GERON_BRINSTAR_ROOM_15] = "GERON_BRINSTAR_ROOM_15",
    [PSPRITE_GERON_BRINSTAR_ROOM_1C] = "GERON_BRINSTAR_ROOM_1C",
    [PSPRITE_GERON_VARIA1] = "GERON_VARIA1",
    [PSPRITE_GERON_VARIA2] = "GERON_VARIA2",
    [PSPRITE_GERON_VARIA3] = "GERON_VARIA3",
    [PSPRITE_GLASS_TUBE] = "GLASS_TUBE",
    [PSPRITE_SAVE_PLATFORM_CHOZODIA] = "SAVE_PLATFORM_CHOZODIA",
    [PSPRITE_BARISTUTE] = "BARISTUTE",
    [PSPRITE_CHOZO_STATUE_PLASMA_BEAM] = "CHOZO_STATUE_PLASMA_BEAM",
    [PSPRITE_KRAID_ELEVATOR_STATUE] = "KRAID_ELEVATOR_STATUE",
    [PSPRITE_RIDLEY_ELEVATOR_STATUE] = "RIDLEY_ELEVATOR_STATUE",
    [PSPRITE_RISING_CHOZO_PILLAR] = "RISING_CHOZO_PILLAR",
    [PSPRITE_SECURITY_LASER_VERTICAL] = "SECURITY_LASER_VERTICAL",
    [PSPRITE_SECURITY_LASER_HORIZONTAL] = "SECURITY_LASER_HORIZONTAL",
    [PSPRITE_SECURITY_LASER_VERTICAL2] = "SECURITY_LASER_VERTICAL2",
    [PSPRITE_SECURITY_LASER_HORIZONTAL2] = "SECURITY_LASER_HORIZONTAL2",
    [PSPRITE_LOCK_UNLOCK_METROID_DOORS_UNUSED] = "LOCK_UNLOCK_METROID_DOORS_UNUSED",
    [PSPRITE_GAMET_BLUE_LEADER] = "GAMET_BLUE_LEADER",
    [PSPRITE_GAMET_BLUE_FOLLOWER] = "GAMET_BLUE_FOLLOWER",
    [PSPRITE_GEEGA_LEADER] = "GEEGA_LEADER",
    [PSPRITE_GEEGA_FOLLOWER] = "GEEGA_FOLLOWER",
    [PSPRITE_ZEBBO_GREEN_LEADER] = "ZEBBO_GREEN_LEADER",
    [PSPRITE_ZEBBO_GREEN_FOLLOWER] = "ZEBBO_GREEN_FOLLOWER",
    [PSPRITE_KRAID_STATUE] = "KRAID_STATUE",
    [PSPRITE_RIDLEY_STATUE] = "RIDLEY_STATUE",
    [PSPRITE_RINKA_GREEN] = "RINKA_GREEN",
    [PSPRITE_SEARCHLIGHT_EYE] = "SEARCHLIGHT_EYE",
    [PSPRITE_SEARCHLIGHT_EYE2] = "SEARCHLIGHT_EYE2",
    [PSPRITE_STEAM_LARGE] = "STEAM_LARGE",
    [PSPRITE_STEAM_SMALL] = "STEAM_SMALL",
    [PSPRITE_PLASMA_BEAM_BLOCK] = "PLASMA_BEAM_BLOCK",
    [PSPRITE_GRAVITY_SUIT_BLOCK] = "GRAVITY_SUIT_BLOCK",
    [PSPRITE_SPACE_JUMP_BLOCK] = "SPACE_JUMP_BLOCK",
    [PSPRITE_GADORA_KRAID] = "GADORA_KRAID",
    [PSPRITE_GADORA_RIDLEY] = "GADORA_RIDLEY",
    [PSPRITE_SEARCHLIGHT] = "SEARCHLIGHT",
    [PSPRITE_SEARCHLIGHT2] = "SEARCHLIGHT2",
    [PSPRITE_SEARCHLIGHT3] = "SEARCHLIGHT3",
    [PSPRITE_SEARCHLIGHT4] = "SEARCHLIGHT4",
    [PSPRITE_MAYBE_SEARCHLIGHT_TRIGGER] = "MAYBE_SEARCHLIGHT_TRIGGER",
    [PSPRITE_DISCOVERED_IMAGO_PASSAGE_EVENT_TRIGGER] = "DISCOVERED_IMAGO_PASSAGE_EVENT_TRIGGER",
    [PSPRITE_FAKE_POWER_BOMB] = "FAKE_POWER_BOMB",
    [PSPRITE_SPACE_PIRATE_CARRYING_POWER_BOMB] = "SPACE_PIRATE_CARRYING_POWER_BOMB",
    [PSPRITE_TANGLE_VINE_RED_GARUTA] = "TANGLE_VINE_RED_GARUTA",
    [PSPRITE_TANGLE_VINE_GERUTA] = "TANGLE_VINE_GERUTA",
    [PSPRITE_TANGLE_VINE_LARVA_RIGHT] = "TANGLE_VINE_LARVA_RIGHT",
    [PSPRITE_TANGLE_VINE_LARVA_LEFT] = "TANGLE_VINE_LARVA_LEFT",
    [PSPRITE_WATER_DROP] = "WATER_DROP",
    [PSPRITE_FALLING_CHOZO_PILLAR] = "FALLING_CHOZO_PILLAR",
    [PSPRITE_MECHA_RIDLEY] = "MECHA_RIDLEY",
    [PSPRITE_EXPLOSION_ZEBES_ESCAPE] = "EXPLOSION_ZEBES_ESCAPE",
    [PSPRITE_STEAM_LARGE_DIAGONAL_UP] = "STEAM_LARGE_DIAGONAL_UP",
    [PSPRITE_STEAM_SMALL_DIAGONAL_UP] = "STEAM_SMALL_DIAGONAL_UP",
    [PSPRITE_STEAM_LARGE_DIAGONAL_DOWN] = "STEAM_LARGE_DIAGONAL_DOWN",
    [PSPRITE_STEAM_SMALL_DIAGONAL_DOWN] = "STEAM_SMALL_DIAGONAL_DOWN",
    [PSPRITE_BARISTUTE_KRAID_UPPER] = "BARISTUTE_KRAID_UPPER",
    [PSPRITE_ESCAPE_GATE1] = "ESCAPE_GATE1",
    [PSPRITE_ESCAPE_GATE2] = "ESCAPE_GATE2",
    [PSPRITE_BLACK_SPACE_PIRATE] = "BLACK_SPACE_PIRATE",
    [PSPRITE_ESCAPE_SHIP_SPACE_PIRATE] = "ESCAPE_SHIP_SPACE_PIRATE",
    [PSPRITE_BARISTUTE_KRAID_LOWER] = "BARISTUTE_KRAID_LOWER",
    [PSPRITE_RINKA_MOTHER_BRAIN2] = "RINKA_MOTHER_BRAIN2",
    [PSPRITE_RINKA_MOTHER_BRAIN3] = "RINKA_MOTHER_BRAIN3",
    [PSPRITE_RINKA_MOTHER_BRAIN4] = "RINKA_MOTHER_BRAIN4",
    [PSPRITE_RINKA_MOTHER_BRAIN5] = "RINKA_MOTHER_BRAIN5",
    [PSPRITE_RINKA_MOTHER_BRAIN6] = "RINKA_MOTHER_BRAIN6",
};

const char* const sSecondarySpriteName[SSPRITE_END] = {
    [SSPRITE_CHOZO_BALL] = "CHOZO_BALL",
    [SSPRITE_CHOZO_STATUE_PART] = "CHOZO_STATUE_PART",
    [SSPRITE_CHOZO_STATUE_REFILL] = "CHOZO_STATUE_REFILL",
    [SSPRITE_KRAID_PART] = "KRAID_PART",
    [SSPRITE_CHOZO_STATUE_MOVEMENT] = "CHOZO_STATUE_MOVEMENT",
    [SSPRITE_CHARGE_BEAM_GLOW] = "CHARGE_BEAM_GLOW",
    [SSPRITE_WINGED_RIPPER] = "WINGED_RIPPER",
    [SSPRITE_MULTIVIOLA_UNUSED] = "MULTIVIOLA_UNUSED",
    [SSPRITE_DRAGON_FIREBALL] = "DRAGON_FIREBALL",
    [SSPRITE_DEOREM_SEGMENT] = "DEOREM_SEGMENT",
    [SSPRITE_DEOREM_EYE] = "DEOREM_EYE",
    [SSPRITE_DEOREM_THORN] = "DEOREM_THORN",
    [SSPRITE_SKREE_EXPLOSION] = "SKREE_EXPLOSION",
    [SSPRITE_SAVE_PLATFORM_PART] = "SAVE_PLATFORM_PART",
    [SSPRITE_SAVE_YES_NO_CURSOR] = "SAVE_YES_NO_CURSOR",
    [SSPRITE_BLUE_SKREE_EXPLOSION] = "BLUE_SKREE_EXPLOSION",
    [SSPRITE_ZEELA_EYES] = "ZEELA_EYES",
    [SSPRITE_HIVE_ROOTS] = "HIVE_ROOTS",
    [SSPRITE_IMAGO_LARVA_PART] = "IMAGO_LARVA_PART",
    [SSPRITE_MORPH_BALL_OUTSIDE] = "MORPH_BALL_OUTSIDE",
    [SSPRITE_IMAGO_COCOON_VINE] = "IMAGO_COCOON_VINE",
    [SSPRITE_IMAGO_COCOON_SPORE] = "IMAGO_COCOON_SPORE",
    [SSPRITE_SPACE_PIRATE_LASER] = "SPACE_PIRATE_LASER",
    [SSPRITE_RIDLEY_PART] = "RIDLEY_PART",
    [SSPRITE_RIDLEY_TAIL] = "RIDLEY_TAIL",
    [SSPRITE_SEARCHLIGHT_EYE_BEAM] = "SEARCHLIGHT_EYE_BEAM",
    [SSPRITE_METROID_SHELL] = "METROID_SHELL",
    [SSPRITE_POLYP_PROJECTILE] = "POLYP_PROJECTILE",
    [SSPRITE_KRAID_SPIKE] = "KRAID_SPIKE",
    [SSPRITE_KRAID_NAIL] = "KRAID_NAIL",
    [SSPRITE_ZIPLINE_GENERATOR_PART] = "ZIPLINE_GENERATOR_PART",
    [SSPRITE_ATOMIC_ELECTRICITY] = "ATOMIC_ELECTRICITY",
    [SSPRITE_MOTHER_BRAIN_PART] = "MOTHER_BRAIN_PART",
    [SSPRITE_RIDLEY_FIREBALL] = "RIDLEY_FIREBALL",
    [SSPRITE_UNKNOWN_ITEM_CHOZO_STATUE_PART] = "UNKNOWN_ITEM_CHOZO_STATUE_PART",
    [SSPRITE_UNKNOWN_ITEM_CHOZO_STATUE_REFILL] = "UNKNOWN_ITEM_CHOZO_STATUE_REFILL",
    [SSPRITE_MORPH_BALL_LAUNCHER_PART] = "MORPH_BALL_LAUNCHER_PART",
    [SSPRITE_ACID_WORM_BODY] = "ACID_WORM_BODY",
    [SSPRITE_ACID_WORM_SPIT] = "ACID_WORM_SPIT",
    [SSPRITE_CANNON_BULLET] = "CANNON_BULLET",
    [SSPRITE_CROCOMIRE_PART] = "CROCOMIRE_PART",
    [SSPRITE_IMAGO_PART] = "IMAGO_PART",
    [SSPRITE_DEFEATED_IMAGO_COCOON] = "DEFEATED_IMAGO_COCOON",
    [SSPRITE_IMAGO_CEILING_VINE] = "IMAGO_CEILING_VINE",
    [SSPRITE_SEARCHLIGHT_EYE_BEAM2] = "SEARCHLIGHT_EYE_BEAM2",
    [SSPRITE_TANGLE_VINE_GERUTA_PART] = "TANGLE_VINE_GERUTA_PART",
    [SSPRITE_CHOZODIA_SAVE_PLATFORM_PART] = "CHOZODIA_SAVE_PLATFORM_PART",
    [SSPRITE_IMAGO_NEEDLE] = "IMAGO_NEEDLE",
    [SSPRITE_ELEVATOR_STATUE_DEBRIS] = "ELEVATOR_STATUE_DEBRIS",
    [SSPRITE_IMAGO_DAMAGED_STINGER] = "IMAGO_DAMAGED_STINGER",
    [SSPRITE_GUNSHIP_PART] = "GUNSHIP_PART",
    [SSPRITE_IMAGO_EGG] = "IMAGO_EGG",
    [SSPRITE_MAP_STATION_PART] = "MAP_STATION_PART",
    [SSPRITE_CHOZO_PILLAR_PLATFORM] = "CHOZO_PILLAR_PLATFORM",
    [SSPRITE_GADORA_EYE] = "GADORA_EYE",
    [SSPRITE_GADORA_BEAM] = "GADORA_BEAM",
    [SSPRITE_UNKNOWN_ITEM_BLOCK_LIGHT] = "UNKNOWN_ITEM_BLOCK_LIGHT",
    [SSPRITE_SEARCHLIGHT_EYE_PROJECTILE] = "SEARCHLIGHT_EYE_PROJECTILE",
    [SSPRITE_CHOZO_PILLAR_PLATFORM_SHADOW] = "CHOZO_PILLAR_PLATFORM_SHADOW",
    [SSPRITE_RUINS_TEST_SYMBOL] = "RUINS_TEST_SYMBOL",
    [SSPRITE_RUINS_TEST_SAMUS_REFLECTION_START] = "RUINS_TEST_SAMUS_REFLECTION_START",
    [SSPRITE_RUINS_TEST_REFLECTION_COVER] = "RUINS_TEST_REFLECTION_COVER",
    [SSPRITE_RUINS_TEST_GHOST_OUTLINE] = "RUINS_TEST_GHOST_OUTLINE",
    [SSPRITE_RUINS_TEST_GHOST] = "RUINS_TEST_GHOST",
    [SSPRITE_RUINS_TEST_SHOOTABLE_SYMBOL] = "RUINS_TEST_SHOOTABLE_SYMBOL",
    [SSPRITE_RUINS_TEST_SAMUS_REFLECTION_END] = "RUINS_TEST_SAMUS_REFLECTION_END",
    [SSPRITE_RUINS_TEST_LIGHTNING] = "RUINS_TEST_LIGHTNING",
    [SSPRITE_RIDLEY_BIG_FIREBALL] = "RIDLEY_BIG_FIREBALL",
    [SSPRITE_MECHA_RIDLEY_PART] = "MECHA_RIDLEY_PART",
    [SSPRITE_ESCAPE_SHIP_PART] = "ESCAPE_SHIP_PART",
    [SSPRITE_POWER_GRIP_GLOW] = "POWER_GRIP_GLOW",
    [SSPRITE_MECHA_RIDLEY_LASER] = "MECHA_RIDLEY_LASER",
    [SSPRITE_MECHA_RIDLEY_MISSILE] = "MECHA_RIDLEY_MISSILE",
    [SSPRITE_MECHA_RIDLEY_FIREBALL] = "MECHA_RIDLEY_FIREBALL",
    [SSPRITE_MOTHER_BRAIN_BEAM] = "MOTHER_BRAIN_BEAM",
    [SSPRITE_MOTHER_BRAIN_BLOCK] = "MOTHER_BRAIN_BLOCK",
    [SSPRITE_MOTHER_BRAIN_GLASS_BREAKING] = "MOTHER_BRAIN_GLASS_BREAKING"
};

const char* const sMainGameModeNames[] = {
    [GM_SOFTRESET] = "SOFTRESET",
    [GM_INTRO] = "INTRO",
    [GM_TITLE] = "TITLE",
    [GM_FILESELECT] = "FILESELECT",
    [GM_INGAME] = "INGAME",
    [GM_MAP_SCREEN] = "MAP_SCREEN",
    [GM_GAMEOVER] = "GAMEOVER",
    [GM_CHOZODIA_ESCAPE] = "CHOZODIA_ESCAPE",
    [GM_CREDITS] = "CREDITS",
    [GM_TOURIAN_ESCAPE] = "TOURIAN_ESCAPE",
    [GM_CUTSCENE] = "CUTSCENE",
    [GM_DEMO] = "DEMO",
    [GM_GALLERY] = "GALLERY",
    [GM_FUSION_GALLERY] = "FUSION_GALLERY",
    [GM_START_SOFTRESET] = "START_SOFTRESET",
    [GM_ERASE_SRAM] = "ERASE_SRAM",
    [GM_DEBUG_MENU] = "DEBUG_MENU",
};

void PrintDebug_HitboxesSamus(void)
{
    ImDrawList* dl = igGetBackgroundDrawList_Nil();

    int x;
    int y;
    glfwGetWindowPos(gWindow, &x, &y);

    ImVec2 min = { x + gSamusData.xPosition + gSamusPhysics.hitboxLeftOffset - gBg1XPosition, y + gSamusData.yPosition + gSamusPhysics.hitboxTopOffset - gBg1YPosition };
    ImVec2 max = { x + gSamusData.xPosition + gSamusPhysics.hitboxRightOffset - gBg1XPosition, y + gSamusData.yPosition + 0 - gBg1YPosition };

    ImDrawList_AddRect(dl, min, max, CV_COL32(0xFF, 0, 0, 0xFF), 0, ImDrawFlags_None, 1.f);
}

void PrintDebug_HitboxesSprites(void)
{
    ImDrawList* dl = igGetBackgroundDrawList_Nil();

    int x;
    int y;
    glfwGetWindowPos(gWindow, &x, &y);

    for (s32 i = 0; i < MAX_AMOUNT_OF_SPRITES; i++)
    {
        struct SpriteData* pSprite = &gSpriteData[i];

        if (!(pSprite->status & SPRITE_STATUS_EXISTS))
            continue;

        ImVec2 min = { x + pSprite->xPosition + pSprite->hitboxLeftOffset - gBg1XPosition, y + pSprite->yPosition + pSprite->hitboxTopOffset - gBg1YPosition };
        ImVec2 max = { x + pSprite->xPosition + pSprite->hitboxRightOffset - gBg1XPosition, y + pSprite->yPosition + pSprite->hitboxBottomOffset - gBg1YPosition };

        ImDrawList_AddRect(dl, min, max, CV_COL32(0, 0xFF, 0, 0xFF), 0, ImDrawFlags_None, 1.f);
    }
}

void PrintDebug_HitboxesProjectiles(void)
{
    ImDrawList* dl = igGetBackgroundDrawList_Nil();

    int x;
    int y;
    glfwGetWindowPos(gWindow, &x, &y);

    for (s32 i = 0; i < MAX_AMOUNT_OF_PROJECTILES; i++)
    {
        struct ProjectileData* pProj = &gProjectileData[i];

        if (!(pProj->status & PROJ_STATUS_EXISTS))
            continue;

        ImVec2 min = { x + pProj->xPosition + pProj->hitboxLeftOffset - gBg1XPosition, y + pProj->yPosition + pProj->hitboxTopOffset - gBg1YPosition };
        ImVec2 max = { x + pProj->xPosition + pProj->hitboxRightOffset - gBg1XPosition, y + pProj->yPosition + pProj->hitboxBottomOffset - gBg1YPosition };

        ImDrawList_AddRect(dl, min, max, CV_COL32(0xFF, 0xFF, 0, 0xFF), 0, ImDrawFlags_None, 1.f);
    }
}

void PrintDebug_HitboxesTerrain(void)
{
    ImDrawList* dl = igGetBackgroundDrawList_Nil();

    int x;
    int y;
    glfwGetWindowPos(gWindow, &x, &y);

    for (s32 i = 0; i < gBgPointersAndDimensions.clipdataWidth; i++)
    {
        for (s32 j = 0; j < gBgPointersAndDimensions.clipdataHeight; j++)
        {
            if (gBgPointersAndDimensions.pClipDecomp[j * gBgPointersAndDimensions.clipdataWidth + i] == CLIPDATA_AIR)
                continue;

            if (i > 0)
            {
                if (gBgPointersAndDimensions.pClipDecomp[j * gBgPointersAndDimensions.clipdataWidth + i - 1] == CLIPDATA_AIR)
                {
                    ImVec2 p1 = {
                        x + PIXEL_TO_SUB_PIXEL(i * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL(j * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImVec2 p2 = {
                        x + PIXEL_TO_SUB_PIXEL(i * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL((j + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImDrawList_AddLine(dl, p1, p2, CV_COL32_WHITE, 1.f);
                }
            }

            if (j > 0)
            {
                if (gBgPointersAndDimensions.pClipDecomp[(j - 1) * gBgPointersAndDimensions.clipdataWidth + i] == CLIPDATA_AIR)
                {
                    ImVec2 p1 = {
                        x + PIXEL_TO_SUB_PIXEL(i * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL(j * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImVec2 p2 = {
                        x + PIXEL_TO_SUB_PIXEL((i + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL(j * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImDrawList_AddLine(dl, p1, p2, CV_COL32_WHITE, 1.f);
                }
            }

            if (i < gBgPointersAndDimensions.clipdataWidth - 1)
            {
                if (gBgPointersAndDimensions.pClipDecomp[j * gBgPointersAndDimensions.clipdataWidth + i + 1] == CLIPDATA_AIR)
                {
                    ImVec2 p1 = {
                        x + PIXEL_TO_SUB_PIXEL((i + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL(j * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImVec2 p2 = {
                        x + PIXEL_TO_SUB_PIXEL((i + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL((j + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImDrawList_AddLine(dl, p1, p2, CV_COL32_WHITE, 1.f);
                }
            }

            if (j < gBgPointersAndDimensions.clipdataHeight - 1)
            {
                if (gBgPointersAndDimensions.pClipDecomp[(j + 1) * gBgPointersAndDimensions.clipdataWidth + i] == CLIPDATA_AIR)
                {
                    ImVec2 p1 = {
                        x + PIXEL_TO_SUB_PIXEL(i * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL((j + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImVec2 p2 = {
                        x + PIXEL_TO_SUB_PIXEL((i + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1XPosition,
                        y + PIXEL_TO_SUB_PIXEL((j + 1) * SUB_PIXEL_TO_PIXEL(BLOCK_SIZE)) - gBg1YPosition,
                    };

                    ImDrawList_AddLine(dl, p1, p2, CV_COL32_WHITE, 1.f);
                }
            }
        }
    }
}

void PrintDebug_Hitboxes(void)
{
    PrintDebug_HitboxesSamus();
    PrintDebug_HitboxesSprites();
    PrintDebug_HitboxesProjectiles();
    PrintDebug_HitboxesTerrain();
}

void PrintDebug_Sprites(void)
{
    igBegin("Sprites info", NULL, ImGuiWindowFlags_None);

    const u16 stepPosSlow = PIXEL_SIZE;
    const u16 stepPosFast = BLOCK_SIZE;
    const u8 one = 1;

    for (s32 i = 0; i < MAX_AMOUNT_OF_SPRITES; i++)
    {
        struct SpriteData* pSprite = &gSpriteData[i];
        char buffer[10];
        sprintf_s(buffer, sizeof(buffer), "Sprite %d", i);
        if (igTreeNode_Str(buffer))
        {
            igCheckboxFlags_IntPtr("Exists", (s32*)&pSprite->status, SPRITE_STATUS_EXISTS);

            igBeginDisabled(!(pSprite->status & SPRITE_STATUS_EXISTS));

            igText("ID : ");
            igSameLine(0, 10);

            if (pSprite->properties & SP_SECONDARY_SPRITE)
                igText("%s", sSecondarySpriteName[pSprite->spriteId]);
            else
                igText("%s", sPrimarySpriteNames[pSprite->spriteId]);

            igText("X : ");
            igSameLine(0, 10);
            igInputScalar("##spriteY", ImGuiDataType_U16, &pSprite->xPosition, &stepPosSlow, &stepPosFast, "%d", ImGuiInputTextFlags_CharsDecimal);
            
            igText("Y : ");
            igSameLine(0, 10);
            igInputScalar("##spriteX", ImGuiDataType_U16, &pSprite->yPosition, &stepPosSlow, &stepPosFast, "%d", ImGuiInputTextFlags_CharsDecimal);
            
            igText("Pose : ");
            igSameLine(0, 10);
            igInputScalar("##pose", ImGuiDataType_U8, &pSprite->pose, &one, &one, "%d", ImGuiInputTextFlags_CharsDecimal);;
            
            igText("Oam : %p", pSprite->pOam);

            igEndDisabled();
            igTreePop();
        }
    }

    igEnd();
}

void PrintDebug_Samus(void)
{
    igBegin("Samus info", NULL, ImGuiWindowFlags_None);

    igText("%s", sPoseNames[gSamusData.pose]);

    const u16 stepPosSlow = PIXEL_SIZE;
    const u16 stepPosFast = BLOCK_SIZE;

    const u16 stepEnergySlow = 1;
    const u16 stepEnergyFast = 10;

    igText("Samus X : ");
    igSameLine(0, 5);
    igInputScalar("##samusX", ImGuiDataType_U16, &gSamusData.xPosition, &stepPosSlow, &stepPosFast, "%d", ImGuiInputTextFlags_None);
    
    igText("Samus Y : ");
    igSameLine(0, 5);
    igInputScalar("##samusY", ImGuiDataType_U16, &gSamusData.yPosition, &stepPosSlow, &stepPosFast, "%d", ImGuiInputTextFlags_None);

    igText("Current energy : ");
    igSameLine(0, 5);
    igInputScalar("##currEnergy", ImGuiDataType_U16, &gEquipment.currentEnergy, &stepEnergySlow, &stepEnergyFast, "%d", ImGuiInputTextFlags_None);

    igCheckboxFlags_IntPtr("HIGH_JUMP", (s32*)&gEquipment.suitMisc, SMF_HIGH_JUMP);
    igCheckboxFlags_IntPtr("HIGH_JUMP active", (s32*)&gEquipment.suitMiscActivation, SMF_HIGH_JUMP);
    igCheckboxFlags_IntPtr("SPEEDBOOSTER", (s32*)&gEquipment.suitMisc, SMF_SPEEDBOOSTER);
    igCheckboxFlags_IntPtr("SPEEDBOOSTER active", (s32*)&gEquipment.suitMiscActivation, SMF_SPEEDBOOSTER);
    igCheckboxFlags_IntPtr("SPACE_JUMP", (s32*)&gEquipment.suitMisc, SMF_SPACE_JUMP);
    igCheckboxFlags_IntPtr("SPACE_JUMP active", (s32*)&gEquipment.suitMiscActivation, SMF_SPACE_JUMP);
    igCheckboxFlags_IntPtr("SCREW_ATTACK", (s32*)&gEquipment.suitMisc, SMF_SCREW_ATTACK);
    igCheckboxFlags_IntPtr("SCREW_ATTACK active", (s32*)&gEquipment.suitMiscActivation, SMF_SCREW_ATTACK);
    igCheckboxFlags_IntPtr("VARIA_SUIT", (s32*)&gEquipment.suitMisc, SMF_VARIA_SUIT);
    igCheckboxFlags_IntPtr("VARIA_SUIT active", (s32*)&gEquipment.suitMiscActivation, SMF_VARIA_SUIT);
    igCheckboxFlags_IntPtr("GRAVITY_SUIT", (s32*)&gEquipment.suitMisc, SMF_GRAVITY_SUIT);
    igCheckboxFlags_IntPtr("GRAVITY_SUIT active", (s32*)&gEquipment.suitMiscActivation, SMF_GRAVITY_SUIT);
    igCheckboxFlags_IntPtr("MORPH_BALL", (s32*)&gEquipment.suitMisc, SMF_MORPH_BALL);
    igCheckboxFlags_IntPtr("MORPH_BALL active", (s32*)&gEquipment.suitMiscActivation, SMF_MORPH_BALL);
    igCheckboxFlags_IntPtr("POWER_GRIP", (s32*)&gEquipment.suitMisc, SMF_POWER_GRIP);
    igCheckboxFlags_IntPtr("POWER_GRIP active", (s32*)&gEquipment.suitMiscActivation, SMF_POWER_GRIP);

    igSeparator();

    igCheckboxFlags_IntPtr("LONG_BEAM", (s32*)&gEquipment.beamBombs, BBF_LONG_BEAM);
    igCheckboxFlags_IntPtr("LONG_BEAM active", (s32*)&gEquipment.beamBombsActivation, BBF_LONG_BEAM);
    igCheckboxFlags_IntPtr("ICE_BEAM", (s32*)&gEquipment.beamBombs, BBF_ICE_BEAM);
    igCheckboxFlags_IntPtr("ICE_BEAM active", (s32*)&gEquipment.beamBombsActivation, BBF_ICE_BEAM);
    igCheckboxFlags_IntPtr("WAVE_BEAM", (s32*)&gEquipment.beamBombs, BBF_WAVE_BEAM);
    igCheckboxFlags_IntPtr("WAVE_BEAM active", (s32*)&gEquipment.beamBombsActivation, BBF_WAVE_BEAM);
    igCheckboxFlags_IntPtr("PLASMA_BEAM", (s32*)&gEquipment.beamBombs, BBF_PLASMA_BEAM);
    igCheckboxFlags_IntPtr("PLASMA_BEAM active", (s32*)&gEquipment.beamBombsActivation, BBF_PLASMA_BEAM);
    igCheckboxFlags_IntPtr("CHARGE_BEAM", (s32*)&gEquipment.beamBombs, BBF_CHARGE_BEAM);
    igCheckboxFlags_IntPtr("CHARGE_BEAM active", (s32*)&gEquipment.beamBombsActivation, BBF_CHARGE_BEAM);
    igCheckboxFlags_IntPtr("BOMBS", (s32*)&gEquipment.beamBombs, BBF_BOMBS);
    igCheckboxFlags_IntPtr("BOMBS active", (s32*)&gEquipment.beamBombsActivation, BBF_BOMBS);

    igEnd();
}

void PrintDebug_GameInfo(void)
{
    igBegin("Game info", NULL, ImGuiWindowFlags_None);

    ImGuiIO* io = igGetIO();

    igText("Game mode : %s", sMainGameModeNames[gMainGameMode]);
    igText("Sub modes : %d ; %d ; %d", gGameModeSub1, gGameModeSub2, gGameModeSub3);
    igText("Delta time : %.3f", io->DeltaTime);
    u8 minFps = 1;
    igDragScalar("Target FPS", ImGuiDataType_U8, &gTargetFps, 1.f, &minFps, NULL, NULL, ImGuiInputTextFlags_None);
    igText("Actual FPS : %2d", (s32) (1.f / io->DeltaTime));

    igEnd();
}
