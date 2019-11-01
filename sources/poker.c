#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/structure.h"
#include "../headers/pioche.h"

void poker(){
  JoueurPoker joueurs[5];
  CentrePlateau centre;
  int nbJoueurs;
  int miseDepart;
  int nbTours;
  int argentDepart;
  scanf("%d\n", &nbJoueurs);
  scanf("%d\n", &miseDepart);
  scanf("%d\n", &nbTours);
  scanf("%d\n", &argentDepart);
  tourPartie(centre, joueurs,nbJoueurs,nbTours);
  centre=initialisePoker(joueurs, nbJoueurs, argentDepart, 1, miseDepart);

}
