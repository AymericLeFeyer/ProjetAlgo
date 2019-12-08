#include "../headers/score.h"

void highscore(tabP p){
  int i=0;
  int total=0;
  for (i=0;i<10;i++){
    total=p[i].scorePoker+p[i].scoreNavale+p[i].scoreLoto+p[i].scoreSudoku;
    total = total/4;
    p[i].scoreTotal=total;
    total=0;
  }

}
