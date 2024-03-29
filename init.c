#include "main.h"

extern App app;

void initSDL(){
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED; // hardware aceleration

    windowFlags = 0; //

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Could not initialize DSL: %s\n", 
        SDL_GetError());
        
        exit(1);
    }

    app.window = SDL_CreateWindow(
        "tetris", 
        100,
        100, 
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        windowFlags);


    if (!app.window){
		printf("Failed to open %d x %d window: %s\n", 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_GetError());
		
        exit(1);
	}

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer){
		printf("Failed to create renderer: %s\n", 
        SDL_GetError());
		
        exit(1);
	}

}