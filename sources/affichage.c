#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/shortcuts.h"
#include "../headers/constantes.h"
#include "../headers/structure.h"
#include "../headers/affichage.h"
#include "../headers/interface.h"
#include "../headers/placement.h"


void affichageBatailleNavale(SDL_Surface* screen, Joueur j)
{
  // variables pour la boucle principale
  SDL_Event event;
  int continuer = 1;

  // Polices
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);

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

  Coord c;
  int selection = -1;
  bool enSelection = false;

  // Boucle principale
  while (continuer){

    // On affiche le fond blanc
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    // Position du curseur
    c.x = event.button.x;
    c.y = event.button.y;

    // On regarde l'event
    SDL_WaitEvent(&event);

    // En fonction de l'event, on fait des actions
    switch(event.type)
    {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_o) {
          tournerBateau(&j.tab[2]);
        }
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (!(enSelection)) {
            selection = choixBateau(c, j);
            if (selection != -1) enSelection = true;
          }
          else if (enSelection) {
            selection = -1;
            enSelection = false;
          }
        }

        if (event.button.button == SDL_BUTTON_RIGHT) {
          if (enSelection) tournerBateau(&j.tab[selection]);
        }

    }

    if (enSelection) { // Test si un bateau est touche par le curseur
      deplacerBateau(&j.tab[selection], c);
    }


    // On affiche toutes les cases
    for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
        SDL_BlitSurface(case1, NULL, screen, &positionCases[2*i][2*j]);
        SDL_BlitSurface(case1, NULL, screen, &positionCases[2*i+1][2*j+1]);
        SDL_BlitSurface(case2, NULL, screen, &positionCases[2*i+1][2*j]);
        SDL_BlitSurface(case2, NULL, screen, &positionCases[2*i][2*j+1]);
      }
    }

    // On affiche les bateaux
    afficherBateaux(screen, j);

    // Afficher les textes pour la bataille navale
    afficherInterfaceBatailleNavale(screen, font);

    // On actualise l'écran
    SDL_Flip(screen);
  }
}

void afficherBateaux(SDL_Surface* screen, Joueur j)
{
  // On affiche le bateau en fonction de sa direction
  for(int i=0;i<=4;i++){
    switch (j.tab[i].direction) {
      case 1:
        SDL_BlitSurface(j.tab[i].nord, NULL, screen, &j.tab[i].r);
        break;
      case 2:
        SDL_BlitSurface(j.tab[i].west, NULL, screen, &j.tab[i].r);
        break;
      case 3:
        SDL_BlitSurface(j.tab[i].sud, NULL, screen, &j.tab[i].r);
        break;
      case 4:
        SDL_BlitSurface(j.tab[i].est, NULL, screen, &j.tab[i].r);
        break;
      default:
        break;
      }
    }
  // Flip
  SDL_Flip(screen);
}
