#include <stdio.h>
#include <stdlib.h>

#include "../headers/structure.h"

void chargementProfils(tabP p) //on mettra en paramètre l'état du joueur pour lequel on veut charger ses infos
{
  FILE *f;
  f = fopen("profils.txt", "r");
  if(f)
  {
    for(int i = 0; i < 10; i++)
    {
      fscanf(f, "%s ", p[i].nom);
      fscanf(f, "%d ", &p[i].scoreNavale);
      fscanf(f, "%d ", &p[i].scorePoker);
      fscanf(f, "%d ", &p[i].scoreLoto);
      fscanf(f, "%d ", &p[i].scoreSudoku);
      fscanf(f, "%d ", &p[i].scoreLoto);
    }
    fclose(f);
  }
    else printf("Erreur de chargement\n");
}
