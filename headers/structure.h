#include <SDL/SDL.h>

#include <stdbool.h>

//structure de coordoonnée pour un bateau
typedef struct{
int x;
int y;
} Coord;

typedef struct {
  int h; //hauteur de la grille
  int l; //largeur de la grille
  int tab[10][10]; //grille générique de jeu
} Grille;

typedef struct{
  SDL_Surface* tabS[10][10];//grille de surface associées aux case de la grille
  SDL_Rect tabR[10][10];//grille des rectangles associés aux surfaces
} GrilleSDL;

//entier direction haut=1 gauche=2 bas=3 droite=4
//entier PV si a 0 , bateau mort
//entier taille qui correspondra a la taille du bateau
//struct coord qui prendra la tête du bateau
//tete initialisée a -1 -1 si pas placée
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





void updateGrille(Joueur *j);
int nbCaseBateau(Joueur j);
void tournerBateau(Bateau* b);
void deplacerBateau(Bateau*b, Coord c);
void magnetiserBateau(Bateau* b);
bool bateauxValide(Bateau* b);
void effacerBateauxGrille(Joueur *j);
