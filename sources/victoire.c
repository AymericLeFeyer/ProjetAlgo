#include "../headers/structure.h"

int victoire(Joueur j){
  int i;int victoire=1;
  while(i<=4 && victoire==1){
    if(j.tab[i].pv>0){
      victoire=0;
    }else{
      i++;
    }
  }
  return victoire;
}
