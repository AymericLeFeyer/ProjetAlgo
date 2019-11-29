#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/shortcuts.h"
#include "../headers/structure.h"
#include "../headers/affichageSudoku.h"
#include "../headers/initGrilleSud.h"
#include "../headers/detection.h"
#include "../headers/constantes.h"
#include "../headers/interface.h"

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
  SDL_Surface* menuBouton = NULL;
  SDL_Surface* menuBoutonHover = NULL;


  reglesImage = IMG_Load("assets/sudoku/difficulteSudoku.jpg");
  hoverFacile = IMG_Load("assets/sudoku/facileButton.png");
  hoverMoyen = IMG_Load("assets/sudoku/moyenButton.png");
  hoverDifficile = IMG_Load("assets/sudoku/difficileButton.png");
  hoverDemoniaque = IMG_Load("assets/sudoku/demoniaqueButton.png");
  nextButton = IMG_Load("assets/sudoku/nextButton.png");
  nextButtonHover = IMG_Load("assets/sudoku/nextButtonHover.png");
  menuBouton = IMG_Load("assets/sudoku/menuBouton.png");
  menuBoutonHover = IMG_Load("assets/sudoku/menuBoutonHover.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posFacileButton = newRect(80, 489, 76, 339);
  SDL_Rect posMoyenButton = newRect(775, 489, 76, 324);
  SDL_Rect posDifficileButton = newRect(51, 593, 68, 435);
  SDL_Rect posDemoniaqueButton = newRect(642, 595, 68, 590);
  SDL_Rect posNextButton = newRect(479, 278, 99, 278);
  SDL_Rect posMenuBouton = newRect(25, 25, 200, 200);

  // Boucle principale
  while (continuer) {
    SDL_BlitSurface(reglesImage, NULL, screen, &fullscreen);
    SDL_BlitSurface(menuBouton, NULL, screen, &posMenuBouton);
    if (choix) SDL_BlitSurface(nextButton, NULL, screen, &fullscreen);
    c.x = event.button.x;
    c.y = event.button.y;

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
    if (posInclusion(c.x, c.y, posNextButton) && (choix)) {
      SDL_BlitSurface(nextButtonHover, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posMenuBouton)) {
      SDL_BlitSurface(menuBoutonHover, NULL, screen, &posMenuBouton);
    }

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
          if (posInclusion(c.x, c.y, posNextButton) && choix) {
            continuer = playSudoku(screen, choix-1, time(NULL));
            if (continuer == 0) {
              return 0;
            }
            if (continuer == 2) {
              return 2;
            }
          }
          if (posInclusion(c.x, c.y, posMenuBouton)) {
            continuer = 0;
            return 2;
          }
        }


    }



    SDL_Flip(screen);
  }
}

int playSudoku(SDL_Surface* screen, int difficulte, time_t temps) {

  SDL_Surface* ecranVictoire = NULL;
  ecranVictoire = IMG_Load("assets/sudoku/fin.png");


  JoueurSudoku J;

  Coord c;
  SDL_Surface* imageDeFond = NULL;
  imageDeFond = IMG_Load("assets/sudoku/grilleVide.jpg");

  SDL_Surface* caseHover = NULL;
  caseHover = IMG_Load("assets/sudoku/numeros/caseHover.png");

  SDL_Surface* menuBouton = NULL;
  SDL_Surface* menuBoutonHover = NULL;
  SDL_Rect posMenuBouton = newRect(25, 25, 200, 200);

  SDL_Color blanc = {255, 255, 255};
  SDL_Color orange = {255, 136, 0};
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  TTF_Font *font2 = NULL;
  font2 = TTF_OpenFont(FONT_UBUNTU, 50);

  SDL_Rect zoneTextNiveau = newRect(580, 50, 0, 0);

  menuBouton = IMG_Load("assets/sudoku/menuBouton.png");
  menuBoutonHover = IMG_Load("assets/sudoku/menuBoutonHover.png");

  SDL_Surface* nbBlancs[9];
  SDL_Surface* nbVerts[9];
  SDL_Surface* nbRouges[9];

  SDL_Surface* niveauAffichage = NULL;
  char textNiveauAffichage[50];



  SDL_Surface* newNumArea = NULL;
  newNumArea = IMG_Load("assets/sudoku/newNumber.png");

  char a;
  int b;
  char d;
  Coord onClicked;
  int newNum = 0;

  int nouveau = 0;

  // il faut random le numero dans la fonction, selon la difficulte
  int niveau = 0;
  switch (difficulte) {
    case 0:
      niveau = intAlea(4);
      break;
    case 1:
      niveau = 4 + intAlea(4);
      break;
    case 2:
      niveau = 8 + intAlea(4);
      break;
    case 3:
      niveau = 12 + intAlea(2);
      break;
    default:
      break;
  }

  sprintf(textNiveauAffichage, "Grille %d", niveau + 1 );
  niveauAffichage = creerTexte(screen, textNiveauAffichage, blanc, font);

  grilleSudokuBrute g = initGrilleSudoku(niveau);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      a = g.gsb[i*9 + j];
      J.i.tab[j][i] = atoi(&a);
      J.g.tab[j][i] = atoi(&a);
      a = g.gss[i*9 + j];
      J.s.tab[j][i] = atoi(&a);
    }
  }

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
  SDL_Rect positionsNewNumberArea[3][3];
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect temp = newRect(0, 0, 0, 0);
  SDL_Rect temp2 = newRect(0, 0, 0, 0);

  SDL_Surface* timerSurface = NULL;
  SDL_Rect timerPos = newRect(1100, 50, 0, 0);
  char timerText[20];

  Coord cTab;

  int c_fini = 0;
  int current_time = 0;



  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      positionsNumeros[i][j] = newRect(372 + (56 + 4)*i, 92 + (56 + 4)*j, 56, 56);
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      positionsNewNumberArea[i][j] = newRect(1000 + (56 + 4)*i, 272 + (56 + 4)*j, 56, 56);
    }
  }

  while (continuer) {
    if (!c_fini) current_time = time(NULL) - temps;
    sprintf(timerText, "%ld", current_time);
    timerSurface = creerTexte(screen, timerText, orange, font2);

    SDL_PollEvent(&event);
    c.x = event.button.x;
    c.y = event.button.y;

    SDL_BlitSurface(imageDeFond, NULL, screen, &fullscreen);
    SDL_BlitSurface(menuBouton, NULL, screen, &posMenuBouton);
    SDL_BlitSurface(niveauAffichage, NULL, screen , &zoneTextNiveau);
    SDL_BlitSurface(timerSurface, NULL, screen, &timerPos);

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        temp = newPos(positionsNumeros[i][j]);
        temp.w = 60;
        temp.h = 60;
        if (posInclusion(c.x, c.y, temp)) {
          SDL_BlitSurface(caseHover, NULL, screen, &temp);
        }
      }
    }

    // Affichage des chiffres

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (verification(J))
        {
          if (J.i.tab[i][j]) {
            SDL_BlitSurface(nbBlancs[J.i.tab[i][j]-1], NULL, screen, &positionsNumeros[i][j]);
          }
          else if (J.g.tab[i][j]) {
            cTab.x = i;
            cTab.y = j;
            if (detection(cTab, J)) {
              SDL_BlitSurface(nbVerts[J.g.tab[i][j]-1], NULL, screen, &positionsNumeros[i][j]);
            }
            else SDL_BlitSurface(nbRouges[J.g.tab[i][j]-1], NULL, screen, &positionsNumeros[i][j]);
          }
        }
        else {
          c_fini = 1;
          SDL_BlitSurface(nbBlancs[J.g.tab[i][j]-1], NULL, screen, &positionsNumeros[i][j]);
        }
      }
    }




    if (newNum) {
      SDL_BlitSurface(newNumArea, NULL, screen, &fullscreen);
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (posInclusion(c.x, c.y, positionsNewNumberArea[i][j])) {
            temp = newPos(positionsNewNumberArea[i][j]);
            SDL_BlitSurface(caseHover, NULL, screen, &temp);
          }
        }
      }
      temp2 = newPos(positionsNumeros[onClicked.x][onClicked.y]);
      if (!c_fini) SDL_BlitSurface(caseHover, NULL, screen, &temp2);



    }

    switch(event.type) {
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
      case SDL_KEYDOWN:
        c_fini = 1;
        break;

      case SDL_MOUSEBUTTONDOWN:
        if (posInclusion(c.x, c.y, posMenuBouton)) {
          continuer = 0;
          return 2;
        }
        if (!c_fini) {
          for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
              if (posInclusion(c.x, c.y, positionsNumeros[i][j])) {
                if (J.i.tab[i][j] == 0) {
                  onClicked.x = i;
                  onClicked.y = j;
                  newNum = 1;
                }


              }
              if (newNum) {
                for (int i = 0; i < 3; i++) {
                  for (int j = 0; j < 3; j++) {
                    if (posInclusion(c.x, c.y, positionsNewNumberArea[i][j])) {
                      nouveau = (i+j*3) + 1;
                      J.g.tab[onClicked.x][onClicked.y] = nouveau;
                      newNum = 0;
                    }
                  }
                }
              }


            }
          }

        }

    }
    if (posInclusion(c.x, c.y, posMenuBouton)) {
      SDL_BlitSurface(menuBoutonHover, NULL, screen, &posMenuBouton);
    }

    if (c_fini) SDL_BlitSurface(ecranVictoire, NULL, screen, &fullscreen);
    SDL_Flip(screen);

  }

  return 1;
}

SDL_Rect newPos (SDL_Rect oldPos) {
  return newRect(oldPos.x - 4, oldPos.y - 4, 64, 64);
}
