#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "../headers/structure.h"
#include "../headers/shortcuts.h"
#include "../headers/timerLoto.h"
#include "../headers/loto.h"
#include "../headers/constantes.h"
#include "../headers/affichageLoto.h"
#include "../headers/grilleLoto.h"
#include "../headers/bouleLoto.h"

int afficherLoto(SDL_Surface* screen, int nbJoueurs){
  srand(time(NULL));
  int gagnant=0;

  int score[4]={2,0,0,0};
  int punition[4]={0,0,0,0};
  int nombrePasse[4]={0,0,0,0};
  CaseLoto grille1[9][3];
  CaseLoto grille2[9][3];
  CaseLoto grille3[9][3];
  CaseLoto grille4[9][3];


  int tasBoules[90];
  int tailleTas = initialisationLoto(tasBoules,nbJoueurs,grille1,grille2,grille3,grille4);
  int nombreTire;

  long current_time;
  long temps;
  int newNombre=1;
  Coord c;

  Uint32 start;
  int continuer=1;
  SDL_Event event;
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 70);
  SDL_Color blanc = {0, 0, 0, 0};
  SDL_Rect position = newRect(0, 0, 0, 0);
  SDL_Rect positiontimer = newRect(1010, 336, 0, 0);
  SDL_Rect boutonMenu = newRect(133,290,84,154);
  int tempsmax=5;
  char timerText[10];
  SDL_Surface* texte=NULL;
  SDL_Surface* tempsRestant;
  SDL_Surface* fond=NULL;
  fond=IMG_Load("assets/Loto/backLoto.png");
  while (continuer==1){


    //changement de nombre
    if(newNombre==1){
      for (int i = 0; i < 4; i++) {
        if (punition[i]>0) {
          punition[i]--;
        }
      }
      //score[0]=nbJetons(grille1);
      score[1]=nbJetons(grille2);
      score[2]=nbJetons(grille3);
      score[3]=nbJetons(grille4);
      if (nombrePasse[0]+nombrePasse[1]+nombrePasse[2]+nombrePasse[3]>=nbJoueurs*15 || tailleTas<=0) {
        gagnant=maxJeton(score)+1;
      }
      for (int i = 0; i < 4; i++) {
        if (score[i]>=15) {
          gagnant=i+1;
        }
      }
      if (tailleTas>=1) {
        nombreTire=prendreNombre(&tailleTas,tasBoules);
        if (nombreDansGrille(grille1,nombreTire)){
          nombrePasse[0]++;
        }
        if (nombreDansGrille(grille2,nombreTire)){
          nombrePasse[1]++;
        }
        if (nombreDansGrille(grille3,nombreTire)){
          nombrePasse[2]++;
        }
        if (nombreDansGrille(grille4,nombreTire)){
          nombrePasse[3]++;
        }
      }
      newNombre=0;
      temps=time(NULL);
    }




    SDL_PollEvent(&event);
    switch(event.type)
    {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        break;

      //retour au menu
      case SDL_MOUSEBUTTONDOWN:
        boutonMenu = newRect(133,290,84,154);
        c.x = event.button.x;
        c.y = event.button.y;
        if(posInclusion(c.x, c.y, boutonMenu)){
          continuer=2;
        }
        break;


      case SDL_KEYDOWN:
              if (gagnant==0) {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LCTRL: /* Appui sur la touche ctrl gauche pour le joueur 1 */
                      if (punition[0]==0) {
                        if (nombreDansGrille(grille1,nombreTire)) {
                          poserJeton(grille1,nombreTire);
                        }else{
                          punition[0]=2;
                        }
                      }
                      break;

                    case SDLK_SPACE: /* Appui sur la touche ctrl droite pour le joueur 2 */
                      if (punition[1]==0) {
                        if (nbJoueurs>=2) {
                          if (nombreDansGrille(grille2,nombreTire)) {
                            poserJeton(grille2,nombreTire);
                          }else{
                            punition[1]=2;
                          }
                        }
                      }
                      break;
                    case SDLK_RCTRL: /* Appui sur la touche ctrl droit pour le joueur 3 */
                      if (punition[2]==0) {
                        if (nbJoueurs>=3) {
                          if (nombreDansGrille(grille3,nombreTire)) {
                            poserJeton(grille3,nombreTire);
                          }else{
                            punition[2]=2;
                          }
                        }
                      }
                      break;
                    case SDLK_RIGHT: /* Appui sur la touche ctrl droit pour le joueur 4 */
                      if (punition[3]==0) {
                        if (nbJoueurs==4) {
                          if (nombreDansGrille(grille4,nombreTire)) {
                            poserJeton(grille4,nombreTire);
                          }else{
                            punition[3]=2;
                          }
                        }
                      }
                      break;
                }
              }
              break;
    }


    current_time = time(NULL) - temps;
    sprintf(timerText, "%ld", tempsmax-current_time);
    SDL_BlitSurface(fond, NULL, screen, &position);
    if (gagnant==0) {
      if (tempsmax-current_time<=0) {
        newNombre=1;
      }
      font = TTF_OpenFont(FONT_UBUNTU, 70);
      tempsRestant = TTF_RenderText_Solid(font, timerText, blanc);
      SDL_BlitSurface(tempsRestant, NULL, screen, &positiontimer);
      TTF_CloseFont(font);
      SDL_FreeSurface(tempsRestant);
    }
    afficherJeuLoto(screen,font,texte,nombreTire,nbJoueurs,grille1,grille2,grille3,grille4,punition);

    //victoire
    if (gagnant!=0) {
      continuer= victoireLoto(screen,gagnant);
      /*sprintf(timerText, "Victoire du Joueur %d", gagnant);
      font = TTF_OpenFont(FONT_UBUNTU, 70);
      tempsRestant = TTF_RenderText_Solid(font, timerText, blanc);
      SDL_BlitSurface(tempsRestant, NULL, screen, &position);
      TTF_CloseFont(font);
      SDL_FreeSurface(tempsRestant);*/
    }




    SDL_Flip(screen);
  }
  SDL_FreeSurface(fond);
  return continuer;
}
//joueur 1: ctrl g
//joueur 2: espace
//joueur 3: ctrl d
//joueur 4: flèche droite
