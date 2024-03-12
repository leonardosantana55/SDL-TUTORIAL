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

void createBullet(App *app, SDL_Rect *bullet){
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 255, 128);
    SDL_RenderFillRect(app->renderer, bullet);
    SDL_RenderDrawRect(app->renderer, bullet);
}
//criar essa estrutura e destruir ela com base em criterios internos

void presentScene(App *app){
    SDL_RenderPresent(app->renderer);
}