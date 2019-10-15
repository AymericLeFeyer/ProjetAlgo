#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/shortcuts.h"
#include "../headers/constantes.h"
#include "../headers/structure.h"
#include "../headers/affichage.h"
#include "../headers/interface.h"


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

    afficherBateaux(screen, j);

    // Afficher les textes pour la bataille navale
    afficherInterfaceBatailleNavale(screen, font);

    // On actualise l'écran
    SDL_Flip(screen);
  }
}

void afficherBateaux(SDL_Surface* screen, Joueur j)
{
  // Creation des 5 surfaces de bateaux
  SDL_Surface *bateau1 = NULL;
  SDL_Surface *bateau2 = NULL;
  SDL_Surface *bateau3 = NULL;
  SDL_Surface *bateau4 = NULL;
  SDL_Surface *bateau5 = NULL;

  // Images des 5 bateaux
  bateau1 = IMG_Load("assets/batailleNavale/bateau1-1.png");
  bateau2 = IMG_Load("assets/batailleNavale/bateau2-1.png");
  bateau3 = IMG_Load("assets/batailleNavale/bateau3-1.png");
  bateau4 = IMG_Load("assets/batailleNavale/bateau4-1.png");
  bateau5 = IMG_Load("assets/batailleNavale/bateau5-1.png");

  // Positions des bateaux
  SDL_Rect posBateau1 = newRect(10, 10, 0, 0);
  SDL_Rect posBateau2 = newRect(10, 200, 0, 0);
  SDL_Rect posBateau3 = newRect(10, 400, 0, 0);
  SDL_Rect posBateau4 = newRect(100, 10, 0, 0);
  SDL_Rect posBateau5 = newRect(100, 300, 0, 0);

  for(int i=0;i<=4;i++){
    if(j.tab[i].direction==1){
      SDL_BlitSurface(j.tab[i].nord, NULL, screen, &j.tab[i].r);
    }
    if(j.tab[i].direction==2){
      SDL_BlitSurface(j.tab[i].west, NULL, screen, &j.tab[i].r);
    }
    if(j.tab[i].direction==3){
      SDL_BlitSurface(j.tab[i].sud, NULL, screen, &j.tab[i].r);
    }
    if(j.tab[i].direction==4){
      SDL_BlitSurface(j.tab[i].est, NULL, screen, &j.tab[i].r);
    }
  }

  // Flip
  SDL_Flip(screen);
}
