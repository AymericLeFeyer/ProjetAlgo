#include "../headers/structure.h"
#include "../headers/scoreLoto.h"

Profil scoreLoto(int totalPunition, CaseLoto grille[9][3], Profil p)
{
  //on a le nombre total de punition du joueur qui est en entré (on ne prend que le nombre qui nous
  //interesse dans le tableau total punition dans la fonction loto.c)
  //on prend egalement uniquement la grille qui nous interesse
  //et le profil qui nous interesse
  int n = 0;       // compte les cases rempli par ligne
  int nbLigne = 0; //compte le nombre de lignes rempli par rapport a n
  int i, j;
  int score;

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (grille[j][i].val != -1 && grille[j][i].jeton == true)
      {
        n++;
      }
    }
    if (n == 5)
    {
      nbLigne++;
    }
    n = 0;
  }

  if (nbLigne == 3)
  {
    score = 100 - 5 * totalPunition;
  }
  else
  {
    score = 25 * nbLigne - 5 * totalPunition;
  }

  if (score > p.scoreLoto)
  {
    p.scoreLoto = score;
  }

  return p;
}
