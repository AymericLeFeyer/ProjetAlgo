#include <stdio.h>
#include <SDL/SDL_image.h>

#include "headers/structure.h"

#include "headers/affichage.h"


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

//test de si on sort du tableau
Joueur placementBateau (Coord clic, Joueur j, int* nBateau, int tailleCase, SDL_Rect g,SDL_Surface* screen){
  if(clic.x<0 || clic.x>10 || clic.y<0 || clic.y>10){
    return j;
  }
  if(j.g.tab[clic.x][clic.y]!=0){
    return j;
  }
  Bateau b;
  SDL_Event event;
  b.direction=j.tab[*nBateau].direction;
  b.pv=j.tab[*nBateau].pv;
  b.taille=j.tab[*nBateau].taille;
  b.tete.x=j.tab[*nBateau].tete.x;
  b.tete.y=j.tab[*nBateau].tete.y;
  b.r.y=j.tab[*nBateau].r.y;
  b.r.x=j.tab[*nBateau].r.x;
  b.r.w=j.tab[*nBateau].r.w;
  b.r.h=j.tab[*nBateau].r.h;
  while(1){
  while(SDL_PollEvent(&event)){
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
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
                            SDL_BlitSurface(j.tab[*nBateau].nord, NULL, screen, &j.tab[*nBateau].r);
                          }
                          if(j.tab[*nBateau].direction==2){
                            j.tab[*nBateau].r.x=g.x+tailleCase*clic.x;
                            j.tab[*nBateau].r.y=g.y+tailleCase*clic.y;
                            j.tab[*nBateau].r.w=(g.x+tailleCase*clic.x)+j.tab[*nBateau].taille*tailleCase;
                            j.tab[*nBateau].r.h=(g.x+tailleCase*clic.x)+tailleCase;
                            SDL_BlitSurface(j.tab[*nBateau].west, NULL, screen, &j.tab[*nBateau].r);
                          }
                          if(j.tab[*nBateau].direction==3){
                            j.tab[*nBateau].r.x=g.x+tailleCase*clic.x;
                            j.tab[*nBateau].r.h=g.y+tailleCase*clic.y;
                            j.tab[*nBateau].r.y=(g.x+tailleCase*clic.x)-j.tab[*nBateau].taille*tailleCase;
                            j.tab[*nBateau].r.w=(g.x+tailleCase*clic.x)+tailleCase;
                            SDL_BlitSurface(j.tab[*nBateau].sud, NULL, screen, &j.tab[*nBateau].r);
                          }
                          if(j.tab[*nBateau].direction==4){
                            j.tab[*nBateau].r.w=g.x+tailleCase*clic.x;
                            j.tab[*nBateau].r.y=g.y+tailleCase*clic.y;
                            j.tab[*nBateau].r.x=(g.x+tailleCase*clic.x)-j.tab[*nBateau].taille*tailleCase;
                            j.tab[*nBateau].r.h=(g.x+tailleCase*clic.x)+tailleCase;
                            SDL_BlitSurface(j.tab[*nBateau].est, NULL, screen, &j.tab[*nBateau].r);
                          }
                        }
                        if (event.button.button == SDL_BUTTON_LEFT){
                            int i;
                            if(j.tab[*nBateau].direction==1){
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
                              for(i=clic.y;i<=clic.y+(j.tab[*nBateau].taille-1);i++){
                                j.g.tab[clic.x][i]=0;
                                }
                              j.tab[*nBateau].tete.x=clic.x;
                              j.tab[*nBateau].tete.y=clic.y;
                              for(i=clic.y;i<=clic.y+(j.tab[*nBateau].taille-1);i++){
                                j.g.tab[clic.x][i]=*nBateau+11;
                                }
                              *nBateau=-1;
                              return j;
                            }
                            if(j.tab[*nBateau].direction==2){
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
                              for(i=clic.x;i<=clic.x+(j.tab[*nBateau].taille-1);i++){
                                j.g.tab[i][clic.y]=0;
                                }
                              j.tab[*nBateau].tete.x=clic.x;
                              j.tab[*nBateau].tete.y=clic.y;
                              for(i=clic.x;i<=clic.x+(j.tab[*nBateau].taille-1);i++){
                                j.g.tab[i][clic.y]=*nBateau+11;
                                }
                                *nBateau=-1;
                              return j;
                            }
                            if(j.tab[*nBateau].direction==3){
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
                              for(i=clic.y;i<=clic.y-(j.tab[*nBateau].taille-1);i--){
                                j.g.tab[clic.x][i]=0;
                                }
                              j.tab[*nBateau].tete.x=clic.x;
                              j.tab[*nBateau].tete.y=clic.y;
                              for(i=clic.y;i<=clic.y-(j.tab[*nBateau].taille-1);i--){
                                j.g.tab[clic.x][i]=*nBateau+11;
                                }
                                *nBateau=-1;
                              return j;
                            }
                            if(j.tab[*nBateau].direction==4){
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
                              for(i=clic.x;i<=clic.x-(j.tab[*nBateau].taille-1);i--){
                                j.g.tab[i][clic.y]=0;
                                }
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
            affichageBatailleNavale(screen,j);
          }
}

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


//A FINIR !!
int phasePlacement(SDL_Surface* screen, Joueur* j1, Joueur* j2,int tailleCase, SDL_Rect g, int tourJoueur,SDL_Rect confirm){
  int nBateau;
  Coord clic;
  SDL_Event event;
  int confirmation=0;
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
  return confirmation;
}
