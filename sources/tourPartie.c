#include <stdio.h>
#include <stdlib.h>
#include "../headers/structure.h"
#include "../headers/tourPartie.h"
#include "../headers/pioche.h"
#include "../headers/mainsPoker.h"


void tourPartie(CentrePlateau cp, JoueurPoker* t, int nbJoueurs, int mancheTotale,int argentDepart, int miseDepart)
{
    int manche = 0, i, j, k, max=0,maxi;
    while(manche < mancheTotale)
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
                        miseJeu(&t[j], &cp);
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
