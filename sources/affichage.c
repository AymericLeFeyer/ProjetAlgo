#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/shortcuts.h"
#include "../headers/constantes.h"
#include "../headers/structure.h"
#include "../headers/affichage.h"
#include "../headers/interface.h"
#include "../headers/placement.h"
#include "../headers/tir.h"

void affichageBatailleNavale(SDL_Surface* screen, Joueur j1, Joueur j2)
{
  // variables pour la boucle principale
  SDL_Event event;
  int continuer = 1;

  /*  Index de la phase en cours
  1 : Placement J1
  2 : Placement J2
  3 : Tour J1
  4 : Tour J2
  */
  int phase = 1;

  // Polices
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);

  SDL_Color rouge = {255, 0, 0, 0};



  // Position de la grille sur l'écran
  SDL_Rect positionGrille = newRect((WIDTH_GAME - 640)/2, (HEIGHT_GAME - 640)/2, 640, 640);

  // Variables utiles
  Coord c;

  int nbBateauxValides = 0;

  // Boucle principale
  while (continuer){

    // Position du curseur
    c.x = event.button.x;
    c.y = event.button.y;

    // On regarde l'event
    SDL_PollEvent(&event);

    // En fonction de l'event, on fait des actions
    switch(event.type)
    {
      // Si on clique sur la croix, on ferme la fenêtre
      case SDL_QUIT:
        continuer = 0;
        break;


    }
    switch (phase) {
      case 1:
        phasePlacement(screen, &j1, &continuer);
        phase++;
        break;
      case 2:
        phasePlacement(screen, &j2, &continuer);
        phase++;
        break;
      case 3:
        aToiDeJouer(screen, &j1);
        phase = 4;
        break;
      case 4:
        aToiDeJouer(screen, &j2);
        phase = 3;
        break;
    }

    // On affiche les bateaux
    //afficherBateaux(screen, j1);

    // Afficher les textes pour la bataille navale
    afficherInterfaceBatailleNavale(screen, font);

    char result[50];
    sprintf(result, "%d", nbCaseBateau(j1));




    // On actualise l'écran
    SDL_Flip(screen);
  }
}

void afficherBateaux(SDL_Surface* screen, Joueur j)
{
  // On affiche le bateau en fonction de sa direction
  for(int i=0;i<=4;i++){
    switch (j.tab[i].direction) {
      case 1:
        SDL_BlitSurface(j.tab[i].nord, NULL, screen, &j.tab[i].r);
        break;
      case 2:
        SDL_BlitSurface(j.tab[i].west, NULL, screen, &j.tab[i].r);
        break;
      case 3:
        SDL_BlitSurface(j.tab[i].sud, NULL, screen, &j.tab[i].r);
        break;
      case 4:
        SDL_BlitSurface(j.tab[i].est, NULL, screen, &j.tab[i].r);
        break;
      default:
        break;
      }
    }
  // Flip
  SDL_Flip(screen);
}
void ciblerCase(SDL_Surface* screen, SDL_Surface* c, SDL_Rect pos) {
  SDL_BlitSurface(c, NULL, screen, &pos);
}
