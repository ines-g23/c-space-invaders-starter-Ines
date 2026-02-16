#include "../include/game.h"

static LevelConfig levels[3] = {
    /* LEVEL_EASY */
    {
        .NUMBER_ENNEMY_X = 6,
        .NUMBER_ENNEMY_Y = 3,
        .ENNEMY_SPEED_X = 40.0f,
        .ENNEMY_SPEED_X_MAX = 100.0f,
        .ENNEMY_SPEED_Y = 10.0f,
        .FAST_ENNEMY_SPEED_Y = 20.0f,
        .BULLET_SPEED = 600.0f,
        .TIR_ENNEMI_PROBA = 0.003f,
        .NUMBER_PROTECTION = 3,
        .VIE_INITIALE_PROTECTION = 2,
        .PROTECTION_WIDTH = 70,
    },
    /* LEVEL_MEDIUM */
    {
        .NUMBER_ENNEMY_X = 8,
        .NUMBER_ENNEMY_Y = 4,
        .ENNEMY_SPEED_X = 60.0f,
        .ENNEMY_SPEED_X_MAX = 130.0f,
        .ENNEMY_SPEED_Y = 15.0f,
        .FAST_ENNEMY_SPEED_Y = 30.0f,
        .BULLET_SPEED = 700.0f,
        .TIR_ENNEMI_PROBA = 0.005f,
        .NUMBER_PROTECTION = 3,
        .VIE_INITIALE_PROTECTION = 3,
        .PROTECTION_WIDTH = 70,
    },
    /* LEVEL_HARD */
    {
        .NUMBER_ENNEMY_X = 11,
        .NUMBER_ENNEMY_Y = 5,
        .ENNEMY_SPEED_X = 80.0f,
        .ENNEMY_SPEED_X_MAX = 150.0f,
        .ENNEMY_SPEED_Y = 20.0f,
        .FAST_ENNEMY_SPEED_Y = 40.0f,
        .BULLET_SPEED = 600.0f,
        .TIR_ENNEMI_PROBA = 0.008f,
        .NUMBER_PROTECTION = 2,
        .VIE_INITIALE_PROTECTION = 2,
        .PROTECTION_WIDTH = 60,
    }
};

LevelConfig current_level;

void set_level(Level level) {
    if (level < LEVEL_EASY) level = LEVEL_EASY;
    if (level > LEVEL_HARD) level = LEVEL_HARD;
    current_level = levels[(int)level];
}
