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
        const char PLAY_BUTTON_PATH[24] = "textures/buttonPlay.png";
        const char FONT[26] = "textures/superfly2001.ttf";
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const int GAME_DELAY = 15;
        const int RADIUS = 7;
        const int RED = 255;
        const int GREEN = 255;
        const int BLUE = 255;
        const int PLAY_BUTTON_WIDTH = 256;
        const int PLAY_BUTTON_HEIGHT = 128;
        const double PIXELS_IN_UNIT = 10000;
        const double INC_DELTA = 20000;
        const double MIN_MASS = 1;
        const double MAX_MASS = 3000000;
        const double GR_CONST = 15.0;
        const double COLLISION_CONTROL = 1000.0;
        const double SPEED_COEFFICENT = 0.1;
        const bool STAY_INSIDE = false;
        const bool BOUNCES_OFF_THE_WALLS = true;
        const bool PAUSE_INTERACTION = false;
        const bool PAUSE_GAME = true;
};

#endif
