#include "Text.h"
#include "Environment.h"
#include <string>
#include <iostream>

Text::Text(const char path[], int size, Environment *envNew)
{
    font = TTF_OpenFont(path, size);
    if (!font)
    {
        std::cerr << SDL_GetError() << std::endl;
    }
    env = envNew;
}

void Text::centerByX(int xb, int xe)
{
    x = (xe - xb - w) / 2 + xb;
}

void Text::centerByY(int yb, int ye)
{
    y = (ye - yb - h) / 2 + yb;
}

void Text::setText(const char t[], int r, int g, int b, int a, SDL_Renderer *renderer)
{
    SDL_Color cl;
    cl.r = r;
    cl.g = g;
    cl.b = b;
    cl.a = a;
    surface = TTF_RenderText_Solid(font, t, cl);
    if (!surface)
    {
        std::cerr << "Error while TTF_RenderText_Solid" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cerr << "Error while SDL_CreateTextureFromSurface" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
    }
    w = surface->w;
    h = surface->h;
}

Text::~Text()
{
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
}

int Text::getX() { return x; }
int Text::getY() { return y; }
int Text::getH() { return h; }
int Text::getW() { return w; }

void Text::setX(int xNew) { x = xNew; }
void Text::setY(int yNew) { y = yNew; }
void Text::setW(int wNew) { w = wNew; }
void Text::setH(int hNew) { h = hNew; }
