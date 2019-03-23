#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../include/Object.h"

int getRandInt(int b, int e);

void blitSurface(SDL_Surface *what, int xWhat, int yWhat, int w, int h, SDL_Surface *where, int xWhere, int yWhere);

void blitScaled(SDL_Surface *what, int xWhat, int yWhat, int wWhat, int hWhat, SDL_Surface *where);

void clearStack();

void updateWindow(SDL_Window *window);

SDL_Surface *tryLoadImage(const char path[]);

SDL_Texture *tryLoadTexture(const char path[], SDL_Renderer *renderer);

void DrawCircle(SDL_Renderer *Renderer, int32_t _x, int32_t _y, int32_t radius);

void fillCircle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void updateAllAcc(std::vector<Object> &objs, const double G, int PIXELS_IN_UNIT, double COLLISION_CONTROL);
