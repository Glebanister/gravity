#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../include/Object.h"
#include "../include/Functions.h"
#include "../include/Environment.h"
#include "../include/Button.h"
#include "../include/Text.h"

Environment env;
SDL_Renderer *renderer;
bool exitGame = false;

void close()
{
    SDL_DestroyWindow(env.window);
    IMG_Quit();
    SDL_Quit();
}

void init()
{
    renderer = SDL_CreateRenderer(env.window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void mainActivity()
{
    init();
    SDL_RenderClear(renderer);
    std::vector<Object> objs;
    SDL_Event ev;
    bool circleOnCreate = false;
    Object newCircle;
    SDL_Texture *bg = tryLoadTexture(env.BACKGROUND_PATH, renderer);

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
                else if (ev.key.keysym.sym == 99)
                {
                    for (Object &obj : objs)
                    {
                        obj.~Object();
                    }
                    objs.clear();
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
}

void helloScreen()
{
    SDL_Event ev;
    bool continueGame = false;

    Text GravityText(env.FONT, 150, &env);
    GravityText.setText("Gravity", 100, 100, 150, 255, renderer);
    GravityText.centerByX(0, env.SCREEN_WIDTH);
    GravityText.setY(100);

    Button playButton {0, 0, env.PLAY_BUTTON_WIDTH, env.PLAY_BUTTON_HEIGHT, &env};
    playButton.centerByX(0, env.SCREEN_WIDTH);
    playButton.centerByY(60, env.SCREEN_HEIGHT);
    SDL_Texture *playButtonImg = tryLoadTexture(env.PLAY_BUTTON_PATH, renderer);
    SDL_Texture *helloBg = tryLoadTexture(env.BACKGROUND_PATH, renderer);

    Text gameText(env.FONT, 30, &env);
    gameText.setText("Game", 100, 100, 150, 255, renderer);
    gameText.centerByX(0, env.SCREEN_WIDTH);
    gameText.setY(GravityText.getY() - gameText.getH() + 30);

    Text playText(env.FONT, 50, &env);
    playText.setText("Play", 70, 70, 120, 255, renderer);
    playText.centerByX(playButton.getX(), playButton.getX() + playButton.getW());
    playText.centerByY(playButton.getY(), playButton.getY() + playButton.getH());

    while (!exitGame && !continueGame)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                exitGame = true;
            }
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    if (playButton.cursorInside())
                    {
                        continueGame = true;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);

        renderTexture(helloBg, 0, 0, env.SCREEN_WIDTH, env.SCREEN_HEIGHT, renderer);

        renderTexture(playButtonImg, playButton.getX(), playButton.getY(), playButton.getW(), playButton.getH(), renderer);

        renderTexture(gameText.texture, gameText.getX(), gameText.getY(), gameText.getW(), gameText.getH(), renderer);

        renderTexture(GravityText.texture, GravityText.getX(), GravityText.getY(), GravityText.getW(), GravityText.getH(), renderer);

        renderTexture(playText.texture, playText.getX(), playText.getY(), playText.getW(), playText.getH(), renderer);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(env.GAME_DELAY);
    }   
    SDL_DestroyTexture(playButtonImg);
    SDL_DestroyTexture(helloBg);
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
}

int main()
{
    init();
    helloScreen();
    mainActivity();
    close();
}
