#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

SDL_Surface* creerTexte(SDL_Surface* screen, const char *text, SDL_Color couleur, TTF_Font* font);
void afficherInterfaceBatailleNavale(SDL_Surface* screen, TTF_Font* font);
void debugMessage(SDL_Surface* screen, TTF_Font* font, const char *text);
void afficherTexte(SDL_Surface *a, SDL_Surface* screen, SDL_Rect pos);
void afficherGrille(SDL_Surface* screen, SDL_Surface* case1, SDL_Surface* case2, SDL_Rect positionCases[10][10]);
