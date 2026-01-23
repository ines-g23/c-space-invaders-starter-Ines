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
    bool exist; 
} ENNEMY;

typedef struct 
{
    float x, y;
    float vy;
    int w, h;
} TIR_ENNEMI;

#endif
