#include <SDL2/SDL.h>
#include <algorithm>
#include "../include/Object.h"
#include "../include/Environment.h"
#include "../include/Functions.h"

Object::Object() {}

Object::Object(double xNew, double yNew, Environment *envNew)
    : x(xNew), y(yNew), vx(0), vy(0), ax(0), ay(0), onCreate(false), env(envNew), movable(true) {}

void Object::render(SDL_Renderer *renderer)
{
    fillCircle(renderer, x, y, r,
               255 - 255 * (m - env->MIN_MASS) / (env->MAX_MASS - env->MIN_MASS),
               env->GREEN,
               255 * (m - env->MIN_MASS) / (env->MAX_MASS - env->MIN_MASS),
               0xFF);
}

void Object::updatePhysics()
{
    if (movable)
    {
        vx += ax;
        vy += ay;
        x += vx;
        y += vy;
    }
    if (env->BOUNCES_OFF_THE_WALLS)
    {
        if (x < r)
        {
            x = r;
            vx *= -1;
            ax *= -1;
        }
        else if (x > env->SCREEN_WIDTH - r)
        {
            x = env->SCREEN_WIDTH - r;
            vx *= -1;
            ax *= -1;
        }
        if (y < r)
        {
            y = r;
            vy *= -1;
            ay *= -1;
        }
        else if (y > env->SCREEN_HEIGHT - r)
        {
            y = env->SCREEN_HEIGHT - r;
            vy *= -1;
            ay *= -1;
        }
    }
    else if (env->STAY_INSIDE)
    {
        x = std::max(r, x);
        y = std::max(r, y);
        x = std::min(x, env->SCREEN_WIDTH - r);
        y = std::min(y, env->SCREEN_HEIGHT - r);
    }
}

void Object::annul()
{
    vx = vy = ax = ay = 0;
}

double Object::getX() { return x; }
double Object::getY() { return y; }
double Object::getAX() { return ax; }
double Object::getAY() { return ay; }
double Object::getVX() { return vx; }
double Object::getVY() { return vy; }
double Object::getR() { return r; }
double Object::getM() { return m; }

void Object::setX(double xNew) { x = xNew; }
void Object::setY(double yNew) { y = yNew; }
void Object::setAX(double axNew) { ax = axNew; }
void Object::setAY(double ayNew) { ay = ayNew; }
void Object::setVX(double vxNew) { vx = vxNew; }
void Object::setVY(double vyNew) { vy = vyNew; }
void Object::setR(double rNew) { r = rNew; }
void Object::setM(double mNew) { m = mNew; }
void Object::setEnvironment(Environment *envNew) { env = envNew; }
