#include <stdbool.h>

SDL_Rect newRect(int x, int y, int h, int w);
bool inclusion(SDL_Rect a, SDL_Rect b);
bool collision(SDL_Rect a, SDL_Rect b);
bool posInclusion(int x, int y, SDL_Rect b);
void regulerFPS(int FPS, Uint32 start);
