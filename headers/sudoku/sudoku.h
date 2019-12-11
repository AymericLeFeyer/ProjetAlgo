int affichageSudoku(SDL_Surface *screen, tabJP jp);
int playSudoku(SDL_Surface *screen, int difficulte, time_t temps,tabJP jp);
SDL_Rect newPos(SDL_Rect oldPos);
JoueurSudoku *chargementGrille(int numeroGrille);
void scoreSud(int current_time,tabJP jp, int difficulte);
