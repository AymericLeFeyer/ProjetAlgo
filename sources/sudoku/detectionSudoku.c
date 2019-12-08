#include <stdio.h>
#include <stdlib.h>
#include "../../headers/global/structure.h"
#include "../../headers/sudoku/detectionSudoku.h"

int detection(Coord c, JoueurSudoku j)
{
  //Stocke la valeur qu'on vient de mettre dans le tableau
  int n = j.g.tab[c.x][c.y];
  //Si on retourne 0, cela veut dire que ce n'est pas possible
  //Sinon, la valeur peut être ajoutée dans la grille de Sudoku
  if (detectionLigne(c, j, n) == 0)
  {
    printf("Erreur Ligne\n");
    return 0;
  }
  if (detectionColonne(c, j, n) == 0)
  {
    printf("Erreur Colonne\n");
    return 0;
  }
  if (detectionChunk(c, j, n) == 0)
  {
    printf("Erreur Chunk\n");
    return 0;
  }
  return 1;
}

int detectionLigne(Coord c, JoueurSudoku j, int n)
{
  int cpt = 0;
  for (int jj = 0; jj < 9; jj++)
  {
    if (j.g.tab[c.x][jj] == n)
    {
      cpt++;
    }
  }
  if (cpt > 1)
  {
    return 0;
  }
  return 1;
}

int detectionColonne(Coord c, JoueurSudoku j, int n)
{
  int cpt = 0;
  for (int i = 0; i < 9; i++)
  {
    if (j.g.tab[i][c.y] == n)
    {
      cpt++;
    }
  }
  if (cpt > 1)
  {
    return 0;
  }
  return 1;
}

int detectionChunk(Coord c, JoueurSudoku j, int n)
{
  int cpt = 0;

  int cx = c.x / 3;
  int cy = c.y / 3;

  for (int i = 3; i < 3; i++)
  {
    for (int k = 3; k < 3; k++)
    {
      if (j.g.tab[cx + i][cy + k] == n)
      {
        cpt++;
      }
    }
  }
  if (cpt > 1)
    return 0;
  return 1;

  //chunk t;
  //Ici on a besoin de savoir quel "grand carré" se trouve la valeur
  //On considère que les grands carrés sont définis par le modul0 3 de c.x et c.y allant dont les valeurs vont de 0 à 2
  //Une fois les "corrdonnées" du "grand carré" trouvées, on initalise un tableau 3x3 pour pouvoir faciliter les recherches
  //Et on fera après la vérification
  //   switch(c.x%3)
  //   {
  //     //0
  //     case 0:
  //     {
  //       switch(c.y%3)
  //       {
  //         //0.0
  //         case 0:
  //         {
  //           iniChunk(j, t, 0, 0);
  //           break;
  //         }
  //         //0.1
  //         case 1:
  //         {
  //           iniChunk(j, t, 0, 3);
  //           break;
  //         }
  //         //0.2
  //         case 2:
  //         {
  //           iniChunk(j, t, 0, 5);
  //           break;
  //         }
  //         default:
  //         {
  //
  //         }
  //       }
  //       break;
  //     }
  //     //1
  //     case 1:
  //     {
  //       switch(c.y%3)
  //       {
  //         //1.0
  //         case 0:
  //         {
  //           iniChunk(j, t, 3, 0);
  //           break;
  //         }
  //         //1.1
  //         case 1:
  //         {
  //           iniChunk(j, t, 3, 3);
  //           break;
  //         }
  //         //1.2
  //         case 2:
  //         {
  //           iniChunk(j, t, 3, 6);
  //           break;
  //         }
  //         default:
  //         {
  //
  //         }
  //       }
  //       break;
  //     }
  //     //2
  //     case 2:
  //     {
  //       switch(c.y%3)
  //       {
  //         //2.0
  //         case 0:
  //         {
  //           iniChunk(j, t, 6, 0);
  //           break;
  //         }
  //         //2.1
  //         case 1:
  //         {
  //           iniChunk(j, t, 6, 3);
  //           break;
  //         }
  //         //2.2
  //         case 2:
  //         {
  //           iniChunk(j, t, 6, 6);
  //           break;
  //         }
  //         default:
  //         {
  //
  //         }
  //       }
  //       break;
  //     }
  //     default:
  //     {
  //
  //     }
  //   }
  //   for(int x = 0; x < 3; x++)
  //   {
  //     for(int y = 0; y < 3; y++)
  //     {
  //       if(t[x][y] == n)
  //       {
  //         cpt++;
  //       }
  //     }
  //   }
  //   if(cpt > 1)
  //   {
  //     return 0;
  //   }
  // return 1;
}

void iniChunk(JoueurSudoku j, chunk t, int lig, int col)
{
  int temp = col;
  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      t[x][y] = j.g.tab[lig][col];
      col++;
    }
    //On passe à la ligne suivante et on remet col à sa valeur initiale
    lig++;
    col = temp;
  }
}
