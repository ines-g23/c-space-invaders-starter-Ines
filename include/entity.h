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
    bool exist; 
} ENNEMY;


#endif
