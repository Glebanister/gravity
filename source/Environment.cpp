#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "../include/Environment.h"
#include "../include/Functions.h"

Environment::Environment()
{
    if (SDL_Init(SDL_INIT_VIDEO < 0))
    {
        printError("Initialization error");
    }
    else
    {
        printInfo("SDL initializated");
    }
    window = SDL_CreateWindow(TOP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printError("Window could not be created");
    }
    screen = SDL_GetWindowSurface(window);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}
