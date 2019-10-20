#include "headers/pioche.h"

void initialisationPioche(Carte *pioche){ //initialise le talon puis le mélange dans la pioche
    ///entrée: pioche, le tableau de cartes correspondant à la pioche


    Carte talon[52];

    //Initialisation de toutes les cartes dans un tableau de cartes temporaire
    int i, j, k=0;
    for (i = 1; i < 4; i++) {
      for (j = 1; j < 13; j++) {
        talon[k].couleur=i;
        talon[k].valeur=j;
        k++;
      }
    }
    //mélange des cartes dans la vraie pioche
    tailleTalon=shuffle(talon,52,pioche);
}


void shuffle(Carte* talon,int tailleTalon,Carte* pioche){ //permet de mélanger le talon dans la pioche
    ///entrée: talon, le tableau de Cartes correspondant au talon; tailleTalon , le nombre de cartes présents dans le talon; pioche, le tableau de cartes correspondant à la pioche
int i,j,k,a=tailleTalon;

for(i=0;i<a;i++){

        j=rand()%tailleTalon;
        pioche[i]=talon[j];
        for(k=j;k<tailleTalon-1;k++){
            talon[k]=talon[k+1];
        }
        talon[tailleTalon-1].couleur=-1;  //
        talon[tailleTalon-1].valeur=-1;   //   mise en place d'une carte inexistante à la fin du talon
        tailleTalon=tailleTalon-1;
    }
}

JoueurPoker piocher(Carte *pioche, int* taillePioche, JoueurPoker j, int nCarte){ // permet de piocher une carte
    j.main.carte1=pioche[*taillePioche-1];
    *nbCarte +=1;
    *taillePioche -=1;
}
