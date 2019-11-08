#include <stdio.h>
#include <stdlib.h>

void tourPartie(CentrePlateau cp, JoueurPoker* t, int nbJoueurs, int mancheTotale)
{
    int manche = 0, i, j, choix, continuer;
    while(manche < mancheTotale)
    {
        //Faire une boucle qui initialise l'état des joueurs à 0
        //Dès qu'une nouvelle manche demarre, tous les joueurs se "réveillent"
        for(i = 0; i < nbJoueurs; i++)
        {
            t[i].etat = 0;
        }
        for(i = 0; i < 4; i++)
        {
            //Parcourir tableau pour savoir si joueur j suit ou se couche
            /*for(j = 0; j < nbJoueurs; j++)
            {
                if(t[j].etat != 1)
                {
                    continuer = 1;
                    while(continuer == 1)
                    {
                        printf("Joueur %d, que voulez-vous faire ? (0: se coucher, 1: suivre ou 2: relance) ", t[j].joueur);
                        scanf("%d", &choix);
                        switch(choix)
                        {
                            //Se couche
                            case 0:
                            {
                                t[j].etat = 1;
                                continuer = 0;
                                break;
                            }
                            //Suivre
                            case 1:
                            {
                                continuer = 0;
                                break;
                            }
                            //Relance
                            case 2:
                            {
                              continuer = 0;
                              break;
                            }
                            //Choix incorrect
                            default:
                            {
                                printf("Choix incorrect, veuillez choisir => 0: se coucher, 1: suivre ou 2: relance !\n");
                            }
                        }
                    }
                }
            }*/
            switch(i)
            {
                //Tour 1
                case 0:
                {
                    cp.flop.visible = 1;
                    break;
                }
                //Tour 2
                case 1:
                {
                    cp.turn.visible = 1;
                    break;
                }
                //Tour 3
                case 2:
                {
                    cp.river.visible = 1;
                    break;
                }
                //Tour 4
                default:
                {

                }
            }
        }
        manche++;
    }
}
