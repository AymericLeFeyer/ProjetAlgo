#include <stdio.h>
#include <stdlib.h>

typedef structure
{
  Grille g
  Grille s
  int nbErreurs;
}JoueurSudoku

int detection(Coord c, JoueurSudoku j)
{
  int n = j.g.tab[c.x][c.y];
  //Ligne
  for(int x = 0; x < c.x; x++)
  {
    if(j.g.tab[x][c.y] == n)
    {
      return 0;
    }
  }
  for(int x = c.x+1; x < 10; x++)
  {
    if(j.g.tab[x][c.y] == n)
    {
      return 0;
    }
  }
  //Colonne
  for(int y = 0; y < c.y; y++)
  {
    if(j.g.tab[c.x][y] == n)
    {
      return 0;
    }
  }
  for(int y = c.y+1; y < 10; y++)
  {
    if(j.g.tab[c.x][y] == n)
    {
      return 0;
    }
  }
  //Carré
  //Stocker division et modulo 
  switch(c.x)
  {
    case
  }
  if(c.x < 3)
  {

  }
  if(c.x < 6)
  {

  }
  if(c.x )

}
