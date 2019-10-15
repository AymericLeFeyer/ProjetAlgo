#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../headers/structure.h"
#include "../headers/shortcuts.h"

Joueur initJoueur(int nJoueur, int h, int l){
  Joueur j;
  j.score=0;
  j.joueur=nJoueur;

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

  j.tab[0].r = newRect(10, 10, 0, 0);
  j.tab[1].r = newRect(10, 200, 0, 0);
  j.tab[2].r = newRect(10, 400, 0, 0);
  j.tab[3].r = newRect(100, 10, 0, 0);
  j.tab[4].r = newRect(100, 300, 0, 0);

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

  j.tab[0].direction = 1;
  j.tab[1].direction = 1;
  j.tab[2].direction = 1;
  j.tab[3].direction = 1;
  j.tab[4].direction = 1;

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

  int i;
  int k;
  j.g.h=h;
  j.g.l=l;
  for(i=0;i<h;i++){
    for(k=0;i<l;i++){
      j.g.tab[i][k]=0;
    }
  }
  return j;
}
