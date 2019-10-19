#include <SDL/SDL.h>
#include <stdbool.h>

typedef struct{
int x;
int y;
} Coord; //structure de coordoonnée pour un bateau

typedef struct {
  int h; //hauteur de la grille
  int l; //largeur de la grille
  int tab[10][10]; //grille générique de jeu
} Grille; // Structure grille generique

/*
    BATAILLE NAVALE
*/

typedef struct{
int direction; //entier direction haut=1 gauche=2 bas=3 droite=4
int pv; //entier PV si a 0 , bateau mort
int taille; //entier taille qui correspondra a la taille du bateau
SDL_Rect r; //rect du bateau
SDL_Surface* nord;
SDL_Surface* sud;
SDL_Surface* est;
SDL_Surface* west;
Coord tete; //struct coord qui prendra la tête du bateau //tete initialisée a -1 -1 si pas placée
} Bateau; // Structure bateau


typedef struct{
  int joueur;
  Bateau tab[5]; //tableau de structure de bateau qui regroupe tout les bateaux du Joueur
  Grille g; // grille des bateaux
  Grille infos; // grille des coups joues
} JoueurBatailleNavale;

/*
    POKER
*/


typedef struct{
  int couleur; // 1 coeur 2 carreau 3 pik 4 trefle
  int valeur; // 1 a 13
} Carte;

typedef struct{
  Carte carte1;
  Carte carte2;
} Main;

typedef struct{
  Carte flop;
  Carte turn;
  Carte river;
  int mise;
} CentrePlateau;

typedef struct{
  int joueur; // id du joueur
  int argent;
  Main main;
  int etat; // encore en jeu ou non
} JoueurPoker;

/*
    HEADERS
*/

void updateGrille(JoueurBatailleNavale *j);
int nbCaseBateau(JoueurBatailleNavale j);
void tournerBateau(Bateau* b);
void deplacerBateau(Bateau*b, Coord c);
void magnetiserBateau(Bateau* b);
bool bateauxValide(Bateau* b);
void effacerBateauxGrille(JoueurBatailleNavale *j);
int nbCaseNonVide(Grille g);
int nbBateauxVivant(JoueurBatailleNavale j);


/*
  HEADERS POKER
*/
void miseTotal(JoueurPoker* j1, JoueurPoker* j2, JoueurPoker* j3, JoueurPoker* j4, JoueurPoker* j5,CentrePlateau* p);
void miseJeu (JoueurPoker *j, CentrePlateau* p);
