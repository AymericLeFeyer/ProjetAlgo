#include "../../headers/global/structure.h"

//mise au jeu , suivre=memesomme , relance= mindouble de la memesomme, coucher=etat a 1
void miseJeu(JoueurPoker *j, CentrePlateau *p, int choix, int value)
{
  int a = 0;
  while (a == 0)
  {

    switch (choix)
    {
    case 1: //Suivre
      if (j->argent >= p->miseD)
      {
        suivre(j, p);
        a = 1;
      }
      else
      {
        tapis(j, p);
        a = 1;
      }
      break;
    case 2: //relance
      if (j->argent >= (p->miseD * 2))
      {
        relancer(j, p, value);
        a = 1;
      }
      break;
    case 3: // se coucher
      j->etat = 1;
      a = 1;
      break;
    case 4: //tapis

      tapis(j, p);
      a = 1;

      break;
    }
  }
}

void suivre(JoueurPoker *j, CentrePlateau *p)
{
  j->argent -= p->miseD;
  p->mise += p->miseD;
}

void relancer(JoueurPoker *j, CentrePlateau *p, int value)
{

  j->argent -= value;
  p->mise += value;
  p->miseD = value;
}

void tapis(JoueurPoker *j, CentrePlateau *p)
{
  if (p->miseD < j->argent)
    p->miseD = j->argent;
  p->mise += j->argent;
  j->argent -= j->argent;
}
