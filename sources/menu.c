#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "../headers/structure.h"
#include "../headers/batailleNavale.h"
#include "../headers/initialisation.h"
#include "../headers/constantes.h"
#include "../headers/shortcuts.h"
#include "../headers/mainsPoker.h"
#include "../headers/menu.h"
#include "../headers/poker.h"

int afficherMenu(SDL_Surface* screen){
  int continuer=1;
  SDL_Event event;
  JoueurBatailleNavale j1, j2;
  j1 = initJoueurBN(1, 10, 10);
  j2 = initJoueurBN(2, 10, 10);
  Coord clic;

  //background
  SDL_Surface* back = NULL;
  back = IMG_Load("assets/menu/menuBackground.jpg");
  SDL_Rect background = newRect(0, 0, 1280, 720);
  //logo
  SDL_Surface* titre = NULL;
  titre = IMG_Load("assets/menu/logoFourFun.png");
  SDL_Rect logo = newRect(384, 0, 512, 200);
  //jeu bataille naval
  SDL_Surface* bataille = NULL;
  bataille = IMG_Load("assets/menu/batailleNavale.png");
  SDL_Rect boutonBN = newRect(0, 260, 468, 130);
  //jeu poker
  SDL_Surface* poker = NULL;
  poker = IMG_Load("assets/menu/poker.png");
  SDL_Rect boutonPoker = newRect(812, 260, 468, 130);
  //jeu loto (image a remplacer)
  SDL_Surface* loto = NULL;
  loto = IMG_Load("assets/menu/batailleNavale.png");
  SDL_Rect boutonLoto = newRect(0, 520, 468, 130);
  //jeu sudoku (image a remplacer)
  SDL_Surface* sudoku = NULL;
  sudoku = IMG_Load("assets/menu/poker.png");
  SDL_Rect boutonSudoku = newRect(812, 520, 468, 130);

  // Sons
  Mix_Music* myMus;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  myMus = Mix_LoadMUS("assets/sounds/batailleNavale.wav");

//tout afficher
  while(continuer){
    SDL_BlitSurface(back, NULL, screen, &background);
    SDL_BlitSurface(titre, NULL, screen, &logo);
    SDL_BlitSurface(bataille, NULL, screen, &boutonBN);
    SDL_BlitSurface(poker, NULL, screen, &boutonPoker);
    SDL_BlitSurface(loto, NULL, screen, &boutonLoto);
    SDL_BlitSurface(sudoku, NULL, screen, &boutonSudoku);

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
                if ((posInclusion(clic.x, clic.y, boutonBN))) {
                  //lancer bataille navale
                  Mix_PlayMusic(myMus, 1);
                  continuer = affichageBatailleNavale(screen, j1, j2);
                  // Liberation bataille Navale
                  freeJoueurBN(&j1);
                  freeJoueurBN(&j2);
                }
                if ((posInclusion(clic.x, clic.y, boutonPoker))) {
                  continuer = affichagePoker(screen);
                  if (!continuer) return 0;
                }
                if ((posInclusion(clic.x, clic.y, boutonLoto))) {
                  //lancer loto
                }
                if ((posInclusion(clic.x, clic.y, boutonSudoku))) {
                  //lancer sudoku
                }
            }
            break;

        }
      }


  }
  // Liberation
  SDL_FreeSurface(back);
  SDL_FreeSurface(titre);
  SDL_FreeSurface(bataille);
  SDL_FreeSurface(poker);
  SDL_FreeSurface(loto);
  SDL_FreeSurface(sudoku);
  Mix_FreeMusic(myMus);
  Mix_CloseAudio();
}
