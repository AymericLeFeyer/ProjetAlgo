//structure de coordoonnée pour un bateau
typedef struct{
int x;
int y;
}Coord;

//structure bateau qui comprendra un entier coulé, coulé = 1 (kapout) coulé = 0 (vivant),
//entier direction haut=1 bas=2 droite=3 gauche=4
//entier PV si a 0 , coulé passe a 1
//entier taille qui correspondra a la taille du bateau
//struct coord qui prendra la tête du bateau
typedef struct{
int coule;
int direction = 1 ;
int pv;
Coord tete;
}Bateau;

//tableau de structure de bateau qui regroupe tout les bateaux du Joueur
//entier score qui regroupe le total de point du joueur
//entier joueur qui definit le joueur ; 1 =j1 , 2=j2, 3=j3 etc.
typedef struct{
  Bateau tab[5];
  int score;
  int joueur;
}Joueur;
