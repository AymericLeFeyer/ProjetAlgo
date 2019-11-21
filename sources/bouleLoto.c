#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include "../headers/structure.h"
#include "../headers/bouleLoto.h"
#include "../headers/grilleLoto.h"

int appartient(int n,int t[90]){
  int a=0;
  for (int i = 0; i < 90; i++) {
    if(t[i]==n){
      a=1;
    }
  }
  return a;
}

int initialisationLoto(int tasBoules[90],int nbJoueurs, CaseLoto g1[9][3], CaseLoto g2[9][3], CaseLoto g3[9][3], CaseLoto g4[9][3]){
    int talon[90]={0};
    int k=0;
    int a;
    carteLoto(g1);
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 3; j++) {
        if(g1[i][j].val>0 && appartient(g1[i][j].val,talon)==0){
          talon[k]=g1[i][j].val;
          k++;
        }
      }
    }
    if (nbJoueurs>=2) {
      carteLoto(g2);
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
          if(g2[i][j].val>0 && appartient(g2[i][j].val,talon)==0){
            talon[k]=g2[i][j].val;
            k++;
          }
        }
      }
    }else{
      grilleVide(g2);
    }
    if (nbJoueurs>=3) {
      carteLoto(g3);
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
          if(g3[i][j].val>0 && appartient(g3[i][j].val,talon)==0){
            talon[k]=g3[i][j].val;
            k++;
          }
        }
      }
    }else{
      grilleVide(g3);
    }
    if (nbJoueurs==4) {
      carteLoto(g4);
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
          if(g4[i][j].val>0 && appartient(g4[i][j].val,talon)==0){
            talon[k]=g4[i][j].val;
            k++;
          }
        }
      }
    }else{
      grilleVide(g4);
    }
    for (int i = 0; i < 10; i++) {
      a=rand()%((90-1)+1);
      while (appartient(a,talon)==1) {
        a=rand()%((90-1)+1);
      }
      talon[k]=a;
      k++;
    }
    shuffleLoto(talon,k,tasBoules);
    return k;
}

void shuffleLoto(int* talon,int tailleTalon,int* tasBoules){
int i,j,k,a=tailleTalon;

for(i=0;i<a;i++){
        j=rand()%tailleTalon;
        tasBoules[i]=talon[j];
        for(k=j;k<tailleTalon-1;k++){
            talon[k]=talon[k+1];
        }
        talon[tailleTalon-1]=-1;
        tailleTalon=tailleTalon-1;
    }
}

//tire un nombre au hazard dans la pile de nombres
int prendreNombre(int *taille,int* tasBoules){
  int a;

  if(*taille<=0){
    a=-1;
  }else{
    a=tasBoules[*taille-1];
    *taille=*taille-1;
  }
  return a;
}

//retourne 1 si le nombre tiré est dans la grille, 0 sinon
int nombreDansGrille(CaseLoto grille [9][3],int nombre){
  int a=0,i=0,j=0;
  while (a==0 && i<=8) {
    j=0;
    while (a==0 && j<=2) {
      if(grille[i][j].val==nombre){
        a=1;
      }
      j++;
    }
    i++;
  }
  return a;
}
