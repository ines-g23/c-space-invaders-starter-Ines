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
#define BULLET_SPEED 800.0f


#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 20
#define ENEMY_SPEED_X 40.0f
#define ENEMY_SPEED_X_MAX 150.0f
#define ENEMY_SPEED_Y 10.0f
#define FAST_ENEMY_SPEED_Y 20.0f
#define NUMBER_ENEMY_X 11
#define NUMBER_ENEMY_Y 5


#define TIR_ENEMY_SPEED 400.0f
#define TIR_ENEMY_WIDTH 10
#define TIR_ENEMY_HEIGHT 20
#define TIR_ENEMY_PROBA 0.005

#define VIE_WIDTH 16
#define VIE_HEIGHT 15

#define COEUR_WIDTH 30
#define COEUR_HEIGHT 27
#define COEUR_SPEED 400.0f
#define COEUR_PROBA 0.0005

#define NUMBER_PROTECTION 3
#define VIE_INITIALE_PROTECTION 3
#define PROTECTION_WIDTH 70
#define PROTECTION_HEIGHT 20


bool init(SDL_Window **window, SDL_Renderer **renderer);
void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active, bool *menu);
void update(Entity *player, Entity *bullet, bool *bullet_active, float dt, ENEMY *enemy_list, bool *droite, bool *descente, bool *partie_finie, bool *partie_gagnee,TIR_ENEMY *tir_ennemi, bool *tir_ennemi_active, COEUR *coeur, bool *coeur_active, PROTECTION *protection_list);
void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, bool bullet_active, ENEMY *enemy_list, bool partie_finie, bool partie_gagnee, TIR_ENEMY *tir_ennemi, bool tir_ennemi_active,COEUR *coeur, bool coeur_active,PROTECTION *protection_list, bool menu);
void render_text(SDL_Renderer *renderer, const char *text, int x, int y, SDL_Color color, int taille);
void render_image(SDL_Renderer *renderer, const char *image_path, int x, int y, int width, int height);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);

void deplacement_player (Entity *player, float dt);

ENEMY *create_all_enemy();
void free_enemy(ENEMY *enemy_list);
void gestion_tir_ennemi(TIR_ENEMY *tir_ennemi, bool *tir_ennemi_active, ENEMY *enemy_list);
void gestion_vie(Entity *player, TIR_ENEMY *tir_ennemi, bool *tir_ennemi_active);
void deplacement_ennemi(ENEMY *enemy_list, bool *droite, bool *descente, float dt);
void deplacement_tir_ennemi(TIR_ENEMY *tir_ennemi, bool *tir_ennemi_active, float dt);

void gestion_collision_bullet_enemy(ENEMY *enemy_list, Entity *bullet, bool *bullet_active);
void deplacement_bullet(Entity *bullet, bool *bullet_active, float dt);

void fin_de_partie(ENEMY *enemy_list, bool *partie_finie, bool *partie_gagnee, Entity *player);

void apparition_coeur(COEUR *coeur, bool *coeur_active);
void collision_coeur(COEUR *coeur, bool *coeur_active, Entity *player);
void deplacement_coeur(COEUR *coeur, bool *coeur_active, float dt);

PROTECTION *create_all_protection();
void gestion_collision_protection(TIR_ENEMY *tir_ennemi, bool *tir_ennemi_active, PROTECTION *protection_list,Entity *bullet, bool *bullet_active);

#endif

