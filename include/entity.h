#ifndef ENTITY_H
#define ENTITY_H

typedef struct
{
    float x, y;
    float vx, vy;
    int w, h;
    int vie;
} Entity;

typedef struct
{
    float x, y;
    float vy;
    int w, h;
    bool bullet_active;
} BULLET;

typedef enum {
    ENEMY_NORMAL = 0,
    ENEMY_FAST = 1,
    ENEMY_RESISTANT = 2,
    ENEMY_RESISTANT_ET_RAPIDE = 3,
} EnemyType;


typedef struct 
{
    float x, y;
    float vx, vy;
    int w, h;
    int vie;
    EnemyType enemy_type;
} ENEMY;


typedef struct 
{
    float x, y;
    float vy;
    int w, h;
} TIR_ENEMY;

typedef struct 
{
    float x, y;
    float vy;
    int w, h;
    const char *path;
} COEUR;

typedef struct 
{
    float x, y;
    int w, h;
    int vie;
} PROTECTION;


#endif
