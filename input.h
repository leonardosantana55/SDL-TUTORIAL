#ifndef INPUT_H
#define INPUT_H

void doInput(SDL_Rect *r);
void directionalMovement(SDL_Rect *r, SDL_Event event, Uint32 *last_keydown_time_stamp);
#endif