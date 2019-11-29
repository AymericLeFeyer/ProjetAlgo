#include <SDL/SDL_ttf.h>
#include "../headers/structure.h"
#include "../headers/affichageLoto.h"
#include "../headers/interface.h"
#include "../headers/shortcuts.h"
#include "../headers/constantes.h"
#include "../headers/loto.h"


void afficheGrilleLoto(CaseLoto t[9][3],SDL_Surface* screen, int numJoueur,TTF_Font* font,SDL_Surface* texte,int punition[4]){
  int x=0,y=0;
  if (numJoueur==2 || numJoueur == 4) {
    x=735;
  }
  if (numJoueur==3 || numJoueur == 4) {
    y=469;
  }
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  SDL_Color noir = {0, 0, 0, 0};
  int i,j;
  char valeur[10];
  SDL_Rect rectTexte = newRect(x+50,y+3,0,0);
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
  SDL_FreeSurface(texte);
  if (punition[numJoueur-1]>0) {
    texte = IMG_Load("assets/loto/puni.png");
    SDL_BlitSurface(texte, NULL, screen, &rectTexte);
    SDL_FreeSurface(texte);
  }
  for (i=0; i<9; i++){
    for(j=0; j<3; j++){
      if(t[i][j].val!=-1){
        sprintf(valeur, "%d", t[i][j].val);
        texte = TTF_RenderText_Solid(font, valeur, noir);
        rectTexte.x=x+49*(i+1)+10;
        rectTexte.y=y+50*(j)+64;
        SDL_BlitSurface(texte, NULL, screen, &rectTexte);
        SDL_FreeSurface(texte);
        if (t[i][j].jeton==true) {
          texte = IMG_Load("assets/loto/jeton.png");
          rectTexte.x=x+49*(i+1)+1;
          rectTexte.y=y+50*(j)+49;
          SDL_BlitSurface(texte, NULL, screen, &rectTexte);
          SDL_FreeSurface(texte);
        }
      }
      else{
        if(t[i][j].val==-1){
          rectTexte.x=x+49*(i+1)+1;
          rectTexte.y=y+50*(j)+49;
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
        SDL_FreeSurface(texte);
        }
      }
    }
  }
  TTF_CloseFont(font);
}


void afficherNombreLoto(SDL_Surface* screen,int nombre,TTF_Font* font,SDL_Surface* texte){
  font = TTF_OpenFont(FONT_UBUNTU, 80);
  SDL_Color noir = {0, 0, 0, 0};
  SDL_Rect rectTexte = newRect(565,305,0,0);
  char valeur[3];
  sprintf(valeur, "%d", nombre);
  texte = TTF_RenderText_Solid(font, valeur, noir);
  SDL_BlitSurface(texte, NULL, screen, &rectTexte);
  SDL_FreeSurface(texte);
  TTF_CloseFont(font);
}

void afficherJeuLoto(SDL_Surface* screen,TTF_Font* font,SDL_Surface* texte,int nombre, int nbJoueurs,CaseLoto g1[9][3],CaseLoto g2[9][3],CaseLoto g3[9][3],CaseLoto g4[9][3],int punition[4]){
  afficherNombreLoto(screen,nombre,font,texte);
  afficheGrilleLoto(g1,screen,1,font,texte,punition);
  if (nbJoueurs>=2) {
    afficheGrilleLoto(g2,screen,2,font,texte,punition);
  }
  if (nbJoueurs>=3) {
    afficheGrilleLoto(g3,screen,3,font,texte,punition);
  }
  if (nbJoueurs==4) {
    afficheGrilleLoto(g4,screen,4,font,texte,punition);
  }
}

//gére le menu de choix de joueur du loto
int menuChoixJoueur(SDL_Surface* screen){
  int continuer=1;
  SDL_Event event;
  Coord clic;
  //Affiche l'image du menu de choix
  SDL_Surface* choix = NULL;
  choix = IMG_Load("assets/Loto/choixJoueurLoto.png");
  SDL_Rect choixNbJoueur = newRect(0, 0, 1280, 720);
  //bouton 1 joueur
  SDL_Rect un = newRect(148, 113, 232, 112);
  //bouton 2 Joueurs
  SDL_Rect deux = newRect(900, 113, 232, 112);
  //bouton 3 joueurs
  SDL_Rect trois = newRect(148, 455, 232, 112);
  //bouton 4 joueurs
  SDL_Rect quatre = newRect(900, 455, 232, 112);
  //bouton menu
  SDL_Rect menu = newRect(552, 546, 149, 84);

  while(continuer==1){
    SDL_BlitSurface(choix, NULL, screen, &choixNbJoueur);

    SDL_Flip(screen);

    //evenements
    clic.x=event.button.x;
    clic.y=event.button.y;
    while(SDL_PollEvent(&event)){
      switch(event.type) {
        case SDL_QUIT:
          continuer = 0;
          return 0;

          break;

          case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT){
                //conditions des clics
                if (posInclusion(clic.x, clic.y, un)) {
                  continuer=afficherLoto(screen, 1);
                }
                if (posInclusion(clic.x, clic.y, deux)) {
                  continuer=afficherLoto(screen, 2);
                }
                if (posInclusion(clic.x, clic.y, trois)) {
                  continuer=afficherLoto(screen, 3);
                }
                if (posInclusion(clic.x, clic.y, quatre)) {
                  continuer=afficherLoto(screen, 4);
                }
                if (posInclusion(clic.x, clic.y, menu)) {
                  continuer=afficherMenu(screen);
                }
            }
            break;

        }
      }
  }
//free les surfaces
SDL_FreeSurface(choix);
return continuer;
}
