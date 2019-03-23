#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../include/Object.h"
#include "../include/Functions.h"
#include "../include/Environment.h"

Environment env;

void close()
{
    SDL_DestroyWindow(env.window);
    IMG_Quit();
    SDL_Quit();
}

int main()
{
    SDL_Renderer *renderer = SDL_CreateRenderer(env.window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    std::vector<Object> objs;
    SDL_Event ev;
    bool circleOnCreate = false;
    Object newCircle;
    SDL_Texture *bg = tryLoadTexture(env.BACKGROUND_PATH, renderer);

    bool exitGame = false;
    bool pauseInteraction = env.PAUSE_INTERACTION;
    bool pauseGame = env.PAUSE_GAME;

    while (!exitGame)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                exitGame = true;
            }
            else if (ev.type == SDL_KEYDOWN)
            {
                // std::cout << ev.key.keysym.sym << std::endl;
                if (ev.key.keysym.sym == 100)
                {
                    pauseInteraction ^= 1;
                }
                else if (ev.key.keysym.sym == 112)
                {
                    pauseGame ^= 1;
                }
            }
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                circleOnCreate = true;
                int xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                newCircle.onCreate = true;
                newCircle.setX(xMouse);
                newCircle.setY(yMouse);
                newCircle.setR(env.RADIUS);
                newCircle.setEnvironment(&env);
                if (ev.button.button == SDL_BUTTON_LEFT)
                    newCircle.setMassIncPos();
                else
                    newCircle.setMassIncNeg();
                newCircle.setM(env.MIN_MASS * newCircle.getMassInc());
            }
            else if (ev.type == SDL_MOUSEBUTTONUP)
            {
                circleOnCreate = false;
                newCircle.onCreate = false;
                newCircle.annul();
                int xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                newCircle.setVX(env.SPEED_COEFFICENT * (newCircle.getX() - xMouse));
                newCircle.setVY(env.SPEED_COEFFICENT * (newCircle.getY() - yMouse));
                objs.push_back(newCircle);
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, NULL, NULL);

        if (!pauseInteraction)
        {
            updateAllAcc(objs, env.GR_CONST, env.PIXELS_IN_UNIT, env.COLLISION_CONTROL);
        }
        else
        {
            annulAllAcc(objs);
        }
        

        for (Object &planet : objs)
        {   
            if (!pauseGame)
                planet.updatePhysics();
            planet.render(renderer);
        }


        if (circleOnCreate)
        {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            SDL_SetRenderDrawColor(renderer, env.RED, env.GREEN, env.BLUE, 0xFF);
            SDL_RenderDrawLine(renderer, xMouse, yMouse, newCircle.getX(), newCircle.getY());
            newCircle.setM(newCircle.getM() + env.INC_DELTA * newCircle.getMassInc());
            if (newCircle.getMassInc() > 0)
                newCircle.setM(std::min(newCircle.getM(), env.MAX_MASS));
            else
                newCircle.setM(std::max(newCircle.getM(), -env.MAX_MASS));

            newCircle.render(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(env.GAME_DELAY);
    }

    close();
}
