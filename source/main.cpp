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
    bool exitGame = false;
    SDL_Renderer *renderer = SDL_CreateRenderer(env.window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    std::vector<Object> objs;
    SDL_Event ev;
    bool circleOnCreate = false;
    Object newCircle;
    SDL_Texture *bg = tryLoadTexture(env.BACKGROUND_PATH, renderer);

    while (!exitGame)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                exitGame = true;
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
                newCircle.setM(env.MIN_MASS);
                newCircle.setEnvironment(&env);
            }
            else if (ev.type == SDL_MOUSEBUTTONUP)
            {
                circleOnCreate = false;
                newCircle.onCreate = false;
                newCircle.annul();
                objs.push_back(newCircle);
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, NULL, NULL);

        updateAllAcc(objs, env.GR_CONST, env.PIXELS_IN_UNIT, env.COLLISION_CONTROL);

        for (Object &planet : objs)
        {
            planet.updatePhysics();
            planet.render(renderer);
        }

        if (circleOnCreate)
        {
            newCircle.setM(newCircle.getM() + env.INC_DELTA);
            newCircle.setM(std::min(newCircle.getM() + env.INC_DELTA, env.MAX_MASS));
            newCircle.render(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(env.GAME_DELAY);
    }

    close();
}
