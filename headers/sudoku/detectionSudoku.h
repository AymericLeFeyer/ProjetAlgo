typedef int chunk[3][3];

int detection(Coord c, JoueurSudoku j);
int detectionLigne(Coord c, JoueurSudoku j, int n);
int detectionColonne(Coord c, JoueurSudoku j, int n);
int detectionChunk(Coord c, JoueurSudoku j, int n);
void iniChunk(JoueurSudoku j, chunk t, int lig, int col);
