#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Environment.h"

class Text
{
  private:
    TTF_Font *font;
    SDL_Surface *surface;
    Environment *env;
    int x, y;
    int w, h;
  public:
    SDL_Texture *texture;
    Text(const char path[], int size, Environment *env);
    void centerByX(int xb, int xe);
    void centerByY(int yb, int ye);

    int getX();
    int getY();
    int getH();
    int getW();

    void setX(int);
    void setY(int);
    void setW(int);
    void setH(int);
    void setText(const char t[], int r, int g, int b, int a, SDL_Renderer *renderer);

    ~Text();
};

#endif
