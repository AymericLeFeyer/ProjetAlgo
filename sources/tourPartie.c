#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/structure.h"
#include "../headers/shortcuts.h"
#include "../headers/tourPartie.h"
#include "../headers/pioche.h"
#include "../headers/mainsPoker.h"
#include "../headers/poker.h"

// en textuel
int tourPartie(SDL_Surface* screen, CentrePlateau cp, JoueurPoker* t, int nbJoueurs, int mancheTotale,int argentDepart, int miseDepart)
{
  // Images
  SDL_Surface* table = NULL;
  table = IMG_Load("assets/poker/table/tablePoker.jpg");
  SDL_Rect posTable = newRect(0, 0, 720, 1280);

  // Variables principales
  int continuer = 1;
  SDL_Event event;

  // Variables poker
  int manche = 0, i, j, k, max=0,maxi;
  int onPeutContinuer = 0;

  while (continuer) {
    SDL_BlitSurface(table, NULL, screen, &posTable);

    SDL_PollEvent(&event);
    switch(event.type) {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
    }

    if (manche < mancheTotale)
    {
        printf("manche numero %d \n\n",manche+1);
        cp=initialisePoker(t, nbJoueurs, argentDepart, manche, miseDepart);
        //Faire une boucle qui initialise l'état des joueurs à 0
        //Dès qu'une nouvelle manche demarre, tous les joueurs se "réveillent"
        for(i = 0; i < nbJoueurs; i++)
        {
            t[i].etat = 0;
        }
        for(i = 0; i < 4; i++)
        {
            printf("tour numero %d\n",i+1);
            //Parcourir tableau pour savoir ce que le joueur j fais
            for(j = 0; j < nbJoueurs; j++)
            {
                if(t[j].etat==0){
                    if(nbNonCouche(t,nbJoueurs)!=1){


                        if(cp.flop.visible==1){
                            printf("flop: %d %d\n",cp.flop.couleur,cp.flop.valeur);
                        }
                        if(cp.turn.visible==1){
                            printf("turn: %d %d\n",cp.turn.couleur,cp.turn.valeur);
                        }
                        if(cp.river.visible==1){
                            printf("river: %d %d\n",cp.river.couleur,cp.river.valeur);
                        }
                        printf("tour du joueur %d \n", j+1);
                        printf("mise actuelle : %d \n", cp.miseD);
                        printf("argent possede par le joueur actuel : %d \n", t[j].argent);
                        printf("cartes possedees : \n");
                        printf("%d %d | %d %d\n",t[j].hand.carte1.couleur,t[j].hand.carte1.valeur,t[j].hand.carte2.couleur,t[j].hand.carte2.valeur);



                        continuer = tourPoker(screen, &t[j], &cp);
                        if (continuer != 1) return continuer;


                    }
                }
            }
            switch(i)
            {
                //Tour 1
                case 0:
                    cp.flop.visible = 1;
                    break;

                //Tour 2
                case 1:
                    cp.turn.visible = 1;
                    break;

                //Tour 3
                case 2:
                    cp.river.visible = 1;
                    break;

                //Tour 4
                default:
                    break;
            }
        }
        //determinons le vainqueur de la manche
        for(k=0;k<nbJoueurs;k++){
            if(t[k].etat==0){
                    if(valeurMain(t[k],cp)>max){
                        max=valeurMain(t[k],cp);
                        maxi=k;
                    }
            }
        }
        max=0;
        printf("le joueur %d remporte cette manche !",k);
        t[k].argent+=cp.mise;
        cp.mise=0;
        manche++;
    }

    SDL_Flip(screen);
  }




}

//compte le nombre de joueurs non couchés
int nbNonCouche(JoueurPoker *t,int nbJoueurs){
    int a=0;
    for(int i=0;i<nbJoueurs;i++){
        if(t[i].etat==0){
            a++;
        }
    }
    return a;
}

//tour Poker
int tourPoker(SDL_Surface* screen, JoueurPoker* j, CentrePlateau* cp) {
  int continuer = 1;
  SDL_Event event;

  // Images
  SDL_Surface* table = NULL;
  SDL_Surface* troisOptionsWhiteSelection = NULL;
  SDL_Surface* troisOptionsGreenSelection = NULL;
  SDL_Surface* okWhiteSelection = NULL;
  SDL_Surface* relanceWhiteSelection = NULL;
  SDL_Surface* affichageJetonsGlobal = NULL;
  SDL_Surface* affichageJetonsPersos = NULL;
  SDL_Surface* affichageRelance = NULL;
  SDL_Surface* boutonNext = NULL;
  SDL_Surface* nextSelection = NULL;

  table = IMG_Load("assets/poker/table/tablePoker.jpg");

  nextSelection = IMG_Load("assets/poker/regles/nextSelection.png");

  troisOptionsWhiteSelection = IMG_Load("assets/poker/table/troisOptionsWhiteSelection.png");
  troisOptionsGreenSelection = IMG_Load("assets/poker/table/troisOptionsGreenSelection.png");
  okWhiteSelection = IMG_Load("assets/poker/table/okWhiteSelection.png");
  relanceWhiteSelection = IMG_Load("assets/poker/table/relanceWhiteSelection.png");

  affichageJetonsGlobal = IMG_Load("assets/poker/table/affichageJetonsGlobal.png");
  affichageJetonsPersos = IMG_Load("assets/poker/table/affichageJetonsPersos.png");
  affichageRelance = IMG_Load("assets/poker/table/affichageRelance.png");
  boutonNext = IMG_Load("assets/poker/table/boutonNext.png");


  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posZoneJetonsPersos = newRect(900, 466, 108, 108);
  SDL_Rect posZoneJetonsGlobal = newRect(480, 0, 192, 320);
  SDL_Rect posAffichageJetonsPersos = newRect(901, 385, 50, 105);
  SDL_Rect posAffichageJetonsGlobal = newRect(858, 63, 50, 200);

  SDL_Rect posSuivreButton = newRect(1060, 228, 80, 200);
  SDL_Rect posTapisButton = newRect(1060, 338, 80, 200);
  SDL_Rect posRelanceButton = newRect(1060, 448, 80, 200);
  SDL_Rect posPasserButton = newRect(1060, 558, 80, 200);

  SDL_Rect posNextButton = newRect(1110, 25, 125, 150);
  SDL_Rect posMenuButton = newRect(25, 25, 125, 150);

  SDL_Rect posZoneRelance = newRect(25, 179, 300, 200);
  SDL_Rect posZoneJetonsRelance = newRect(30, 184, 40, 190);
  SDL_Rect posZoneOkRelance = newRect(71, 435, 38, 108);
  SDL_Rect posPlus5Relance = newRect(41, 244, 75, 75);
  SDL_Rect posPlus10Relance = newRect(41, 339, 75, 75);
  SDL_Rect posFois2Relance = newRect(134, 244, 75, 75);
  SDL_Rect posResetRelance = newRect(134, 339, 75, 75);

  // Positions des cartes
  SDL_Rect posCarte1 = newRect(480, 524, 196, 128);
  SDL_Rect posCarte2 = newRect(672, 524, 196, 128);
  SDL_Rect posFlop = newRect(416, 262, 196, 128);
  SDL_Rect posTurn = newRect(576, 262, 196, 128);
  SDL_Rect posRiver = newRect(736, 262, 196, 128);

  // Variables
  int choix = 0; // 1 = suivre, 2 = tapis, 3 = relance, 4 = passer
  Coord c;

  // Boucle Principale
  while(continuer) {
    // Affichage de la table
    SDL_BlitSurface(table, NULL, screen, &fullscreen);
    // Affichage des cartes
    afficherCarte(screen, j->hand.carte1, posCarte1);
    afficherCarte(screen, j->hand.carte2, posCarte2);
    afficherCarte(screen, cp->flop, posFlop);
    afficherCarte(screen, cp->turn, posTurn);
    afficherCarte(screen, cp->river, posRiver);

    c.x = event.button.x;
    c.y = event.button.y;

    SDL_PollEvent(&event);

    switch(event.type) {
      case SDL_KEYDOWN:
        continuer = 0;
        return 1;
        break;
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (posInclusion(c.x, c.y, posMenuButton)) {
          continuer = 0;
          return 5;
        }
        if (posInclusion(c.x, c.y, posSuivreButton)) {
          choix = 1;
        }
        if (posInclusion(c.x, c.y, posTapisButton)) {
          choix = 2;
        }
        if (posInclusion(c.x, c.y, posRelanceButton)) {
          choix = 3;
        }
        if (posInclusion(c.x, c.y, posPasserButton)) {
          choix = 4;
        }
        if (choix) {
          if (posInclusion(c.x, c.y, posNextButton)) {
            continuer = 0;
            return 1;
          }
        }
        break;
    }

    // Affichages au survol
    if (posInclusion(c.x, c.y, posZoneJetonsPersos)) {
      SDL_BlitSurface(affichageJetonsPersos, NULL, screen, &fullscreen);
      // Afficher le montant des jetons perso
    }
    if (posInclusion(c.x, c.y, posZoneJetonsGlobal)) {
      SDL_BlitSurface(affichageJetonsGlobal, NULL, screen, &fullscreen);
      // Afficher le montant des jetons globaux
    }
    if (posInclusion(c.x, c.y, posMenuButton)) {
      SDL_BlitSurface(nextSelection, NULL, screen, &posMenuButton);
      // Afficher le montant des jetons globaux
    }
    if (posInclusion(c.x, c.y, posSuivreButton)) {
      SDL_BlitSurface(troisOptionsWhiteSelection, NULL, screen, &posSuivreButton);
      // Afficher le montant des jetons globaux
    }
    if (posInclusion(c.x, c.y, posTapisButton)) {
      SDL_BlitSurface(troisOptionsWhiteSelection, NULL, screen, &posTapisButton);
      // Afficher le montant des jetons globaux
    }
    if (posInclusion(c.x, c.y, posRelanceButton)) {
      SDL_BlitSurface(troisOptionsWhiteSelection, NULL, screen, &posRelanceButton);
      // Afficher le montant des jetons globaux
    }
    if (posInclusion(c.x, c.y, posPasserButton)) {
      SDL_BlitSurface(troisOptionsWhiteSelection, NULL, screen, &posPasserButton);
      // Afficher le montant des jetons globaux
    }

    // Affichage du choix courant
    switch (choix) {
      case 1:
        SDL_BlitSurface(troisOptionsGreenSelection, NULL, screen, &posSuivreButton);
        break;
      case 2:
        SDL_BlitSurface(troisOptionsGreenSelection, NULL, screen, &posTapisButton);
        break;
      case 3:
        SDL_BlitSurface(troisOptionsGreenSelection, NULL, screen, &posRelanceButton);
        break;
      case 4:
        SDL_BlitSurface(troisOptionsGreenSelection, NULL, screen, &posPasserButton);
        break;
    }

    if (choix) {
      SDL_BlitSurface(boutonNext, NULL, screen, &fullscreen);
      if (posInclusion(c.x, c.y, posNextButton)) {
        SDL_BlitSurface(nextSelection, NULL, screen, &posNextButton);
      }
    }





  SDL_Flip(screen);
  }

}
