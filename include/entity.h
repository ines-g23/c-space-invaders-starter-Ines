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
    float vx, vy;
    int w, h;
    int vie;
} ENNEMY;

typedef struct 
{
    float x, y;
    float vy;
    int w, h;
} TIR_ENNEMI;

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
