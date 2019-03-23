#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <algorithm>
#include "../include/Functions.h"
#include "../include/Object.h"

int getRandInt(int b, int e)
{
    return rand() % (e - b + 1) + b;
}

void blitSurface(SDL_Surface *what, int xWhat, int yWhat, int w, int h, SDL_Surface *where, int xWhere, int yWhere)
{
    SDL_Rect desc;
    desc.x = xWhere;
    desc.y = yWhere;
    SDL_Rect src;
    src.x = xWhat;
    src.y = yWhat;
    src.h = h;
    src.w = w;
    SDL_BlitSurface(what, &src, where, &desc);
}

void blitScaled(SDL_Surface *what, int xWhat, int yWhat, int wWhat, int hWhat, SDL_Surface *where)
{
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = wWhat;
    stretchRect.h = hWhat;
    SDL_BlitScaled(what, NULL, where, &stretchRect);
}

void clearStack()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
    };
}

void updateWindow(SDL_Window *window)
{
    SDL_UpdateWindowSurface(window);
}

SDL_Surface *tryLoadImage(const char path[])
{
    SDL_Surface *img = IMG_Load(path);
    if (img == NULL)
    {
        std::cerr << "Unable to load image " << path << std::endl;
    }
    return img;
}

void DrawCircle(SDL_Renderer *Renderer, int32_t _x, int32_t _y, int32_t radius)
{
    int32_t x = radius - 1;
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t err = tx - (radius << 1); // shifting bits left by 1 effectively
                                      // doubles the value. == tx - diameter
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(Renderer, _x + x, _y - y);
        SDL_RenderDrawPoint(Renderer, _x + x, _y + y);
        SDL_RenderDrawPoint(Renderer, _x - x, _y - y);
        SDL_RenderDrawPoint(Renderer, _x - x, _y + y);
        SDL_RenderDrawPoint(Renderer, _x + y, _y - x);
        SDL_RenderDrawPoint(Renderer, _x + y, _y + x);
        SDL_RenderDrawPoint(Renderer, _x - y, _y - x);
        SDL_RenderDrawPoint(Renderer, _x - y, _y + x);

        if (err <= 0)
        {
            y++;
            err += ty;
            ty += 2;
        }
        else if (err > 0)
        {
            x--;
            tx += 2;
            err += tx - (radius << 1);
        }
    }
}

void fillCircle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Note that there is more to altering the bitrate of this
    // method than just changing this value.  See how pixels are
    // altered at the following web page for tips:
    //   http://www.libsdl.org/intro.en/usingvideo.html
    static const int BPP = 4;

    //double ra = (double)radius;

    for (double dy = 1; dy <= radius; dy += 1.0)
    {
        // This loop is unrolled a bit, only iterating through half of the
        // height of the circle.  The result is used to draw a scan line and
        // its mirror image below it.

        // The following formula has been simplified from our original.  We
        // are using half of the width of the circle because we are provided
        // with a center and we need left/right coordinates.

        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        int x = cx - dx;
        SDL_SetRenderDrawColor(surface, r, g, b, a);
        SDL_RenderDrawLine(surface, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
        SDL_RenderDrawLine(surface, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);

        // Grab a pointer to the left-most pixel for each half of the circle
        /*Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
		Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
		for (; x <= cx + dx; x++)
		{
			*(Uint32 *)target_pixel_a = pixel;
			*(Uint32 *)target_pixel_b = pixel;
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}*/
        /*
		// sleep for debug
		SDL_RenderPresent(gRenderer);
		std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
		*/
    }
}

SDL_Texture *tryLoadTexture(const char path[], SDL_Renderer *rend)
{
    SDL_Surface *texImg = tryLoadImage(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, texImg);
    SDL_FreeSurface(texImg);
    return tex;
}

void updateAllAcc(std::vector<Object> &objs, const double G, int PIXELS_IN_UNIT, double COLLISION_CONTROL)
{
    // long double M = 0;
    // long double MX = 0;
    // long double MY = 0;
    // for (int i = 0; i < (int)objs.size(); i++)
    // {
    //     M += objs[i].getM();
    //     MX += objs[i].getM() * (objs[i].getX() / PIXELS_IN_UNIT);
    //     MY += objs[i].getM() * (objs[i].getY() / PIXELS_IN_UNIT);
    // }
    // std::cout << M << ' ' << MX << ' ' << MY << std::endl;
    // for (int i = 0; i < (int)objs.size(); i++)
    // {
    //     long double xc = (MX - objs[i].getX() * objs[i].getM()) / (M - objs[i].getM());
    //     long double yc = (MY - objs[i].getY() * objs[i].getM()) / (M - objs[i].getM());
    //     objs[i].setAX(G * (M - objs[i].getM()) / ((xc - objs[i].getX()) * abs(xc - objs[i].getX())));
    //     objs[i].setAY(G * (M - objs[i].getM()) / ((yc - objs[i].getY()) * abs(yc - objs[i].getY())));
    //     // std::cout << objs[i].getAX() << std::endl;// << ' ' << objs[i].getAY() << std::endl;
    //     // std::cout << G * (M - objs[i].getM()) / ((xc - objs[i].getX()) * abs(xc - objs[i].getX())) << std::endl;
    //     // std::cout << G << ' ' << M << ' ' << objs[i].getM() << ' ' << xc << ' ' << objs[i].getX() << std::endl;
    // }

    for (int i = 0; i < (int)objs.size(); i++)
    {                                              // считаем текущей
        for (int j = 0; j < (int)objs.size(); j++) // считаем второй
        {
            if (i == j)
                continue;
            double dx = objs[j].getX() - objs[i].getX();
            double dy = objs[j].getY() - objs[i].getY();

            double r = dx * dx + dy * dy; // R^2
            r = std::max(r, COLLISION_CONTROL);
            double a = G * (objs[j].getM()) / r;

            r = sqrt(r); // R
            double ax = a * dx / r; // a * cos
            double ay = a * dy / r;

            // objs[i].setVX(objs[i].getVX() + ax * dt);
            // objs[i].setVY(objs[i].getVY() + ay * dt);
            objs[i].setAX(ax);
            objs[i].setAY(ay);
            // std::cout << dx / R << ' ' << dy / R << std::endl;
        }
        // for (int i = 0; i < (int)objs.size(); i++)
        // {
        //     objs[i].setX()
        // }
    }
}
