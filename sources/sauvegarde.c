#include <stdio.h>
#include <stdlib.h>

#include "../headers/structure.h"

void sauvegardeProfils(tabP p)
{
  FILE *f;
  f = fopen("profils.txt", "w");
  if(f)
  {
    for(int i = 0; i < 10; i++)
    {
      fprintf(f, "%s ", p[i].nom);
      fprintf(f, "%f ", p[i].scoreNavale);
      fprintf(f, "%f ", p[i].scorePoker);
      fprintf(f, "%f ", p[i].scoreLoto);
      fprintf(f, "%f ", p[i].scoreSudoku);
      fprintf(f, "%f\n", p[i].scoreTotal);
    }
      fclose(f);
  }
  else printf("Erreur de sauvegarde\n");
}

//----------
