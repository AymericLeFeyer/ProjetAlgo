#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "headers/affichage.h"
#include "headers/constantes.h"

int main(int argc, char *argv[])
{
  // Variable de la boucle principale
  int continuer = 1;

  // Initialisation de la SDL
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
  {
    fprintf(stderr, "Erreur d'initialisation de la SDL");
    exit(EXIT_FAILURE);
  }

  // Création de la surface principale
  SDL_Surface *screen = NULL;

  screen = SDL_SetVideoMode(WIDTH_GAME, HEIGHT_GAME, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

  // Nom de la fenêtre
  SDL_WM_SetCaption(TITLE_GAME, NULL);


  // On affiche la bataille navale
  affichageBatailleNavale(screen);

  // On quitte le programme, sans erreur
  return EXIT_SUCCESS;
}
