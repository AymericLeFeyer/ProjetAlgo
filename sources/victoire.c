#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/structure.h"
#include "../headers/shortcuts.h"
#include "../headers/victoire.h"
#include "../headers/constantes.h"
#include "../headers/interface.h"
#include "../headers/mainsPoker.h"

int victoire(JoueurBatailleNavale j){
  int i;int victoire=1;
  while(i<=4 && victoire==1){
    if(j.tab[i].pv>0){
      victoire=0;
    }else{
      i++;
    }
  }
  return victoire;
}

int victoirePokerManche(SDL_Surface* screen, JoueurPoker*t, CentrePlateau* cp, JoueurPoker k, int nbJoueurs) {
  int continuer = 1;
  SDL_Event event;
  // Images
  SDL_Surface* ecranVictoire = NULL;
  SDL_Surface* winJ1 = NULL;
  SDL_Surface* winJ2 = NULL;
  SDL_Surface* winJ3 = NULL;
  SDL_Surface* winJ4 = NULL;
  SDL_Surface* winJ5 = NULL;
  SDL_Surface* nextSelection = NULL;

  ecranVictoire = IMG_Load("assets/poker/victoire/ecranVictoire.jpg");
  winJ1 = IMG_Load("assets/poker/victoire/winJ1.png");
  winJ2 = IMG_Load("assets/poker/victoire/winJ2.png");
  winJ3 = IMG_Load("assets/poker/victoire/winJ3.png");
  winJ4 = IMG_Load("assets/poker/victoire/winJ4.png");
  winJ5 = IMG_Load("assets/poker/victoire/winJ5.png");
  nextSelection = IMG_Load("assets/poker/regles/nextSelection.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posZoneMenu = newRect(25, 25, 125, 150);
  SDL_Rect posNextMenu = newRect(1110, 25, 125, 150);
  SDL_Rect posDetailsMenu = newRect(1110, 175, 125, 150);

  SDL_Rect posCarte1 = newRect(152, 400, 196, 128);
  SDL_Rect posCarte2 = newRect(364, 440, 196, 128);
  SDL_Rect posCarte3 = newRect(576, 480, 196, 128);
  SDL_Rect posCarte4 = newRect(788, 440, 196, 128);
  SDL_Rect posCarte5 = newRect(1000, 400, 196, 128);

  // variables
  Coord c;

  while(continuer) {
    // Blit des surfaces
    SDL_BlitSurface(ecranVictoire, NULL, screen, &fullscreen);
    SDL_BlitSurface(k.hand.carte1.skin, NULL, screen, &posCarte1);
    SDL_BlitSurface(k.hand.carte2.skin, NULL, screen, &posCarte2);
    SDL_BlitSurface(cp->flop1.skin, NULL, screen, &posCarte3);
    SDL_BlitSurface(cp->turn.skin, NULL, screen, &posCarte4);
    SDL_BlitSurface(cp->river.skin, NULL, screen, &posCarte5);

    switch(k.joueur) {
      case 1:
        SDL_BlitSurface(winJ1, NULL, screen, &fullscreen);
        break;
      case 2:
        SDL_BlitSurface(winJ2, NULL, screen, &fullscreen);
        break;
      case 3:
        SDL_BlitSurface(winJ3, NULL, screen, &fullscreen);
        break;
      case 4:
        SDL_BlitSurface(winJ4, NULL, screen, &fullscreen);
        break;
      case 5:
        SDL_BlitSurface(winJ5, NULL, screen, &fullscreen);
        break;
      default:
        break;
    }

    // Pointeur souris
    c.x = event.button.x;
    c.y = event.button.y;

    SDL_WaitEvent(&event);
    switch(event.type) {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
      // Actions souris
      case SDL_MOUSEBUTTONDOWN:
        if (posInclusion(c.x, c.y, posZoneMenu)) {
          continuer = 0;
          return 2;
        }
        if (posInclusion(c.x, c.y, posNextMenu)) {
          continuer = 0;
          return 1;
        }
        if (posInclusion(c.x, c.y, posDetailsMenu)) {
          continuer = detailsVictoirePoker(screen, t, *cp, nbJoueurs, k.joueur);
        }
    }
    // survol
    if (posInclusion(c.x, c.y, posZoneMenu)) {
      SDL_BlitSurface(nextSelection, NULL, screen, &posZoneMenu);
    }
    if (posInclusion(c.x, c.y, posNextMenu)) {
      SDL_BlitSurface(nextSelection, NULL, screen, &posNextMenu);
    }
    if (posInclusion(c.x, c.y, posDetailsMenu)) {
      SDL_BlitSurface(nextSelection, NULL, screen, &posDetailsMenu);
    }

    SDL_Flip(screen);
  }


}

int detailsVictoirePoker(SDL_Surface* screen, JoueurPoker* t, CentrePlateau cp, int nbJoueurs, int winner) {
  // variables
  int continuer = 1;
  SDL_Event event;
  Coord c;

  // Images
  SDL_Surface* ecranDetails2 = NULL;
  SDL_Surface* ecranDetails3 = NULL;
  SDL_Surface* ecranDetails4 = NULL;
  SDL_Surface* ecranDetails5 = NULL;
  SDL_Surface* etatDead = NULL;
  SDL_Surface* etatWin = NULL;
  SDL_Surface* etatLoose = NULL;
  SDL_Surface* selection = NULL;

  ecranDetails2 = IMG_Load("assets/poker/victoire/details2.jpg");
  ecranDetails3 = IMG_Load("assets/poker/victoire/details3.jpg");
  ecranDetails4 = IMG_Load("assets/poker/victoire/details4.jpg");
  ecranDetails5 = IMG_Load("assets/poker/victoire/details5.jpg");
  etatDead = IMG_Load("assets/poker/victoire/playerDead.png");
  etatWin = IMG_Load("assets/poker/victoire/playerWin.png");
  etatLoose = IMG_Load("assets/poker/victoire/playerLoose.png");
  selection = IMG_Load("assets/poker/regles/nextSelection.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posCartes[7][5];
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 5; j++) {
      posCartes[i][j] = newRect(807 + (59 + 5) * i, 200 + (90 + 5) * j, 59, 90);
    }
  }
  SDL_Rect posEtat[5];
  for (int i = 0; i < 5; i++) {
    posEtat[i] = newRect(616, 200 + (90 + 5) * i, 90, 185);
  }
  SDL_Rect posArgent[5];
  for (int i = 0; i < 5; i++) {
    posArgent[i] = newRect(477, 200 + (90 + 5) * i, 90, 195);
  }
  SDL_Rect posPoints[5];
  for (int i = 0; i < 5; i++) {
    posPoints[i] = newRect(336, 200 + (90 + 5) * i, 90, 204);
  }
  SDL_Rect backButton = newRect(25, 25, 125, 150);

  // Textes
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);

  SDL_Color noir = {0, 0, 0, 0};

  SDL_Surface* texteArgent1 = NULL;
  SDL_Surface* textePoints1 = NULL;
  char valeurTexteArgent1[5];
  char valeurTextePoints1[5];
  sprintf(valeurTexteArgent1, "%d", t[0].argent);
  texteArgent1 = creerTexte(screen, valeurTexteArgent1, noir, font);
  sprintf(valeurTextePoints1, "%d", valeurMain(t[0], cp));
  textePoints1 = creerTexte(screen, valeurTextePoints1, noir, font);

  SDL_Surface* texteArgent2 = NULL;
  SDL_Surface* textePoints2 = NULL;
  char valeurTexteArgent2[5];
  char valeurTextePoints2[5];
  sprintf(valeurTexteArgent2, "%d", t[1].argent);
  texteArgent2 = creerTexte(screen, valeurTexteArgent2, noir, font);
  sprintf(valeurTextePoints2, "%d", valeurMain(t[1], cp));
  textePoints2 = creerTexte(screen, valeurTextePoints2, noir, font);

  SDL_Surface* texteArgent3 = NULL;
  SDL_Surface* textePoints3 = NULL;
  SDL_Surface* texteArgent4 = NULL;
  SDL_Surface* textePoints4 = NULL;
  SDL_Surface* texteArgent5 = NULL;
  SDL_Surface* textePoints5 = NULL;

  if (nbJoueurs > 2) {

    char valeurTexteArgent3[5];
    char valeurTextePoints3[5];
    sprintf(valeurTexteArgent3, "%d", t[2].argent);
    texteArgent3 = creerTexte(screen, valeurTexteArgent3, noir, font);
    sprintf(valeurTextePoints3, "%d", valeurMain(t[2], cp));
    textePoints3 = creerTexte(screen, valeurTextePoints3, noir, font);

    if (nbJoueurs > 3) {

      char valeurTexteArgent4[5];
      char valeurTextePoints4[5];
      sprintf(valeurTexteArgent4, "%d", t[3].argent);
      texteArgent4 = creerTexte(screen, valeurTexteArgent4, noir, font);
      sprintf(valeurTextePoints4, "%d", valeurMain(t[3], cp));
      textePoints4 = creerTexte(screen, valeurTextePoints4, noir, font);

      if (nbJoueurs > 4) {

        char valeurTexteArgent5[5];
        char valeurTextePoints5[5];
        sprintf(valeurTexteArgent5, "%d", t[4].argent);
        texteArgent5 = creerTexte(screen, valeurTexteArgent5, noir, font);
        sprintf(valeurTextePoints5, "%d", valeurMain(t[4], cp));
        textePoints5 = creerTexte(screen, valeurTextePoints5, noir, font);
      }
    }
  }

  // Boucle Principale
  while (continuer) {
    // Affichage du background
    switch (nbJoueurs) {
      case 2:
        SDL_BlitSurface(ecranDetails2, NULL, screen, &fullscreen);
        break;
      case 3:
        SDL_BlitSurface(ecranDetails3, NULL, screen, &fullscreen);
        break;
      case 4:
        SDL_BlitSurface(ecranDetails4, NULL, screen, &fullscreen);
        break;
      case 5:
        SDL_BlitSurface(ecranDetails5, NULL, screen, &fullscreen);
        break;
    }

    // Affichage des mains
    for (int i = 0; i < nbJoueurs; i++) {

      SDL_BlitSurface(t[i].hand.carte1.petit, NULL, screen, &posCartes[0][i]);
      SDL_BlitSurface(t[i].hand.carte2.petit, NULL, screen, &posCartes[1][i]);
      SDL_BlitSurface(cp.flop1.petit, NULL, screen, &posCartes[2][i]);
      SDL_BlitSurface(cp.flop2.petit, NULL, screen, &posCartes[3][i]);
      SDL_BlitSurface(cp.flop3.petit, NULL, screen, &posCartes[4][i]);
      SDL_BlitSurface(cp.turn.petit, NULL, screen, &posCartes[5][i]);
      SDL_BlitSurface(cp.river.petit, NULL, screen, &posCartes[6][i]);

    }
    // Affichage de l'etat
    for (int i = 0; i < nbJoueurs; i++) {
      if (t[i].etat == 1) SDL_BlitSurface(etatDead, NULL, screen, &posEtat[i]);
      else if (t[i].joueur == winner) SDL_BlitSurface(etatWin, NULL, screen, &posEtat[i]);
      else SDL_BlitSurface(etatLoose, NULL, screen, &posEtat[i]);
    }

    // Affichage des textes
    SDL_BlitSurface(texteArgent1, NULL, screen, &posArgent[0]);
    SDL_BlitSurface(textePoints1, NULL, screen, &posPoints[0]);
    SDL_BlitSurface(texteArgent2, NULL, screen, &posArgent[1]);
    SDL_BlitSurface(textePoints2, NULL, screen, &posPoints[1]);
    if (nbJoueurs > 2) {
      SDL_BlitSurface(texteArgent3, NULL, screen, &posArgent[2]);
      SDL_BlitSurface(textePoints3, NULL, screen, &posPoints[2]);
      if (nbJoueurs > 3) {
        SDL_BlitSurface(texteArgent4, NULL, screen, &posArgent[3]);
        SDL_BlitSurface(textePoints4, NULL, screen, &posPoints[3]);
        if (nbJoueurs > 4) {
          SDL_BlitSurface(texteArgent5, NULL, screen, &posArgent[4]);
          SDL_BlitSurface(textePoints5, NULL, screen, &posPoints[4]);
        }
      }
    }

    SDL_WaitEvent(&event);

    c.x = event.button.x;
    c.y = event.button.y;

    switch (event.type) {
      // On quitte
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
      // Actions souris
      case SDL_MOUSEBUTTONDOWN:
        if (posInclusion(c.x, c.y, backButton)) {
          continuer = 0;
          return 1;
        }

    }

    // Au survol
    if (posInclusion(c.x, c.y, backButton)) {
      SDL_BlitSurface(selection, NULL, screen, &backButton);
    }

    SDL_Flip(screen);
  }



}

int victoirePokerFinale(SDL_Surface* screen, JoueurPoker t) {
  // Variable
  int continuer = 1;
  SDL_Event event;
  Coord c;

  // Images
  SDL_Surface* ecranVictoireFinale = NULL;
  SDL_Surface* winJ1 = NULL;
  SDL_Surface* winJ2 = NULL;
  SDL_Surface* winJ3 = NULL;
  SDL_Surface* winJ4 = NULL;
  SDL_Surface* winJ5 = NULL;
  SDL_Surface* nextSelection = NULL;

  ecranVictoireFinale = IMG_Load("assets/poker/victoire/ecranVictoireFinale.jpg");
  winJ1 = IMG_Load("assets/poker/victoire/winJ1.png");
  winJ2 = IMG_Load("assets/poker/victoire/winJ2.png");
  winJ3 = IMG_Load("assets/poker/victoire/winJ3.png");
  winJ4 = IMG_Load("assets/poker/victoire/winJ4.png");
  winJ5 = IMG_Load("assets/poker/victoire/winJ5.png");
  nextSelection = IMG_Load("assets/poker/regles/nextSelection.png");

  // textes
  SDL_Color noir = {0, 0, 0, 0};
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 50);
  SDL_Surface* texteArgent = NULL;
  char valeurTexteArgent[10];
  sprintf(valeurTexteArgent, "%d", t.argent);
  texteArgent = creerTexte(screen, valeurTexteArgent, noir, font);

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posMenuButton = newRect(25, 25, 125, 150);
  SDL_Rect posArgent = newRect(650, 600, 0, 0);

  while(continuer) {
    SDL_BlitSurface(ecranVictoireFinale, NULL, screen, &fullscreen);
    SDL_BlitSurface(texteArgent, NULL, screen, &posArgent);

    c.x = event.button.x;
    c.y = event.button.y;


    SDL_WaitEvent(&event);
    switch(event.type) {
      // On quitte
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (posInclusion(c.x, c.y, posMenuButton)) {
          continuer = 0;
          return 2;
        }

    }

    switch(t.joueur) {
      case 1:
        SDL_BlitSurface(winJ1, NULL, screen, &fullscreen);
        break;
      case 2:
        SDL_BlitSurface(winJ2, NULL, screen, &fullscreen);
        break;
      case 3:
        SDL_BlitSurface(winJ3, NULL, screen, &fullscreen);
        break;
      case 4:
        SDL_BlitSurface(winJ4, NULL, screen, &fullscreen);
        break;
      case 5:
        SDL_BlitSurface(winJ5, NULL, screen, &fullscreen);
        break;
      default:
        break;
    }

    // Au survol
    if (posInclusion(c.x, c.y, posMenuButton)) {
      SDL_BlitSurface(nextSelection, NULL, screen, &posMenuButton);
    }

    SDL_Flip(screen);

  }

}
