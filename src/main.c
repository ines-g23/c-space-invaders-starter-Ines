#include <SDL2/SDL.h>
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

    bool running = true;
    Uint32 last_ticks = SDL_GetTicks();

    Entity player = {
        .x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2,
        .y = SCREEN_HEIGHT - 60,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
        .vx = 0,
        .vy = 0};

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
        update(&player, &bullet, &bullet_active, dt, ennemy_list, &droite, &descente, &partie_finie);
        render(renderer, &player, &bullet, bullet_active, ennemy_list, &partie_finie);
    }

    free_ennemy(ennemy_list);
    cleanup(window, renderer);
    return 0;
}
