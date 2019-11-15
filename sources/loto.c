#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../headers/shortcuts.h"
#include "../headers/timerLoto.h"
#include "../headers/loto.h"
#include "../headers/constantes.h"

void loto(SDL_Surface* screen){
  int a;
  Uint32 start;
  int continuer=1;
  SDL_Event event;
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  SDL_Color blanc = {255, 255, 255, 0};
  SDL_Surface* tempsRestant=NULL;
  SDL_Rect position = newRect(0, 0, 0, 0);
  SDL_Rect position2 = newRect(946, 336, 0, 0);
  int FPS=60;
  int tempsmax=15;
  int temps=0;
  SDL_Surface* fond=NULL;
  fond=IMG_Load("assets/Loto/backLoto.png");
  while (continuer){
    start= SDL_GetTicks();
    SDL_PollEvent(&event);
    switch(event.type)
    {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        break;
    }
    regulerFPS(FPS,start);
    SDL_BlitSurface(fond, NULL, screen, &position);
    a=timerLoto(FPS,&temps,tempsmax,position2,font,blanc,tempsRestant,screen);
    if(a){
      continuer=0;
    }
    SDL_Flip(screen);
  }
}
