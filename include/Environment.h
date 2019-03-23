#include <vector>
#include <SDL2/SDL.h>

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
    public:
        Environment();
        SDL_Window* window;
        SDL_Surface* screen;
        SDL_Surface* surface;
        const char TOP_NAME[8] = "GRAVITY";
        const char BACKGROUND_PATH[21] = "textures/back.png";
        const int SCREEN_WIDTH = 1024;
        const int SCREEN_HEIGHT = 768;
        const int GAME_DELAY = 15;
        const int RADIUS = 10;
        const int RED = 255;
        const int GREEN = 255;
        const int BLUE = 255;
        const int INC_DELTA = 2;
        const int PIXELS_IN_UNIT = 100;
        const double MIN_MASS = 1;
        const double MAX_MASS = 300;
        const double GR_CONST = 20.0;
        const double COLLISION_CONTROL = 1000.0;
        const bool STAY_INSIDE = false;
        const bool BOUNCES_OFF_THE_WALLS = true;
};

#endif
