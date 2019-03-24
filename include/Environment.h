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
        const int RADIUS = 8;
        const int RED = 200;
        const int GREEN = 200;
        const int BLUE = 200;
        const int PLAY_BUTTON_WIDTH = 256;
        const int PLAY_BUTTON_HEIGHT = 128;
        const int PIXELS_IN_UNIT = 100;
        const double INC_DELTA = 2;
        const double MIN_MASS = 1;
        const double MAX_MASS = 300;
        const double GR_CONST = 8.0;
        const double COLLISION_CONTROL = 1000.0;
        const double SPEED_COEFFICENT = 0.1;
        const bool STAY_INSIDE = false;
        const bool BOUNCES_OFF_THE_WALLS = true;
        const bool PAUSE_INTERACTION = false;
        const bool PAUSE_GAME = true;
};

#endif
