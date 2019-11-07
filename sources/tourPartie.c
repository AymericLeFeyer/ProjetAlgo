#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#include "../headers/structure.h"
#include "../headers/shortcuts.h"
#include "../headers/tourPartie.h"
#include "../headers/pioche.h"
#include "../headers/mainsPoker.h"
#include "../headers/poker.h"
#include "../headers/interface.h"
#include "../headers/constantes.h"
#include "../headers/victoire.h"

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



                        continuer = tourPoker(screen, &t[j], &cp, nbNonCouche(t, nbJoueurs), manche + 1);
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
        t[maxi].argent+=cp.mise;
        cp.mise=0;
        continuer = victoirePokerManche(screen, t, &cp, t[maxi], nbJoueurs);
        if (continuer == 2) return 2;

        manche++;
    }

    if (manche == mancheTotale)
    {
      //determinons le vainqueur final
      max = 0;
      for(k=0;k<nbJoueurs;k++){
          if(t[k].etat==0){
                  if(t[k].argent>max){
                      max=t[k].argent;
                      maxi=k;
                  }
          }
      }
      continuer = victoirePokerFinale(screen, t[maxi]);
      if (continuer == 2) return 2;
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
int tourPoker(SDL_Surface* screen, JoueurPoker* j, CentrePlateau* cp, int enJeu, int currentManche) {
  if (j->argent == 0) return 1;
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

  // Textes
  SDL_Surface* texteJetonsPersos = NULL;
  SDL_Surface* texteJetonsGlobal = NULL;
  SDL_Surface* texteCurrentJoueur = NULL;
  SDL_Surface* texteCurrentManche = NULL;
  SDL_Surface* texteNbJoueursEnJeu = NULL;
  SDL_Surface* texteMontantRemise = NULL;
  SDL_Surface* texteMiseMinimumActuelle = NULL;
  char valeurTexteJetonsPersos[5];
  char valeurTexteJetonsGlobal[5];
  char valeurTexteCurrentJoueur[20];
  char valeurTexteCurrentManche[20];
  char valeurTexteNbJoueursEnJeu[30];
  char valeurTexteMontantRemise[10];
  char valeurTexteMinimumActuelle[50];

  SDL_Color noir = {0, 0, 0, 0};
  SDL_Color rouge = {255, 0, 0, 0};
  SDL_Color vert = {0, 255, 0, 0};

  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);

  TTF_Font *font2 = NULL;
  font2 = TTF_OpenFont(FONT_UBUNTU, 20);

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

  // Positions des Textes
  SDL_Rect posTextCurrentManche = newRect(30, 520, 45, 180);
  SDL_Rect posTextCurrentJoueur = newRect(30, 560, 45, 180);
  SDL_Rect posTextJoueursEnJeu = newRect(30, 600, 45, 180);
  SDL_Rect posTextMiseRelance = newRect(32, 186, 36, 186);
  SDL_Rect posTexteMinimumMise = newRect(475, 210, 36, 320);

  // Variables
  int choix = 0; // 1 = suivre, 2 = tapis, 3 = relance, 4 = passer
  Coord c;
  int relanceMise = cp->miseD * 2;
  int etat = 0; //0: rouge, 1:noir, 2:vert

  sprintf(valeurTexteJetonsPersos, "%d", j->argent);
  texteJetonsPersos = creerTexte(screen, valeurTexteJetonsPersos, noir, font);

  sprintf(valeurTexteJetonsGlobal, "%d", cp->mise);
  texteJetonsGlobal = creerTexte(screen, valeurTexteJetonsGlobal, noir, font);

  sprintf(valeurTexteCurrentManche, "Manche %d", currentManche);
  texteCurrentManche = creerTexte(screen, valeurTexteCurrentManche, noir, font2);

  sprintf(valeurTexteCurrentJoueur, "Joueur %d", j->joueur);
  texteCurrentJoueur = creerTexte(screen, valeurTexteCurrentJoueur, noir, font2);

  sprintf(valeurTexteNbJoueursEnJeu, "%d Joueurs restants" , enJeu);
  texteNbJoueursEnJeu = creerTexte(screen, valeurTexteNbJoueursEnJeu, noir, font2);

  sprintf(valeurTexteMinimumActuelle, "Mise minumum : %d", cp->miseD);
  texteMiseMinimumActuelle = creerTexte(screen, valeurTexteMinimumActuelle, noir, font);

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

    // Affichage des infos de partie
    SDL_BlitSurface(texteCurrentManche, NULL, screen, &posTextCurrentManche);
    SDL_BlitSurface(texteCurrentJoueur, NULL, screen, &posTextCurrentJoueur);
    SDL_BlitSurface(texteNbJoueursEnJeu, NULL, screen, &posTextJoueursEnJeu);

    // Affichage de la mise en cours
    SDL_BlitSurface(texteMiseMinimumActuelle, NULL, screen, &posTexteMinimumMise);

    // Affichage des jetons
    afficherJetons(screen, cp);


    c.x = event.button.x;
    c.y = event.button.y;

    SDL_WaitEvent(&event);

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
          choix = 4;
        }
        if (posInclusion(c.x, c.y, posRelanceButton)) {
          choix = 2;
        }
        if (posInclusion(c.x, c.y, posPasserButton)) {
          choix = 3;
        }
        if ((choix == 1) || (choix == 3) || (choix == 4) || ((choix == 2) && (etat == 2))) {
          if (posInclusion(c.x, c.y, posNextButton)) {
            continuer = 0;
            miseJeu(j, cp, choix, relanceMise);
            return 1;
          }
        }
        if (choix == 2) {
          if (posInclusion(c.x, c.y, posPlus5Relance)) {
            // On ajoute 5
            if (relanceMise < 10000 && etat != 2)
            relanceMise += 5;

          }
          if (posInclusion(c.x, c.y, posPlus10Relance)) {
            // On ajoute 10
            if (relanceMise < 10000 && etat != 2)
            relanceMise += 10;

          }
          if (posInclusion(c.x, c.y, posFois2Relance)) {
            // On double
            if (relanceMise < 10000 && etat != 2)
            relanceMise *= 2;

          }
          if (posInclusion(c.x, c.y, posResetRelance)) {
            // On reset
            relanceMise = cp->miseD * 2;
            etat = 1;

          }
          if (posInclusion(c.x, c.y, posZoneOkRelance)) {
            // On poursuit
            if (relanceMise <= j->argent) if (etat) etat = 2;

          }
        }
        break;
    }

    // Affichages au survol
    if (posInclusion(c.x, c.y, posZoneJetonsPersos)) {
      SDL_BlitSurface(affichageJetonsPersos, NULL, screen, &fullscreen);
      // Afficher le montant des jetons perso
      SDL_BlitSurface(texteJetonsPersos, NULL, screen, &posAffichageJetonsPersos);

    }
    if (posInclusion(c.x, c.y, posZoneJetonsGlobal)) {
      SDL_BlitSurface(affichageJetonsGlobal, NULL, screen, &fullscreen);
      // Afficher le montant des jetons globaux
      SDL_BlitSurface(texteJetonsGlobal, NULL, screen, &posAffichageJetonsGlobal);
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
      case 4:
        SDL_BlitSurface(troisOptionsGreenSelection, NULL, screen, &posTapisButton);
        break;
      case 2:
        SDL_BlitSurface(troisOptionsGreenSelection, NULL, screen, &posRelanceButton);
        SDL_BlitSurface(affichageRelance, NULL, screen, &fullscreen);
        break;
      case 3:
        SDL_BlitSurface(troisOptionsGreenSelection, NULL, screen, &posPasserButton);
        break;
    }

    if (choix == 2) {
      if (posInclusion(c.x, c.y, posPlus5Relance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posPlus5Relance);
      if (posInclusion(c.x, c.y, posPlus10Relance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posPlus10Relance);
      if (posInclusion(c.x, c.y, posFois2Relance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posFois2Relance);
      if (posInclusion(c.x, c.y, posResetRelance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posResetRelance);
      if (posInclusion(c.x, c.y, posZoneOkRelance)) SDL_BlitSurface(okWhiteSelection, NULL, screen, &posZoneOkRelance);
      // Relance
      sprintf(valeurTexteMontantRemise, "%d", relanceMise);
      texteMontantRemise = creerTexte(screen, valeurTexteMontantRemise, noir, font2);
      if (etat != 2) {
        if (relanceMise <= j->argent) etat = 1;
        else etat = 0;
      }
      switch(etat) {
        case 0:
          texteMontantRemise = creerTexte(screen, valeurTexteMontantRemise, rouge, font2);
          break;
        case 1:
          texteMontantRemise = creerTexte(screen, valeurTexteMontantRemise, noir, font2);
          break;
        case 2:
          texteMontantRemise = creerTexte(screen, valeurTexteMontantRemise, vert, font2);
          break;
      }
      SDL_BlitSurface(texteMontantRemise, NULL, screen, &posTextMiseRelance);

    }

    if ((choix == 1) || (choix == 3) || (choix == 4) || ((choix == 2) && (etat == 2))) {
      SDL_BlitSurface(boutonNext, NULL, screen, &fullscreen);
      if (posInclusion(c.x, c.y, posNextButton)) {
        SDL_BlitSurface(nextSelection, NULL, screen, &posNextButton);
      }
    }






  SDL_Flip(screen);
  }

}

void afficherJetons(SDL_Surface* screen, CentrePlateau* cp) {
  // Images
  SDL_Surface* jetons[8];
  jetons[0] = IMG_Load("assets/poker/jetons/128res/1.png");
  jetons[1] = IMG_Load("assets/poker/jetons/128res/2.png");
  jetons[2] = IMG_Load("assets/poker/jetons/128res/5.png");
  jetons[3] = IMG_Load("assets/poker/jetons/128res/10.png");
  jetons[4] = IMG_Load("assets/poker/jetons/128res/20.png");
  jetons[5] = IMG_Load("assets/poker/jetons/128res/50.png");
  jetons[6] = IMG_Load("assets/poker/jetons/128res/100.png");
  jetons[7] = IMG_Load("assets/poker/jetons/128res/500.png");

  // Positions
  SDL_Rect posTable = newRect(473, 0, 199, 334);
  SDL_Rect posJetons[12];
  posJetons[0] = newRect(501, 25, 128, 128);
  posJetons[1] = newRect(665, 49, 128, 128);
  posJetons[2] = newRect(579, 1, 128, 128);
  posJetons[3] = newRect(579, 97, 128, 128);
  posJetons[4] = newRect(445, 78, 128, 128);
  posJetons[5] = newRect(724, 0, 128, 128);
  posJetons[6] = newRect(501, 0, 128, 128);
  posJetons[7] = newRect(665, 78, 128, 128);
  posJetons[8] = newRect(579, 97, 128, 128);
  posJetons[9] = newRect(579, 1, 128, 128);
  posJetons[10] = newRect(445, 49, 128, 128);
  posJetons[11] = newRect(724, 25, 128, 128);




  // Nombres de jetons
  int restant = cp->mise;
  int nbJetons[8];
  nbJetons[7] = restant / 500;
  restant %= 500;
  nbJetons[6] = restant / 100;
  restant %= 100;
  nbJetons[5] = restant / 50;
  restant %= 50;
  nbJetons[4] = restant / 20;
  restant %= 20;
  nbJetons[3] = restant / 10;
  restant %= 10;
  nbJetons[2] = restant / 5;
  restant %= 5;
  nbJetons[1] = restant / 2;
  restant %= 2;
  nbJetons[0] = restant;

  int currentIndexInTheTable = 0;

  for (int k = 0; k < 8; k ++) {
    for (int i = 0; i < nbJetons[k]; i++) {
      SDL_BlitSurface(jetons[k], NULL, screen, &posJetons[currentIndexInTheTable++]);
    }
  }
}
