int choixBateau (Coord clic, Joueur j);
Coord clicGrille ( Coord clic, int tailleCase, SDL_Rect g);
Joueur placementBateau (Coord clic, Joueur j, int* nBateau, int tailleCase, SDL_Rect g,SDL_Surface* screen);
int clicConfirmerPlacement(Coord clic, SDL_Rect confirm, Joueur j);
int phasePlacement(SDL_Surface* screen, Joueur* j1, Joueur* j2,int tailleCase, SDL_Rect g, int tourJoueur,SDL_Rect confirm);
