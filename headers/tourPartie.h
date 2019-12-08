int tourPartie(SDL_Surface* screen, CentrePlateau cp, JoueurPoker* t, int nbJoueurs, int mancheTotale,int argentDepart, int miseDepart);
int nbNonCouche(JoueurPoker *t,int nbJoueurs);
int tourPoker(SDL_Surface* screen, JoueurPoker* t, CentrePlateau* cp, int nbJoueurs, int currentManche, JoueurPoker* tabJ, int totalManche);
void afficherJetons(SDL_Surface* screen, CentrePlateau* cp);
