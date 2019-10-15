#include <stdbool.h>

#include "../headers/constantes.h"
#include "../headers/structure.h"
#include "../headers/shortcuts.h"

// Bataille navale

void tournerBateau(Bateau* b) {
  b->direction = (b->direction++ % 4) + 1;
  int temp = b->r.w;
  b->r.w = b->r.h;
  b->r.h = temp;
}

void deplacerBateau(Bateau* b, Coord c) {
  b->r.x = c.x;
  b->r.y = c.y;
  magnetiserBateau(b);
}

void magnetiserBateau(Bateau* b) {
  b->r.x -= (b->r.x % 64);
  b->r.y -= (b->r.y % 64) - 40;
}

bool bateauxValide(Bateau* b) {
  SDL_Rect g = newRect((WIDTH_GAME - 640)/2, (HEIGHT_GAME - 640)/2, 640, 640);
  for (int i = 0; i < 5; i++) {
    if (!(inclusion(b[i].r, g))) return false;
  }
  return true;
}

// Met a jour la grille en fonction des bateaux poses
void updateGrille(Joueur *j) {

}

int nbCaseBateau(Joueur j) {

}

void effacerBateauxGrille(Joueur *j) {
  for (int i = 0; i < 10; i++) {
    for (int k = 0; k < 10; k++) {
      if ((j->g.tab[i][k] == 10) || (j->g.tab[i][k] == 11) || (j->g.tab[i][k] == 12) || (j->g.tab[i][k] == 13) || (j->g.tab[i][k] == 14)) {
        j->g.tab[i][k] = 0;
      }
    }
  }
}
