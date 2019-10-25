#include "../headers/pioche.h"


void initialisationPioche(Carte *pioche){ //initialise le talon puis le mélange dans la pioche
    ///entrée: pioche, le tableau de cartes correspondant à la pioche


    Carte talon[52];

    //Initialisation de toutes les cartes dans un tableau de cartes temporaire
    int i, j, k=0;
    for (i = 1; i < 4; i++) {
      for (j = 1; j < 13; j++) {
        talon[k].couleur=i;
        talon[k].valeur=j;
        talon[k].visible=0;
        k++;
      }
    }
    //mélange des cartes dans la vraie pioche
    shuffle(talon,52,pioche);
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


CentrePlateau piocher(Carte *pioche, int* taillePioche, JoueurPoker* j, CentrePlateau centre, int nombreJoueurs){ // permet de piocher une carte
    for (int i = 0; i < nombreJoueurs; i++) { //distribution des premières cartes des joueurs
      j[i].hand.carte1=pioche[*taillePioche-1];
      *taillePioche -=1;
    }
    for (int i = 0; i < nombreJoueurs; i++) { //distribution des secondes cartes des joueurs
      j[i].hand.carte2=pioche[*taillePioche-1];
      *taillePioche -=1;
    }
    centre.flop=pioche[*taillePioche-1];
    *taillePioche -=1;
    centre.turn=pioche[*taillePioche-1];
    *taillePioche -=1;
    centre.river=pioche[*taillePioche-1];
    *taillePioche -=1;
    return centre;
}

void initialisePoker(JoueurPoker* j, CentrePlateau centre, int nbJoueurs, int argentDepart, int premiereManche, int miseInit){
  Carte pioche[52];
  centre.mise=0;
  initialisationPioche(pioche);
  centre=piocher(pioche,52,j,centre,nbJoueurs);
  for (int i = 0; i < nbJoueurs; i++) {
    j[i].etat=0;
  }
  for (int i = 0; i < nbJoueurs; i++) {
    j[i].amiser=0;
  }
  if (premiereManche) {
    for (int i = 0; i < nbJoueurs; i++) {
      j[i].argent=argentDepart-miseInit;
    }
    centre.mise=nbJoueurs*miseInit;
  }else{
    for (int i = 0; i < nbJoueurs; i++) {
      if(j[i].argent>=miseInit){
        j[i].argent-=miseInit;
        centre.mise+=miseInit;
      }else{
        j[i].etat=1;
      }
    }
  }
  centre.miseD=miseInit;
}
