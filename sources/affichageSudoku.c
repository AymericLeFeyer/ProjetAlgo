#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/shortcuts.h"
#include "../headers/structure.h"
#include "../headers/affichageSudoku.h"

int affichageSudoku(SDL_Surface* screen) {
  // Variables
  int continuer;
  SDL_Event event;
  Coord c;
  int choix = 0;

  // Images
  SDL_Surface* reglesImage = NULL;
  SDL_Surface* hoverFacile = NULL;
  SDL_Surface* hoverMoyen = NULL;
  SDL_Surface* hoverDifficile = NULL;
  SDL_Surface* hoverDemoniaque = NULL;
  SDL_Surface* nextButton = NULL;
  SDL_Surface* nextButtonHover = NULL;

  reglesImage = IMG_Load("assets/sudoku/difficulteSudoku.jpg");
  hoverFacile = IMG_Load("assets/sudoku/facileButton.png");
  hoverMoyen = IMG_Load("assets/sudoku/moyenButton.png");
  hoverDifficile = IMG_Load("assets/sudoku/difficileButton.png");
  hoverDemoniaque = IMG_Load("assets/sudoku/demoniaqueButton.png");
  nextButton = IMG_Load("assets/sudoku/nextButton.png");
  nextButtonHover = IMG_Load("assets/sudoku/nextButtonHover.png");



  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posFacileButton = newRect(80, 489, 76, 339);
  SDL_Rect posMoyenButton = newRect(775, 489, 76, 324);
  SDL_Rect posDifficileButton = newRect(51, 593, 68, 435);
  SDL_Rect posDemoniaqueButton = newRect(642, 595, 68, 590);
  SDL_Rect posNextButton = newRect(479, 278, 99, 278);

  // Boucle principale
  while (continuer) {
    SDL_BlitSurface(reglesImage, NULL, screen, &fullscreen);
    if (choix) SDL_BlitSurface(nextButton, NULL, screen, &fullscreen);
    c.x = event.button.x;
    c.y = event.button.y;

    while(SDL_PollEvent(&event)){


      switch(event.type) {
        case SDL_QUIT:
          continuer = 0;
          return 0;

          break;
        case SDL_MOUSEBUTTONDOWN:
          if (posInclusion(c.x, c.y, posFacileButton)) {
            choix = 1;
          }
          if (posInclusion(c.x, c.y, posMoyenButton)) {
            choix = 2;
          }
          if (posInclusion(c.x, c.y, posDifficileButton)) {
            choix = 3;
          }
          if (posInclusion(c.x, c.y, posDemoniaqueButton)) {
            choix = 4;
          }
          if (posInclusion(c.x, c.y, posNextButton)) {
            continuer = playSudoku(screen);
          }
        }


    }

    if (posInclusion(c.x, c.y, posFacileButton) || (choix == 1)) {
      SDL_BlitSurface(hoverFacile, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posMoyenButton) || (choix == 2)) {
      SDL_BlitSurface(hoverMoyen, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posDifficileButton) || (choix == 3)) {
      SDL_BlitSurface(hoverDifficile, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posDemoniaqueButton) || (choix == 4)) {
      SDL_BlitSurface(hoverDemoniaque, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posNextButton)) {
      SDL_BlitSurface(nextButtonHover, NULL, screen, &fullscreen);
    }

    SDL_Flip(screen);
  }
}

int playSudoku(SDL_Surface* screen) {

  Coord c;
  SDL_Surface* imageDeFond = NULL;
  imageDeFond = IMG_Load("assets/sudoku/grilleVide.jpg");

  SDL_Surface* caseHover = NULL;
  caseHover = IMG_Load("assets/sudoku/numeros/caseHover.png");

  SDL_Surface* nbBlancs[9];
  SDL_Surface* nbVerts[9];
  SDL_Surface* nbRouges[9];

  SDL_Event event;

  int continuer = 1;

  nbBlancs[0] = IMG_Load("assets/sudoku/numeros/base/1.png");
  nbBlancs[1] = IMG_Load("assets/sudoku/numeros/base/2.png");
  nbBlancs[2] = IMG_Load("assets/sudoku/numeros/base/3.png");
  nbBlancs[3] = IMG_Load("assets/sudoku/numeros/base/4.png");
  nbBlancs[4] = IMG_Load("assets/sudoku/numeros/base/5.png");
  nbBlancs[5] = IMG_Load("assets/sudoku/numeros/base/6.png");
  nbBlancs[6] = IMG_Load("assets/sudoku/numeros/base/7.png");
  nbBlancs[7] = IMG_Load("assets/sudoku/numeros/base/8.png");
  nbBlancs[8] = IMG_Load("assets/sudoku/numeros/base/9.png");

  nbVerts[0] = IMG_Load("assets/sudoku/numeros/valide/1.png");
  nbVerts[1] = IMG_Load("assets/sudoku/numeros/valide/2.png");
  nbVerts[2] = IMG_Load("assets/sudoku/numeros/valide/3.png");
  nbVerts[3] = IMG_Load("assets/sudoku/numeros/valide/4.png");
  nbVerts[4] = IMG_Load("assets/sudoku/numeros/valide/5.png");
  nbVerts[5] = IMG_Load("assets/sudoku/numeros/valide/6.png");
  nbVerts[6] = IMG_Load("assets/sudoku/numeros/valide/7.png");
  nbVerts[7] = IMG_Load("assets/sudoku/numeros/valide/8.png");
  nbVerts[8] = IMG_Load("assets/sudoku/numeros/valide/9.png");

  nbRouges[0] = IMG_Load("assets/sudoku/numeros/invalide/1.png");
  nbRouges[1] = IMG_Load("assets/sudoku/numeros/invalide/2.png");
  nbRouges[2] = IMG_Load("assets/sudoku/numeros/invalide/3.png");
  nbRouges[3] = IMG_Load("assets/sudoku/numeros/invalide/4.png");
  nbRouges[4] = IMG_Load("assets/sudoku/numeros/invalide/5.png");
  nbRouges[5] = IMG_Load("assets/sudoku/numeros/invalide/6.png");
  nbRouges[6] = IMG_Load("assets/sudoku/numeros/invalide/7.png");
  nbRouges[7] = IMG_Load("assets/sudoku/numeros/invalide/8.png");
  nbRouges[8] = IMG_Load("assets/sudoku/numeros/invalide/9.png");

  SDL_Rect positionsNumeros[9][9];
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect temp = newRect(0, 0, 0, 0);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      positionsNumeros[i][j] = newRect(372 + (56 + 4)*i, 92 + (56 + 4)*j, 56, 56);
    }
  }

  while (continuer) {
    SDL_WaitEvent(&event);
    c.x = event.button.x;
    c.y = event.button.y;

    SDL_BlitSurface(imageDeFond, NULL, screen, &fullscreen);
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        temp = newPos(positionsNumeros[i][j]);
        if (posInclusion(c.x, c.y, temp)) {
          SDL_BlitSurface(caseHover, NULL, screen, &temp);
        }
      }
    }
    for (int i = 0; i < 9; i++) {
      SDL_BlitSurface(nbBlancs[i], NULL, screen, &positionsNumeros[0][i]);
    }


    switch(event.type) {
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
      }

    SDL_Flip(screen);



  }

  return 1;
}

SDL_Rect newPos (SDL_Rect oldPos) {
  return newRect(oldPos.x - 4, oldPos.y - 4, 64, 64);
}
