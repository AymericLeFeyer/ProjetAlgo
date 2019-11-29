#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>

#include "../headers/structure.h"
#include "../headers/batailleNavale.h"
#include "../headers/initialisation.h"
#include "../headers/constantes.h"
#include "../headers/shortcuts.h"
#include "../headers/mainsPoker.h"
#include "../headers/menu.h"
#include "../headers/affichageloto.h"
#include "../headers/poker.h"
#include "../headers/affichageSudoku.h"
#include "../headers/choixProfils.h"

int afficherMenu(SDL_Surface* screen){
  int continuer=1;
  SDL_Event event;
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
  SDL_Surface* batailleHover = NULL;
  bataille = IMG_Load("assets/menu/batailleNavale.png");
  batailleHover = IMG_Load("assets/menu/batailleNavaleHover.png");
  SDL_Rect boutonBN = newRect(0, 260, 468, 130);
  //jeu poker
  SDL_Surface* poker = NULL;
  SDL_Surface* pokerHover = NULL;
  poker = IMG_Load("assets/menu/poker.png");
  pokerHover = IMG_Load("assets/menu/pokerHover.png");
  SDL_Rect boutonPoker = newRect(812, 260, 468, 130);
  //loto
  SDL_Surface* loto = NULL;
  SDL_Surface* lotoHover = NULL;
  loto = IMG_Load("assets/menu/loto.png");
  lotoHover = IMG_Load("assets/menu/lotoHover.png");
  SDL_Rect boutonLoto = newRect(0, 520, 468, 130);
  //sudoku
  SDL_Surface* sudoku = NULL;
  SDL_Surface* sudokuHover = NULL;
  sudoku = IMG_Load("assets/menu/sudoku.png");
  sudokuHover = IMG_Load("assets/menu/sudokuHover.png");
  SDL_Rect boutonSudoku = newRect(812, 520, 468, 130);

  // Sons
  Mix_Music* myMus;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  myMus = Mix_LoadMUS("assets/sounds/batailleNavale.wav");

//tout afficher
  while(continuer>0){
    SDL_BlitSurface(back, NULL, screen, &background);
    SDL_BlitSurface(titre, NULL, screen, &logo);


//evenements
    clic.x=event.button.x;
    clic.y=event.button.y;

    // Hover boutons
    if (posInclusion(clic.x, clic.y, boutonBN)) SDL_BlitSurface(batailleHover, NULL, screen, &boutonBN);
    else SDL_BlitSurface(bataille, NULL, screen, &boutonBN);
    if (posInclusion(clic.x, clic.y, boutonPoker)) SDL_BlitSurface(pokerHover, NULL, screen, &boutonPoker);
    else SDL_BlitSurface(poker, NULL, screen, &boutonPoker);
    if (posInclusion(clic.x, clic.y, boutonLoto)) SDL_BlitSurface(lotoHover, NULL, screen, &boutonLoto);
    else SDL_BlitSurface(loto, NULL, screen, &boutonLoto);
    if (posInclusion(clic.x, clic.y, boutonSudoku)) SDL_BlitSurface(sudokuHover, NULL, screen, &boutonSudoku);
    else SDL_BlitSurface(sudoku, NULL, screen, &boutonSudoku);

    while(SDL_PollEvent(&event)){
      switch(event.type) {
        case SDL_QUIT:
          continuer = 0;
          return 0;

          break;
          case SDL_KEYDOWN:
            afficherProfils(screen);
            break;

          case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT){
                //conditions des clics
                if ((posInclusion(clic.x, clic.y, boutonBN))) {
                  //  Mix_PlayMusic(myMus, 1);
                  continuer = affichageBatailleNavale(screen);
                  if (continuer == 0) return 0;

                }
                if ((posInclusion(clic.x, clic.y, boutonPoker))) {
                  continuer = affichagePoker(screen);
                  if (continuer == 0) return 0;

                }
                if ((posInclusion(clic.x, clic.y, boutonLoto))) {
                   continuer = menuChoixJoueur(screen); //raméne au menu de choix de joueur du loto
                   if (continuer == 0) return 0;
                }
                if ((posInclusion(clic.x, clic.y, boutonSudoku))) {
                  continuer = affichageSudoku(screen);
                  if (continuer == 0) return 0;

                }
            }
            break;
        }


        SDL_Flip(screen);
      }

  }
  // Liberation
  SDL_FreeSurface(back);
  SDL_FreeSurface(titre);
  SDL_FreeSurface(bataille);
  SDL_FreeSurface(batailleHover);
  SDL_FreeSurface(poker);
  SDL_FreeSurface(pokerHover);
  SDL_FreeSurface(loto);
  SDL_FreeSurface(lotoHover);
  SDL_FreeSurface(sudoku);
  SDL_FreeSurface(sudokuHover);
  Mix_FreeMusic(myMus);
  Mix_CloseAudio();
}
