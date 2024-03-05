#include "main.h"

void prepareScene(App *app){
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
}

void createRectangle(App *app, SDL_Rect *r){
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 255, 128);
    SDL_RenderFillRect(app->renderer, r);
    SDL_RenderDrawRect(app->renderer, r);
}


void presentScene(App *app){
    SDL_RenderPresent(app->renderer);
}