#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../headers/structure.h"
#include "../headers/shortcuts.h"
#include "../headers/constantes.h"

//permet d'initialiser un joueur pour la bataille navale
JoueurBatailleNavale initJoueurBN(int nJoueur, int h, int l){
  JoueurBatailleNavale j;
  j.joueur=nJoueur;

//images des différents bateaux avec leurs directions
  j.tab[0].nord = IMG_Load("assets/batailleNavale/bateau1-1.png");
  j.tab[1].nord = IMG_Load("assets/batailleNavale/bateau2-1.png");
  j.tab[2].nord = IMG_Load("assets/batailleNavale/bateau3-1.png");
  j.tab[3].nord = IMG_Load("assets/batailleNavale/bateau4-1.png");
  j.tab[4].nord = IMG_Load("assets/batailleNavale/bateau5-1.png");
  j.tab[0].west = IMG_Load("assets/batailleNavale/bateau1-2.png");
  j.tab[1].west = IMG_Load("assets/batailleNavale/bateau2-2.png");
  j.tab[2].west = IMG_Load("assets/batailleNavale/bateau3-2.png");
  j.tab[3].west = IMG_Load("assets/batailleNavale/bateau4-2.png");
  j.tab[4].west = IMG_Load("assets/batailleNavale/bateau5-2.png");
  j.tab[0].sud = IMG_Load("assets/batailleNavale/bateau1-3.png");
  j.tab[1].sud = IMG_Load("assets/batailleNavale/bateau2-3.png");
  j.tab[2].sud = IMG_Load("assets/batailleNavale/bateau3-3.png");
  j.tab[3].sud = IMG_Load("assets/batailleNavale/bateau4-3.png");
  j.tab[4].sud = IMG_Load("assets/batailleNavale/bateau5-3.png");
  j.tab[0].est = IMG_Load("assets/batailleNavale/bateau1-4.png");
  j.tab[1].est = IMG_Load("assets/batailleNavale/bateau2-4.png");
  j.tab[2].est = IMG_Load("assets/batailleNavale/bateau3-4.png");
  j.tab[3].est = IMG_Load("assets/batailleNavale/bateau4-4.png");
  j.tab[4].est = IMG_Load("assets/batailleNavale/bateau5-4.png");

  j.tab[0].r = newRect(10, 10, 128, 64);
  j.tab[1].r = newRect(10, 200, 192, 64);
  j.tab[2].r = newRect(10, 400, 192, 64);
  j.tab[3].r = newRect(100, 10, 256, 64);
  j.tab[4].r = newRect(100, 280, 320, 64);

//tailles correspondant aux bateaux
  j.tab[0].taille = 2;
  j.tab[1].taille = 3;
  j.tab[2].taille = 3;
  j.tab[3].taille = 4;
  j.tab[4].taille = 5;

  j.tab[0].pv = j.tab[0].taille;
  j.tab[1].pv = j.tab[1].taille;
  j.tab[2].pv = j.tab[2].taille;
  j.tab[3].pv = j.tab[3].taille;
  j.tab[4].pv = j.tab[4].taille;

//vers le nord, direction pas defaut
  j.tab[0].direction = 1;
  j.tab[1].direction = 1;
  j.tab[2].direction = 1;
  j.tab[3].direction = 1;
  j.tab[4].direction = 1;

//position par défaut car pas dans le tableau a la base
  j.tab[0].tete.x=-1;
  j.tab[0].tete.y=-1;
  j.tab[1].tete.x=-1;
  j.tab[1].tete.y=-1;
  j.tab[2].tete.x=-1;
  j.tab[2].tete.y=-1;
  j.tab[3].tete.x=-1;
  j.tab[3].tete.y=-1;
  j.tab[4].tete.x=-1;
  j.tab[4].tete.y=-1;

//initialisation d'une grille vide pour le joueur
  int i;
  int k;
  j.g.h=h;
  j.g.l=l;
  j.infos.h = h;
  j.infos.l = l;
  for(i=0;i<h;i++){
    for(k=0;k<l;k++){
      j.g.tab[i][k]=0;
      j.infos.tab[i][k]=0;
    }
  }
  return j;
}

void freeJoueurBN(JoueurBatailleNavale *j) {
  for (int i = 0; i < 5; i++) {
    SDL_FreeSurface(j->tab[i].nord);
    SDL_FreeSurface(j->tab[i].sud);
    SDL_FreeSurface(j->tab[i].west);
    SDL_FreeSurface(j->tab[i].est);
  }
}
