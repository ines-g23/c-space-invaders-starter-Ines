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

#define BULLET_WIDTH 10
#define BULLET_HEIGHT 20
#define BULLET_SPEED 600.0f


#define ENNEMY_WIDTH 40
#define ENNEMY_HEIGHT 20
#define ENNEMY_SPEED_X 60.0f
#define ENNEMY_SPEED_Y 10.0f
#define NUMBER_ENNEMY_X 11
#define NUMBER_ENNEMY_Y 5

bool init(SDL_Window **window, SDL_Renderer **renderer);
void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active);
void update(Entity *player, Entity *bullet, bool *bullet_active, float dt, ENNEMY *ennemy_list, bool *droite, bool *descente);
void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, bool bullet_active, ENNEMY *ennemy_list);
ENNEMY *create_all_ennemy();
void free_ennemy(ENNEMY *ennemy_list);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);

#endif
