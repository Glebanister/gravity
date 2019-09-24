#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include "Environment.h"

class Object
{
  private:
    double x, y, vx, vy, ax, ay, r, m;
    int massInc;
    Environment *env;

  public:
    Object();
    Object(double x, double y, Environment *env);
    bool movable;
    bool onCreate;

    void render(SDL_Renderer*);
    void updatePhysics();
    void annul();

    double getX();
    double getY();
    double getAX();
    double getAY();
    double getVX();
    double getVY();
    double getR();
    double getM();
    int getMassInc();

    void setX(double);
    void setY(double);
    void setAX(double);
    void setAY(double);
    void setVX(double);
    void setVY(double);
    void setR(double);
    void setM(double);
    void setEnvironment(Environment *);
    void setMassIncPos();
    void setMassIncNeg();

    ~Object();
};

#endif
