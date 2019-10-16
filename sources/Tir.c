#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/structure.h"
#include "../headers/shortcuts.h"
#include "../headers/constantes.h"
#include "../headers/affichage.h"
#include "../headers/interface.h"
#include "../headers/placement.h"

//Touché coulé raté bataille Navale

void aToiDeJouer(SDL_Surface* screen, Joueur* j) {
  // Case cible
  SDL_Surface* caseCible = NULL;
  caseCible = IMG_Load("assets/batailleNavale/case3.jpg");
  SDL_Rect posCaseCible = newRect(0, 0, 0, 0);
  // Les deux types de cases (couleurs différentes)
  SDL_Surface *case1 = NULL;
  SDL_Surface *case2 = NULL;
  case1 = IMG_Load("assets/batailleNavale/case1.jpg");
  case2 = IMG_Load("assets/batailleNavale/case2.jpg");
  // Police pour les textes, couleurs
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  SDL_Color noir = {0, 0, 0, 0};
  SDL_Surface* texte = NULL;
  // Variables importantes
  Coord clic;
  SDL_Event event;
  int continuer = 1;
  Coord temp;

  // Positions des cases
  SDL_Rect positionCases[10][10];
  // Position de la grille sur l'écran
  SDL_Rect positionGrille = newRect((WIDTH_GAME - 640)/2, (HEIGHT_GAME - 640)/2, 640, 640);

  // Initialisation de ces positions
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      positionCases[i][j] = newRect(positionGrille.x + 64 * i, positionGrille.y + 64 * j, 64, 64);
    }
  }

  // Afficher le texte correspondant au Joueur
  switch (j->joueur) {
    case 1:
      texte = creerTexte(screen, "Au tour du joueur 1", noir, font);
      break;
    case 2:
      texte = creerTexte(screen, "Au tour du joueur 2", noir, font);
      break;
  }
  SDL_Rect posTexte = newRect(500, 0, 0, 0);

  while(continuer){
    // On affiche le fond blanc
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    afficherGrille(screen, case1, case2, positionCases);

    SDL_BlitSurface(texte, NULL, screen, &posTexte);
    //afficherBateaux(screen, *j);
    afficherInterfaceBatailleNavale(screen, font);

    clic.x=event.button.x;
    clic.y=event.button.y;

    // Surligner la case pointee
    if (posInclusion(clic.x, clic.y, positionGrille)) {
      posCaseCible.x = clic.x - clic.x % 64;
      posCaseCible.y = clic.y - (clic.y - 40) % 64;

      ciblerCase(screen, caseCible, posCaseCible);
    }

    while(SDL_PollEvent(&event)){
      switch(event.type) {
        case SDL_QUIT:
          continuer = 0;

          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT){

          }
          if (event.button.button == SDL_BUTTON_RIGHT) {

          }
          break;
        }
    }
    SDL_Flip(screen);
  }
}

//retourne 1 si c'est possible, 0 si c'est pas possible
int tcr (int x, int y, Joueur* j){ //rajouter une grille dans joueur comme ils ont chacun leurs grille
   //si il n'y a pas de bateau :            //le joueur c le joueur adverse, celui qu'on attaque
   int i;
   if(j->g.tab[x][y]==0){
     j->g.tab[x][y]=4;
     return 1;
   }
   //Si la case contient un bateau et a deja été touché (mais pas coulé) :
   if(j->g.tab[x][y]==2){
     return 0; //On ne peut pas choisir la même case 2 fois
   }
   //Si la case contient un bâteau qui a déjà été coulé :
   if(j->g.tab[x][y]==3){
     return 0;
   }
   //Si la case ne contient pas de bâteau et a déjà été raté :
   if(j->g.tab[x][y]==4){
     return 0;
   }
   //Si il y a un bateau :
   if((j->g.tab[x][y]<=15)&&(j->g.tab[x][y]>=11)){
     if(j->tab[j->g.tab[x][y]-11].pv==0){
       return -1; //(dans ce cas il y a un probleme dans le programme parce que les pv du bateau ne peuvent pas être a 0 si une case n'a pas été touché)
     }
     j->tab[j->g.tab[x][y]-11].pv=j->tab[j->g.tab[x][y]-11].pv-1;
     //Si le bâteau est juste touché mais pas coulé :
     if(j->tab[j->g.tab[x][y]-11].pv!=0){
       j->g.tab[x][y]=2;
       return 1;
     }
     //on viens de couler le bâteau :
     else{
       if(j->tab[j->g.tab[x][y]-11].direction==1){ //bateau a la vertical tête en haut
          for(i=j->tab[j->g.tab[x][y]-11].tete.y; i<j->tab[j->g.tab[x][y]-11].tete.y+j->tab[j->g.tab[x][y]-11].taille; i++){
            j->g.tab[x][i]=3;
          }
          return 1;
       }
       if(j->tab[j->g.tab[x][y]-11].direction==2){ //bateau a l'horizontal tête à gauche
          for(i=j->tab[j->g.tab[x][y]-11].tete.x; i<j->tab[j->g.tab[x][y]-11].tete.x+j->tab[j->g.tab[x][y]-11].taille; i++){
            j->g.tab[i][y]=3;
          }
          return 1;
       }
       if(j->tab[j->g.tab[x][y]-11].direction==3){ //bateau a la vertical tête en bas
          for(i=j->tab[j->g.tab[x][y]-11].tete.y; i<j->tab[j->g.tab[x][y]-11].tete.y-j->tab[j->g.tab[x][y]-11].taille; i--){
            j->g.tab[x][i]=3;
          }
          return 1;
       }
       if(j->tab[j->g.tab[x][y]-11].direction==4){ //bateau a l'horizontal tête à droite
          for(i=j->tab[j->g.tab[x][y]-11].tete.x; i<j->tab[j->g.tab[x][y]-11].tete.x-j->tab[j->g.tab[x][y]-11].taille; i--){
            j->g.tab[i][y]=3;
          }
          return 1;
       }
     }
   }
 }


//Initialise la grille de l'interface graphique de la bataille navale

/*void initGrilleBN (Joueur j, SDL_Surface ecran, GrilleSDL gs){
  int i, k, ii;
  for (i=0; i<10;i++){
    for (k=0; k<10; k++){
      if(j.g.tab[j][k]==2){ //case touché
        //Faire apparaitre une croix rouge
         gs.tabS[i][k] = IMG_Load("touche.png");
         SDL_BlitSurface(gs.tabS[i][k], NULL, ecran, &gs.tabR[i][k]);
      }
      if(j.g.tab[j][k]==4){ //case raté
        //Faire apparaitre une croix blanche
        gs.tabS[i][k] = IMG_Load("rate.png");
        SDL_BlitSurface(gs.tabS[i][k], NULL, ecran, &gs.tabR[i][k]);
      }
      if(j.g.tab[j][k]==3){ //case de la tête du bateau coulé
        //Faire apparaitre le bateaux
        for(ii=0; ii<5; ii++){
          if((i==j.tab[ii].tete.x)&&(k==j.tab[ii].tete.y)){ //Cherche un bateau qui a sa tete sur la case
            if(j.tab[ii].direction==1){ //le bateau se dirige vers le nord
              SDL_BlitSurface(j.tab[ii].nord, NULL, ecran, &j.tab[ii].r);
              break;
            }
            if(j.tab[ii].direction==2){ // le bateau se dirige vers l'ouest
              SDL_BlitSurface(j.tab[ii].ouest, NULL, ecran, &j.tab[ii].r);
              break;
            }
            if(j.tab[ii].direction==3){ //le bateau se dirige vers le sud
              SDL_BlitSurface(j.tab[ii].sud, NULL, ecran, &j.tab[ii].r);
              break;
            }
            if(j.tab[ii].direction==4){ //le bateau se dirige vers l'est
              SDL_BlitSurface(j.tab[ii].est, NULL, ecran, &j.tab[ii].r);
              break;
            }
          }
        }
      }
    }
  }
}*/
