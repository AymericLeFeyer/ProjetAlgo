#include "../headers/structure.h"

void tournerBateau(Bateau* b) {
  b->direction = (b->direction++ % 4) + 1;
  int temp = b->r.w;
  b->r.w = b->r.h;
  b->r.h = temp;
}

void deplacerBateau(Bateau*b, Coord c) {
  b->r.x = c.x;
  b->r.y = c.y;
}
