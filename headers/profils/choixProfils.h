void afficherProfils(SDL_Surface *screen);
Profil nouveauProfil(SDL_Surface* screen, int nbProfil, Profil oldProfil);
char* toString(char c);
char updateChar(char c, char t);
SDL_Rect posNoms(SDL_Rect r);
int selectionProfil(SDL_Surface* screen, int nbProfils, tabJP profils);
int iemeProfil(int i);
