#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../../headers/global/shortcuts.h"
#include "../../headers/global/constantes.h"
#include "../../headers/global/structure.h"
#include "../../headers/batailleNavale/batailleNavale.h"
#include "../../headers/global/interface.h"
#include "../../headers/batailleNavale/placementBateaux.h"
#include "../../headers/batailleNavale/initialisationBatailleNavale.h"
#include "../../headers/batailleNavale/tourBatailleNavale.h"
#include "../../headers/profils/chargement.h"
#include "../../headers/profils/sauvegarde.h"

int affichageBatailleNavale(SDL_Surface *screen, tabJP jp)
{
  tabP p;
  chargementProfils(p);

  JoueurBatailleNavale j1, j2;

  int calcul = 0;
  j1 = initJoueurBN(1, 10, 10);
  j2 = initJoueurBN(2, 10, 10);
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

  TTF_Font *fontVictoire = NULL;

  fontVictoire = TTF_OpenFont(FONT_UBUNTU, 36);
  SDL_Color noir = {0, 0, 0, 0};

  // Bouton bouton
  SDL_Surface *boutonMenu = NULL;
  boutonMenu = IMG_Load("assets/batailleNavale/boutonMenu.png");
  SDL_Rect posBoutonMenu = newRect(10, HEIGHT_GAME - 100 - 10, 100, 150);

  // Ecrans de victoires
  SDL_Surface *victoire1 = NULL;
  SDL_Surface *victoire2 = NULL;
  victoire1 = IMG_Load("assets/batailleNavale/victoire1.png");
  victoire2 = IMG_Load("assets/batailleNavale/victoire2.png");
  SDL_Rect posVictoire1 = newRect(0, 0, 0, 0);
  SDL_Rect posVictoire2 = newRect(0, 0, 0, 0);
  // Infos victoires
  SDL_Surface *nbCoupsVictoire = NULL;
  SDL_Surface *precisionVictoire = NULL;
  char strCoups[10];
  char strPrecision[10];
  nbCoupsVictoire = creerTexte(screen, strCoups, noir, fontVictoire);
  precisionVictoire = creerTexte(screen, strPrecision, noir, fontVictoire);
  SDL_Rect nbCoupsVictoireRect = newRect(446, 336, 0, 0);
  SDL_Rect precisionVictoireRect = newRect(755, 336, 0, 0);

  // Position de la grille sur l'écran
  SDL_Rect positionGrille = newRect((WIDTH_GAME - 640) / 2, (HEIGHT_GAME - 640) / 2, 640, 640);

  // Variables utiles
  Coord c;

  int nbBateauxValides = 0;

  int coulej1[5] = {0, 0, 0, 0, 0};
  int coulej2[5] = {0, 0, 0, 0, 0};
  // Boucle principale
  while (continuer == 1)
  {
    // On regarde l'event
    SDL_PollEvent(&event);

    // En fonction de l'event, on fait des actions
    switch (event.type)
    {
    // Si on clique sur la croix, on ferme la fenêtre
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_MOUSEBUTTONDOWN:
      //if (phase == 5) {
      posBoutonMenu = newRect(10, HEIGHT_GAME - 100 - 10, 100, 150);
      c.x = event.button.x;
      c.y = event.button.y;
      if (posInclusion(c.x, c.y, posBoutonMenu))
      {
        continuer = 2;
      }
      //}
      break;
    }
    int t = 0;
    switch (phase)
    {
    case 1:
      // Phase de placement pour le joueur 1
      t = phasePlacement(screen, &j1, &continuer);
      if (t == 1)
        phase = 2;
      else if (t == 2)
      {
        continuer = 2;
      }
      else
      {
        continuer = 0;
      }
      break;
    case 2:
      // Phase de placement pour le joueur 2
      t = phasePlacement(screen, &j2, &continuer);
      if (t == 1)
        phase = 3;
      else if (t == 2)
      {
        continuer = 2;
      }
      else
      {
        continuer = 0;
      }
      break;
    case 3:
      // Si la partie n'est pas finie, le joueur 1 joue
      t = 0;
      if (nbBateauxVivant(j1) > 0)
        t = aToiDeJouer(screen, &j1, &j2, coulej1);
      if (t == 1)
        phase = 4;
      else if (t == 2)
      {
        continuer = 2;
      }
      else if (t == 3)
      {
        phase = 5;
      }
      else
      {
        continuer = 0;
      }
      break;
    case 4:
      // Si la partie n'est pas finie, le joueur 2 joue
      t = 0;
      if (nbBateauxVivant(j2) > 0)
        t = aToiDeJouer(screen, &j2, &j1, coulej2);
      if (t == 1)
        phase = 3;
      else if (t == 2)
      {
        continuer = 2;
      }
      else if (t == 3)
      {
        phase = 5;
      }
      else
      {
        continuer = 0;
      }
      break;
    case 5:
      // La partie est finie
      // Ecrans de victoires
      // Ecran blanc en fond
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
      if (nbBateauxVivant(j1) == 0)
      {
        // On affiche l'image du joueur 2
        SDL_BlitSurface(victoire2, NULL, screen, &posVictoire2);
        // On affiche le nombre de coups
        sprintf(strCoups, "%d", nbCaseNonVide(j2.infos));
        calcul = (int)(100 * ((float)((float)17 / (float)nbCaseNonVide(j2.infos))));
        // On affiche la precision
        sprintf(strPrecision, "%d%%", calcul);
        SDL_FreeSurface(nbCoupsVictoire);
        SDL_FreeSurface(precisionVictoire);
        nbCoupsVictoire = creerTexte(screen, strCoups, noir, fontVictoire);
        precisionVictoire = creerTexte(screen, strPrecision, noir, fontVictoire);
        SDL_BlitSurface(nbCoupsVictoire, NULL, screen, &nbCoupsVictoireRect);
        SDL_BlitSurface(precisionVictoire, NULL, screen, &precisionVictoireRect);
        // Calcul pour les profils
        if (calcul >= jp[1].scoreNavale)
        {
          for (int i = 0; i < 10; i++)
          {
            if (jp[1].ID == p[i].ID)
            {
              p[i].scoreNavale = calcul;
              sauvegardeProfils(p);
            }
          }
        }
      }
      else if (nbBateauxVivant(j2) == 0)
      {
        // On affiche l'image du joueur 1
        SDL_BlitSurface(victoire1, NULL, screen, &posVictoire1);
        // On affiche le nombre de coups
        sprintf(strCoups, "%d", nbCaseNonVide(j1.infos));
        calcul = (int)(100 * ((float)((float)17 / (float)nbCaseNonVide(j1.infos))));
        // On affiche la precision
        sprintf(strPrecision, "%d%%", calcul);
        SDL_FreeSurface(nbCoupsVictoire);
        SDL_FreeSurface(precisionVictoire);
        nbCoupsVictoire = creerTexte(screen, strCoups, noir, fontVictoire);
        precisionVictoire = creerTexte(screen, strPrecision, noir, fontVictoire);
        SDL_BlitSurface(nbCoupsVictoire, NULL, screen, &nbCoupsVictoireRect);
        SDL_BlitSurface(precisionVictoire, NULL, screen, &precisionVictoireRect);
        // Calcul pour les profils
        if (calcul >= jp[0].scoreNavale)
        {
          for (int i = 0; i < 10; i++)
          {
            if (jp[0].ID == p[i].ID)
            {
              p[i].scoreNavale = calcul;
              sauvegardeProfils(p);
            }
          }
        }
      }
      SDL_BlitSurface(boutonMenu, NULL, screen, &posBoutonMenu);
      break;
    }
    // Afficher les textes pour la bataille navale
    char result[50];
    sprintf(result, "%d", nbCaseBateau(j1));

    // On actualise l'écran
    SDL_Flip(screen);
  }
  // Liberation
  j1 = freeJoueurBN(j1);
  j2 = freeJoueurBN(j2);
  TTF_CloseFont(font);
  TTF_CloseFont(fontVictoire);
  SDL_FreeSurface(boutonMenu);
  SDL_FreeSurface(victoire1);
  SDL_FreeSurface(victoire2);
  SDL_FreeSurface(nbCoupsVictoire);
  SDL_FreeSurface(precisionVictoire);
  return continuer;
}

void afficherBateaux(SDL_Surface *screen, JoueurBatailleNavale j)
{
  // On affiche le bateau en fonction de sa direction
  for (int i = 0; i <= 4; i++)
  {
    switch (j.tab[i].direction)
    {
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

void ciblerCase(SDL_Surface *screen, SDL_Surface *c, SDL_Rect pos)
{
  SDL_BlitSurface(c, NULL, screen, &pos);
}

void afficherBateauxSurLeCote(SDL_Surface *screen, JoueurBatailleNavale j1, JoueurBatailleNavale j2)
{
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

  if (j1.tab[0].pv > 0)
    SDL_BlitSurface(j1.tab[0].est, NULL, screen, &pos10);
  if (j1.tab[1].pv > 0)
    SDL_BlitSurface(j1.tab[1].est, NULL, screen, &pos11);
  if (j1.tab[2].pv > 0)
    SDL_BlitSurface(j1.tab[2].est, NULL, screen, &pos12);
  if (j1.tab[3].pv > 0)
    SDL_BlitSurface(j1.tab[3].est, NULL, screen, &pos13);
  if (j1.tab[4].pv > 0)
    SDL_BlitSurface(j1.tab[4].est, NULL, screen, &pos14);

  if (j2.tab[0].pv > 0)
    SDL_BlitSurface(j2.tab[0].west, NULL, screen, &pos20);
  if (j2.tab[1].pv > 0)
    SDL_BlitSurface(j2.tab[1].west, NULL, screen, &pos21);
  if (j2.tab[2].pv > 0)
    SDL_BlitSurface(j2.tab[2].west, NULL, screen, &pos22);
  if (j2.tab[3].pv > 0)
    SDL_BlitSurface(j2.tab[3].west, NULL, screen, &pos23);
  if (j2.tab[4].pv > 0)
    SDL_BlitSurface(j2.tab[4].west, NULL, screen, &pos24);
}

int victoire(JoueurBatailleNavale j)
{
  int i;
  int victoire = 1;
  while (i <= 4 && victoire == 1)
  {
    if (j.tab[i].pv > 0)
    {
      victoire = 0;
    }
    else
    {
      i++;
    }
  }
  return victoire;
}
