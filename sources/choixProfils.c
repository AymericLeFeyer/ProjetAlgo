#include <SDL/SDL_image.h>
#include "../headers/structure.h"
#include "../headers/shortcuts.h"

void afficherProfils(SDL_Surface* screen) {
  SDL_Surface* ecranProfils = NULL;
  SDL_Surface* profilGris = NULL;

  ecranProfils = IMG_Load("assets/profils/ecranProfils.jpg");
  profilGris = IMG_Load("assets/profils/profilGris.png");

  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect positionsFrameProfils[5][2];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 2; j++) {
      positionsFrameProfils[i][j] = newRect(0 + 256*i, 186 + 260*j, 256, 256);
    }
  }

  int profils[5][2] = {0};
  profils[0][0] = 1;

  int continuer = 1;
  SDL_Event event;

  while (continuer) {
    SDL_BlitSurface(ecranProfils, NULL, screen, &fullscreen);
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 2; j++) {
        if (!profils[i][j]) SDL_BlitSurface(profilGris, NULL, screen, &positionsFrameProfils[i][j]);
      }
    }

    while (SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          continuer = 0;
          break;
        }
    }
    SDL_Flip(screen);
  }
  SDL_FreeSurface(ecranProfils);
  SDL_FreeSurface(profilGris);
}
