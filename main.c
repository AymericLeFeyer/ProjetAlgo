#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "headers/global/structure.h"
#include "headers/global/constantes.h"
#include "headers/menu.h"
#include "headers/splashScreen.h"


int main(int argc, char *argv[])
{
  // Variable de la boucle principale
  int continuer = 1;

  // Initialisation de la SDL
  if ((SDL_Init(SDL_INIT_VIDEO) == -1) && (SDL_Init(SDL_INIT_AUDIO) == -1))
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
  // Icone
  SDL_Surface* icone = NULL;
  icone = IMG_Load("assets/logo.png");
  SDL_WM_SetIcon(icone, NULL);

  // Création de la surface principale
  SDL_Surface *screen = NULL;

  screen = SDL_SetVideoMode(WIDTH_GAME, HEIGHT_GAME, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);



  // Nom de la fenêtre
  SDL_WM_SetCaption(TITLE_GAME, NULL);

  // On affiche le MENU
  afficherSplash(screen);

  // Liberation
  SDL_FreeSurface(screen);

  SDL_Quit();
  TTF_Quit();

  SDL_FreeSurface(icone);

  // On quitte le programme, sans erreur
  return EXIT_SUCCESS;
}
