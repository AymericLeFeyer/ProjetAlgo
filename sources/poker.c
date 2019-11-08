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
  centre=initialisePoker(joueurs, 2, 50, 1, 5);

}
