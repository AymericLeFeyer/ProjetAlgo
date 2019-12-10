#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>

#include "../headers/global/structure.h"
#include "../headers/batailleNavale/batailleNavale.h"
#include "../headers/batailleNavale/initialisationBatailleNavale.h"
#include "../headers/global/constantes.h"
#include "../headers/global/shortcuts.h"
#include "../headers/poker/mainsPoker.h"
#include "../headers/menu.h"
#include "../headers/loto/affichageloto.h"
#include "../headers/poker/poker.h"
#include "../headers/sudoku/sudoku.h"
#include "../headers/profils/choixProfils.h"
#include "../headers/profils/score.h"
#include "../headers/profils/tabScore.h"

int afficherMenu(SDL_Surface *screen)
{
  highscore();
  int continuer = 1;
  SDL_Event event;
  Coord clic;

  //background
  SDL_Surface *back = NULL;
  back = IMG_Load("assets/menu/menuBackground.jpg");
  SDL_Rect background = newRect(0, 0, 1280, 720);
  //logo
  SDL_Surface *titre = NULL;
  titre = IMG_Load("assets/menu/logoFourFun.png");
  SDL_Rect logo = newRect(384, 0, 512, 200);
  //jeu bataille naval
  SDL_Surface *bataille = NULL;
  SDL_Surface *batailleHover = NULL;
  bataille = IMG_Load("assets/menu/batailleNavale.png");
  batailleHover = IMG_Load("assets/menu/batailleNavaleHover.png");
  SDL_Rect boutonBN = newRect(0, 240, 468, 130);
  //jeu poker
  SDL_Surface *poker = NULL;
  SDL_Surface *pokerHover = NULL;
  poker = IMG_Load("assets/menu/poker.png");
  pokerHover = IMG_Load("assets/menu/pokerHover.png");
  SDL_Rect boutonPoker = newRect(812, 240, 468, 130);
  //loto
  SDL_Surface *loto = NULL;
  SDL_Surface *lotoHover = NULL;
  loto = IMG_Load("assets/menu/loto.png");
  lotoHover = IMG_Load("assets/menu/lotoHover.png");
  SDL_Rect boutonLoto = newRect(0, 500, 468, 130);
  //sudoku
  SDL_Surface *sudoku = NULL;
  SDL_Surface *sudokuHover = NULL;
  sudoku = IMG_Load("assets/menu/sudoku.png");
  sudokuHover = IMG_Load("assets/menu/sudokuHover.png");
  SDL_Rect boutonSudoku = newRect(812, 500, 468, 130);
  // choixProfils
  SDL_Surface *profils = NULL;
  SDL_Surface *profilsHover = NULL;
  profils = IMG_Load("assets/menu/boutonProfilMenu.png");
  profilsHover = IMG_Load("assets/menu/boutonProfilMenuHover.png");
  SDL_Rect boutonProfils = newRect(540, 260, 200, 200);
  // Scores
  SDL_Surface *scoreButton = NULL;
  SDL_Surface *scoreButtonHover = NULL;
  scoreButton = IMG_Load("assets/menu/scoreButton.png");
  scoreButtonHover = IMG_Load("assets/menu/scoreButtonHover.png");
  SDL_Rect boutonScore = newRect(540, 500, 100, 200);
  //bouton régles (1 surface et 4 rectangles)
  SDL_Surface *regles = NULL;
  regles = IMG_Load("assets/menu/tuto.png");
  SDL_Rect breglesBatailleNavale = newRect(234, 370, 75, 75);
  SDL_Rect breglesPoker = newRect(1046, 370, 75, 75);
  SDL_Rect breglesLoto = newRect(234, 630, 75, 75);
  SDL_Rect breglesSudoku = newRect(1046, 630, 75, 75);



  // Sons
  Mix_Music *myMus;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  myMus = Mix_LoadMUS("assets/sounds/batailleNavale.wav");

  //tout afficher
  while (continuer > 0)
  {
    SDL_BlitSurface(back, NULL, screen, &background);
    SDL_BlitSurface(titre, NULL, screen, &logo);

    SDL_BlitSurface(regles, NULL, screen, &breglesBatailleNavale);
    SDL_BlitSurface(regles, NULL, screen, &breglesPoker);
    SDL_BlitSurface(regles, NULL, screen, &breglesLoto);
    SDL_BlitSurface(regles, NULL, screen, &breglesSudoku);

    //evenements
    clic.x = event.button.x;
    clic.y = event.button.y;

    // Hover boutons
    if (posInclusion(clic.x, clic.y, boutonBN))
      SDL_BlitSurface(batailleHover, NULL, screen, &boutonBN);
    else
      SDL_BlitSurface(bataille, NULL, screen, &boutonBN);
    if (posInclusion(clic.x, clic.y, boutonPoker))
      SDL_BlitSurface(pokerHover, NULL, screen, &boutonPoker);
    else
      SDL_BlitSurface(poker, NULL, screen, &boutonPoker);
    if (posInclusion(clic.x, clic.y, boutonLoto))
      SDL_BlitSurface(lotoHover, NULL, screen, &boutonLoto);
    else
      SDL_BlitSurface(loto, NULL, screen, &boutonLoto);
    if (posInclusion(clic.x, clic.y, boutonSudoku))
      SDL_BlitSurface(sudokuHover, NULL, screen, &boutonSudoku);
    else
      SDL_BlitSurface(sudoku, NULL, screen, &boutonSudoku);
    if (posInclusion(clic.x, clic.y, boutonProfils))
      SDL_BlitSurface(profilsHover, NULL, screen, &boutonProfils);
    else
      SDL_BlitSurface(profils, NULL, screen, &boutonProfils);
    if (posInclusion(clic.x, clic.y, boutonScore))
      SDL_BlitSurface(scoreButtonHover, NULL, screen, &boutonScore);
    else
      SDL_BlitSurface(scoreButton, NULL, screen, &boutonScore);



    tabJP tabProfils;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          //conditions des clics
          if ((posInclusion(clic.x, clic.y, boutonBN)))
          {
            Mix_PlayMusic(myMus, 1);
            continuer = selectionProfil(screen, 2, tabProfils);
            if (tabProfils[0].nom[0] == '0') return 0;
            printf("%s, %s\n",tabProfils[0].nom, tabProfils[1].nom );
            continuer = affichageBatailleNavale(screen, tabProfils);
            if (continuer == 0)
              return 0;
          }
          if ((posInclusion(clic.x, clic.y, boutonPoker)))
          {
            continuer = affichagePoker(screen);
            if (continuer == 0)
              return 0;
          }
          if ((posInclusion(clic.x, clic.y, boutonLoto)))
          {
            continuer = menuChoixJoueur(screen); //raméne au menu de choix de joueur du loto
            if (continuer == 0)
              return 0;
          }
          if ((posInclusion(clic.x, clic.y, boutonSudoku)))
          {
            continuer = affichageSudoku(screen);
            if (continuer == 0)
              return 0;
          }

          if ((posInclusion(clic.x, clic.y, boutonProfils)))
          {
            afficherProfils(screen);
          }
          if ((posInclusion(clic.x, clic.y, boutonScore)))
          {
            afficherTableauScore(screen);
          }
          //conditions de clics pour les régles :
          if (posInclusion(clic.x, clic.y, breglesBatailleNavale))
          {
            continuer = reglesBT(screen);
          }
          if (posInclusion(clic.x, clic.y, breglesPoker))
          {
            continuer = reglesPoker(screen);
          }
          if (posInclusion(clic.x, clic.y, breglesLoto))
          {
            continuer = reglesLoto(screen);
          }
          if (posInclusion(clic.x, clic.y, breglesSudoku))
          {
            continuer = reglesSudoku(screen);
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
  SDL_FreeSurface(profils);
  SDL_FreeSurface(profilsHover);
  SDL_FreeSurface(regles);
  Mix_FreeMusic(myMus);
  Mix_CloseAudio();
}

//affiche les regles de la bataille Navale
int reglesBT(SDL_Surface *screen){
  int continuer = 1;
  SDL_Event event;
  Coord clic;
  SDL_Surface *reglesbt = NULL;
  reglesbt = IMG_Load("assets/imagesRegles/reglesBatailleNavale.png");
  SDL_Rect reglesBatailleNavale = newRect(0, 0, 1280, 720);

  while (continuer ==1){
    SDL_BlitSurface(reglesbt, NULL, screen, &reglesBatailleNavale);

    SDL_Flip(screen);
    clic.x = event.button.x;
    clic.y = event.button.y;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;

        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          //conditions clics
          if (posInclusion(clic.x, clic.y, reglesBatailleNavale))
          {
            continuer = 2;
          }
        }
        break;
      }
    }
  }
  SDL_FreeSurface(reglesbt);
  return continuer;
}

//affiche les regles du poker
int reglesPoker(SDL_Surface *screen){
  int continuer = 1;
  SDL_Event event;
  Coord clic;
  SDL_Surface *reglesp = NULL;
  reglesp = IMG_Load("assets/imagesRegles/reglesPoker.png");
  SDL_Rect reglesPoker = newRect(0, 0, 1280, 720);

  while (continuer ==1){
    SDL_BlitSurface(reglesp, NULL, screen, &reglesPoker);

    SDL_Flip(screen);
    clic.x = event.button.x;
    clic.y = event.button.y;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;

        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          //conditions clics
          if (posInclusion(clic.x, clic.y, reglesPoker))
          {
            continuer = 2;
          }
        }
        break;
      }
    }
  }
  SDL_FreeSurface(reglesp);
  return continuer;
}

//affiche les regles du sudoku
int reglesSudoku(SDL_Surface *screen){
  int continuer = 1;
  SDL_Event event;
  Coord clic;
  SDL_Surface *regless = NULL;
  regless = IMG_Load("assets/imagesRegles/reglesSudoku.png");
  SDL_Rect reglesSudoku = newRect(0, 0, 1280, 720);

  while (continuer ==1){
    SDL_BlitSurface(regless, NULL, screen, &reglesSudoku);

    SDL_Flip(screen);
    clic.x = event.button.x;
    clic.y = event.button.y;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;

        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          //conditions clics
          if (posInclusion(clic.x, clic.y, reglesSudoku))
          {
            continuer = 2;
          }
        }
        break;
      }
    }
  }
  SDL_FreeSurface(regless);
  return continuer;
}

//affiche les regles du loto
int reglesLoto(SDL_Surface *screen){
  int continuer = 1;
  SDL_Event event;
  Coord clic;
  SDL_Surface *reglesl = NULL;
  reglesl = IMG_Load("assets/imagesRegles/reglesLoto.png");
  SDL_Rect reglesLoto = newRect(0, 0, 1280, 720);

  while (continuer ==1){
    SDL_BlitSurface(reglesl, NULL, screen, &reglesLoto);

    SDL_Flip(screen);
    clic.x = event.button.x;
    clic.y = event.button.y;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;

        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          //conditions clics
          if (posInclusion(clic.x, clic.y, reglesLoto))
          {
            continuer = 2;
          }
        }
        break;
      }
    }
  }
  SDL_FreeSurface(reglesl);
  return continuer;
}
