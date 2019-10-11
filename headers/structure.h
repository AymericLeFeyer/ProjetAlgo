#include "grille.h"
#include <SDL/SDL.h>


//structure de coordoonnée pour un bateau
typedef struct{
int x;
int y;
} Coord;

//entier direction haut=1 gauche=2 bas=3 droite=4
//entier PV si a 0 , bateau mort
//entier taille qui correspondra a la taille du bateau
//struct coord qui prendra la tête du bateau
typedef struct{
int direction;
int pv;
int taille;
SDL_Rect r;
SDL_Surface* nord;
SDL_Surface* sud;
SDL_Surface* est;
SDL_Surface* west;
Coord tete;
} Bateau;

//tableau de structure de bateau qui regroupe tout les bateaux du Joueur
//entier score qui regroupe le total de point du joueur
//entier joueur qui definit le joueur ; 1 =j1 , 2=j2, 3=j3 etc.
typedef struct{
  Bateau tab[5];
  int score;
  int joueur;
  Grille g;
} Joueur;
