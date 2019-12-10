#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../../headers/global/structure.h"
#include "../../headers/global/constantes.h"
#include "../../headers/global/shortcuts.h"
#include "../../headers/profils/sauvegarde.h"
#include "../../headers/profils/chargement.h"
#include "../../headers/profils/tabScore.h"
#include "../../headers/global/interface.h"

void afficherTableauScore(SDL_Surface* screen) {
  // Variables
  char jeu = 'b';
  int continuer = 1;
  SDL_Event event;
  Coord c;
  tabP p;
  chargementProfils(p);

  // Images
  SDL_Surface* batailleNavale = NULL;
  SDL_Surface* poker = NULL;
  SDL_Surface* loto = NULL;
  SDL_Surface* sudoku = NULL;
  SDL_Surface* ecran = NULL;
  SDL_Surface* menuHover = NULL;
  SDL_Surface* backHover = NULL;
  SDL_Surface* nextHover = NULL;
  SDL_Surface* surfaceNom[10];

  batailleNavale = IMG_Load("assets/menu/batailleNavale.png");
  poker = IMG_Load("assets/menu/poker.png");
  loto = IMG_Load("assets/menu/loto.png");
  sudoku = IMG_Load("assets/menu/sudoku.png");
  ecran = IMG_Load("assets/menu/scores.jpg");
  menuHover = IMG_Load("assets/menu/menuHover.png");
  backHover = IMG_Load("assets/menu/backHover.png");
  nextHover = IMG_Load("assets/menu/nextHover.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect backPosition = newRect(14, 532, 188, 206);
  SDL_Rect nextPosition = newRect(1035, 510, 210, 245);
  SDL_Rect menuPosition = newRect(0, 0, 157, 293);
  SDL_Rect posJeu = newRect(412, 12, 130, 468);
  SDL_Rect positionNom[10];
  for (int i = 0; i < 10; i++) {
    positionNom[i] = newRect(550, 200 + 40 * i, 0, 0);
  }

  // Couleurs
  SDL_Color blanc = {255, 255, 255, 0};

  // Font
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);

  char buffer[30];

  while (continuer) {
    SDL_BlitSurface(ecran, NULL, screen, &fullscreen);
    switch (jeu) {
      case 'b':
        // BatailleNavale
        SDL_BlitSurface(batailleNavale, NULL, screen, &posJeu);
        // Affichage scores
        for (int i = 0; i < 10; i++) {
          if (p[i].scoreNavale >= 0) {
            sprintf(buffer, "%d - %s", (int)p[i].scoreNavale, p[i].nom);
            surfaceNom[i] = creerTexte(screen, buffer, blanc, font);
            SDL_BlitSurface(surfaceNom[i], NULL, screen, &positionNom[i]);
          }
        }

        break;
      case 'l':
        // Loto
        SDL_BlitSurface(loto, NULL, screen, &posJeu);

        break;
      case 'p':
        // Poker
        SDL_BlitSurface(poker, NULL, screen, &posJeu);

        break;
      case 's':
        // Sudoku
        SDL_BlitSurface(sudoku, NULL, screen, &posJeu);

        break;

    }

    while (SDL_PollEvent(&event))
    {
      c.x = event.button.x;
      c.y = event.button.y;

      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;
        break;
      case SDL_MOUSEBUTTONDOWN:
        // En cas de clic
        if (posInclusion(c.x, c.y, menuPosition)) {
          continuer = 0;
        }
        if (posInclusion(c.x, c.y, nextPosition)) {
          if (jeu == 'b') jeu = 's';
          else if (jeu == 's') jeu = 'p';
          else if (jeu == 'p') jeu = 'l';
          else if (jeu == 'l') jeu = 't';
          else if (jeu == 't') jeu = 'b';
        }
        if (posInclusion(c.x, c.y, backPosition)) {
          if (jeu == 'b') jeu = 't';
          else if (jeu == 't') jeu = 'l';
          else if (jeu == 'l') jeu = 'p';
          else if (jeu == 'p') jeu = 's';
          else if (jeu == 's') jeu = 'b';
        }
      }
    }
    // Hovers
    if (posInclusion(c.x, c.y, menuPosition)) {
      SDL_BlitSurface(menuHover, NULL ,screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, backPosition)) {
      SDL_BlitSurface(backHover, NULL ,screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, nextPosition)) {
      SDL_BlitSurface(nextHover, NULL ,screen, &fullscreen);
    }
    SDL_Flip(screen);
  }
}
