#include <stdio.h>
#include <stdlib.h>

void sauvegardeNavale(Joueur j)
{
    int i, j;
    FILE *f;
    f = fopen("partieNavale.txt", "w");
    if(f != NULL)
    {
        for(i = 0; i <= j.g.h-1; i++)
        {
            for(j = 0; j <= j.g.l-1; j++)
            {
              fprintf(f, "%d ", j.g.tab[i][j]); //sauvegarde la grille du joueur
            }
            fprintf(f, "\n"); //permet de mettre "sous forme" de tableau dans le fichier sauvegarde
        }
        for(i = 0; i <= 4; i++)
        {
          fprintf(f, "%d", j.tab[i]); //sauvegarde la grille des bateaux du joueur
        }
        fprintf(f, "%d\n", j.score);
        fprintf(f, "%d\n", j.joueur); //état du joueur (1 ou 2)
        fclose(f);
    }
    else printf("Erreur de sauvegarde\n");
}

//----------
