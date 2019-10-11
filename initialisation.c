#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Joueur initJoueur(){
  Joueur j;

  j.tab[0].nord = IMG_Load("assets/batailleNavale/bateau1.png");
  j.tab[1].nord = IMG_Load("assets/batailleNavale/bateau2.png");
  j.tab[2].nord = IMG_Load("assets/batailleNavale/bateau3.png");
  j.tab[3].nord = IMG_Load("assets/batailleNavale/bateau4.png");
  j.tab[4].nord = IMG_Load("assets/batailleNavale/bateau5.png");

  j.tab[0].r = newRect(10, 10, 0, 0);
  j.tab[1].r = newRect(10, 200, 0, 0);
  j.tab[2].r = newRect(10, 400, 0, 0);
  j.tab[3].r = newRect(100, 10, 0, 0);
  j.tab[4].r = newRect(100, 300, 0, 0);
  return j;
}
