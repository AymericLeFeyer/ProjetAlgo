#include <stdio.h>
#include <stdlib.h>

#include "../headers/structure.h"

void sauvegardeNavale(Joueur j) //on mettra en paramètre le joueur pour lequel on veut sauvegarder ses infos
{
    int x, y;
    FILE *f;
    if(j.joueur == 1)
    {
        f = fopen("partieNavale1.txt", "w"); //créer un fichier où toutes les infos du joueur 1
    }
    else
    {
        f = fopen("partieNavale2.txt", "w"); //créer un fichier où toutes les infos du joueur 2
    }
    if(f != NULL)
    {
      fprintf(f, "%d ", j.joueur); //état du joueur (1 ou 2)
      fprintf(f, "%d ", j.score); //score du joueur
      for(x = 0; x < 10; x++)
      {
          for(y = 0; y < 10; y++)
          {
            fprintf(f, "%d ", j.g.tab[x][y]); //sauvegarde la grille du joueur
          }
      }
      for(x = 0; x <= 4; x++)
      {
        fprintf(f, "%d ", j.tab[x].direction); //sauvegarde la direction des bateaux
        fprintf(f, "%d ", j.tab[x].pv); //sauvegarde des pv des bateaux
        fprintf(f, "%d ", j.tab[x].taille); //sauvegarde la taille des bateaux
        fprintf(f, "%d ", j.tab[x].tete.x); //sauvegarde la tête des bateaux (abscisse)
        fprintf(f, "%d ", j.tab[x].tete.y); //sauvegarde la tête des bateaux (ordonné)
      }
      fclose(f);
    }
    else printf("Erreur de sauvegarde\n");
}

//----------
