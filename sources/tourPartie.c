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

  // Positions des cartes
  SDL_Rect posCarte1 = newRect(480, 524, 196, 128);
  SDL_Rect posCarte2 = newRect(672, 524, 196, 128);
  SDL_Rect posFlop = newRect(416, 262, 196, 128);
  SDL_Rect posTurn = newRect(576, 262, 196, 128);
  SDL_Rect posRiver = newRect(736, 262, 196, 128);

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
                        afficherCarte(screen, cp.flop, posFlop);
                        afficherCarte(screen, cp.turn, posTurn);
                        afficherCarte(screen, cp.river, posRiver);

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

                        afficherCarte(screen, t[j].hand.carte1, posCarte1);
                        afficherCarte(screen, t[j].hand.carte2, posCarte2);

                        // while(!onPeutContinuer) {
                        //   //action du joueur : miseJeu(&t[j], &cp);
                        //
                        //   switch(event.type) {
                        //     // Si on clique sur la croix, on ferme la fenêtre
                        //     case SDL_QUIT:
                        //       continuer = 0;
                        //       return 0;
                        //       break;
                        //     case SDL_KEYDOWN:
                        //       onPeutContinuer = 1;
                        //       break;
                        //
                        //   }
                        // }
                        // onPeutContinuer = 0;

                        SDL_Delay(1000);

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
