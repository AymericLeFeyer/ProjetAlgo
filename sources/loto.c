#include <stdio.h>
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

int afficherLoto(SDL_Surface* screen){
  int grille1[9][3];
  //carteLoto(grille1);
  long current_time;
  long temps;
  int newNombre=1;
  Coord c;
  int nbJoueurs;
  Uint32 start;
  int continuer=1;
  SDL_Event event;
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 70);
  SDL_Color blanc = {0, 0, 0, 0};
  SDL_Surface* tempsRestant=NULL;
  SDL_Rect position = newRect(0, 0, 0, 0);
  SDL_Rect positiontimer = newRect(1010, 336, 0, 0);
  SDL_Rect boutonMenu = newRect(133,290,84,154);
  int FPS=60;
  int tempsmax=5;
  SDL_Surface* fond=NULL;
  char timerText[10];
  fond=IMG_Load("assets/Loto/backLoto.png");
  while (continuer==1){
    //changement de nombre
    if(newNombre==1){
      newNombre=0;
      temps=time(NULL);
    }
    c.x = event.button.x;
    c.y = event.button.y;
    start= SDL_GetTicks();
    SDL_PollEvent(&event);
    switch(event.type)
    {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        break;

      case SDL_MOUSEBUTTONDOWN:
        if(posInclusion(c.x, c.y, boutonMenu)){
          continuer=2;
        }
        break;


      case SDL_KEYDOWN:
              switch (event.key.keysym.sym)
              {
                  case SDLK_LCTRL: /* Appui sur la touche ctrl gauche pour le joueur 1 */
                      continuer = 0;
                      break;
                  case SDLK_SPACE: /* Appui sur la touche ctrl droite pour le joueur 2 */
                      continuer = 0;
                      break;
                  case SDLK_RCTRL: /* Appui sur la touche ctrl droit pour le joueur 3 */
                      continuer = 0;
                      break;
                  case SDLK_RIGHT: /* Appui sur la touche ctrl droit pour le joueur 4 */
                      continuer = 0;
                      break;
              }
              break;
    }
    //afficheGrilleLoto(grille1,screen,1);

    current_time = time(NULL) - temps;
    sprintf(timerText, "%ld", tempsmax-current_time);
    if (tempsmax-current_time<=0) {
      newNombre=1;
    }
    tempsRestant = creerTexte(screen, timerText, blanc, font);
    SDL_BlitSurface(fond, NULL, screen, &position);
    SDL_BlitSurface(tempsRestant, NULL, screen, &positiontimer);
    SDL_Flip(screen);
  }
  if(continuer==2){
    return 1;
  }else{
    return continuer;
  }
}
//joueur 1: ctrl g
//joueur 2: espace
//joueur 3: ctrl d
//joueur 4: flèche droite

//133 290
