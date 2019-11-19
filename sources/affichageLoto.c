#include "../headers/structure.h"
#include "../headers/affichageLoto.h"
#include "../headers/interface.h"
#include "../headers/shortcuts.h"
#include "../headers/constantes.h"

void afficheGrilleLoto(CaseLoto t[9][3],SDL_Surface* screen, int numJoueur){
  int x=0,y=0;
  if (numJoueur==2 || numJoueur == 4) {
    x=735;
  }
  if (numJoueur==3 || numJoueur == 4) {
    y=469;
  }
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  SDL_Color noir = {0, 0, 0, 0};
  SDL_Surface* texte = NULL;
  int i,j;
  char valeur[10];
  SDL_Rect rectTexte = newRect(x+55,y+3,0,0);
  if(numJoueur==1){
      texte = IMG_Load("assets/loto/J1.png");
  }
  if(numJoueur==2){
      texte = IMG_Load("assets/loto/J2.png");
  }
  if(numJoueur==3){
      texte = IMG_Load("assets/loto/J3.png");
  }
  if(numJoueur==4){
      texte = IMG_Load("assets/loto/J4.png");
  }
  SDL_BlitSurface(texte, NULL, screen, &rectTexte);
  for (i=0; i<9; i++){
    for(j=0; j<3; j++){
      if(t[i][j].val!=-1){
        sprintf(valeur, "%d", t[i][j].val);
        texte = creerTexte(screen, valeur, noir, font);
          SDL_Rect rectTexte = newRect(x+50*(i+1)+5,y+50*(j)+49+5,0,0);
          SDL_BlitSurface(texte, NULL, screen, &rectTexte);
      }
      else{
        if(t[i][j].val==-1){
          SDL_Rect rectTexte = newRect((x+50*(i+1)),y+50*(j)+49,0,0);
          if(numJoueur==1){
              texte = IMG_Load("assets/loto/r.png");
          }
          if(numJoueur==2){
              texte = IMG_Load("assets/loto/b.png");
          }
          if(numJoueur==3){
              texte = IMG_Load("assets/loto/o.png");
          }
          if(numJoueur==4){
              texte = IMG_Load("assets/loto/v.png");
          }
        SDL_BlitSurface(texte, NULL, screen, &rectTexte);
        }
      }

      SDL_FreeSurface(texte);
    }
  }
  //SDL_Flip(screen);
}
