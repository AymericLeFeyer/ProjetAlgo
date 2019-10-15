#include <stdio.h>
#include <stdlib.h>

#include "../headers/structure.h"

void sauvegardeNavale(Joueur J)
{
    int i, j;
    FILE *f;
    f = fopen("partieNavale.txt", "w");
    if(f != NULL)
    {
        for(i = 0; i <= J.g.h-1; i++)
        {
            for(j = 0; j <= J.g.l-1; j++)
            {
              fprintf(f, "%d ", J.g.tab[i][j]); //sauvegarde la grille du joueur
            }
            fprintf(f, "\n"); //permet de mettre "sous forme" de tableau dans le fichier sauvegarde
        }
        for(i = 0; i <= 4; i++)
        {
          fprintf(f, "%d", J.tab[i]); //sauvegarde la grille des bateaux du joueur
        }
        fprintf(f, "%d\n", J.score);
        fprintf(f, "%d\n", J.joueur); //état du joueur (1 ou 2)
        fclose(f);
    }
    else printf("Erreur de sauvegarde\n");
}

//----------
