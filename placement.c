//test si bateau sur grille
int choixBateau (Coord clic, SDL_Rect[5] positionsB, Joueur j){
  if(clic.x>=positionsB[0].x && clic.x<=positionsB[0].w && clic.y>=positionsB[0].y && clic.y<=positionsB[0].h){
    return 0;
  }
  if(clic.x>=positionsB[1].x && clic.x<=positionsB[1].w && clic.y>=positionsB[1].y && clic.y<=positionsB[1].h){
    return 1;
  }
  if(clic.x>=positionsB[2].x && clic.x<=positionsB[2].w && clic.y>=positionsB[2].y && clic.y<=positionsB[2].h){
    return 2;
  }
  if(clic.x>=positionsB[3].x && clic.x<=positionsB[3].w && clic.y>=positionsB[3].y && clic.y<=positionsB[3].h){
    return 3;
  }
  if(clic.x>=positionsB[4].x && clic.x<=positionsB[4].w && clic.y>=positionsB[4].y && clic.y<=positionsB[4].h){
    return 4;
  }
  return -1;
}

Coord clicGrille ( Coord clic, int tailleCase){
  Coord a;
  a.x=(int)(clic.x/tailleCase)
  a.y=(int)(clic.y/tailleCase)
  return a;
}

//test de si on sort du tableau
Joueur placementBateau (Coord clic, SDL_Rect[5] positionsB, Joueur j, int nBateau){
  if(clic.x<0 || clic.x>10 || clic.y<0 || clic.y>10){
    return j;
  }
  if(j.g.tab[clic.x][clic.y]!=0){
    return j;
  }
  while(SDL_PollEvent(&event)){
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_RIGHT){
                          if(j.tab[nBateau].direction==4){
                            j.tab[nBateau].direction=1;
                          }else{
                            j.tab[nBateau].direction=j.tab[nBateau].direction+1;
                          }
                        }
                        if (event.button.button == SDL_BUTTON_LEFT){
                            int i;
                            if(j.tab[nbBateau].direction==1){
                              for(i=clic.y+1;i<=clic.y+(j.tab[nBateau].taille-1);i++){
                                if (j.g.tab[clic.x][i]!=0) {
                                  return j;
                                }
                              }
                              j.tab[nbBateau].tete.x=clic.x;
                              j.tab[nbBateau].tete.y=clic.y;
                              for(i=clic.y;i<=clic.y+(j.tab[nBateau].taille-1);i++){
                                j.g.tab[clic.x][i]=nBateau+11;
                                }
                              }
                              return j;
                            }
                            if(j.tab[nbBateau].direction==2){
                              for(i=clic.x+1;i>=clic.x+(j.tab[nBateau].taille-1);i++){
                                if (j.g.tab[i][clic.y]=0) {
                                  j.tab[nbBateau].direction=1;
                                  return j;
                                }
                              }
                              j.tab[nbBateau].tete.x=clic.x;
                              j.tab[nbBateau].tete.y=clic.y;
                              for(i=clic.x;i<=clic.x+(j.tab[nBateau].taille-1);i++){
                                j.g.tab[i][clic.y]=nBateau+11;
                                }
                              }
                              return j;
                            }
                            if(j.tab[nbBateau].direction==3){
                              for(i=clic.y-1;i<=clic.y-(j.tab[nBateau].taille-1);i--){
                                if (j.g.tab[clic.y][i]!=0) {
                                  j.tab[nbBateau].direction=1;
                                  return j;
                                }
                              }
                              j.tab[nbBateau].tete.x=clic.x;
                              j.tab[nbBateau].tete.y=clic.y;
                              for(i=clic.y;i<=clic.y-(j.tab[nBateau].taille-1);i--){
                                j.g.tab[clic.x][i]=nBateau+11;
                                }
                              }
                              return j;
                            }
                            if(j.tab[nbBateau].direction==4){
                              for(i=clic.x-1;i<=clic.x-(j.tab[nBateau].taille-1);i--){
                                if (j.g.tab[i][clic.y]!=0) {
                                  j.tab[nbBateau].direction=1;
                                  return j;
                                }
                              }
                              j.tab[nbBateau].tete.x=clic.x;
                              j.tab[nbBateau].tete.y=clic.y;
                              for(i=clic.x;i<=clic.x-(j.tab[nBateau].taille-1);i--){
                                j.g.tab[i][clic.y]=nBateau+11;
                                }
                              }
                              return j;
                            }

                        }
                        break;
                }
            }
}
