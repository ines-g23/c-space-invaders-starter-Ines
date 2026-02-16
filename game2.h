#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entity.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 20
#define PLAYER_SPEED 400.0f
#define PLAYER_LIFE 3

#define BULLET_WIDTH 10
#define BULLET_HEIGHT 20
//#define BULLET_SPEED 600.0f
#define BULLET_MAX 5

/*enum NUMBER_ENNEMY_X {
    LEVEL1 = 5,
    LEVEL2 = 8,
    LEVEL3 = 11,
}*/

#define ENNEMY_WIDTH 40
#define ENNEMY_HEIGHT 20
/*#define ENNEMY_SPEED_X 40.0f
#define ENNEMY_SPEED_X_MAX 150.0f
#define ENNEMY_SPEED_Y 10.0f
#define FAST_ENNEMY_SPEED_Y 20.0f
#define NUMBER_ENNEMY_X 11
#define NUMBER_ENNEMY_Y 5*/


#define TIR_ENNEMI_SPEED 400.0f
#define TIR_ENNEMI_WIDTH 10
#define TIR_ENNEMI_HEIGHT 20
//#define TIR_ENNEMI_PROBA 0.005

#define VIE_WIDTH 16
#define VIE_HEIGHT 15

#define COEUR_WIDTH 30
#define COEUR_HEIGHT 27
#define COEUR_SPEED 400.0f
#define COEUR_PROBA 0.0005

//#define NUMBER_PROTECTION 3
//#define VIE_INITIALE_PROTECTION 3
//#define PROTECTION_WIDTH 70
#define PROTECTION_HEIGHT 20

/* Level system */
typedef enum { LEVEL_EASY = 0, LEVEL_MEDIUM = 1, LEVEL_HARD = 2 } Level;

typedef struct {
    int NUMBER_ENNEMY_X;
    int NUMBER_ENNEMY_Y;
    float ENNEMY_SPEED_X;
    float ENNEMY_SPEED_X_MAX;
    float ENNEMY_SPEED_Y;
    float FAST_ENNEMY_SPEED_Y;
    float BULLET_SPEED;
    float TIR_ENNEMI_PROBA;
    int NUMBER_PROTECTION;
    int VIE_INITIALE_PROTECTION;
    int PROTECTION_WIDTH;
} LevelConfig;

extern LevelConfig current_level;
void set_level(Level level);


bool init(SDL_Window **window, SDL_Renderer **renderer);
void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active);
void update(Entity *player, Entity *bullet, bool *bullet_active, float dt, ENNEMY *ennemy_list, bool *droite, bool *descente, bool *partie_finie, bool *partie_gagnee,TIR_ENNEMI *tir_ennemi, bool *tir_ennemi_active, COEUR *coeur, bool *coeur_active, PROTECTION *protection_list);
void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, bool bullet_active, ENNEMY *ennemy_list, bool partie_finie, bool partie_gagnee, TIR_ENNEMI *tir_ennemi, bool tir_ennemi_active,COEUR *coeur, bool coeur_active,PROTECTION *protection_list);
ENNEMY *create_all_ennemy();
void free_ennemy(ENNEMY *ennemy_list);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);
void gestion_collision(ENNEMY *ennemy_list, Entity *bullet, bool *bullet_active);
void fin_de_partie(ENNEMY *ennemy_list, bool *partie_finie, bool *partie_gagnee, Entity *player);
void gestion_vie(Entity *player, TIR_ENNEMI *tir_ennemi, bool *tir_ennemi_active);
void gestion_tir_ennemi(TIR_ENNEMI *tir_ennemi, bool *tir_ennemi_active, ENNEMY *ennemy_list);
void render_text(SDL_Renderer *renderer, const char *text, int x, int y, SDL_Color color);
void render_image(SDL_Renderer *renderer, const char *image_path, int x, int y, int width, int height);
void apparition_coeur(COEUR *coeur, bool *coeur_active);
void collision_coeur(COEUR *coeur, bool *coeur_active, Entity *player);
PROTECTION *create_all_protection();
void gestion_collision_protection(TIR_ENNEMI *tir_ennemi, bool *tir_ennemi_active, PROTECTION *protection_list,Entity *bullet, bool *bullet_active);


#endif

