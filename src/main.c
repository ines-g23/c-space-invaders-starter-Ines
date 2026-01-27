#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>
#include "../include/entity.h"
#include "../include/game.h"

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!init(&window, &renderer))
    {
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1)
    {
        SDL_Log("Erreur d'initialisation de SDL_ttf: %s", TTF_GetError());
        return 1;
    }

    bool running = true;
    Uint32 last_ticks = SDL_GetTicks();  

    Entity player = {
        .x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2,
        .y = SCREEN_HEIGHT - 60,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
        .vx = 0,
        .vy = 0,
        .vie = PLAYER_LIFE,
    };

    Entity bullet = {
        .x = player.x + player.w / 2 - BULLET_WIDTH / 2,
        .y = player.y,
        .w = BULLET_WIDTH,
        .h = BULLET_HEIGHT,
        .vy = -BULLET_SPEED,
    };

    bool bullet_active = false;

    ENNEMY *ennemy_list = create_all_ennemy();
    bool droite = true;
    bool descente = false;
    bool partie_finie = false;
    bool partie_gagnee = false;

    TIR_ENNEMI tir_ennemi = {
        .x = 0,
        .y = 0,
        .h = 10,
        .w = 5,
        .vy = TIR_ENNEMI_SPEED,
    };

    bool tir_ennemi_active = false;

    while (running)
    {
        Uint32 ticks = SDL_GetTicks();
        float dt = (ticks - last_ticks) / 1000.0f;
        if (dt > 0.05f)
            dt = 0.05f;
        last_ticks = ticks;

        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        handle_input(&running, keys, &player, &bullet, &bullet_active);
        update(&player, &bullet, &bullet_active, dt, ennemy_list, &droite, &descente, &partie_finie, &partie_gagnee, &tir_ennemi, &tir_ennemi_active);
        render(renderer, &player, &bullet, bullet_active, ennemy_list, partie_finie, partie_gagnee, &tir_ennemi, tir_ennemi_active);
    }

    free_ennemy(ennemy_list);
    cleanup(window, renderer);
    TTF_Quit();
    return 0;
}
