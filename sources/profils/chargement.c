#include <stdio.h>
#include <stdlib.h>

#include "../../headers/global/structure.h"

void chargementProfils(tabP p) //On passe en paramètre le tableau de profils vierge qui va récupérer les informations dans profils.txt
{
  FILE *f;
  f = fopen("profils.txt", "r");
  //Si on arrive à accèder à profils.txt, on récupére toutes les informations pour les mettre dans le tableau p
  if (f)
  {
    for (int i = 0; i < 10; i++)
    {
      fscanf(f, "%s ", p[i].nom);
      fscanf(f, "%d ", &p[i].ID);
      fscanf(f, "%f ", &p[i].scoreNavale);
      fscanf(f, "%f ", &p[i].scorePoker);
      fscanf(f, "%f ", &p[i].scoreLoto);
      fscanf(f, "%f ", &p[i].scoreSudoku);
      fscanf(f, "%f ", &p[i].scoreTotal);
    }
    fclose(f);
  }
  else
    printf("Erreur de chargement\n");
}
