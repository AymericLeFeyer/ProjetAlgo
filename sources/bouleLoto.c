#include <time.h>
#include "../headers/bouleLoto.h"

void initialisationLoto(int* tasBoules){
    int talon[90];
    //Initialisation de toutes les cartes dans un tableau de cartes temporaire
    int i;
    for (i = 0; i <= 89; i++) {
      talon[i]=i+1;
    }
    //mélange des cartes dans la vraie pioche
    shuffleLoto(talon,90,tasBoules);
}

void shuffleLoto(int* talon,int tailleTalon,int* tasBoules){
int i,j,k,a=tailleTalon;

for(i=0;i<a;i++){

        //j=rand()%tailleTalon;
        tasBoules[i]=talon[j];
        for(k=j;k<tailleTalon-1;k++){
            tasBoules[k]=talon[k+1];
        }
        talon[tailleTalon-1]=0;
        tailleTalon=tailleTalon-1;
    }
}

//tire un nombre au hazard dans la pile de nombres
int prendreNombre(int *taille,int* tasBoules){
  *taille=*taille-1;
  if(*taille<0){
    return -1;
  }else{
    return tasBoules[*taille];
  }
}

//retourne 1 si le nombre tiré est dans la grille, 0 sinon
int nombreDansGrille(int grille [9][3],int nombre){
  int a=0,i=0,j=0;
  while (a==0 && i<=8) {
    j=0;
    while (a==0 && j<=2) {
      if(grille[i][j]==nombre){
        a=1;
      }
      j++;
    }
    i++;
  }
  return a;
}
