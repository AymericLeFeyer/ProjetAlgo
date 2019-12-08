#include <stdio.h>
#include <stdlib.h>

#include "../../headers/global/structure.h"

void sauvegardeProfils(tabP p) //On passe le tableau de profils en paramètre
{
  FILE *f;
  f = fopen("profils.txt", "w"); //Si le fichier "profils.txt" a été créé et possède des valeurs, il sera écrasé
  if (f)                         //Si le  fichier a bien été créé, on sauvegarde toutes les informations des profils
  {
    for (int i = 0; i < 10; i++)
    {
      fprintf(f, "%s ", p[i].nom);
      fprintf(f, "%d ", p[i].ID);
      fprintf(f, "%f ", p[i].scoreNavale);
      fprintf(f, "%f ", p[i].scorePoker);
      fprintf(f, "%f ", p[i].scoreLoto);
      fprintf(f, "%f ", p[i].scoreSudoku);
      fprintf(f, "%f\n", p[i].scoreTotal);
    }
    fclose(f);
  }
  else
    printf("Erreur de sauvegarde\n");
}

//----------
