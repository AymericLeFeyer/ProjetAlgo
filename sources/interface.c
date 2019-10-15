#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/constantes.h"
#include "../headers/shortcuts.h"

SDL_Color blanc = {255, 255, 255, 0};
SDL_Color noir = {0, 0, 0, 0};

void creerTexte(SDL_Surface* screen, const char *text, SDL_Rect pos, SDL_Color couleur, TTF_Font* font) {
  SDL_Surface* a = NULL;
  a = TTF_RenderText_Solid(font, text, couleur);
  SDL_BlitSurface(a, NULL, screen, &pos);
}

void afficherInterfaceBatailleNavale(SDL_Surface* screen, TTF_Font* font) {
  creerTexte(screen, "Joueur 1", newRect(580, 0, 0, 0), noir, font);
}
