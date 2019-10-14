#include <stdio.h>
#include <stdlib.h>

#include "headers/structure.h"

Joueur chargeNavale(int joueur) //on mettra en paramètre l'état du joueur pour lequel on veut charger ses infos
{
    Joueur j;
    int x, y;
    FILE *f;
    if(joueur == 1)
    {
        f = fopen("partieNavale1.txt", "r");
    }
    else
    {
        f = fopen("partieNavale2.txt", "r");
    }
    if(f != NULL)
    {
      fscanf(f, "%d ", &j.joueur);
      fscanf(f, "%d ", &j.score);
      for(x = 0; x < 10; x++)
      {
          for(y = 0; y < 10; y++)
          {
            fscanf(f, "%d ", &j.g.tab[x][y]);
          }
      }
      for(x = 0; x <= 4; x++)
      {
        fscanf(f, "%d", &j.tab[x].direction);
        fscanf(f, "%d", &j.tab[x].pv);
        fscanf(f, "%d", &j.tab[x].taille);
        fscanf(f, "%d", &j.tab[x].tete.x);
        fscanf(f, "%d", &j.tab[x].tete.y);
      }
      fclose(f);
      return j;
    }
    else printf("Erreur de sauvegarde\n");
}
