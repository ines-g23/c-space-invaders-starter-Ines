#ifndef ENTITY_H
#define ENTITY_H

typedef struct
{
    float x, y;
    float vx, vy;
    int w, h;
} Entity;

typedef struct 
{
    float x, y;
    float vx, vy;
    int w, h;
    int exist; //exist = 1 si l'ennemi est vivant 0 sinon
} ENNEMY;


#endif
