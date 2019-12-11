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

void afficherTableauScore(SDL_Surface* screen, char jeu) {
  // Variables
  int continuer = 1;
  SDL_Event event;
  Coord c;
  tabP p;
  tabP trie;
  char next = 'z';
  chargementProfils(p);

  // Images
  SDL_Surface* batailleNavale = NULL;
  SDL_Surface* poker = NULL;
  SDL_Surface* loto = NULL;
  SDL_Surface* sudoku = NULL;
  SDL_Surface* all = NULL;
  SDL_Surface* ecran = NULL;
  SDL_Surface* menuHover = NULL;
  SDL_Surface* backHover = NULL;
  SDL_Surface* nextHover = NULL;
  SDL_Surface* surfaceNom[10];
  SDL_Surface* aymericMeilleurQueToi = NULL;

  batailleNavale = IMG_Load("assets/menu/batailleNavale.png");
  poker = IMG_Load("assets/menu/poker.png");
  loto = IMG_Load("assets/menu/loto.png");
  sudoku = IMG_Load("assets/menu/sudoku.png");
  all = IMG_Load("assets/menu/all.png");
  ecran = IMG_Load("assets/menu/scores.jpg");
  menuHover = IMG_Load("assets/menu/menuHover.png");
  backHover = IMG_Load("assets/menu/backHover.png");
  nextHover = IMG_Load("assets/menu/nextHover.png");
  aymericMeilleurQueToi = IMG_Load("assets/menu/aymericMeilleurQueToi.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect backPosition = newRect(14, 532, 188, 206);
  SDL_Rect nextPosition = newRect(1035, 510, 210, 245);
  SDL_Rect menuPosition = newRect(0, 0, 157, 293);
  SDL_Rect posJeu = newRect(412, 12, 130, 468);
  SDL_Rect positionNom[10];
  for (int i = 0; i < 10; i++) {
    positionNom[i] = newRect(550, 250 + 40 * i, 0, 0);
  }
  SDL_Rect posAymeric = newRect(450, 150, 100, 275);

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
        triProfils(p, trie, 'b');
        // Affichage scores
        for (int i = 0; i < 10; i++) {
          if (trie[i].scoreTotal >= 0) {
            sprintf(buffer, "%d - %s", (int)trie[i].scoreNavale, trie[i].nom);
            surfaceNom[i] = TTF_RenderText_Solid(font, buffer, blanc);

            SDL_BlitSurface(surfaceNom[i], NULL, screen, &positionNom[i]);
          }
        }

        break;
      case 'l':
        // Loto
        SDL_BlitSurface(loto, NULL, screen, &posJeu);
        triProfils(p, trie, 'l');
        // Affichage scores
        for (int i = 0; i < 10; i++) {
          if (trie[i].scoreTotal >= 0) {
            sprintf(buffer, "%d - %s", (int)trie[i].scoreLoto, trie[i].nom);
            surfaceNom[i] = TTF_RenderText_Solid(font, buffer, blanc);

            SDL_BlitSurface(surfaceNom[i], NULL, screen, &positionNom[i]);
          }
        }

        break;
      case 'p':
        // Poker
        SDL_BlitSurface(poker, NULL, screen, &posJeu);
        triProfils(p, trie, 'p');
        // Affichage scores
        for (int i = 0; i < 10; i++) {
          if (trie[i].scoreTotal >= 0) {
            sprintf(buffer, "%d - %s", (int)trie[i].scorePoker, trie[i].nom);
            surfaceNom[i] = TTF_RenderText_Solid(font, buffer, blanc);

            SDL_BlitSurface(surfaceNom[i], NULL, screen, &positionNom[i]);
          }
        }

        break;
      case 's':
        // Sudoku
        SDL_BlitSurface(sudoku, NULL, screen, &posJeu);
        triProfils(p, trie, 's');
        // Affichage scores
        for (int i = 0; i < 10; i++) {
          if (trie[i].scoreTotal >= 0) {
            sprintf(buffer, "%d - %s", (int)trie[i].scoreSudoku, trie[i].nom);
            surfaceNom[i] = TTF_RenderText_Solid(font, buffer, blanc);

            SDL_BlitSurface(surfaceNom[i], NULL, screen, &positionNom[i]);
          }
        }

        break;
        case 'a':
          // All
          SDL_BlitSurface(all, NULL, screen, &posJeu);
          SDL_BlitSurface(aymericMeilleurQueToi, NULL, screen, &posAymeric);
          triProfils(p, trie, 'a');
          // Affichage scores
          for (int i = 0; i < 10; i++) {
            if (trie[i].scoreTotal >= 0) {
              sprintf(buffer, "%d - %s", (int)trie[i].scoreTotal, trie[i].nom);
              surfaceNom[i] = TTF_RenderText_Solid(font, buffer, blanc);

              SDL_BlitSurface(surfaceNom[i], NULL, screen, &positionNom[i]);
            }
          }

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
          continuer = 0;
          if (jeu == 'b') next = 's';
          else if (jeu == 's') next = 'p';
          else if (jeu == 'p') next = 'l';
          else if (jeu == 'l') next = 'a';
          else if (jeu == 'a') next = 'b';
        }
        if (posInclusion(c.x, c.y, backPosition)) {
          continuer = 0;
          if (jeu == 'b') next = 'a';
          else if (jeu == 'a') next = 'l';
          else if (jeu == 'l') next = 'p';
          else if (jeu == 'p') next = 's';
          else if (jeu == 's') next = 'b';
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
  // Free
  SDL_FreeSurface(batailleNavale);
  SDL_FreeSurface(poker);
  SDL_FreeSurface(loto);
  SDL_FreeSurface(sudoku);
  SDL_FreeSurface(ecran);
  SDL_FreeSurface(menuHover);
  SDL_FreeSurface(nextHover);
  SDL_FreeSurface(backHover);
  SDL_FreeSurface(aymericMeilleurQueToi);

  if (next != 'z') afficherTableauScore(screen, next);
}

void triProfils(tabP p, tabP newP, char jeu) {
  int scores[10];
  int nbProfils = 0;
  for (int i = 0; i < 10; i++) {
    if (p[i].scoreTotal != -1) nbProfils++;
  }
  // Tri des scores
  switch (jeu) {
    case 'b':
      for (int i = 0; i < 10; i++) {
        scores[i] = p[i].scoreNavale;
      }
      break;
    case 's':
      for (int i = 0; i < 10; i++) {
        scores[i] = p[i].scoreSudoku;
      }
      break;
    case 'l':
      for (int i = 0; i < 10; i++) {
        scores[i] = p[i].scoreLoto;
      }
      break;
    case 'p':
      for (int i = 0; i < 10; i++) {
        scores[i] = p[i].scorePoker;
      }
      break;
    case 'a':
      for (int i = 0; i < 10; i++) {
        scores[i] = p[i].scoreTotal;
      }
      break;
    default:
      break;
  }
  // Tri
  tri_selection(scores, nbProfils);
  reverseTab(scores);
  printTab(scores);

  // Reattribution
  int dejaMis[10];
  switch (jeu) {
    case 'b':
      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
          if (p[j].scoreNavale == scores[i]) {
            if (nbOccurences(dejaMis, j) == 0) {
              newP[i] = p[j];
              dejaMis[i] = j;
            }
          }
        }
      }
      break;
    case 's':
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (p[j].scoreSudoku == scores[i]) {
          if (nbOccurences(dejaMis, j) == 0) {
            newP[i] = p[j];
            dejaMis[i] = j;
          }
        }
      }
    }
      break;
    case 'l':
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (p[j].scoreLoto == scores[i]) {
          if (nbOccurences(dejaMis, j) == 0) {
            newP[i] = p[j];
            dejaMis[i] = j;
          }
        }
      }
    }
      break;
    case 'p':
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (p[j].scorePoker == scores[i]) {
          if (nbOccurences(dejaMis, j) == 0) {
            newP[i] = p[j];
            dejaMis[i] = j;
          }
        }
      }
    }
      break;
    case 'a':
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (p[j].scoreTotal == scores[i]) {
          if (nbOccurences(dejaMis, j) == 0) {
            newP[i] = p[j];
            dejaMis[i] = j;
          }
        }
      }
    }
      break;
    default:
      break;
  }



}

void tri_selection(int *tableau, int taille)
{
     int en_cours, plus_petit, j, temp;

     for (en_cours = 0; en_cours < taille - 1; en_cours++)
     {
         plus_petit = en_cours;
         for (j = en_cours; j < taille; j++)
              if (tableau[j] < tableau[plus_petit])
                  plus_petit = j;
          temp = tableau[en_cours];
          tableau[en_cours] = tableau[plus_petit];
          tableau[plus_petit] = temp;
     }
}

int nbOccurences(int t[], int n) {
  int nb = 0;
  for (int i = 0; i < 10; i++) {
    if (t[i] == n) nb++;
  }
  return nb;
}

void printTab(int t[]) {
  for (int i = 0; i < 10; i++) {
    printf("%d ", t[i]);
  }
  printf("\n");
}

void reverseTab(int t[]) {
  int newT[10];
  for (int i = 0; i < 10; i++) {
    newT[i] = t[9-i];
  }
  for (int i = 0; i < 10; i++) {
    t[i] = newT[i];
  }
}

void betterTab(int t[], int taille) {
  int temp[10];
  int index = 0;
  for (int i = 0; i < 10; i++) {
    if (t[i] != -1) {
      temp[index] = t[i];
      index++;
    }
  }

  for (int i = 0; i < 10; i++) {
    if (i < taille) {
      t[i] = temp[i];
    }
    else {
      t[i] = -1;
    }
  }

}
