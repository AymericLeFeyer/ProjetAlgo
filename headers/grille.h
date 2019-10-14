#include <SDL/SDL.h>

typedef struct {
  int h; //hauteur de la grille
  int l; //largeur de la grille
  int tab[10][10]; //grille générique de jeu
} Grille;

typedef struct{
  SDL_Surface* tabS[10][10];//grille de surface associées aux case de la grille
  SDL_Rect tabR[10][10];//grille des rectangles associés aux surfaces
} GrilleSDL;
