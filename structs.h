#ifndef APP_H
#define APP_H

#include "main.h"

typedef struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int left;
    int rigth;
    int fire;
}App;

typedef struct Bullet{
    SDL_Rect form;
    int dx;
    int dy;
    int distance;
}Bullet;

#endif