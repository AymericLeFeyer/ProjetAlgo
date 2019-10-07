#include "headers/structure.h"
#include "headers/grille.h"
//Touché coulé raté bateille Navale

//retourne 1 si c'est possible, 0 si c'est pas possible
int tcr (int x, int y, Joueur* j){ //rajouter une grille dans joueur comme ils ont chacun leurs grille
   //si il n'y a pas de bateau :            //le joueur c le joueur adverse, celui qu'on attaque
   if(j->Grille.tab[x][y]==0){
     j->Grille.tab[x][y]=4;
     return 1;
   }
   //Si la case contient un bateau et a deja été touché (mais pas coulé) :
   if(j->Grille.tab[x][y]==2){
     return 0; //On ne peut pas choisir la même case 2 fois
   }
   //Si la case contient un bâteau qui a déjà été coulé :
   if(j->Grille.tab[x][y]==3){
     return 0;
   }
   //Si la case ne contient pas de bâteau et a déjà été raté :
   if(j->Grille.tab[x][y]==4){
     return 0;
   }
   //Si il y a un bateau :
   if((j->Grille.tab[x][y]<=15)&&(j->Grille.tab[x][y]>=11)){
     if(j->tab[j->Grille.tab[x][y]-11].pv==0){
       return -1; //(dans ce cas il y a un probleme dans le programme parce que les pv du bateau ne peuvent pas être a 0 si une case n'a pas été touché)
     }
     j->tab[j->Grille.tab[x][y]-11].pv=j->tab[j->Grille.tab[x][y]-11].pv-1;
     //Si le bâteau est juste touché mais pas coulé :
     if(j->tab[j->Grille.tab[x][y]-11].pv!=0){
       j->Grille.tab[x][y]=2;
       return 1;
     }
     //on viens de couler le bâteau :
     else{
       if(j->tab[j->Grille.tab[x][y]-11].direction==1){ //bateau a la vertical tête en haut
          for(i=j->tab[j->Grille.tab[x][y]-11].tete.y; i<j->tab[j->Grille.tab[x][y]-11].tete.y+j->tab[j->Grille.tab[x][y]-11].taille; i++){
            j->Grille.tab[x][i]=3;
          }
          return 1;
       }
       if(j->tab[j->Grille.tab[x][y]-11].direction==2){ //bateau a l'horizontal tête à gauche
          for(i=j->tab[j->Grille.tab[x][y]-11].tete.x; i<j->tab[j->Grille.tab[x][y]-11].tete.x+j->tab[j->Grille.tab[x][y]-11].taille; i++){
            j->Grille.tab[i][y]=3;
          }
          return 1;
       }
       if(j->tab[j->Grille.tab[x][y]-11].direction==3){ //bateau a la vertical tête en bas
          for(i=j->tab[j->Grille.tab[x][y]-11].tete.y; i<j->tab[j->Grille.tab[x][y]-11].tete.y-j->tab[j->Grille.tab[x][y]-11].taille; i--){
            j->Grille.tab[x][i]=3;
          }
          return 1;
       }
       if(j->tab[j->Grille.tab[x][y]-11].direction==4){ //bateau a l'horizontal tête à droite
          for(i=j->tab[j->Grille.tab[x][y]-11].tete.x; i<j->tab[j->Grille.tab[x][y]-11].tete.x-j->tab[j->Grille.tab[x][y]-11].taille; i--){
            j->Grille.tab[i][y]=3;
          }
          return 1;
       }
     }
   }


 }
