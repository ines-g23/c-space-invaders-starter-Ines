#include <SDL2/SDL.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

ENNEMY *create_all_ennemy(){
    ENNEMY *ennemy_list = malloc(NUMBER_ENNEMY_X*NUMBER_ENNEMY_Y*sizeof(ENNEMY));
    if (ennemy_list == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    // Initialiser le tableau en grille
    for (int row = 0; row < NUMBER_ENNEMY_Y; row++) {
        for (int col = 0; col < NUMBER_ENNEMY_X; col++) {
            int idx = row * NUMBER_ENNEMY_X + col;
            ennemy_list[idx].x = 40 + col * (SCREEN_WIDTH - 80) / NUMBER_ENNEMY_X;
            ennemy_list[idx].y = 20 + row * 50;
            ennemy_list[idx].h = ENNEMY_HEIGHT;
            ennemy_list[idx].w = ENNEMY_WIDTH;
            ennemy_list[idx].vx = ENNEMY_SPEED_X;
            ennemy_list[idx].vy = ENNEMY_SPEED_Y;
            ennemy_list[idx].exist = true;
        }
    }
    return ennemy_list;
}

void free_ennemy(ENNEMY *ennemy_list) {
    free(ennemy_list);
}

void gestion_collision(ENNEMY *ennemy_list, Entity *bullet, bool *bullet_active){
    if (*bullet_active){
        bool deja_collision = false;
        int i = NUMBER_ENNEMY_X*NUMBER_ENNEMY_Y - 1;
        while ((!deja_collision)&& (i >= 0)){
            if ((ennemy_list[i].exist) &&(ennemy_list[i].x <= bullet->x)&&(bullet->x <= (ennemy_list[i].x+ENNEMY_WIDTH))&& (ennemy_list[i].y <= bullet->y)&&(bullet->y <= (ennemy_list[i].y+ENNEMY_HEIGHT)))
            {
                ennemy_list[i].exist = false;
                deja_collision = true;
                *bullet_active = false;
            }
            i -= 1;
        }
        
    }
}

void gestion_vie(Entity *player, TIR_ENNEMI *tir_ennemi, bool *tir_ennemi_active){
    if (*tir_ennemi_active){
        if ((player->x <= tir_ennemi->x)&&(tir_ennemi->x <= (player->x + PLAYER_WIDTH))&& (player->y <= tir_ennemi->y)&&(tir_ennemi->y <= (player->y+ PLAYER_WIDTH)))
        {
            player->vie -= 1;
        }
    }
}

void fin_de_partie(ENNEMY *ennemy_list, bool *partie_finie, bool *partie_gagnee)
{
    if (!(*partie_finie))
    {
        bool il_existe_ennemi = false;
        for (int i = 0; i < NUMBER_ENNEMY_X*NUMBER_ENNEMY_Y; i++)
        {
            // Si un ennemi a atteint le bas de l'écran, la partie est terminée
            if ((ennemy_list[i].exist) && ((ennemy_list[i].y + ENNEMY_HEIGHT) > SCREEN_HEIGHT)){
                *partie_finie = true;
                return;
            }
            // Compter les ennemis qui existent encore
            if (ennemy_list[i].exist){
                il_existe_ennemi = true;
            }
        }  
        // Si aucun ennemi n'existe, la partie est terminée (victoire)
        if (!il_existe_ennemi){
            *partie_finie = true;
            *partie_gagnee = true;
        }
    }

}

bool init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur SDL_Init: %s", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Space Invaders (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!*window)
    {
        SDL_Log("Erreur SDL_CreateWindow: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer)
    {
        SDL_Log("Erreur SDL_CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;
}

void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active, ENNEMY *ennemy_list, TIR_ENNEMI *tir_ennemi, bool *tir_ennemi_active)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *running = false;
    }

    player->vx = 0.0f;
    if (keys[SDL_SCANCODE_LEFT])
        player->vx = -PLAYER_SPEED;
    if (keys[SDL_SCANCODE_RIGHT])
        player->vx = PLAYER_SPEED;

    if (keys[SDL_SCANCODE_SPACE] && !*bullet_active)
    {
        *bullet_active = true;
        bullet->x = ennemy_list[0].x + ennemy_list[0].w / 2 - ENNEMY_WIDTH / 2;
        bullet->y = ennemy_list[0].y;
        bullet->w = BULLET_WIDTH;
        bullet->h = BULLET_HEIGHT;
        bullet->vy = -BULLET_SPEED;
    }
    if (keys[SDL_SCANCODE_T] && !*tir_ennemi_active)
    {
        *tir_ennemi_active = true;
        tir_ennemi->x = player->x + player->w / 2 - BULLET_WIDTH / 2;
        tir_ennemi->y = player->y;
        tir_ennemi->w = TIR_ENNEMI_WIDTH;
        tir_ennemi->h = TIR_ENNEMI_HEIGHT;
        tir_ennemi->vy = TIR_ENNEMI_SPEED;
    }
}
  
void update(Entity *player, Entity *bullet, bool *bullet_active, float dt, ENNEMY *ennemy_list, bool *droite, bool *descente, bool *partie_finie, bool *partie_gagnee, TIR_ENNEMI *tir_ennemi, bool *tir_ennemi_active)
{
    player->x += player->vx * dt;

    if (player->x < 0)
        player->x = 0;
    if (player->x + player->w > SCREEN_WIDTH)
        player->x = SCREEN_WIDTH - player->w;

    if (*bullet_active)
    {
        bullet->y += bullet->vy * dt;
        if (bullet->y + bullet->h < 0)
            *bullet_active = false;
    }
    if (*tir_ennemi_active)
    {
        tir_ennemi->y += tir_ennemi->vy * dt;
        if (tir_ennemi->y + tir_ennemi->h > SCREEN_HEIGHT)
            *tir_ennemi_active = false;
    }
    // Déplacer les ennemis de gauche à droite
    if (*droite) {
        for (int i = 0; i < NUMBER_ENNEMY_X*NUMBER_ENNEMY_Y; i++)
        {
            ennemy_list[i].x += ENNEMY_SPEED_X*dt;
        }
        // Vérifier si l'ennemi le plus à droite touche le bord droit
        if (ennemy_list[NUMBER_ENNEMY_X-1].x + ennemy_list[NUMBER_ENNEMY_X-1].w >= SCREEN_WIDTH) {
            *droite = false;
            *descente = true;
        }
        else 
        {
            *descente = false;
        }
    }
    else 
    {
        for (int i = 0; i < NUMBER_ENNEMY_X*NUMBER_ENNEMY_Y; i++)
        {
            ennemy_list[i].x -= ENNEMY_SPEED_X*dt;
        }
        // Vérifier si l'ennemi le plus à gauche touche le bord gauche
        if (ennemy_list[0].x <= 0) {
            *droite = true;
            *descente = true;
        }
        else 
        {
            *descente = false;
        }
    }
    //Déplacer les ennemis vers le bas
    if (*descente){
        for (int i = 0; i < NUMBER_ENNEMY_X*NUMBER_ENNEMY_Y; i++)
        {
            ennemy_list[i].y += ENNEMY_SPEED_Y;
        }
    }
    //gestion de la collision
    gestion_collision(ennemy_list, bullet, bullet_active);
    fin_de_partie(ennemy_list, partie_finie, partie_gagnee);
    gestion_vie(player, tir_ennemi, tir_ennemi_active);
}
    
void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, bool bullet_active, ENNEMY *ennemy_list, bool partie_finie, bool partie_gagnee, TIR_ENNEMI *tir_ennemi, bool tir_ennemi_active)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (!partie_finie){
        SDL_Rect player_rect = {
        (int)player->x, (int)player->y,
        player->w, player->h};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &player_rect);

        if (bullet_active)
        {
            SDL_Rect bullet_rect = {
                (int)bullet->x, (int)bullet->y,
                bullet->w, bullet->h};
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &bullet_rect);
        }
        if (tir_ennemi_active)
        {
            SDL_Rect tir_ennemi_rect = {
                (int)tir_ennemi->x, (int)tir_ennemi->y,
                tir_ennemi->w, tir_ennemi->h};
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 125);
            SDL_RenderFillRect(renderer, &tir_ennemi_rect);
        }

        for (int i = 0; i < NUMBER_ENNEMY_X*NUMBER_ENNEMY_Y; i++)
        {  
            if (ennemy_list[i].exist){
                SDL_Rect ENNEMY = {
            (int)ennemy_list[i].x, (int)ennemy_list[i].y,
                ennemy_list[i].w, ennemy_list[i].h};
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_RenderFillRect(renderer, &ENNEMY);
            }
        } 
    }
    

    if (partie_finie){
        SDL_Rect fin_partie_rect = {
            SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 25,
            100, 50};
        if (partie_gagnee){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        
        SDL_RenderFillRect(renderer, &fin_partie_rect);
    }

    SDL_RenderPresent(renderer);
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
