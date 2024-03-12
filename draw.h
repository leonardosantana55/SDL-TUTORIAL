#ifndef DRAW_H
#define DRAW_H

void prepareScene(App *app);
void presentScene(App *app);
void createRectangle(App *app, SDL_Rect *r);
void createBullet(App *app, SDL_Rect *bullet);

#endif