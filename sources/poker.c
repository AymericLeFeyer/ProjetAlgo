#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/structure.h"
#include "../headers/pioche.h"
#include "../headers/tourPartie.h"
#include "../headers/mainsPoker.h"


//lance une partie de poker
void poker(){
  srand(time(NULL));
  JoueurPoker joueurs[5];
  CentrePlateau centre;
  int nbJoueurs=2;
  int miseDepart=5;
  int nbTours=2;
  int argentDepart=50;
  printf("nombre de joueurs ? ");
  scanf("%d", &nbJoueurs);
  printf("mise de depart ? ");
  scanf("%d", &miseDepart);
  printf("nombre de manches ? ");
  scanf("%d", &nbTours);
  printf("jetons au depart pour les joueurs ? ");
  scanf("%d", &argentDepart);
  tourPartie(centre, joueurs,nbJoueurs,nbTours,argentDepart,miseDepart);
}
