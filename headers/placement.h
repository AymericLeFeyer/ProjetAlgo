int choixBateau (Coord clic, JoueurBatailleNavale j);//permet le clic sur un bateau pour le selectionner pour pouvoir ensuite le placer
Coord clicGrille ( Coord clic, int tailleCase, SDL_Rect g);//retourne les coordoonnée d'une case en fonction du clic
JoueurBatailleNavale placementBateau (Coord clic, JoueurBatailleNavale j, int* nBateau, int tailleCase, SDL_Rect g,SDL_Surface* screen);
//permet de placer un bateau
int clicConfirmerPlacement(Coord clic, SDL_Rect confirm, JoueurBatailleNavale j);//permet de valider le positionnement
int phasePlacement(SDL_Surface* screen, JoueurBatailleNavale* j, int* continuer);
//permet de lancer la phase de placement de bateau pour un joueur
