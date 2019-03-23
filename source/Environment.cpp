#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Environment.h"
#include "../include/Functions.h"

Environment::Environment() {
    if (SDL_Init(SDL_INIT_VIDEO < 0)) {
        std::cerr << "Initialization error " << SDL_GetError() << std::endl;
    }
    window = SDL_CreateWindow(TOP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr <<  "Window could not be created " << SDL_GetError() << std::endl;
    }
    screen = SDL_GetWindowSurface(window);
    // SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    IMG_Init(IMG_INIT_PNG);
}

