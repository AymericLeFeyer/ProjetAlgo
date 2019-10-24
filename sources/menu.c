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

int afficherMenu(SDL_Surface* screen)
{
  // variables pour la boucle principale
  SDL_Event event;
  int continuer = 1;

  JoueurBatailleNavale j1, j2;
  j1 = initJoueurBN(1, 10, 10);
  j2 = initJoueurBN(2, 10, 10);

  SDL_Surface *menuImage = NULL;
  menuImage = IMG_Load("assets/menu/menuBackground.jpg");
  SDL_Rect posMenuImage = newRect(0, 0, 720, 1280);

  SDL_Surface *menuLogo = NULL;
  menuLogo = IMG_Load("assets/menu/logoFourFun.png");
  SDL_Rect posMenuLogo = newRect(384, 0, 200, 512);

  SDL_Surface *boutonBatailleNavale = NULL;
  boutonBatailleNavale = IMG_Load("assets/menu/batailleNavale.png");
  SDL_Rect posBoutonBatailleNavale = newRect(0, 200, 130, 468);

  SDL_Surface *boutonPoker = NULL;
  boutonPoker = IMG_Load("assets/menu/poker.png");
  SDL_Rect posBoutonPoker = newRect(812, 330, 130, 468);

  // Sons
  Mix_Music* myMus;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  myMus = Mix_LoadMUS("assets/sounds/batailleNavale.wav");


  // Boucle principale
  while (continuer){
    SDL_BlitSurface(menuImage, NULL, screen, &posMenuImage);
    SDL_BlitSurface(menuLogo, NULL, screen, &posMenuLogo);
    SDL_BlitSurface(boutonBatailleNavale, NULL, screen, &posBoutonBatailleNavale);
    SDL_BlitSurface(boutonPoker, NULL, screen, &posBoutonPoker);

    // On regarde l'event
    SDL_WaitEvent(&event);

    // En fonction de l'event, on fait des actions
    switch(event.type)
    {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        return 0;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_b:
            Mix_PlayMusic(myMus, 1);
            continuer = affichageBatailleNavale(screen, j1, j2);
            break;
        }
        break;

    }

    // On actualise l'écran
    SDL_Flip(screen);
  }
}
