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
      fprintf(f, "%d ", p[i].scoreNavale);
      fprintf(f, "%d ", p[i].scorePoker);
      fprintf(f, "%d ", p[i].scoreLoto);
      fprintf(f, "%d ", p[i].scoreSudoku);
      fprintf(f, "%d\n ", p[i].scoreTotal);
    }
      fclose(f);
  }
  else printf("Erreur de sauvegarde\n");
}

//----------
