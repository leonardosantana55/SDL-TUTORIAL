#include "main.h"

extern App app;

void doInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            doKeyDown(&event.key);     
            break;
        case SDL_KEYUP:
            doKeyUp(&event.key);        
        default:
            break;
        }
    }
}

void doKeyDown(SDL_KeyboardEvent *key){

    if (key->repeat == 0){
        switch (key->keysym.scancode){
            case SDL_SCANCODE_DOWN:
                app.down = 1;
                break;
            case SDL_SCANCODE_UP:
                app.up = 1;
                break;
            case SDL_SCANCODE_LEFT:
                app.left = 1;
                break;
            case SDL_SCANCODE_RIGHT:
                app.rigth = 1;
                break;
            case SDL_SCANCODE_0:
                app.fire = 1;
                break;
        }
    }
}

void doKeyUp(SDL_KeyboardEvent *key){
    if (key->repeat == 0){
        switch (key->keysym.scancode){
            case SDL_SCANCODE_DOWN:
                app.down = 0;
                break;
            case SDL_SCANCODE_UP:
                app.up = 0;
                break;
            case SDL_SCANCODE_LEFT:
                app.left = 0;
                break;
            case SDL_SCANCODE_RIGHT:
                app.rigth = 0;
                break;
        }
    }
}










/* OLD WAY */

/* #include "main.h"

Uint32 last_keydown_time_stamp;

void directionalMovement(SDL_Rect *r, SDL_Event event, Uint32 *last_keydown_time_stamp){
        switch (event.type){
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
                switch (event.key.keysym.scancode){
                case SDL_SCANCODE_DOWN:
                    if ((r->y + MOV_SPEED) > (SCREEN_HEIGHT - r->h)){
                        r->y = SCREEN_HEIGHT - r->h;
                    }
                    else{
                        r->y += MOV_SPEED;
                    }
                    printf("down\n");
                    printf("last keydown timestamp: %d\n",event.key.timestamp - *last_keydown_time_stamp);
                    *last_keydown_time_stamp = event.key.timestamp;
                    break;

                case SDL_SCANCODE_UP:
                    if ((r->y - MOV_SPEED) < 0 ){
                        r->y = 0;
                    }
                    else{
                        r->y -= MOV_SPEED;
                    }
                    printf("up\n");
                    break;

                case SDL_SCANCODE_LEFT:
                    if ((r->x - MOV_SPEED) < 0){
                        r->x = 0;
                    }
                    else{
                        r->x -= MOV_SPEED;
                    }
                    printf("left\n");
                    break;

                case SDL_SCANCODE_RIGHT:
                    if ((r->x + MOV_SPEED) > (SCREEN_WIDTH - r->w)){
                        r->x = SCREEN_WIDTH - r->w;
                    }
                    else{
                        r->x += MOV_SPEED;
                    }
                    printf("rigth\n");
                    break;
                
                default:
                    break;
                }
        default:
            break;
        }
}

// TODO: CREATE A TIMER AND A LAST EVENT TRACKER, TO FIRE A SPECIAL MOVE WHEN A BUTTON IS PRESSED FAST ENOUGHT

void doInput(SDL_Rect *r){
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        directionalMovement(r, event, &last_keydown_time_stamp);
        //printf("last keydown timestamp: %d\n", event.key.timestamp - last_keydown_time_stamp); // Add another parameter to change when the if statement is implemented
    }
} */