void afficheGrilleLoto(CaseLoto t[9][3],SDL_Surface* screen, int numJoueur,TTF_Font* font,SDL_Surface* texte,int punition[4]);
void afficherNombreLoto(SDL_Surface* screen,int nombre,TTF_Font* font,SDL_Surface* texte);
void afficherJeuLoto(SDL_Surface* screen,TTF_Font* font,SDL_Surface* texte,int nombre, int nbJoueurs,CaseLoto g1[9][3],CaseLoto g2[9][3],CaseLoto g3[9][3],CaseLoto g4[9][3],int punition[4]);
int menuChoixJoueur(SDL_Surface* screen);
int victoireLoto(SDL_Surface* screen, int gagnant);
