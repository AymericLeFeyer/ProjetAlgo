#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/shortcuts.h"
#include "../headers/structure.h"


int affichageSudoku(SDL_Surface* screen) {
  // Variables
  int continuer;
  SDL_Event event;
  Coord c;

  // Images
  SDL_Surface* reglesImage = NULL;
  SDL_Surface* hoverFacile = NULL;
  SDL_Surface* hoverMoyen = NULL;
  SDL_Surface* hoverDifficile = NULL;
  SDL_Surface* hoverDemoniaque = NULL;

  reglesImage = IMG_Load("assets/sudoku/difficulteSudoku.jpg");
  hoverFacile = IMG_Load("assets/sudoku/facileButton.png");
  hoverMoyen = IMG_Load("assets/sudoku/moyenButton.png");
  hoverDifficile = IMG_Load("assets/sudoku/difficileButton.png");
  hoverDemoniaque = IMG_Load("assets/sudoku/demoniaqueButton.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posFacileButton = newRect(80, 489, 76, 339);
  SDL_Rect posMoyenButton = newRect(775, 489, 76, 324);
  SDL_Rect posDifficileButton = newRect(51, 593, 68, 435);
  SDL_Rect posDemoniaqueButton = newRect(642, 595, 68, 590);

  // Boucle principale
  while (continuer) {
    SDL_BlitSurface(reglesImage, NULL, screen, &fullscreen);
    c.x = event.button.x;
    c.y = event.button.y;

    while(SDL_PollEvent(&event)){


      switch(event.type) {
        case SDL_QUIT:
          continuer = 0;
          return 0;

          break;
        }


    }

    if (posInclusion(c.x, c.y, posFacileButton)) {
      SDL_BlitSurface(hoverFacile, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posMoyenButton)) {
      SDL_BlitSurface(hoverMoyen, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posDifficileButton)) {
      SDL_BlitSurface(hoverDifficile, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posDemoniaqueButton)) {
      SDL_BlitSurface(hoverDemoniaque, NULL, screen, &fullscreen);
    }

    SDL_Flip(screen);
  }
}
