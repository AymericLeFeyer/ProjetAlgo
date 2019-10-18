#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "headers/structure.h"
#include "headers/affichage.h"
#include "headers/initialisation.h"
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

  // Initialisation de TTF
  if (TTF_Init() == -1)
  {
      fprintf(stderr, "Erreur d'initialisation de TTF");
      exit(EXIT_FAILURE);
  }

  // Création de la surface principale
  SDL_Surface *screen = NULL;

  screen = SDL_SetVideoMode(WIDTH_GAME, HEIGHT_GAME, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

  // Nom de la fenêtre
  SDL_WM_SetCaption(TITLE_GAME, NULL);


  // On affiche la bataille navale
  JoueurBatailleNavale j1, j2;
  j1 = initJoueurBN(1, 10, 10);
  j2 = initJoueurBN(2, 10, 10);
  affichageBatailleNavale(screen, j1, j2);

  // On quitte le programme, sans erreur
  return EXIT_SUCCESS;
}
