int choixBateau (Coord clic, Joueur j);//permet le clic sur un bateau pour le selectionner pour pouvoir ensuite le placer
Coord clicGrille ( Coord clic, int tailleCase, SDL_Rect g);//retourne les coordoonnée d'une case en fonction du clic
Joueur placementBateau (Coord clic, Joueur j, int* nBateau, int tailleCase, SDL_Rect g,SDL_Surface* screen);
//permet de placer un bateau
int clicConfirmerPlacement(Coord clic, SDL_Rect confirm, Joueur j);//permet de valider le positionnement
void phasePlacement(SDL_Surface* screen, Joueur* j, int* continuer);
//permet de lancer la phase de placement de bateau pour un joueur
