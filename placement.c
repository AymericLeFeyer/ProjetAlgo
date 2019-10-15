#include <stdio.h>
#include <SDL/SDL_image.h>

#include "headers/structure.h"
#include "headers/placement.h"
#include "headers/affichage.h"

//permet le clic sur un bateau pour le selectionner et retourne son indice dans le tableau de bateau d'un joueur
int choixBateau (Coord clic, Joueur j){
  if(clic.x>=j.tab[0].r.x && clic.x<=j.tab[0].r.x+j.tab[0].r.w && clic.y>=j.tab[0].r.y && clic.y<=j.tab[0].r.y+j.tab[0].r.h){
    return 0;
  }
  if(clic.x>=j.tab[1].r.x && clic.x<=j.tab[1].r.x+j.tab[1].r.w && clic.y>=j.tab[1].r.y && clic.y<=j.tab[1].r.y+j.tab[1].r.h){
    return 1;
  }
  if(clic.x>=j.tab[2].r.x && clic.x<=j.tab[2].r.x+j.tab[2].r.w && clic.y>=j.tab[2].r.y && clic.y<=j.tab[2].r.y+j.tab[2].r.h){
    return 2;
  }
  if(clic.x>=j.tab[3].r.x && clic.x<=j.tab[3].r.x+j.tab[3].r.w && clic.y>=j.tab[3].r.y && clic.y<=j.tab[3].r.y+j.tab[3].r.h){
    return 3;
  }
  if(clic.x>=j.tab[4].r.x && clic.x<=j.tab[4].r.x+j.tab[4].r.w && clic.y>=j.tab[4].r.y && clic.y<=j.tab[4].r.y+j.tab[4].r.h){
    return 4;
  }
  return -1;
}

//retourne les coordoonnée d'une case en fonction du clic
Coord clicGrille ( Coord clic, int tailleCase, SDL_Rect g){
  Coord a;
  if(clic.x<g.x || clic.x>g.x+g.w || clic.y<g.y || clic.y>g.y+g.h){
    a.x=-1;
    a.y=-1;
  }else{
  a.x=(int)(clic.x/tailleCase);
  a.y=(int)(clic.y/tailleCase);
}
  return a;
}

//permet de placer un bateau
Joueur placementBateau (Coord clic, Joueur j, int* nBateau, int tailleCase, SDL_Rect g,SDL_Surface* screen){
  //si on clique en dehors du tableau, pas besoin d'aller plus loin
  if(clic.x<0 || clic.x>10 || clic.y<0 || clic.y>10){
    return j;
  }
  //si il y a déjà un bateau dans la case ciblée, pas besoin d'aller plus loin
  if(j.g.tab[clic.x][clic.y]!=0){
    return j;
  }
  Bateau b;
  SDL_Event event;
  //création d'une copie du bateau actuel a retourner dans le cas ou le placement est impossible
  b.direction=j.tab[*nBateau].direction;
  b.pv=j.tab[*nBateau].pv;
  b.taille=j.tab[*nBateau].taille;
  b.tete.x=j.tab[*nBateau].tete.x;
  b.tete.y=j.tab[*nBateau].tete.y;
  b.r.y=j.tab[*nBateau].r.y;
  b.r.x=j.tab[*nBateau].r.x;
  b.r.w=j.tab[*nBateau].r.w;
  b.r.h=j.tab[*nBateau].r.h;
  //création d'une boucle infinie pour empecher de faire autre chose que tourner ou valider la position du bateau
  while(1){
  while(SDL_PollEvent(&event)){
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        //si on clique droit, le bateau tourne
                        if (event.button.button == SDL_BUTTON_RIGHT){
                          if(j.tab[*nBateau].direction==4){
                            j.tab[*nBateau].direction=1;
                          }else{
                            j.tab[*nBateau].direction=j.tab[*nBateau].direction+1;
                          }
                          if(j.tab[*nBateau].direction==1){
                            j.tab[*nBateau].r.x=g.x+tailleCase*clic.x;
                            j.tab[*nBateau].r.y=g.y+tailleCase*clic.y;
                            j.tab[*nBateau].r.w=(g.x+tailleCase*clic.x)+tailleCase;
                            j.tab[*nBateau].r.h=(g.x+tailleCase*clic.x)+j.tab[*nBateau].taille*tailleCase;
                          }
                          if(j.tab[*nBateau].direction==2){
                            j.tab[*nBateau].r.x=g.x+tailleCase*clic.x;
                            j.tab[*nBateau].r.y=g.y+tailleCase*clic.y;
                            j.tab[*nBateau].r.w=(g.x+tailleCase*clic.x)+j.tab[*nBateau].taille*tailleCase;
                            j.tab[*nBateau].r.h=(g.x+tailleCase*clic.x)+tailleCase;
                          }
                          if(j.tab[*nBateau].direction==3){
                            j.tab[*nBateau].r.x=g.x+tailleCase*clic.x;
                            j.tab[*nBateau].r.h=g.y+tailleCase*clic.y;
                            j.tab[*nBateau].r.y=(g.x+tailleCase*clic.x)-j.tab[*nBateau].taille*tailleCase;
                            j.tab[*nBateau].r.w=(g.x+tailleCase*clic.x)+tailleCase;
                          }
                          if(j.tab[*nBateau].direction==4){
                            j.tab[*nBateau].r.w=g.x+tailleCase*clic.x;
                            j.tab[*nBateau].r.y=g.y+tailleCase*clic.y;
                            j.tab[*nBateau].r.x=(g.x+tailleCase*clic.x)-j.tab[*nBateau].taille*tailleCase;
                            j.tab[*nBateau].r.h=(g.x+tailleCase*clic.x)+tailleCase;
                          }
                        }
                        //si on clique gauche, le bateau est placé si cela est possible
                        if (event.button.button == SDL_BUTTON_LEFT){
                            int i;
                            if(j.tab[*nBateau].direction==1){
                              //test si le bateau placé dans cette direction ne sort pas du tableau
                              if (clic.y+(j.tab[*nBateau].taille-1)>=10) {
                                j.tab[*nBateau].direction=b.direction;
                                j.tab[*nBateau].pv=b.pv;
                                j.tab[*nBateau].taille=b.taille;
                                j.tab[*nBateau].tete.x=b.tete.x;
                                j.tab[*nBateau].tete.y=b.tete.y;
                                j.tab[*nBateau].r.y=b.r.y;
                                j.tab[*nBateau].r.x=b.r.x;
                                j.tab[*nBateau].r.w=b.r.w;
                                j.tab[*nBateau].r.h=b.r.h;
                                return j;
                              }
                              //test si il n'y a pas déjà un bateau dans les cases nécessaires au bateau actuel
                              for(i=clic.y+1;i<=clic.y+(j.tab[*nBateau].taille-1);i++){
                                if (j.g.tab[clic.x][i]!=0) {
                                  j.tab[*nBateau].direction=b.direction;
                                  j.tab[*nBateau].pv=b.pv;
                                  j.tab[*nBateau].taille=b.taille;
                                  j.tab[*nBateau].tete.x=b.tete.x;
                                  j.tab[*nBateau].tete.y=b.tete.y;
                                  j.tab[*nBateau].r.y=b.r.y;
                                  j.tab[*nBateau].r.x=b.r.x;
                                  j.tab[*nBateau].r.w=b.r.w;
                                  j.tab[*nBateau].r.h=b.r.h;
                                  return j;
                                }
                              }
                              //si le bateau avait déjà été placé dans le tableau, on le retire avant de le déplacer
                              if (j.tab[*nBateau].tete.x != -1) {
                                for(i=clic.y;i<=clic.y+(j.tab[*nBateau].taille-1);i++){
                                  j.g.tab[clic.x][i]=0;
                                }
                              }
                              //déplacement du bateau aux coordoonnées souhaitées
                              j.tab[*nBateau].tete.x=clic.x;
                              j.tab[*nBateau].tete.y=clic.y;
                              for(i=clic.y;i<=clic.y+(j.tab[*nBateau].taille-1);i++){
                                j.g.tab[clic.x][i]=*nBateau+11;
                                }
                              *nBateau=-1;
                              return j;
                            }
                            if(j.tab[*nBateau].direction==2){
                              //test si le bateau placé dans cette direction ne sort pas du tableau
                              if (clic.x+(j.tab[*nBateau].taille-1)>=10) {
                                j.tab[*nBateau].direction=b.direction;
                                j.tab[*nBateau].pv=b.pv;
                                j.tab[*nBateau].taille=b.taille;
                                j.tab[*nBateau].tete.x=b.tete.x;
                                j.tab[*nBateau].tete.y=b.tete.y;
                                j.tab[*nBateau].r.y=b.r.y;
                                j.tab[*nBateau].r.x=b.r.x;
                                j.tab[*nBateau].r.w=b.r.w;
                                j.tab[*nBateau].r.h=b.r.h;
                                return j;
                              }
                              //test si il n'y a pas déjà un bateau dans les cases nécessaires au bateau actuel
                              for(i=clic.x+1;i>=clic.x+(j.tab[*nBateau].taille-1);i++){
                                if (j.g.tab[i][clic.y]=0) {
                                  j.tab[*nBateau].direction=b.direction;
                                  j.tab[*nBateau].pv=b.pv;
                                  j.tab[*nBateau].taille=b.taille;
                                  j.tab[*nBateau].tete.x=b.tete.x;
                                  j.tab[*nBateau].tete.y=b.tete.y;
                                  j.tab[*nBateau].r.y=b.r.y;
                                  j.tab[*nBateau].r.x=b.r.x;
                                  j.tab[*nBateau].r.w=b.r.w;
                                  j.tab[*nBateau].r.h=b.r.h;
                                  return j;
                                }
                              }
                              //si le bateau avait déjà été placé dans le tableau, on le retire avant de le déplacer
                              if (j.tab[*nBateau].tete.x != -1) {
                                for(i=clic.x;i<=clic.x+(j.tab[*nBateau].taille-1);i++){
                                  j.g.tab[i][clic.y]=0;
                                }
                              }
                              //déplacement du bateau aux coordoonnées souhaitées
                              j.tab[*nBateau].tete.x=clic.x;
                              j.tab[*nBateau].tete.y=clic.y;
                              for(i=clic.x;i<=clic.x+(j.tab[*nBateau].taille-1);i++){
                                j.g.tab[i][clic.y]=*nBateau+11;
                                }
                                *nBateau=-1;
                              return j;
                            }
                            if(j.tab[*nBateau].direction==3){
                              //test si le bateau placé dans cette direction ne sort pas du tableau
                              if (clic.y-(j.tab[*nBateau].taille-1)>=10) {
                                j.tab[*nBateau].direction=b.direction;
                                j.tab[*nBateau].pv=b.pv;
                                j.tab[*nBateau].taille=b.taille;
                                j.tab[*nBateau].tete.x=b.tete.x;
                                j.tab[*nBateau].tete.y=b.tete.y;
                                j.tab[*nBateau].r.y=b.r.y;
                                j.tab[*nBateau].r.x=b.r.x;
                                j.tab[*nBateau].r.w=b.r.w;
                                j.tab[*nBateau].r.h=b.r.h;
                                return j;
                              }
                              //test si il n'y a pas déjà un bateau dans les cases nécessaires au bateau actuel
                              for(i=clic.y-1;i<=clic.y-(j.tab[*nBateau].taille-1);i--){
                                if (j.g.tab[clic.y][i]!=0) {
                                  j.tab[*nBateau].direction=b.direction;
                                  j.tab[*nBateau].pv=b.pv;
                                  j.tab[*nBateau].taille=b.taille;
                                  j.tab[*nBateau].tete.x=b.tete.x;
                                  j.tab[*nBateau].tete.y=b.tete.y;
                                  j.tab[*nBateau].r.y=b.r.y;
                                  j.tab[*nBateau].r.x=b.r.x;
                                  j.tab[*nBateau].r.w=b.r.w;
                                  j.tab[*nBateau].r.h=b.r.h;
                                  return j;
                                }
                              }
                              //si le bateau avait déjà été placé dans le tableau, on le retire avant de le déplacer
                              if (j.tab[*nBateau].tete.x != -1) {
                                for(i=clic.y;i<=clic.y-(j.tab[*nBateau].taille-1);i--){
                                  j.g.tab[clic.x][i]=0;
                                }
                              }
                              //déplacement du bateau aux coordoonnées souhaitées
                              j.tab[*nBateau].tete.x=clic.x;
                              j.tab[*nBateau].tete.y=clic.y;
                              for(i=clic.y;i<=clic.y-(j.tab[*nBateau].taille-1);i--){
                                j.g.tab[clic.x][i]=*nBateau+11;
                                }
                                *nBateau=-1;
                              return j;
                            }
                            if(j.tab[*nBateau].direction==4){
                              //test si le bateau placé dans cette direction ne sort pas du tableau
                              if (clic.x-(j.tab[*nBateau].taille-1)>=10) {
                                j.tab[*nBateau].direction=b.direction;
                                j.tab[*nBateau].pv=b.pv;
                                j.tab[*nBateau].taille=b.taille;
                                j.tab[*nBateau].tete.x=b.tete.x;
                                j.tab[*nBateau].tete.y=b.tete.y;
                                j.tab[*nBateau].r.y=b.r.y;
                                j.tab[*nBateau].r.x=b.r.x;
                                j.tab[*nBateau].r.w=b.r.w;
                                j.tab[*nBateau].r.h=b.r.h;
                                return j;
                              }
                              //test si il n'y a pas déjà un bateau dans les cases nécessaires au bateau actuel
                              for(i=clic.x-1;i<=clic.x-(j.tab[*nBateau].taille-1);i--){
                                if (j.g.tab[i][clic.y]!=0) {
                                  j.tab[*nBateau].direction=b.direction;
                                  j.tab[*nBateau].pv=b.pv;
                                  j.tab[*nBateau].taille=b.taille;
                                  j.tab[*nBateau].tete.x=b.tete.x;
                                  j.tab[*nBateau].tete.y=b.tete.y;
                                  j.tab[*nBateau].r.y=b.r.y;
                                  j.tab[*nBateau].r.x=b.r.x;
                                  j.tab[*nBateau].r.w=b.r.w;
                                  j.tab[*nBateau].r.h=b.r.h;
                                  return j;
                                }
                              }
                              //si le bateau avait déjà été placé dans le tableau, on le retire avant de le déplacer
                              if (j.tab[*nBateau].tete.x != -1) {
                                for(i=clic.x;i<=clic.x-(j.tab[*nBateau].taille-1);i--){
                                  j.g.tab[i][clic.y]=0;
                                }
                              }
                              //déplacement du bateau aux coordoonnées souhaitées
                              j.tab[*nBateau].tete.x=clic.x;
                              j.tab[*nBateau].tete.y=clic.y;
                              for(i=clic.x;i<=clic.x-(j.tab[*nBateau].taille-1);i--){
                                j.g.tab[i][clic.y]=*nBateau+11;
                                }
                                *nBateau=-1;
                              return j;
                            }

                        }
                        break;
                }
            }
            //renouvellement de l'affichage pour montrer la rotation du bateau
            affichageBatailleNavale(screen,j);
          }
}

//permet de valider le positionnement
/** le rect et la surface de confirm sont a faire **/
int clicConfirmerPlacement(Coord clic, SDL_Rect confirm, Joueur j){
  if(clic.x>=confirm.x && clic.x<=confirm.x+confirm.w && clic.y>=confirm.y && clic.y<=confirm.y+confirm.h){
    for(int i=0;i<=4;i++){
      if(j.tab[i].tete.x==-1 && j.tab[i].tete.y==-1){
        return 0;
      }
    }
    return 1;
  }
  return 0;
}


//permet de lancer la phase de placement de bateau pour un joueur
//A TESTER ET MODIFIER SI BESOIN
int phasePlacement(SDL_Surface* screen, Joueur* j1, Joueur* j2,int tailleCase, SDL_Rect g, int tourJoueur,SDL_Rect confirm){
  int nBateau;
  Coord clic;
  SDL_Event event;
  int confirmation=0;
  //on quitte uniquement si on a confirmé le placement du 2e joueur
  while(confirmation==0){
    while(SDL_PollEvent(&event)){
      switch(event.type)
        {case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT){
            clic.x=event.button.x;
            clic.y=event.button.y;
            if(tourJoueur==1){
              if(nBateau!=-1){
                *j1=placementBateau(clicGrille(clic,tailleCase,g),*j1,&nBateau,tailleCase,g,screen);
              }else{
                nBateau=choixBateau(clic,*j1);
                confirmation=clicConfirmerPlacement(clic,confirm,*j1);
              }
            }else{
              if(nBateau!=-1){
                *j2=placementBateau(clicGrille(clic,tailleCase,g),*j2,&nBateau,tailleCase,g,screen);
              }else{
                nBateau=choixBateau(clic,*j2);
                confirmation=clicConfirmerPlacement(clic,confirm,*j2);
              }
            }
          }
          break;
        }
    }
    //passage au tour du joueur 2
    if(tourJoueur==1 && confirmation==1){
      tourJoueur=2;
      confirmation=0;
    }
  }
  return confirmation;
}
