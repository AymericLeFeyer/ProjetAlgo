#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "../headers/tutoSDL.h"
#include "../headers/shortcuts.h"

int onTestLaSDL(SDL_Surface* screen) {
  // Variable principale
  int continuer = 1;

  // Evenement
  SDL_Event event;

  // Image test
  SDL_Surface* test = NULL;
  test = IMG_Load("assets/menu/logoFourFun.png");
  SDL_Rect posTest = newRect(0, 0, 200, 512);

  // Boucle principale
  while (continuer) {
    // On affiche un fond blanc
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    // On affiche l'Image
    SDL_BlitSurface(test, NULL, screen, &posTest);

    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        // Si on clique sur la croix, on ferme la fenêtre
        case SDL_QUIT:
          continuer = 0;
          return 0;
          break;
        case SDL_KEYDOWN:
          break;
      }
    }
    // On refresh la page
    SDL_Flip(screen);
  }

}
