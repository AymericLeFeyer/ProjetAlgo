#include "../../headers/global/structure.h"
#include "../../headers/profils/score.h"
#include "../../headers/profils/chargement.h"
#include "../../headers/profils/sauvegarde.h"

void highscore()
{
  tabP p;
  chargementProfils(p);
  int i = 0;
  int total = 0;
  for (i = 0; i < 10; i++)
  {
    if (p[i].scoreTotal != -1)
    {
      total = p[i].scorePoker + p[i].scoreNavale + p[i].scoreLoto + p[i].scoreSudoku;
      total = total / 4;
      p[i].scoreTotal = total;
      total = 0;
    }
  }
  sauvegardeProfils(p);
}
