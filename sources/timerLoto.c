#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../headers/shortcuts.h"
#include "../headers/timerLoto.h"
#include "../headers/interface.h"

int timerLoto(int FPS, int *temps, int tempsmax, SDL_Rect rectangle, TTF_Font *font, SDL_Color couleur, SDL_Surface *tempsRestant, SDL_Surface *screen)
{
  double c = (tempsmax * FPS - (*temps)) / FPS;
  int a = (int)c;
  int b = (int)((((tempsmax * FPS - *temps) * 10 / FPS) - (a * 10)));
  int d = (int)((((tempsmax * FPS - *temps) * 100 / FPS) - (b * 10) - (a * 100)));
  char string[100];
  if (a < 10)
  {
    sprintf(string, "0%d:%d%d", a, b, d);
  }
  else
  {
    sprintf(string, "%d:%d%d", a, b, d);
  }
  tempsRestant = creerTexte(screen, string, couleur, font);
  SDL_BlitSurface(tempsRestant, NULL, screen, &rectangle);
  if (*temps >= tempsmax * FPS)
  {
    *temps = 0;
    return 1;
  }
  else
  {
    *temps = *temps + 1;
    return 0;
  }
}
