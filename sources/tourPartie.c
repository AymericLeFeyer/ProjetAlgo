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

//calcule le score total (au niveau de l appel de victoirePokerFinale, appel de fonction en commentaire pour pas faire crash)
void scorePoker (CentrePlateau cp, JoueurPoker* t, tabJP jp, /*tabP p*/){
int argentMax=cp.mise;//argent max present dans la partie, va servir de reference pour le pourcentage du score
for (int i=0;i<5;i++){     //boucle pour faire la somme total de l argent present en jeu
  argentMax=argentMax + t[i].argent;
}
for (int j=0;j<5;j++){  //boucle qui pour le tableau de profil selectionné pour les joueurs va leur faire monter leur scores
  jp[j].scorePoker=t[j].argent/argentMax;
}

//ici reste a voir avec le tableau tabP p en parametre et
//effectuer les test voir si pour un profil en jeu , sont score est superieur au profil déja sauvegarder, si oui save dans le tableau p
}


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

  while (continuer==1) {
    SDL_BlitSurface(table, NULL, screen, &posTable);

    SDL_PollEvent(&event);
    switch(event.type) {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        break;
    }

    if (manche < mancheTotale && continuer==1)
    {
        cp=initialisePoker(t, nbJoueurs, argentDepart, manche, miseDepart);
        //Faire une boucle qui initialise l'état des joueurs à 0
        //Dès qu'une nouvelle manche demarre, tous les joueurs se "réveillent"
        for(i = 0; i < nbJoueurs; i++)
        {
            t[i].etat = 0;
        }
        for(i = 0; i < 4; i++)
        {
            //Parcourir tableau pour savoir ce que le joueur j fais
            for(j = 0; j < nbJoueurs; j++)
            {
                if(t[j].etat==0 && continuer==1){
                    if(nbNonCouche(t,nbJoueurs)!=1 && continuer==1){


                        /*if(cp.flop1.visible==1){
                            printf("flop1: %d %d\n",cp.flop1.couleur,cp.flop1.valeur);
                        }
                        if(cp.flop2.visible==1){
                            printf("flop2: %d %d\n",cp.flop2.couleur,cp.flop2.valeur);
                        }
                        if(cp.flop3.visible==1){
                            printf("flop3: %d %d\n",cp.flop3.couleur,cp.flop3.valeur);
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
                        printf("%d %d | %d %d\n",t[j].hand.carte1.couleur,t[j].hand.carte1.valeur,t[j].hand.carte2.couleur,t[j].hand.carte2.valeur);*/



                        continuer = tourPoker(screen, &t[j], &cp, nbJoueurs, manche + 1, t, mancheTotale);


                    }
                }
            }
            switch(i)
            {
                //Tour 1
                case 0:
                    cp.flop1.visible = 1;
                    cp.flop2.visible = 1;
                    cp.flop3.visible = 1;
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
            if(t[k].etat==0 && continuer==1){
                    if(valeurMain(t[k],cp)>max){
                        max=valeurMain(t[k],cp);
                        maxi=k;
                    }
            }
        }
        max=0;
        t[maxi].argent+=cp.mise;
        cp.mise=0;
        if (continuer==1) {
          continuer = victoirePokerManche(screen, t, &cp, t[maxi], nbJoueurs);
        }

        cp=libererPoker(t,nbJoueurs,cp);
        manche++;
    }

    if (manche == mancheTotale && continuer==1)
    {
      //determinons le vainqueur final
      max = 0;
      for(k=0;k<nbJoueurs;k++){
          if(t[k].etat==0 && continuer==1){
                  if(t[k].argent>max){
                      max=t[k].argent;
                      maxi=k;
                  }
          }
      }
      if (continuer==1) {
        /*scorePoker(cp,t,jp);**/
        continuer = victoirePokerFinale(screen, t[maxi]);
      }
    }



    SDL_Flip(screen);
  }

  //cp=libererPoker(t,nbJoueurs,cp);
  SDL_FreeSurface(table);
  return continuer;


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
int tourPoker(SDL_Surface* screen, JoueurPoker* j, CentrePlateau* cp, int nbJoueurs, int currentManche, JoueurPoker* tabJ, int totalManche) {
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
  SDL_Surface* mancheText = NULL;

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
  mancheText = IMG_Load("assets/poker/table/mancheText.png");

  // Informations de la manche
  SDL_Surface* playerIconPlaying = NULL;
  SDL_Surface* playerIconWaiting = NULL;
  SDL_Surface* playerIconOut = NULL;

  playerIconPlaying = IMG_Load("assets/poker/table/playerIconPlaying.png");
  playerIconWaiting = IMG_Load("assets/poker/table/playerIconWaiting.png");
  playerIconOut = IMG_Load("assets/poker/table/playerIconOut.png");

  SDL_Rect positionPlayerIcon[5];
  for (int i = 0; i < 5; i++) {
    positionPlayerIcon[i] = newRect(25 + 40 * i, 635, 60, 40);
  }


  // Textes
  SDL_Surface* texteJetonsPersos = NULL;
  SDL_Surface* texteJetonsGlobal = NULL;
  SDL_Surface* texteCurrentManche = NULL;
  SDL_Surface* texteTotalManche = NULL;
  SDL_Surface* texteMontantRemise = NULL;
  SDL_Surface* texteMiseMinimumActuelle = NULL;

  char valeurTexteJetonsPersos[5];
  char valeurTexteJetonsGlobal[5];
  char valeurTexteCurrentManche[2];
  char valeurTexteTotalManche[2];
  char valeurTexteMontantRemise[10];
  char valeurTexteMinimumActuelle[50];

  SDL_Color noir = {0, 0, 0, 0};
  SDL_Color rouge = {255, 0, 0, 0};
  SDL_Color vert = {0, 255, 0, 0};
  SDL_Color blanc = {255, 255, 255, 255};

  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);

  TTF_Font *font2 = NULL;
  font2 = TTF_OpenFont(FONT_UBUNTU, 20);

  TTF_Font *font3 = NULL;
  font3 = TTF_OpenFont(FONT_UBUNTU, 36);

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posZoneJetonsPersos = newRect(883, 558, 108, 108);
  SDL_Rect posZoneJetonsGlobal = newRect(480, 0, 192, 320);
  SDL_Rect posAffichageJetonsPersos = newRect(883, 507, 50, 105);
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
  SDL_Rect posFlop1 = newRect(256, 262, 196, 128);
  SDL_Rect posFlop2 = newRect(416, 262, 196, 128);
  SDL_Rect posFlop3 = newRect(576, 262, 196, 128);
  SDL_Rect posTurn = newRect(736, 262, 196, 128);
  SDL_Rect posRiver = newRect(896, 262, 196, 128);

  // Positions des Textes
  SDL_Rect posTextCurrentManche = newRect(90, 570, 0, 0);
  SDL_Rect posTextTotalManche = newRect(132, 570, 0, 0);

  SDL_Rect posTextMiseRelance = newRect(32, 186, 36, 186);
  SDL_Rect posTexteMinimumMise = newRect(500, 210, 36, 320);

  // Variables
  int choix = 0; // 1 = suivre, 2 = tapis, 3 = relance, 4 = passer
  Coord c;
  int relanceMise = cp->miseD * 2;
  int etat = 0; //0: rouge, 1:noir, 2:vert

  sprintf(valeurTexteJetonsPersos, "%d", j->argent);
  texteJetonsPersos = creerTexte(screen, valeurTexteJetonsPersos, noir, font);

  sprintf(valeurTexteJetonsGlobal, "%d", cp->mise);
  texteJetonsGlobal = creerTexte(screen, valeurTexteJetonsGlobal, noir, font);

  sprintf(valeurTexteCurrentManche, "%d", currentManche);
  texteCurrentManche = creerTexte(screen, valeurTexteCurrentManche, blanc, font3);

  sprintf(valeurTexteTotalManche, "%d", totalManche);
  texteTotalManche = creerTexte(screen, valeurTexteTotalManche, blanc, font3);



  sprintf(valeurTexteMinimumActuelle, "Mise minimale : %d", cp->miseD);
  texteMiseMinimumActuelle = creerTexte(screen, valeurTexteMinimumActuelle, noir, font);

  // Boucle Principale
  while(continuer==1) {
    // Affichage de la table
    SDL_BlitSurface(table, NULL, screen, &fullscreen);
    // Affichage des cartes
    j->hand.carte1.visible = posInclusion(c.x, c.y, posCarte1);
    j->hand.carte2.visible = posInclusion(c.x, c.y, posCarte2);
    afficherCarte(screen, j->hand.carte1, posCarte1);
    afficherCarte(screen, j->hand.carte2, posCarte2);
    afficherCarte(screen, cp->flop1, posFlop1);
    afficherCarte(screen, cp->flop2, posFlop2);
    afficherCarte(screen, cp->flop3, posFlop3);
    afficherCarte(screen, cp->turn, posTurn);
    afficherCarte(screen, cp->river, posRiver);

    // Affichage des infos de partie
    SDL_BlitSurface(mancheText, NULL, screen, &fullscreen);
    SDL_BlitSurface(texteCurrentManche, NULL, screen, &posTextCurrentManche);
    SDL_BlitSurface(texteTotalManche, NULL, screen, &posTextTotalManche);

    for (int i = 0; i < nbJoueurs; i++) {
      if (tabJ[i].etat == 1) {
        SDL_BlitSurface(playerIconOut, NULL, screen, &positionPlayerIcon[i]);
      }
      else {
        SDL_BlitSurface(playerIconWaiting, NULL, screen, &positionPlayerIcon[i]);
      }
      if (i == j->joueur - 1) {
        SDL_BlitSurface(playerIconPlaying, NULL, screen, &positionPlayerIcon[i]);
      }

    }

    // Affichage de la mise en cours
    SDL_BlitSurface(texteMiseMinimumActuelle, NULL, screen, &posTexteMinimumMise);

    // Affichage des jetons
    afficherJetons(screen, cp);

    c.x = event.button.x;
    c.y = event.button.y;

    SDL_WaitEvent(&event);

    switch(event.type) {
      /*case SDL_KEYDOWN:
        continuer = 0;
        return 1;
        break;*/
      case SDL_QUIT:
        continuer = 0;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (posInclusion(c.x, c.y, posMenuButton)) {
          continuer = 5;
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
            continuer = 3;
            miseJeu(j, cp, choix, relanceMise);
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

    if (choix == 2 && continuer==1) {
      if (posInclusion(c.x, c.y, posPlus5Relance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posPlus5Relance);
      if (posInclusion(c.x, c.y, posPlus10Relance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posPlus10Relance);
      if (posInclusion(c.x, c.y, posFois2Relance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posFois2Relance);
      if (posInclusion(c.x, c.y, posResetRelance)) SDL_BlitSurface(relanceWhiteSelection, NULL, screen, &posResetRelance);
      if (posInclusion(c.x, c.y, posZoneOkRelance)) SDL_BlitSurface(okWhiteSelection, NULL, screen, &posZoneOkRelance);
      // Relance
      sprintf(valeurTexteMontantRemise, "%d", relanceMise);
      /*texteMontantRemise = creerTexte(screen, valeurTexteMontantRemise, noir, font2);
      SDL_FreeSurface(texteMontantRemise);*/
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
      SDL_FreeSurface(texteMontantRemise);
    }

    if ((choix == 1) || (choix == 3) || (choix == 4) || ((choix == 2) && (etat == 2))) {
      SDL_BlitSurface(boutonNext, NULL, screen, &fullscreen);
      if (posInclusion(c.x, c.y, posNextButton)) {
        SDL_BlitSurface(nextSelection, NULL, screen, &posNextButton);
      }
    }






  SDL_Flip(screen);
  }
  SDL_FreeSurface(troisOptionsWhiteSelection);
  SDL_FreeSurface(table);
  SDL_FreeSurface(troisOptionsGreenSelection);
  SDL_FreeSurface(okWhiteSelection);
  SDL_FreeSurface(relanceWhiteSelection);
  SDL_FreeSurface(affichageJetonsGlobal);
  SDL_FreeSurface(affichageJetonsPersos);
  SDL_FreeSurface(affichageRelance);
  SDL_FreeSurface(boutonNext);
  SDL_FreeSurface(nextSelection);
  SDL_FreeSurface(mancheText);
  SDL_FreeSurface(playerIconPlaying);
  SDL_FreeSurface(playerIconWaiting);
  SDL_FreeSurface(playerIconOut);
  SDL_FreeSurface(texteJetonsPersos);
  SDL_FreeSurface(texteJetonsGlobal);
  SDL_FreeSurface(texteCurrentManche);
  SDL_FreeSurface(texteTotalManche);
  SDL_FreeSurface(texteMiseMinimumActuelle);
  TTF_CloseFont(font);
  TTF_CloseFont(font2);
  TTF_CloseFont(font3);
  if (continuer==3) {
    return 1;
  }else{
    return continuer;
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
    SDL_FreeSurface(jetons[k]);
  }
}
