#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ENEMY *create_all_enemy(){
    ENEMY *enemy_list = malloc(NUMBER_ENEMY_X*NUMBER_ENEMY_Y*sizeof(ENEMY));
    if (enemy_list == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    for (int ligne = 0; ligne < NUMBER_ENEMY_Y; ligne++) {
        for (int col = 0; col < NUMBER_ENEMY_X; col++){
            int idx = ligne * NUMBER_ENEMY_X + col;
            enemy_list[idx].enemy_type = ENEMY_NORMAL;
        }
    }

    for (int ligne = 0; ligne < NUMBER_ENEMY_Y; ligne++){
        int idx1 = ligne * NUMBER_ENEMY_X;
        enemy_list[idx1].enemy_type = ENEMY_FAST;
        int idx2 = ligne * NUMBER_ENEMY_X + NUMBER_ENEMY_X- 1;
        enemy_list[idx2].enemy_type = ENEMY_FAST;
    }

    for (int ligne = 0; ligne < NUMBER_ENEMY_Y; ligne++) {
            for (int col = 0; col < NUMBER_ENEMY_X; col++) {
                int idx = ligne * NUMBER_ENEMY_X + col;
                enemy_list[idx].x = 40 + col * (SCREEN_WIDTH - 80) / NUMBER_ENEMY_X;
                enemy_list[idx].y = 20 + ligne * 50;
                enemy_list[idx].h = ENEMY_HEIGHT;
                enemy_list[idx].w = ENEMY_WIDTH;
                enemy_list[idx].vx = ENEMY_SPEED_X;
                enemy_list[idx].vy = ENEMY_SPEED_Y;
                if (enemy_list[idx].enemy_type == ENEMY_FAST)
                    enemy_list[idx].vy = FAST_ENEMY_SPEED_Y;
                if (ligne == 0)
                    enemy_list[idx].vie = 2;
                else 
                    enemy_list[idx].vie = 1;
            }
        }
    return enemy_list;
}

void free_enemy(ENEMY *enemy_list) {
    free(enemy_list);
}

void gestion_collision_bullet_enemy(ENEMY *enemy_list, Entity *bullet, bool *bullet_active){
    if (*bullet_active){
        bool deja_collision = false;
        int i = NUMBER_ENEMY_X*NUMBER_ENEMY_Y - 1;
        while ((!deja_collision)&& (i >= 0)){
            if ((enemy_list[i].vie > 0) &&(enemy_list[i].x <= bullet->x)&&(bullet->x <= (enemy_list[i].x+ENEMY_WIDTH))&& (enemy_list[i].y <= bullet->y)&&(bullet->y <= (enemy_list[i].y+ENEMY_HEIGHT)))
            {
                enemy_list[i].vie -= 1;
                deja_collision = true;
                *bullet_active = false;
            }
            i -= 1;
        } 
    }
} 

void gestion_vie(Entity *player, TIR_ENEMY *tir_enemy, bool *tir_enemy_active){
    if (*tir_enemy_active){
        if ((player->x <= tir_enemy->x)&&(tir_enemy->x <= (player->x + PLAYER_WIDTH))&& (player->y <= tir_enemy->y)&&(tir_enemy->y <= (player->y+ PLAYER_WIDTH)))
        {
            player->vie -= 1;
            *tir_enemy_active = false;
        }
    }
}

void fin_de_partie(ENEMY *enemy_list, bool *partie_finie, bool *partie_gagnee, Entity *player)
{
    if (!(*partie_finie))
    {
        bool il_existe_ennemi = false;
        for (int i = 0; i < NUMBER_ENEMY_X*NUMBER_ENEMY_Y; i++)
        {
            // Si un ennemi a atteint le bas de l'écran, la partie est terminée
            if ((enemy_list[i].vie > 0) && ((enemy_list[i].y + ENEMY_HEIGHT + 60) > SCREEN_HEIGHT)){
                *partie_finie = true;
                return;
            }
            // Compter les ennemis qui existent encore
            if (enemy_list[i].vie > 0){
                il_existe_ennemi = true;
            }
        }  
        // Si aucun ennemi n'existe, la partie est terminée (victoire)
        if (!il_existe_ennemi){
            *partie_finie = true;
            *partie_gagnee = true;
        }
        if(player->vie == 0){
            *partie_finie = true;
            *partie_gagnee = false;
        }
    }
}

void gestion_TIR_ENEMY(TIR_ENEMY *tir_enemy, bool *tir_enemy_active, ENEMY *enemy_list)
{
    if (!*tir_enemy_active){
        int a = rand()%1000;
        if (a < 1000*TIR_ENEMY_PROBA)
        {
            int colonne = rand()%NUMBER_ENEMY_X;
            int ligne_celui_qui_tire = -1;
            // Chercher l'ennemi le plus bas (dernier vivant) dans cette colonne
            for (int ligne = NUMBER_ENEMY_Y - 1; ligne >= 0; ligne--)
            {
                int id = ligne * NUMBER_ENEMY_X + colonne;
                if (enemy_list[id].vie > 0)
                {
                    ligne_celui_qui_tire = ligne;
                    break;
                }
            } 
            if (ligne_celui_qui_tire >= 0)
            {
                int id = ligne_celui_qui_tire * NUMBER_ENEMY_X + colonne;
                *tir_enemy_active = true;
                tir_enemy->x = enemy_list[id].x + enemy_list[id].w / 2;
                tir_enemy->y = enemy_list[id].y;
                tir_enemy->w = TIR_ENEMY_WIDTH;
                tir_enemy->h = TIR_ENEMY_HEIGHT;
                tir_enemy->vy = TIR_ENEMY_SPEED;
            }
        }
    }
}

void apparition_coeur(COEUR *coeur, bool *coeur_active)
{
    if (!*coeur_active){
        int a = rand()%1000;
        if (a < 1000*COEUR_PROBA)
        {
            *coeur_active = true;
            coeur->x = rand()%(SCREEN_WIDTH-COEUR_WIDTH-15)+ 15;
            coeur->y = 20;
            coeur->w = COEUR_HEIGHT;
            coeur->h = COEUR_HEIGHT;
            coeur->vy = COEUR_SPEED;
            coeur->path = "coeur.png";
        }
    }
}

void collision_coeur(COEUR *coeur, bool *coeur_active, Entity *player)
{
    if (*coeur_active){
        if ((player->x <= coeur->x)&&(coeur->x <= (player->x+PLAYER_WIDTH))&& (player->y <= coeur->y)&&(coeur->y <= (player->y+PLAYER_HEIGHT)))
        {
            *coeur_active = false;
            player->vie += 1;
            if (player->vie > 3)
                player->vie = 3;
        }
    }
}

PROTECTION *create_all_protection(){
    PROTECTION *protection_list = malloc(NUMBER_PROTECTION*sizeof(PROTECTION));
    if (protection_list == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    // Initialiser le tableau en grille
    for (int i = 0; i < NUMBER_PROTECTION; i++) {
        protection_list[i].x = (i+1)*SCREEN_WIDTH/(NUMBER_PROTECTION+1) - (PROTECTION_WIDTH/2);
        protection_list[i].y = (int) (SCREEN_HEIGHT*0.8);
        protection_list[i].w = PROTECTION_WIDTH;
        protection_list[i].h = PROTECTION_HEIGHT;
        protection_list[i].vie = VIE_INITIALE_PROTECTION;
    }
    return protection_list;
}

void gestion_collision_protection(TIR_ENEMY *tir_enemy, bool *tir_enemy_active, PROTECTION *protection_list, Entity *bullet, bool *bullet_active)
{
    if (*tir_enemy_active){
        bool deja_collision = false;
        int i = NUMBER_PROTECTION - 1;
        while ((!deja_collision)&& (i >= 0)){
            if ((protection_list[i].vie > 0) &&(protection_list[i].x <= tir_enemy->x + TIR_ENEMY_WIDTH)&&(tir_enemy->x <= (protection_list[i].x + PROTECTION_WIDTH))&& (protection_list[i].y <= tir_enemy->y)&&(tir_enemy->y <= (protection_list[i].y+PROTECTION_HEIGHT)))
            {
                protection_list[i].vie -= 1;
                deja_collision = true;
                *tir_enemy_active = false;
            }
            i -= 1;
        } 
    }
    if (*bullet_active){
        bool deja_collision = false;
        int i = NUMBER_PROTECTION - 1;
        while ((!deja_collision)&& (i >= 0)){
            if ((protection_list[i].vie > 0) &&(protection_list[i].x <= bullet->x + BULLET_WIDTH)&&(bullet->x <= (protection_list[i].x+ PROTECTION_WIDTH))&& (protection_list[i].y <= bullet->y + BULLET_HEIGHT)&&(bullet->y <= (protection_list[i].y+PROTECTION_HEIGHT)))
            {
                deja_collision = true;
                *bullet_active = false;
            }
            i -= 1;
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

void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active, bool *menu)
{
    // Gérer les événements SDL en permanence (menu ou pas)
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *running = false;
    }

    if (*menu){
        if (keys[SDL_SCANCODE_SPACE]){
            *menu = false;
        }
    }
    if(!*menu) { 

        player->vx = 0.0f;
        if (keys[SDL_SCANCODE_LEFT])
            player->vx = -PLAYER_SPEED;
        if (keys[SDL_SCANCODE_RIGHT])
            player->vx = PLAYER_SPEED;

        if (keys[SDL_SCANCODE_SPACE] && !*bullet_active)
        {
            *bullet_active = true;
            bullet->x = player->x + player->w / 2 - BULLET_WIDTH / 2;
            bullet->y = player->y;
            bullet->w = BULLET_WIDTH;
            bullet->h = BULLET_HEIGHT;
            bullet->vy = -BULLET_SPEED;
        }
    }
}

void deplacement_player (Entity *player, float dt){
    player->x += player->vx * dt;

    if (player->x < 0)
        player->x = 0;
    if (player->x + player->w > SCREEN_WIDTH)
        player->x = SCREEN_WIDTH - player->w;
}

void deplacement_bullet(Entity *bullet, bool *bullet_active, float dt){
    if (*bullet_active)
    {
        bullet->y += bullet->vy * dt;
        if (bullet->y + bullet->h < 0)
            *bullet_active = false;
    }
}

void deplacement_coeur(COEUR *coeur, bool *coeur_active, float dt){
    if (*coeur_active)
    {
        coeur->y += coeur->vy*dt;
        if (coeur->y + coeur->h > SCREEN_HEIGHT)
            *coeur_active = false;
    }
}

void deplacement_ennemi(ENEMY *enemy_list, bool *droite, bool *descente, float dt){
    // Déplacer les ennemis de gauche à droite
    if (*droite) {
        for (int i = 0; i < NUMBER_ENEMY_X*NUMBER_ENEMY_Y; i++)
        {
            enemy_list[i].x += (ENEMY_SPEED_X + (ENEMY_SPEED_X_MAX-ENEMY_SPEED_X)*enemy_list[0].y/SCREEN_HEIGHT)*dt;
        }
        // Vérifier si l'ennemi le plus à droite touche le bord droit
        if (enemy_list[NUMBER_ENEMY_X-1].x + enemy_list[NUMBER_ENEMY_X-1].w >= SCREEN_WIDTH) {
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
        for (int i = 0; i < NUMBER_ENEMY_X*NUMBER_ENEMY_Y; i++)
        {
            enemy_list[i].x -= (ENEMY_SPEED_X + (ENEMY_SPEED_X_MAX-ENEMY_SPEED_X)*enemy_list[0].y/SCREEN_HEIGHT)*dt;
        }
        // Vérifier si l'ennemi le plus à gauche touche le bord gauche
        if (enemy_list[0].x <= 0) {
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
        for (int i = 0; i < NUMBER_ENEMY_X*NUMBER_ENEMY_Y; i++)
        {
            enemy_list[i].y += enemy_list[i].vy;
        }
    }
}

void deplacement_TIR_ENEMY(TIR_ENEMY *tir_enemy, bool *tir_enemy_active, float dt){
    if (*tir_enemy_active)
    {
        tir_enemy->y += tir_enemy->vy * dt;
        if (tir_enemy->y + tir_enemy->h > SCREEN_HEIGHT)
            *tir_enemy_active = false;
    }
}

void update(Entity *player, Entity *bullet, bool *bullet_active, float dt, ENEMY *enemy_list, bool *droite, bool *descente, bool *partie_finie, bool *partie_gagnee, TIR_ENEMY *tir_enemy, bool *tir_enemy_active, COEUR *coeur, bool *coeur_active, PROTECTION *protection_list)
{
    deplacement_player (player,dt);
    deplacement_ennemi(enemy_list, droite, descente,dt);
    deplacement_coeur(coeur, coeur_active, dt);
    deplacement_bullet(bullet, bullet_active, dt);
    deplacement_TIR_ENEMY(tir_enemy, tir_enemy_active, dt);
    gestion_collision_bullet_enemy(enemy_list, bullet, bullet_active);
    fin_de_partie(enemy_list, partie_finie, partie_gagnee, player);
    gestion_vie(player, tir_enemy, tir_enemy_active);
    gestion_TIR_ENEMY(tir_enemy, tir_enemy_active, enemy_list);
    apparition_coeur(coeur, coeur_active);
    collision_coeur(coeur, coeur_active, player);
    gestion_collision_protection(tir_enemy, tir_enemy_active, protection_list, bullet, bullet_active);
}
    
void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, bool bullet_active, ENEMY *enemy_list, bool partie_finie, bool partie_gagnee, TIR_ENEMY *tir_enemy, bool tir_enemy_active, COEUR *coeur, bool coeur_active, PROTECTION *protection_list, bool menu)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    
    const char *vie = "vie.png";
    
    if (menu){
        render_text(renderer, "MENU", SCREEN_WIDTH/2 - 65, 100, white, 40);
        render_text(renderer, "appuyer sur espace pour lancer la partie", 130, 200, white, 15);
    }
    else {
        if (!partie_finie){
            SDL_Rect player_rect = {
            (int)player->x, (int)player->y,
            player->w, player->h};
            SDL_SetRenderDrawColor(renderer, 184, 134, 11, 255);
            SDL_RenderFillRect(renderer, &player_rect);

            for (int i = 0; i < player->vie; i++){
                render_image(renderer, vie, SCREEN_WIDTH - (15 + i*30), 20, VIE_WIDTH, VIE_HEIGHT);
            }

            if (bullet_active)
            {
                SDL_Rect bullet_rect = {
                    (int)bullet->x, (int)bullet->y,
                    bullet->w, bullet->h};
                SDL_SetRenderDrawColor(renderer, 255, 235, 205, 255);
                SDL_RenderFillRect(renderer, &bullet_rect);
            }
            if (tir_enemy_active)
            {
                SDL_Rect tir_enemy_rect = {
                    (int)tir_enemy->x, (int)tir_enemy->y,
                    tir_enemy->w, tir_enemy->h};
                SDL_SetRenderDrawColor(renderer, 192, 192, 192, 125);
                SDL_RenderFillRect(renderer, &tir_enemy_rect);
            }
            
            if (coeur_active)
            {
                render_image(renderer, coeur->path, coeur->x, coeur->y, COEUR_WIDTH, COEUR_HEIGHT);
            }

            for (int i = 0; i < NUMBER_PROTECTION; i++){
                if (protection_list[i].vie > 0){
                    SDL_Rect PROTECTION = {
                (int)protection_list[i].x, (int)protection_list[i].y,
                    protection_list[i].w, protection_list[i].h};
                    if (protection_list[i].vie == 1)
                        SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255);
                    else if (protection_list[i].vie == 2)
                        SDL_SetRenderDrawColor(renderer, 205, 133, 63, 255);
                    else 
                        SDL_SetRenderDrawColor(renderer, 165, 42, 42, 255);
                    SDL_RenderFillRect(renderer, &PROTECTION);
                }
            }

            for (int i = 0; i < NUMBER_ENEMY_X*NUMBER_ENEMY_Y; i++)
            {  
                if (enemy_list[i].vie > 0){
                    SDL_Rect ENEMY = {
                (int)enemy_list[i].x, (int)enemy_list[i].y,
                    enemy_list[i].w, enemy_list[i].h};
                    if (enemy_list[i].vie == 1)
                        SDL_SetRenderDrawColor(renderer, 255, 50, 255, 255);
                    else 
                        SDL_SetRenderDrawColor(renderer, 255, 200, 255, 255);
                    SDL_RenderFillRect(renderer, &ENEMY);
                }
            } 
        }
        

        if (partie_finie){
            if (partie_gagnee){
                render_text(renderer, "Tu as gagne !", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 15, white, 28);
            }
            else{
                render_text(renderer, "Tu as perdu !", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 15, white, 28);
            }
            
            
        }
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

void render_text(SDL_Renderer *renderer, const char *text, int x, int y, SDL_Color color, int taille)
{
    //TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", taille); si EarlyCameBoy n'est pas installé
    TTF_Font *font = TTF_OpenFont("./fonts/EarlyGameBoy.ttf", taille);
    if (!font)
    {
        SDL_Log("Erreur: impossible de charger la police: %s", TTF_GetError());
        return;
    }
    
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    if (!surface)
    {
        SDL_Log("Erreur: impossible de créer la surface de texte: %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_Log("Erreur: impossible de créer la texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }
    
    int text_width = surface->w;
    int text_height = surface->h;
    SDL_Rect rect = {x, y, text_width, text_height};
    
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void render_image(SDL_Renderer *renderer, const char *image_path, int x, int y, int width, int height)
{
    SDL_Surface *surface = IMG_Load(image_path);
    if (!surface)
    {
        SDL_Log("Erreur: impossible de charger l'image %s: %s", image_path, IMG_GetError());
        return;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_Log("Erreur: impossible de créer la texture pour l'image: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
