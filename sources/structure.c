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
  SDL_Rect g = newRect((WIDTH_GAME - 640)/2, (HEIGHT_GAME - 640)/2, 640, 640);
  effacerBateauxGrille(j);
  for (int i = 0; i < 5; i++) {
    // Si le bateau est inclus dans la grille ...
    if (inclusion(j->tab[i].r, g)) {
      // On ajoute sa tete
      j->g.tab[(j->tab[i].r.x - 320) / 64][(j->tab[i].r.y - 40) / 64] = 10 + i;
      switch (j->tab[i].direction) {
        // On ajoute son corps en fonction de sa direction
        case 1:
        case 3:
          for (int k = 1; k < j->tab[i].taille; k++) {
            j->g.tab[(j->tab[i].r.x - 320) / 64][(j->tab[i].r.y - 40) / 64 + k] = 10 + i;
          }

          break;
        case 2:
        case 4:
          for (int k = 1; k < j->tab[i].taille; k++) {
            j->g.tab[(j->tab[i].r.x - 320) / 64 + k][(j->tab[i].r.y - 40) / 64] = 10 + i;
          }
          break;
        default:
          break;
      }
    }
  }

}

int nbCaseBateau(Joueur j) {
  // Retour le nombre de case avec un bateau (10 a 14) pour la validation du placement notamment
  int n = 0;
  for (int i = 0; i < 10; i++) {
    for (int k = 0; k < 10; k++) {
      if ((j.g.tab[i][k] == 10) || (j.g.tab[i][k] == 11) || (j.g.tab[i][k] == 12) || (j.g.tab[i][k] == 13) || (j.g.tab[i][k] == 14)) {
        n++;
      }
    }
  }
  return n;

}

void effacerBateauxGrille(Joueur *j) {
  // Reset la grille au niveau des bateaux uniquement
  for (int i = 0; i < 10; i++) {
    for (int k = 0; k < 10; k++) {
      if ((j->g.tab[i][k] == 10) || (j->g.tab[i][k] == 11) || (j->g.tab[i][k] == 12) || (j->g.tab[i][k] == 13) || (j->g.tab[i][k] == 14)) {
        j->g.tab[i][k] = 0;
      }
    }
  }
}
