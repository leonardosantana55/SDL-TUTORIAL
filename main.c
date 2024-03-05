// compile: gcc main.c input.c init.c draw.c -o prog -lSDL2

#include "main.h"

int WinMain(int argc, char *argv[]){
    App app;
    memset(&app, 0, sizeof(App));
    
    SDL_Rect r1; r1.h = 50; r1.w = 50; r1.x = 50; r1.y = 50;  
    
    initSDL(&app); // create window

    while (1){
        prepareScene(&app);
        doInput(&r1);
        createRectangle(&app, &r1);
        presentScene(&app);
        SDL_Delay(16);
    }

return 0;

}