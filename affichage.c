#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "headers/shortcuts.h"
#include "headers/constantes.h"

void affichageBatailleNavale(SDL_Surface* screen)
{
  // variables pour la boucle principale
  SDL_Event event;
  int continuer = 1;

  // Les deux types de cases (couleurs différentes)
  SDL_Surface *case1 = NULL;
  SDL_Surface *case2 = NULL;

  case1 = IMG_Load("assets/batailleNavale/case1.jpg");
  case2 = IMG_Load("assets/batailleNavale/case2.jpg");

  // Position de la grille sur l'écran
  SDL_Rect positionGrille = newRect((WIDTH_GAME - 640)/2, (HEIGHT_GAME - 640)/2, 640, 640);

  // Positions des cases stockées dans ce tableau
  SDL_Rect positionCases[10][10];

  // Initialisation de ces positions
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      positionCases[i][j] = newRect(positionGrille.x + 64 * i, positionGrille.y + 64 * j, 64, 64);
    }
  }

  // Boucle principale
  while (continuer){

    // On regarde l'event
    SDL_WaitEvent(&event);

    // En fonction de l'event, on fait des actions
    switch(event.type)
    {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
    }

    // On affiche le fond blanc
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    // On affiche toutes les cases
    for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
        SDL_BlitSurface(case1, NULL, screen, &positionCases[2*i][2*j]);
        SDL_BlitSurface(case1, NULL, screen, &positionCases[2*i+1][2*j+1]);
        SDL_BlitSurface(case2, NULL, screen, &positionCases[2*i+1][2*j]);
        SDL_BlitSurface(case2, NULL, screen, &positionCases[2*i][2*j+1]);
      }
    }

    // On actualise l'écran
    SDL_Flip(screen);
  }
}
