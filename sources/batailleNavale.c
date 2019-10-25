#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/shortcuts.h"
#include "../headers/constantes.h"
#include "../headers/structure.h"
#include "../headers/batailleNavale.h"
#include "../headers/interface.h"
#include "../headers/placement.h"
#include "../headers/tir.h"

int affichageBatailleNavale(SDL_Surface* screen, JoueurBatailleNavale j1, JoueurBatailleNavale j2)
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
        return 0;
        break;


    }
    int t = 0;
    switch (phase) {
      case 1:
        if (phasePlacement(screen, &j1, &continuer)) phase = 2;
        else continuer = 0;
        return 0;
        break;
      case 2:
        if (phasePlacement(screen, &j2, &continuer)) phase = 3;
        else continuer = 0;
        return 0;
        break;
      case 3:
        t = 0;
        if (nbBateauxVivant(j1) > 0)
          t = aToiDeJouer(screen, &j1, &j2);
        if (t == 1) phase = 4;
        else continuer = 0;
        return 0;


        break;
      case 4:
        t = 0;
        if (nbBateauxVivant(j2) > 0)
          t = aToiDeJouer(screen, &j2, &j1);
        if (t == 1) phase = 3;
        else continuer = 0;
        return 0;

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

void afficherBateaux(SDL_Surface* screen, JoueurBatailleNavale j)
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

void afficherBateauxSurLeCote(SDL_Surface* screen, JoueurBatailleNavale j1, JoueurBatailleNavale j2) {
  SDL_Rect pos10 = newRect(0, 168, 0, 0);
  SDL_Rect pos11 = newRect(0, 232, 0, 0);
  SDL_Rect pos12 = newRect(0, 296, 0, 0);
  SDL_Rect pos13 = newRect(0, 360, 0, 0);
  SDL_Rect pos14 = newRect(0, 424, 0, 0);

  SDL_Rect pos20 = newRect(1152, 168, 0, 0);
  SDL_Rect pos21 = newRect(1088, 232, 0, 0);
  SDL_Rect pos22 = newRect(1088, 296, 0, 0);
  SDL_Rect pos23 = newRect(1024, 360, 0, 0);
  SDL_Rect pos24 = newRect(960, 424, 0, 0);

  if (j1.tab[0].pv > 0) SDL_BlitSurface(j1.tab[0].est, NULL, screen, &pos10);
  if (j1.tab[1].pv > 0) SDL_BlitSurface(j1.tab[1].est, NULL, screen, &pos11);
  if (j1.tab[2].pv > 0) SDL_BlitSurface(j1.tab[2].est, NULL, screen, &pos12);
  if (j1.tab[3].pv > 0) SDL_BlitSurface(j1.tab[3].est, NULL, screen, &pos13);
  if (j1.tab[4].pv > 0) SDL_BlitSurface(j1.tab[4].est, NULL, screen, &pos14);

  if (j2.tab[0].pv > 0) SDL_BlitSurface(j2.tab[0].west, NULL, screen, &pos20);
  if (j2.tab[1].pv > 0) SDL_BlitSurface(j2.tab[1].west, NULL, screen, &pos21);
  if (j2.tab[2].pv > 0) SDL_BlitSurface(j2.tab[2].west, NULL, screen, &pos22);
  if (j2.tab[3].pv > 0) SDL_BlitSurface(j2.tab[3].west, NULL, screen, &pos23);
  if (j2.tab[4].pv > 0) SDL_BlitSurface(j2.tab[4].west, NULL, screen, &pos24);

}
