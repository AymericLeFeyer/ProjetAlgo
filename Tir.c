#include "headers/structure.h"
#include "headers/grille.h"
//Touché coulé raté bataille Navale

//retourne 1 si c'est possible, 0 si c'est pas possible
int tcr (int x, int y, Joueur* j){ //rajouter une grille dans joueur comme ils ont chacun leurs grille
   //si il n'y a pas de bateau :            //le joueur c le joueur adverse, celui qu'on attaque
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

void initGrilleBN (Joueur j, SDL_Surface ecran, GrilleSDL gs){
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
}
