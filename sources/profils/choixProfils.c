#include <SDL/SDL_image.h>
#include <string.h>
#include "../../headers/global/structure.h"
#include "../../headers/global/shortcuts.h"
#include "../../headers/profils/chargement.h"
#include "../../headers/profils/sauvegarde.h"
#include "../../headers/profils/initTabProfils.h"
#include "../../headers/global/interface.h"
#include "../../headers/global/constantes.h"
#include "../../headers/profils/choixProfils.h"

void afficherProfils(SDL_Surface *screen)
{
  tabP profils;
  iniTabP(profils);
  chargementProfils(profils);

  Coord c;

  SDL_Surface *ecranProfils = NULL;
  SDL_Surface *profilGris = NULL;

  Profil p;

  ecranProfils = IMG_Load("assets/profils/ecranProfils.jpg");
  profilGris = IMG_Load("assets/profils/profilGris.png");

  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect positionsFrameProfils[5][2];
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      positionsFrameProfils[i][j] = newRect(0 + 256 * i, 186 + 260 * j, 256, 256);
    }
  }

  char texteJoueur[10];
  SDL_Surface* nomsJoueur[10];



  int continuer = 1;
  SDL_Event event;

  // Couleurs
  SDL_Color noir = {0, 0, 0, 0};

  // Font
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_SKRIBBLE, 20);


  while (continuer)
  {
    SDL_BlitSurface(ecranProfils, NULL, screen, &fullscreen);

    for (int i = 0; i < 10; i++) {
      if (profils[i].scoreTotal != -1) {
        sprintf(texteJoueur, "%s", profils[i].nom);
        nomsJoueur[i] = creerTexte(screen, texteJoueur, noir, font);
        SDL_Rect temp = posNoms(positionsFrameProfils[i%5][i/5]);
        SDL_BlitSurface(nomsJoueur[i], NULL, screen, &temp);



      } else {
        SDL_BlitSurface(profilGris, NULL, screen, &positionsFrameProfils[i%5][i/5]);
      }
    }


    while (SDL_PollEvent(&event))
    {
      c.x = event.button.x;
      c.y = event.button.y;

      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;
        sauvegardeProfils(profils);
        break;
      case SDL_MOUSEBUTTONDOWN:

        for (int i = 0; i < 10; i++) {
          if (posInclusion(c.x, c.y, positionsFrameProfils[i%5][i/5])) {
            profils[i] = nouveauProfil(screen, i, profils[i]);
          }
        }

        break;

      }

    }
    SDL_Flip(screen);
  }
  SDL_FreeSurface(ecranProfils);
  SDL_FreeSurface(profilGris);
}

Profil nouveauProfil(SDL_Surface* screen, int nbProfil, Profil oldProfil) {
  Profil p;
    p.nom[0] = oldProfil.nom[0];
    p.nom[1] = oldProfil.nom[1];
    p.nom[2] = oldProfil.nom[2];
    p.nom[3] = oldProfil.nom[3];
    p.nom[4] = oldProfil.nom[4];
    p.nom[5] = oldProfil.nom[5];
    p.nom[6] = oldProfil.nom[6];
    p.nom[7] = '\0';
    p.ID = nbProfil;
    if (oldProfil.scoreTotal != -1) {
      p.scoreNavale = oldProfil.scoreNavale;
      p.scorePoker = oldProfil.scorePoker;
      p.scoreLoto = oldProfil.scoreLoto;
      p.scoreSudoku = oldProfil.scoreSudoku;
      p.scoreTotal = oldProfil.scoreTotal;

    } else {
      p.scoreNavale = 0;
      p.scorePoker = 0;
      p.scoreLoto = 0;
      p.scoreSudoku = 0;
      p.scoreTotal = 0;
    }

  Profil vide;
  strcpy(vide.nom, "AAAAAAA");
  vide.ID = 0;
  vide.scoreNavale = -1;
  vide.scorePoker = -1;
  vide.scoreLoto = -1;
  vide.scoreSudoku = -1;
  vide.scoreTotal = -1;



  // Variables
  int continuer;
  SDL_Event event;
  Coord c;

  // Images
  SDL_Surface* ecran = NULL;
  SDL_Surface* flecheUp = NULL;
  SDL_Surface* flecheDown = NULL;
  SDL_Surface* flecheUpHover = NULL;
  SDL_Surface* flecheDownHover = NULL;
  SDL_Surface* trashHover = NULL;
  SDL_Surface* annulerHover = NULL;
  SDL_Surface* confirmerHover = NULL;

  ecran = IMG_Load("assets/profils/nouveauProfils.jpg");
  flecheUp = IMG_Load("assets/profils/flecheUp.png");
  flecheDown = IMG_Load("assets/profils/flecheDown.png");
  flecheUpHover = IMG_Load("assets/profils/flecheUpHover.png");
  flecheDownHover = IMG_Load("assets/profils/flecheDownHover.png");
  trashHover = IMG_Load("assets/profils/trashHover.png");
  annulerHover = IMG_Load("assets/profils/retourHover.png");
  confirmerHover = IMG_Load("assets/profils/confirmerHover.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posLettres[7];
  SDL_Rect posFleches[7][2];
  SDL_Rect posZoneLettre[7]; // Zone ou on peux afficher les fleches
  for (int i = 0; i < 7; i++) {
    posLettres[i] = newRect(50 + (37 + 140) * i, 410, 150, 150);
    posZoneLettre[i] = newRect(37 + (37 + 140) * i, 200, 450, 150);
    for (int j = 0; j < 2; j++) {
      posFleches[i][j] = newRect(37 + (37 + 140) * i, 250 + j * 250, 150, 150);
    }
  }
  SDL_Rect posTrash = newRect(617, 637, 83, 77);
  SDL_Rect posAnnuler = newRect(0, 619, 101, 229);
  SDL_Rect posConfirmer = newRect(987, 620, 100, 293);


  // Couleurs
  SDL_Color noir = {0, 0, 0, 0};

  // Font
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_SKRIBBLE, 60);

  // Lettres
  SDL_Surface* lettreSurface[7];


  char temp[10];
  while(continuer) {
    // Coords de la souris
    c.x = event.button.x;
    c.y = event.button.y;
    // Ecran de fond
    SDL_BlitSurface(ecran, NULL, screen, &fullscreen);

    for (int i = 0; i < 7; i++) {
      if (posInclusion(c.x, c.y, posZoneLettre[i])) {
        SDL_BlitSurface(flecheUp, NULL, screen, &posFleches[i][0]);
        SDL_BlitSurface(flecheDown, NULL, screen, &posFleches[i][1]);
      }
    }
    // Affichage des lettres
    for (int i = 0; i < 7; i++) {
      sprintf(temp, "%c", p.nom[i]);
      lettreSurface[i] = TTF_RenderText_Solid(font,temp, noir);
      //lettreSurface[i] = creerTexte(screen, toString(p.nom[i]), noir, font);
      SDL_BlitSurface(lettreSurface[i], NULL, screen, &posLettres[i]);
    }



    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        // On quitte
      case SDL_QUIT:
        continuer = 0;
        break;
        // On clique
      case SDL_MOUSEBUTTONDOWN:
        // Fleches
        for (int i = 0; i < 7; i++) {
          if (posInclusion(c.x, c.y, posFleches[i][0])) {
            p.nom[i] = updateChar(p.nom[i], 'i');
          }
          if (posInclusion(c.x, c.y, posFleches[i][1])) {
            p.nom[i] = updateChar(p.nom[i], 'd');
          }
          if (posInclusion(c.x, c.y, posLettres[i])) {
            p.nom[i] = ' ';
          }
        }
        // On confirme
        if (posInclusion(c.x, c.y, posConfirmer)) {
          continuer = 0;
          break;
        }
        if (posInclusion(c.x, c.y, posTrash)) {
          p = vide;
          continuer = 0;
          break;
        }
        if (posInclusion(c.x, c.y, posAnnuler)) {
          p = oldProfil;
          continuer = 0;
          break;
        }

      }
    }

    // Hover fleches
    for (int i = 0; i < 7; i++) {
      if (posInclusion(c.x, c.y, posFleches[i][0])) {
        SDL_BlitSurface(flecheUpHover, NULL, screen, &posFleches[i][0]);
      }
      if (posInclusion(c.x, c.y, posFleches[i][1])) {
        SDL_BlitSurface(flecheDownHover, NULL, screen, &posFleches[i][1]);
      }
    }
    // Hover boutons
    if (posInclusion(c.x, c.y, posTrash)) {
      SDL_BlitSurface(trashHover, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posAnnuler)) {
      SDL_BlitSurface(annulerHover, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posConfirmer)) {
      SDL_BlitSurface(confirmerHover, NULL, screen, &fullscreen);
    }

    SDL_Flip(screen);

  }

  SDL_FreeSurface(flecheUp);
  SDL_FreeSurface(flecheDown);
  SDL_FreeSurface(flecheUpHover);
  SDL_FreeSurface(flecheDownHover);
  SDL_FreeSurface(trashHover);
  SDL_FreeSurface(annulerHover);
  SDL_FreeSurface(confirmerHover);
  SDL_FreeSurface(ecran);
  for (int i = 0; i < 7; i++) {
    SDL_FreeSurface(lettreSurface[i]);
  }


  return p;

}

char* toString(char c) {
  char* string;
  string = (char*) malloc(15);
  string[0] = c;
  return string;
}

char updateChar(char c, char t) {
  if (t == 'i') {
    if (c == ' ') return 'A';
    if (c == 'A') return 'B';
    if (c == 'B') return 'C';
    if (c == 'C') return 'D';
    if (c == 'D') return 'E';
    if (c == 'E') return 'F';
    if (c == 'F') return 'G';
    if (c == 'G') return 'H';
    if (c == 'H') return 'I';
    if (c == 'I') return 'J';
    if (c == 'J') return 'K';
    if (c == 'K') return 'L';
    if (c == 'L') return 'M';
    if (c == 'M') return 'N';
    if (c == 'N') return 'O';
    if (c == 'O') return 'P';
    if (c == 'P') return 'Q';
    if (c == 'Q') return 'R';
    if (c == 'R') return 'S';
    if (c == 'S') return 'T';
    if (c == 'T') return 'U';
    if (c == 'U') return 'V';
    if (c == 'V') return 'W';
    if (c == 'W') return 'X';
    if (c == 'X') return 'Y';
    if (c == 'Y') return 'Z';
    if (c == 'Z') return 'A';
  }
  if (t == 'd') {
    if (c == ' ') return 'Z';
    if (c == 'A') return 'Z';
    if (c == 'B') return 'A';
    if (c == 'C') return 'B';
    if (c == 'D') return 'C';
    if (c == 'E') return 'D';
    if (c == 'F') return 'E';
    if (c == 'G') return 'F';
    if (c == 'H') return 'G';
    if (c == 'I') return 'H';
    if (c == 'J') return 'I';
    if (c == 'K') return 'J';
    if (c == 'L') return 'K';
    if (c == 'M') return 'L';
    if (c == 'N') return 'M';
    if (c == 'O') return 'N';
    if (c == 'P') return 'O';
    if (c == 'Q') return 'P';
    if (c == 'R') return 'Q';
    if (c == 'S') return 'R';
    if (c == 'T') return 'S';
    if (c == 'U') return 'T';
    if (c == 'V') return 'U';
    if (c == 'W') return 'V';
    if (c == 'X') return 'W';
    if (c == 'Y') return 'X';
    if (c == 'Z') return 'Y';
  }
}

SDL_Rect posNoms(SDL_Rect r) {
  return newRect(r.x + 30, r.y + 30, r.h, r.w);
}

int selectionProfil(SDL_Surface* screen, int nbProfils, tabJP profils) {
  tabP p;
  chargementProfils(p);
  SDL_Event event;
  int continuer = 1;
  int trueContinue = 1;
  int cbChecked[10] = {0};
  int temp = 0;
  Coord c;
  int weCanContinue = 0;
  int whichOnes[10] = {-1};

  tabJP tableauProfils;

  int profilsTotaux = 0;
  for (int i = 0; i < 10; i++) {
    if (p[i].scoreTotal != -1) profilsTotaux++;
  }

  // Images
  SDL_Surface* imageFond = NULL;
  SDL_Surface* checkboxEmpty = NULL;
  SDL_Surface* checkboxFilled = NULL;
  SDL_Surface* noms[10];
  SDL_Surface* barre = NULL;
  SDL_Surface* attendus = NULL;
  SDL_Surface* confirmerHover = NULL;
  SDL_Surface* retourHover = NULL;

  imageFond = IMG_Load("assets/profils/choixProfilsRaw.jpg");
  checkboxEmpty = IMG_Load("assets/profils/checkboxEmpty.png");
  checkboxFilled = IMG_Load("assets/profils/checkboxFilled.png");
  barre = IMG_Load("assets/profils/confirmerBarre.png");
  confirmerHover = IMG_Load("assets/profils/confirmerHover.png");
  retourHover = IMG_Load("assets/profils/retourHover.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect positionsCheckbox[10];
  SDL_Rect positionsNoms[10];
  for (int i = 0; i < 10; i++) {
    positionsCheckbox[i] = newRect(50 + (i/5)* 600, 200 + (i%5) * 70, 120, 120);
    positionsNoms[i] = newRect(200 + (i/5)* 600, 200 + (i%5) * 70, 120, 120);
  }
  SDL_Rect positionAttendue = newRect(50, 50, 0, 0);
  SDL_Rect posAnnuler = newRect(0, 619, 101, 229);
  SDL_Rect posConfirmer = newRect(987, 620, 100, 293);

  // Textes
  char buffer[20];
  char buffer2[50];

  // Couleurs
  SDL_Color noir = {0, 0, 0, 0};

  // Font
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_SKRIBBLE, 25);
  TTF_Font *font2 = NULL;
  font2 = TTF_OpenFont(FONT_SKRIBBLE, 20);

  while(continuer == 1) {
    // Affichage du fond
    SDL_BlitSurface(imageFond, NULL, screen, &fullscreen);
    // Affichage des checkbox
    for (int i = 0; i < profilsTotaux; i++) {
      if (cbChecked[i] == 0) SDL_BlitSurface(checkboxEmpty, NULL, screen, &positionsCheckbox[i]);
      if (cbChecked[i] == 1) SDL_BlitSurface(checkboxFilled, NULL, screen, &positionsCheckbox[i]);
    }
    // Affichage des noms
    for (int i = 0; i < 10; i++) {
      if (temp < profilsTotaux) {
        if (p[i].scoreTotal != -1) {
          noms[temp] = creerTexte(screen, p[i].nom, noir, font);
          temp++;
        }
      }
    }
    for (int i = 0; i < profilsTotaux; i++) {
      SDL_BlitSurface(noms[i], NULL, screen, &positionsNoms[i]);
    }
    // Compter nb Checked
    int n = 0;
    for (int i = 0; i < 10; i++) {
      whichOnes[i] = -1;
    }
    int nombresValeursChecked = 0;
    for (int i = 0; i < 10; i++) {
      if (cbChecked[i] == 1) {
        nombresValeursChecked++;
        whichOnes[n] = i;
        n++;
      }

    }
    // Recuperation des vrais id
    int vraisID[10];



    // Confirmer barre ?
    if (nombresValeursChecked != nbProfils) {
      SDL_BlitSurface(barre, NULL, screen, &fullscreen);
      weCanContinue = 0;
    } else weCanContinue = 1;

    // Afficher nombre de joueurs attendus
    sprintf(buffer2, "Joueurs requis : %d", nbProfils);
    attendus = creerTexte(screen, buffer2, noir, font2);
    SDL_BlitSurface(attendus, NULL, screen, &positionAttendue);

    // Boucle principale
    while (SDL_PollEvent(&event))
    {
      c.x = event.button.x;
      c.y = event.button.y;

      switch (event.type)
      {
        // On quitte
      case SDL_QUIT:
        continuer = 0;
        trueContinue = 0;
        break;

      // On clique
      case SDL_MOUSEBUTTONDOWN:
        for (int i = 0; i < profilsTotaux; i++) {
          if (posInclusion(c.x, c.y, positionsCheckbox[i])) {
            cbChecked[i] = (cbChecked[i]+1)%2;
          }
        }
        if (posInclusion(c.x, c.y, posConfirmer) && (weCanContinue)) {
          continuer = 0;
          trueContinue = 1;
          int n = 0;
          for (int i = 0; i < 11; i++) {
            if (p[i].scoreTotal != -1) {
              if (p[i].ID == whichOnes[n]) {
                strcpy(profils[n].nom, p[i].nom);
                profils[n].ID = p[i].ID;
                profils[n].scoreNavale = p[i].scoreNavale;
                profils[n].scorePoker = p[i].scorePoker;
                profils[n].scoreLoto = p[i].scoreLoto;
                profils[n].scoreSudoku = p[i].scoreSudoku;
                profils[n].scoreTotal = p[i].scoreTotal;
                n++;
              }
            }
          }
        }
      }
    }
    // Hovers boutons
    if (posInclusion(c.x, c.y, posConfirmer) && (weCanContinue)) {
      SDL_BlitSurface(confirmerHover, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posAnnuler)) {
      SDL_BlitSurface(retourHover, NULL, screen, &fullscreen);
    }
    SDL_Flip(screen);
  }
  SDL_FreeSurface(imageFond);
  SDL_FreeSurface(checkboxEmpty);
  SDL_FreeSurface(checkboxFilled);
  SDL_FreeSurface(barre);
  SDL_FreeSurface(attendus);
  SDL_FreeSurface(confirmerHover);
  SDL_FreeSurface(retourHover);
  temp=0;
  for (int i = 0; i < 10; i++) {
    if (temp < profilsTotaux) {
      if (p[i].scoreTotal != -1) {
        SDL_FreeSurface(noms[temp]);
        temp++;
      }
    }
  }
  return trueContinue;
}

int iemeProfil(int i) {
  tabP profils;
  int step = 0;
  chargementProfils(profils);
  for (int a = 0; a < 10; a++) {
    if (profils[a].scoreTotal != -1) {
      step++;
    }
    if (step == i) {
      return a;
    }
  }
  return -1;
}
