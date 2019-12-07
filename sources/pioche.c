#include <time.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../headers/structure.h"
#include "../headers/pioche.h"



void initialisationPioche(Carte *pioche){ //initialise le talon puis le mélange dans la pioche
    ///entrée: pioche, le tableau de cartes correspondant à la pioche


    Carte talon[52];
    int a;
    //Initialisation de toutes les cartes dans un tableau de cartes temporaire
    int i, j, k=0;
    for (i = 1; i <= 4; i++) {
      for (j = 1; j <= 13; j++) {
        talon[k].couleur=i;
        talon[k].valeur=j;
        talon[k].visible=0;
        k++;
      }
    }
    // Initialisation des skins des cartes
    for (i = 0; i < 52; i++) {
      talon[i].dos = IMG_Load("assets/poker/cartes/dos.jpg");
    }

    // Skins en grand
    talon[0].skin = IMG_Load("assets/poker/cartes/2coeur.jpg");
    talon[1].skin = IMG_Load("assets/poker/cartes/3coeur.jpg");
    talon[2].skin = IMG_Load("assets/poker/cartes/4coeur.jpg");
    talon[3].skin = IMG_Load("assets/poker/cartes/5coeur.jpg");
    talon[4].skin = IMG_Load("assets/poker/cartes/6coeur.jpg");
    talon[5].skin = IMG_Load("assets/poker/cartes/7coeur.jpg");
    talon[6].skin = IMG_Load("assets/poker/cartes/8coeur.jpg");
    talon[7].skin = IMG_Load("assets/poker/cartes/9coeur.jpg");
    talon[8].skin = IMG_Load("assets/poker/cartes/10coeur.jpg");
    talon[9].skin = IMG_Load("assets/poker/cartes/valletCoeur.jpg");
    talon[10].skin = IMG_Load("assets/poker/cartes/dameCoeur.jpg");
    talon[11].skin = IMG_Load("assets/poker/cartes/roiCoeur.jpg");
    talon[12].skin = IMG_Load("assets/poker/cartes/asCoeur.jpg");

    talon[13].skin = IMG_Load("assets/poker/cartes/2carreau.jpg");
    talon[14].skin = IMG_Load("assets/poker/cartes/3carreau.jpg");
    talon[15].skin = IMG_Load("assets/poker/cartes/4carreau.jpg");
    talon[16].skin = IMG_Load("assets/poker/cartes/5carreau.jpg");
    talon[17].skin = IMG_Load("assets/poker/cartes/6carreau.jpg");
    talon[18].skin = IMG_Load("assets/poker/cartes/7carreau.jpg");
    talon[19].skin = IMG_Load("assets/poker/cartes/8carreau.jpg");
    talon[20].skin = IMG_Load("assets/poker/cartes/9carreau.jpg");
    talon[21].skin = IMG_Load("assets/poker/cartes/10carreau.jpg");
    talon[22].skin = IMG_Load("assets/poker/cartes/valletCarreau.jpg");
    talon[23].skin = IMG_Load("assets/poker/cartes/dameCarreau.jpg");
    talon[24].skin = IMG_Load("assets/poker/cartes/roiCarreau.jpg");
    talon[25].skin = IMG_Load("assets/poker/cartes/asCarreau.jpg");

    talon[26].skin = IMG_Load("assets/poker/cartes/2pique.jpg");
    talon[27].skin = IMG_Load("assets/poker/cartes/3pique.jpg");
    talon[28].skin = IMG_Load("assets/poker/cartes/4pique.jpg");
    talon[29].skin = IMG_Load("assets/poker/cartes/5pique.jpg");
    talon[30].skin = IMG_Load("assets/poker/cartes/6pique.jpg");
    talon[31].skin = IMG_Load("assets/poker/cartes/7pique.jpg");
    talon[32].skin = IMG_Load("assets/poker/cartes/8pique.jpg");
    talon[33].skin = IMG_Load("assets/poker/cartes/9pique.jpg");
    talon[34].skin = IMG_Load("assets/poker/cartes/10pique.jpg");
    talon[35].skin = IMG_Load("assets/poker/cartes/valletPique.jpg");
    talon[36].skin = IMG_Load("assets/poker/cartes/damePique.jpg");
    talon[37].skin = IMG_Load("assets/poker/cartes/roiPique.jpg");
    talon[38].skin = IMG_Load("assets/poker/cartes/asPique.jpg");

    talon[39].skin = IMG_Load("assets/poker/cartes/2trefle.jpg");
    talon[40].skin = IMG_Load("assets/poker/cartes/3trefle.jpg");
    talon[41].skin = IMG_Load("assets/poker/cartes/4trefle.jpg");
    talon[42].skin = IMG_Load("assets/poker/cartes/5trefle.jpg");
    talon[43].skin = IMG_Load("assets/poker/cartes/6trefle.jpg");
    talon[44].skin = IMG_Load("assets/poker/cartes/7trefle.jpg");
    talon[45].skin = IMG_Load("assets/poker/cartes/8trefle.jpg");
    talon[46].skin = IMG_Load("assets/poker/cartes/9trefle.jpg");
    talon[47].skin = IMG_Load("assets/poker/cartes/10trefle.jpg");
    talon[48].skin = IMG_Load("assets/poker/cartes/valletTrefle.jpg");
    talon[49].skin = IMG_Load("assets/poker/cartes/dameTrefle.jpg");
    talon[50].skin = IMG_Load("assets/poker/cartes/roiTrefle.jpg");
    talon[51].skin = IMG_Load("assets/poker/cartes/asTrefle.jpg");

    // Skins en petit
    talon[0].petit = IMG_Load("assets/poker/cartes/cartesSmall/2coeur.jpg");
    talon[1].petit = IMG_Load("assets/poker/cartes/cartesSmall/3coeur.jpg");
    talon[2].petit = IMG_Load("assets/poker/cartes/cartesSmall/4coeur.jpg");
    talon[3].petit = IMG_Load("assets/poker/cartes/cartesSmall/5coeur.jpg");
    talon[4].petit = IMG_Load("assets/poker/cartes/cartesSmall/6coeur.jpg");
    talon[5].petit = IMG_Load("assets/poker/cartes/cartesSmall/7coeur.jpg");
    talon[6].petit = IMG_Load("assets/poker/cartes/cartesSmall/8coeur.jpg");
    talon[7].petit = IMG_Load("assets/poker/cartes/cartesSmall/9coeur.jpg");
    talon[8].petit = IMG_Load("assets/poker/cartes/cartesSmall/10coeur.jpg");
    talon[9].petit = IMG_Load("assets/poker/cartes/cartesSmall/valletCoeur.jpg");
    talon[10].petit = IMG_Load("assets/poker/cartes/cartesSmall/dameCoeur.jpg");
    talon[11].petit = IMG_Load("assets/poker/cartes/cartesSmall/roiCoeur.jpg");
    talon[12].petit = IMG_Load("assets/poker/cartes/cartesSmall/asCoeur.jpg");

    talon[13].petit = IMG_Load("assets/poker/cartes/cartesSmall/2carreau.jpg");
    talon[14].petit = IMG_Load("assets/poker/cartes/cartesSmall/3carreau.jpg");
    talon[15].petit = IMG_Load("assets/poker/cartes/cartesSmall/4carreau.jpg");
    talon[16].petit = IMG_Load("assets/poker/cartes/cartesSmall/5carreau.jpg");
    talon[17].petit = IMG_Load("assets/poker/cartes/cartesSmall/6carreau.jpg");
    talon[18].petit = IMG_Load("assets/poker/cartes/cartesSmall/7carreau.jpg");
    talon[19].petit = IMG_Load("assets/poker/cartes/cartesSmall/8carreau.jpg");
    talon[20].petit = IMG_Load("assets/poker/cartes/cartesSmall/9carreau.jpg");
    talon[21].petit = IMG_Load("assets/poker/cartes/cartesSmall/10carreau.jpg");
    talon[22].petit = IMG_Load("assets/poker/cartes/cartesSmall/valletCarreau.jpg");
    talon[23].petit = IMG_Load("assets/poker/cartes/cartesSmall/dameCarreau.jpg");
    talon[24].petit = IMG_Load("assets/poker/cartes/cartesSmall/roiCarreau.jpg");
    talon[25].petit = IMG_Load("assets/poker/cartes/cartesSmall/asCarreau.jpg");

    talon[26].petit = IMG_Load("assets/poker/cartes/cartesSmall/2pique.jpg");
    talon[27].petit = IMG_Load("assets/poker/cartes/cartesSmall/3pique.jpg");
    talon[28].petit = IMG_Load("assets/poker/cartes/cartesSmall/4pique.jpg");
    talon[29].petit = IMG_Load("assets/poker/cartes/cartesSmall/5pique.jpg");
    talon[30].petit = IMG_Load("assets/poker/cartes/cartesSmall/6pique.jpg");
    talon[31].petit = IMG_Load("assets/poker/cartes/cartesSmall/7pique.jpg");
    talon[32].petit = IMG_Load("assets/poker/cartes/cartesSmall/8pique.jpg");
    talon[33].petit = IMG_Load("assets/poker/cartes/cartesSmall/9pique.jpg");
    talon[34].petit = IMG_Load("assets/poker/cartes/cartesSmall/10pique.jpg");
    talon[35].petit = IMG_Load("assets/poker/cartes/cartesSmall/valletPique.jpg");
    talon[36].petit = IMG_Load("assets/poker/cartes/cartesSmall/damePique.jpg");
    talon[37].petit = IMG_Load("assets/poker/cartes/cartesSmall/roiPique.jpg");
    talon[38].petit = IMG_Load("assets/poker/cartes/cartesSmall/asPique.jpg");

    talon[39].petit = IMG_Load("assets/poker/cartes/cartesSmall/2trefle.jpg");
    talon[40].petit = IMG_Load("assets/poker/cartes/cartesSmall/3trefle.jpg");
    talon[41].petit = IMG_Load("assets/poker/cartes/cartesSmall/4trefle.jpg");
    talon[42].petit = IMG_Load("assets/poker/cartes/cartesSmall/5trefle.jpg");
    talon[43].petit = IMG_Load("assets/poker/cartes/cartesSmall/6trefle.jpg");
    talon[44].petit = IMG_Load("assets/poker/cartes/cartesSmall/7trefle.jpg");
    talon[45].petit = IMG_Load("assets/poker/cartes/cartesSmall/8trefle.jpg");
    talon[46].petit = IMG_Load("assets/poker/cartes/cartesSmall/9trefle.jpg");
    talon[47].petit = IMG_Load("assets/poker/cartes/cartesSmall/10trefle.jpg");
    talon[48].petit = IMG_Load("assets/poker/cartes/cartesSmall/valletTrefle.jpg");
    talon[49].petit = IMG_Load("assets/poker/cartes/cartesSmall/dameTrefle.jpg");
    talon[50].petit = IMG_Load("assets/poker/cartes/cartesSmall/roiTrefle.jpg");
    talon[51].petit = IMG_Load("assets/poker/cartes/cartesSmall/asTrefle.jpg");

    //mélange des cartes dans la vraie pioche
    a=shuffle(talon,52,pioche);
    for (int i = 0; i < a; i++) {
      SDL_FreeSurface(talon[i].dos);
      SDL_FreeSurface(talon[i].skin);
      SDL_FreeSurface(talon[i].petit);
    }
}


int shuffle(Carte* talon,int tailleTalon,Carte* pioche){ //permet de mélanger le talon dans la pioche
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
    return tailleTalon;
}

//fais piocher toutes les cartes necessaires au deroulement d'une manche
CentrePlateau piocher(Carte *pioche, int taillePioche, JoueurPoker* j, CentrePlateau centre, int nombreJoueurs){
    for (int i = 0; i < nombreJoueurs; i++) { //distribution des premières cartes des joueurs
      j[i].joueur = i + 1;
      j[i].hand.carte1=pioche[taillePioche-1];
      j[i].hand.carte1.visible = 1;
      taillePioche -=1;
    }
    for (int i = 0; i < nombreJoueurs; i++) { //distribution des secondes cartes des joueurs
      j[i].hand.carte2=pioche[taillePioche-1];
      j[i].hand.carte2.visible = 1;
      taillePioche -=1;
    }
    centre.flop1=pioche[taillePioche-1];
    taillePioche -=1;
    centre.flop2=pioche[taillePioche-1];
    taillePioche -=1;
    centre.flop3=pioche[taillePioche-1];
    taillePioche -=1;
    centre.turn=pioche[taillePioche-1];
    taillePioche -=1;
    centre.river=pioche[taillePioche-1];
    taillePioche -=1;
    return centre;
}

//initialise tout pour une partie de poker, a refaire a chaque manche
CentrePlateau initialisePoker(JoueurPoker* j, int nbJoueurs, int argentDepart, int premiereManche, int miseInit){
  CentrePlateau centre;
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
  if (premiereManche==0) {
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
  return centre;
}

CentrePlateau libererPoker(JoueurPoker* t,int nbJoueurs,CentrePlateau cp){
  for (int i = 0; i < nbJoueurs; i++) {
    SDL_FreeSurface(t[i].hand.carte1.dos);
    SDL_FreeSurface(t[i].hand.carte1.petit);
    SDL_FreeSurface(t[i].hand.carte1.skin);
    SDL_FreeSurface(t[i].hand.carte2.dos);
    SDL_FreeSurface(t[i].hand.carte2.petit);
    SDL_FreeSurface(t[i].hand.carte2.skin);
  }
  SDL_FreeSurface(cp.river.dos);
  SDL_FreeSurface(cp.river.skin);
  SDL_FreeSurface(cp.river.petit);
  SDL_FreeSurface(cp.flop1.dos);
  SDL_FreeSurface(cp.flop1.skin);
  SDL_FreeSurface(cp.flop1.petit);
  SDL_FreeSurface(cp.flop2.dos);
  SDL_FreeSurface(cp.flop2.skin);
  SDL_FreeSurface(cp.flop2.petit);
  SDL_FreeSurface(cp.flop3.dos);
  SDL_FreeSurface(cp.flop3.skin);
  SDL_FreeSurface(cp.flop3.petit);
  SDL_FreeSurface(cp.turn.dos);
  SDL_FreeSurface(cp.turn.skin);
  SDL_FreeSurface(cp.turn.petit);
  return cp;
}
