#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../../headers/global/constantes.h"
#include "../../headers/global/shortcuts.h"

SDL_Color blanc = {255, 255, 255, 0};
SDL_Color noir = {0, 0, 0, 0};
SDL_Color rouge = {255, 0, 0, 0};

SDL_Surface *creerTexte(SDL_Surface *screen, const char *text, SDL_Color couleur, TTF_Font *font)
{
  SDL_Surface *a = NULL;
  return TTF_RenderText_Solid(font, text, couleur);
}

void afficherGrille(SDL_Surface *screen, SDL_Surface *case1, SDL_Surface *case2, SDL_Rect positionCases[10][10])
{
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      SDL_BlitSurface(case1, NULL, screen, &positionCases[2 * i][2 * j]);
      SDL_BlitSurface(case1, NULL, screen, &positionCases[2 * i + 1][2 * j + 1]);
      SDL_BlitSurface(case2, NULL, screen, &positionCases[2 * i + 1][2 * j]);
      SDL_BlitSurface(case2, NULL, screen, &positionCases[2 * i][2 * j + 1]);
    }
  }
}
