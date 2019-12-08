void initialisationPioche(Carte *pioche); //initialise le talon puis le mélange dans la pioche
    ///entrée: pioche, le tableau de cartes correspondant à la pioche
int shuffle(Carte* talon,int tailleTalon,Carte* pioche); //permet de mélanger le talon dans la pioche
    ///entrée: talon, le tableau de Cartes correspondant au talon; tailleTalon , le nombre de cartes présents dans le talon; pioche, le tableau de cartes correspondant à la pioche
CentrePlateau initialisePoker(JoueurPoker* j, int nbJoueurs, int argentDepart, int premiereManche, int miseInit);//initialise une partie de poker
CentrePlateau piocher(Carte *pioche, int taillePioche, JoueurPoker* j, CentrePlateau centre, int nombreJoueurs);//fait piocher toutes les cartes necessaires a une partie de poker
CentrePlateau libererPoker(JoueurPoker* t,int nbJoueurs,CentrePlateau cp);
