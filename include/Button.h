#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include "../include/Environment.h"

class Button
{
  private:
    int x, y, w, h;
    int xOfButton, yOfButton;
    Environment *env;

  public:
    Button();
    Button(int x, int y, int w, int h, Environment *env);
    SDL_Texture *img;

    void updateTexture();
    void centerByX(int xb, int xe);
    void centerByY(int yb, int ye);
    bool cursorInside();

    void setX(int);
    void setY(int);
    void setW(int);
    void setH(int);

    int getX();
    int getY();
    int getW();
    int getH();
};

#endif