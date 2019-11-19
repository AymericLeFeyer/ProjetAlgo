#include "grilleLoto.h"

//génération d'une grille de loto
void carteLoto (CaseLoto t[9][3]){ //un tableau de case
  int n=0; //nombre de chiffre total
  int i,j,k;
  int nbNombresLigne; //nb de chiffres sur une ligne
  for (i=0; i<9; i++){  //initialisation de la grille a -1 (aucun nombres)
    for (j=0; j<3; j++){
      t[i][j].val=-1;
    }
  }
  while (n!=15){
    i=rand()%8;
    j=rand()%2;
    nbNombresLigne=0; //Pour vériffier si le nombre de chiffre sur la ligne ne dépasse pas 15
    for(k=0;k<9;k++){
      if(t[k][j].val!=-1){
         nbNombresLigne++;
      }
    }
    if(t[i][j].val==-1 && nbNombresLigne<5){ //alors on met un chiffre dans la grille
      //vérifications pour les chiffre aléatoire :
      if(j==0){
        t[i][j].val=(rand()%(3-1)+1)+10*i;
        n++;
      }
      else{
        if(j==1){
          t[i][j].val=(rand()%(7-4)+4)+10*i;
          n++;
        }
        else{
          if(j==2){
            t[i][j].val=(rand()%(10-8)+8)+10*i;
            n++;
          }
        }
      }

    }

  }

}


int nbJetons (CaseLoto t[9][3]){
  int i,j;
  int nb=0;
  for(i=0;i<9;i++){
    for(j=0;j<3;j++){
      if(t[i][j].jeton==true){
        nb++;
      }
    }
  }
  return nb;
}
