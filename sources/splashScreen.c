#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "../headers/global/structure.h"
#include "../headers/global/constantes.h"
#include "../headers/global/shortcuts.h"
#include "../headers/menu.h"

void afficherSplash(SDL_Surface *screen)
{
  int delaySplash = 0; // temps normal 1000

  // variables pour la boucle principale
  SDL_Event event;
  int continuer = 1;
  int i = 0;
  int aff = 0;
  int temps = 0;
  int tempsIni = 0;

  SDL_Surface *aymeric = NULL;
  aymeric = IMG_Load("assets/team/aymericNoirP.png");
  SDL_Rect posAymeric = newRect(950, 380, 340, 340);

  SDL_Surface *angele = NULL;
  angele = IMG_Load("assets/team/angeleNoireP.png");
  SDL_Rect posAngele = newRect(200, 420, 340, 340);

  SDL_Surface *steven = NULL;
  steven = IMG_Load("assets/team/stevenNoirP.png");
  SDL_Rect posSteven = newRect(700, 380, 340, 340);

  SDL_Surface *guillaume = NULL;
  guillaume = IMG_Load("assets/team/guillaumeNoirP.png");
  SDL_Rect posGuillaume = newRect(-50, 410, 340, 340);

  SDL_Surface *dylan = NULL;
  dylan = IMG_Load("assets/team/dylanNoirP.png");
  SDL_Rect posDylan = newRect(450, 380, 340, 340);

  SDL_Surface *menuLogo = NULL;
  menuLogo = IMG_Load("assets/menu/logoFourFun.png");
  SDL_Rect posMenuLogo = newRect(384, 0, 200, 512);

  SDL_Surface *petitTexte = NULL;
  petitTexte = IMG_Load("assets/petitTexte.png");
  SDL_Rect posPetitTexte = newRect(290, 250, 100, 700);

  SDL_Surface *cachePetitTexte = NULL;
  cachePetitTexte = IMG_Load("assets/cachePetitTexte.jpg");
  SDL_Rect posCachePetitTexte = newRect(290, 250, 100, 700);

  SDL_Surface *background = NULL;
  background = IMG_Load("assets/splash.jpg");
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);

  // Boucle principale
  while (continuer == 1)
  {
    SDL_BlitSurface(background, NULL, screen, &fullscreen);
    SDL_BlitSurface(guillaume, NULL, screen, &posGuillaume);

    SDL_Delay(delaySplash);

    SDL_BlitSurface(angele, NULL, screen, &posAngele);

    SDL_Delay(delaySplash);

    SDL_BlitSurface(dylan, NULL, screen, &posDylan);

    SDL_Delay(delaySplash);

    SDL_BlitSurface(steven, NULL, screen, &posSteven);

    SDL_Delay(delaySplash);

    SDL_BlitSurface(aymeric, NULL, screen, &posAymeric);

    SDL_Delay(delaySplash);

    SDL_BlitSurface(menuLogo, NULL, screen, &posMenuLogo);
    SDL_Flip(screen);
    // Clignotement du texte
    tempsIni = SDL_GetTicks();
    if (tempsIni - temps > 500 && aff == 0)
    {
      SDL_BlitSurface(cachePetitTexte, NULL, screen, &posCachePetitTexte);
      aff = 1;
      temps = tempsIni;
    }
    if (tempsIni - temps > 500 && aff == 1)
    {
      SDL_BlitSurface(petitTexte, NULL, screen, &posPetitTexte);
      if (tempsIni - temps > 1500)
      {
        aff = 0;
        temps = tempsIni;
      }
    }

    // On regarde l'event
    SDL_PollEvent(&event);

    // En fonction de l'event, on fait des actions
    switch (event.type)
    {
    // Si on clique sur la croix, on ferme la fenêtre
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym != SDLK_ESCAPE)
      {
        continuer = afficherMenu(screen);
      }
      else
      {
        continuer = 0;
      }
      break;
    }

    // On actualise l'écran
    SDL_Flip(screen);
  }

  SDL_FreeSurface(aymeric);
  SDL_FreeSurface(dylan);
  SDL_FreeSurface(angele);
  SDL_FreeSurface(steven);
  SDL_FreeSurface(guillaume);
  SDL_FreeSurface(menuLogo);
  SDL_FreeSurface(petitTexte);
  SDL_FreeSurface(cachePetitTexte);
}
