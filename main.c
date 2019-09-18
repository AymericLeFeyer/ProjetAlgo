#include <stdio.h>
#include <SDL/SDL.h>
//ceci est un test, rien de plus
//test
int main(int argc, char *argv[])
{
  // Variable de la boucle principale
  int continuer = 1;

  // Initialisation de la SDL
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
  {
    fprintf(stderr, "Erreur d'initialisation de la SDL");
    exit(EXIT_FAILURE);
  }

  // Création de la surface
  SDL_Surface *screen = NULL;

  // Affichage de la fenêtre

  screen = SDL_SetVideoMode(500 , 500, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

  // Nom de la fenêtre
  SDL_WM_SetCaption("Test SDL !", NULL);

  // Event pour la détection des entrées (clavier, souris)
  //Test-icule
  SDL_Event event;

  // Boucle principale
  while (continuer){

    // On regarde l'event
    SDL_WaitEvent(&event);

    // En fonction de l'event, on fait des actions
    switch(event.type)
    {
      // Si on clique sur la croix, on fenêtre
      case SDL_QUIT:
        continuer = 0;
    }

    // On remplit la surface screen avec la couleur, ici du bleu (le meilleur bleu qui existe sur cette terre)
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 161, 255));

    // On "actualise" le tout
    SDL_Flip(screen);
  }

  //test guillaume

  // On quitte le programme, sans erreur
  return EXIT_SUCCESS;
}
