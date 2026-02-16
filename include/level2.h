typedef struct {
    int NUMBER_ENNEMY_X;
    int NUMBER_ENNEMY_Y;
    float ENNEMY_SPEED_X;
    float ENNEMY_SPEED_Y;
    float ENNEMY_SPEED_X_MAX;
    float FAST_ENNEMY_SPEED_Y;
    float BULLET_SPEED;
    float TIR_ENNEMI_PROBA;
    int NUMBER_PROTECTION;
    int VIE_INITIALE_PROTECTION;
    int PROTECTION_WIDTH;
    // ajouter ici toutes les constantes utilisées
} LevelConfig;

extern LevelConfig current_level;
void set_level(int level);

static LevelConfig levels[3] = {
    // niveau 0 (facile)
    {
        .NUMBER_ENNEMY_X = 8,
        .NUMBER_ENNEMY_Y = 5,
        .ENNEMY_SPEED_X = 40.0,
        .ENNEMY_SPEED_Y = 10.0,
        .ENNEMY_SPEED_X_MAX = 150.0,
        .FAST_ENNEMY_SPEED_Y = 20.0,
        .BULLET_SPEED = 600.0,
        .TIR_ENNEMI_PROBA = 0.005, 
        .NUMBER_PROTECTION = 3,
        .VIE_INITIALE_PROTECTION = 3,
        .PROTECTION_WIDTH = 70,
    },
    // niveau 1 (moyen) ...
    // niveau 2 (difficile) ...
};

LevelConfig current_level;

void set_level(int level) {
    if (level < 0) level = 0;
    if (level > 2) level = 2;
    current_level = levels[level];
}