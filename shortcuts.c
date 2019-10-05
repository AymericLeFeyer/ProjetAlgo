#include <stdio.h>
#include <SDL/SDL.h>

SDL_Rect newRect(int x, int y, int h, int w) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.h = h;
    r.w = w;
    return r;
}
