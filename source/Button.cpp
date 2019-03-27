#include "../include/Button.h"
#include "../include/Functions.h"
#include <iostream>

Button::Button(){};
Button::Button(int xNew, int yNew, int wNew, int hNew, Environment *envNew)
    : x(xNew), y(yNew), w(wNew), h(hNew), env(envNew), xOfButton(0), yOfButton(0)
{
    printInfo("Button created");
};

bool Button::cursorInside()
{
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);
    return ((x <= xMouse && xMouse <= x + w) && (y <= yMouse && yMouse <= y + h));
}

void Button::updateTexture()
{
    // if (cursorInside())
    // {

    // }
}

void Button::centerByX(int xb, int xe)
{
    x = (xe - xb - w) / 2 + xb;
}

void Button::centerByY(int yb, int ye)
{
    y = (ye - yb - h) / 2 + yb;
}

void Button::setX(int xNew) { x = xNew; }
void Button::setY(int yNew) { y = yNew; }
void Button::setW(int wNew) { w = wNew; }
void Button::setH(int hNew) { h = hNew; }

int Button::getX() { return x; }
int Button::getY() { return y; }
int Button::getW() { return w; }
int Button::getH() { return h; }

Button::~Button()
{
    SDL_DestroyTexture(imgPressed);
    SDL_DestroyTexture(imgUnpressed);
}