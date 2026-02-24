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

    BULLET1 bullet1 = {
        .x = player.x + player.w / 2 - BULLET_WIDTH / 2,
        .y = player.y,
        .w = BULLET_WIDTH,
        .h = BULLET_HEIGHT,
        .vy = -BULLET_SPEED,
        .bullet_active1 = false,
    };  

    BULLET2 bullet2 = {
        .x = player.x + player.w / 2 - BULLET_WIDTH / 2,
        .y = player.y,
        .w = BULLET_WIDTH,
        .h = BULLET_HEIGHT,
        .vy = -BULLET_SPEED,
        .bullet_active2 = false,
    };

    ENEMY *enemy_list = create_all_enemy();
    PROTECTION *protection_list = create_all_protection();
    bool droite = true;
    bool descente = false;
    bool partie_finie = false;
    bool partie_gagnee = false;
    bool coeur_active = false;
    bool menu = true;

    TIR_ENEMY TIR_ENEMY = {
        .x = 0,
        .y = 0,
        .h = 10,
        .w = 5,
        .vy = TIR_ENEMY_SPEED,
    };

    COEUR coeur = {
        .x = 0,
        .y = 0,
        .h = COEUR_HEIGHT,
        .w = COEUR_WIDTH,
        .vy = COEUR_SPEED,
        .path = "coeur.png"
    };

    bool TIR_ENEMY_active = false;

    while (running)
    {
        Uint32 ticks = SDL_GetTicks();
        float dt = (ticks - last_ticks) / 1000.0f;
        if (dt > 0.05f)
            dt = 0.05f;
        last_ticks = ticks;

        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        handle_input(&running, keys, &player, &bullet1, &bullet2, &menu);
        if (!menu)
            update(&player, &bullet1, &bullet2, dt, enemy_list, &droite, &descente, &partie_finie, &partie_gagnee, &TIR_ENEMY, &TIR_ENEMY_active, &coeur, &coeur_active, protection_list);
        render(renderer, &player, &bullet1, &bullet2, enemy_list, partie_finie, partie_gagnee, &TIR_ENEMY, TIR_ENEMY_active, &coeur, coeur_active, protection_list, menu);
    }

    free_enemy(enemy_list);
    cleanup(window, renderer);
    TTF_Quit();
    return 0;
}
