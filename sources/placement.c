#include <stdio.h>
#include <SDL/SDL_image.h>

#include "../headers/structure.h"
#include "../headers/placement.h"
#include "../headers/batailleNavale.h"
#include "../headers/interface.h"
#include "../headers/constantes.h"
#include "../headers/shortcuts.h"
#include "../headers/mainsPoker.h"

//permet le clic sur un bateau pour le selectionner et retourne son indice dans le tableau de bateau d'un joueur
int choixBateau(Coord clic, JoueurBatailleNavale j)
{
  if (clic.x >= j.tab[0].r.x && clic.x <= j.tab[0].r.x + j.tab[0].r.w && clic.y >= j.tab[0].r.y && clic.y <= j.tab[0].r.y + j.tab[0].r.h)
  {
    return 0;
  }
  if (clic.x >= j.tab[1].r.x && clic.x <= j.tab[1].r.x + j.tab[1].r.w && clic.y >= j.tab[1].r.y && clic.y <= j.tab[1].r.y + j.tab[1].r.h)
  {
    return 1;
  }
  if (clic.x >= j.tab[2].r.x && clic.x <= j.tab[2].r.x + j.tab[2].r.w && clic.y >= j.tab[2].r.y && clic.y <= j.tab[2].r.y + j.tab[2].r.h)
  {
    return 2;
  }
  if (clic.x >= j.tab[3].r.x && clic.x <= j.tab[3].r.x + j.tab[3].r.w && clic.y >= j.tab[3].r.y && clic.y <= j.tab[3].r.y + j.tab[3].r.h)
  {
    return 3;
  }
  if (clic.x >= j.tab[4].r.x && clic.x <= j.tab[4].r.x + j.tab[4].r.w && clic.y >= j.tab[4].r.y && clic.y <= j.tab[4].r.y + j.tab[4].r.h)
  {
    return 4;
  }
  return -1;
}

//retourne les coordoonnée d'une case en fonction du clic
Coord clicGrille(Coord clic, int tailleCase, SDL_Rect g)
{
  Coord a;
  if (clic.x < g.x || clic.x > g.x + g.w || clic.y < g.y || clic.y > g.y + g.h)
  {
    a.x = -1;
    a.y = -1;
  }
  else
  {
    a.x = (int)((clic.x - 320) / tailleCase);
    a.y = (int)((clic.y - 40) / tailleCase);
  }
  if ((a.x < 0) || (a.y < 0))
  {
    a.x = -1;
    a.y = -1;
  }
  return a;
}

int phasePlacement(SDL_Surface *screen, JoueurBatailleNavale *j, int *continuer)
{

  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  SDL_Color noir = {0, 0, 0, 0};
  Coord clic;
  SDL_Event event;
  int selection = -1;
  bool enSelection = false;

  SDL_Surface *boutonTourSuivant = NULL;
  boutonTourSuivant = IMG_Load("assets/batailleNavale/tourSuivant.png");
  SDL_Rect posButton = newRect(WIDTH_GAME - 300 - 10, HEIGHT_GAME - 200 - 10, 200, 300);

  SDL_Surface *boutonMenu = NULL;
  boutonMenu = IMG_Load("assets/batailleNavale/boutonMenu.png");
  SDL_Rect posBoutonMenu = newRect(10, HEIGHT_GAME - 100 - 10, 100, 150);

  // Positions des cases
  SDL_Rect positionCases[10][10];

  // Position de la grille sur l'écran
  SDL_Rect positionGrille = newRect((WIDTH_GAME - 640) / 2, (HEIGHT_GAME - 640) / 2, 640, 640);

  // Initialisation de ces positions
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      positionCases[i][j] = newRect(positionGrille.x + 64 * i, positionGrille.y + 64 * j, 64, 64);
    }
  }

  // Les deux types de cases (couleurs différentes)
  SDL_Surface *case1 = NULL;
  SDL_Surface *case2 = NULL;

  case1 = IMG_Load("assets/batailleNavale/case1.jpg");
  case2 = IMG_Load("assets/batailleNavale/case2.jpg");

  // Creation texte necessaire
  SDL_Surface *texte = NULL;
  switch (j->joueur)
  {
  case 1:
    texte = creerTexte(screen, "Placement : Joueur 1", noir, font);
    break;
  case 2:
    texte = creerTexte(screen, "Placement : Joueur 2", noir, font);
    break;
  }

  SDL_Rect posTexte = newRect(496, 0, 0, 0);

  int t = 2;
  //on quitte uniquement si on a confirmé le placement du 2e joueur
  while (*continuer == 1 && t == 2)
  {
    // On affiche le fond blanc
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    afficherGrille(screen, case1, case2, positionCases);
    if (nbCaseBateau(*j) == 17)
      SDL_BlitSurface(boutonTourSuivant, NULL, screen, &posButton);
    SDL_BlitSurface(boutonMenu, NULL, screen, &posBoutonMenu);

    SDL_BlitSurface(texte, NULL, screen, &posTexte);
    afficherBateaux(screen, *j);

    clic.x = event.button.x;
    clic.y = event.button.y;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        *continuer = 0;
        t = 0;

        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {

          if (nbCaseBateau(*j) == 17)
          {
            if ((posInclusion(clic.x, clic.y, posButton)) && (!enSelection))
            {
              *continuer = 0;
              t = 1;
            }
          }
          if (!(enSelection))
          {
            selection = choixBateau(clic, *j);
            if (selection != -1)
              enSelection = true;
          }
          else if (enSelection)
          {
            // On lache le bateau
            updateGrille(j);
            selection = -1;
            enSelection = false;
          }
          if (posInclusion(clic.x, clic.y, posBoutonMenu) && (!(enSelection)))
          {
            *continuer = 2;
          }
        }
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
          // Pivot du bateau
          if (enSelection)
            tournerBateau(&j->tab[selection]);
        }
        break;
      }
    }
    if (enSelection)
    {
      // Deplacement du Bateau
      deplacerBateau(&j->tab[selection], clic);
      updateGrille(j);
      if (nbCaseBateau(*j) == 17)
        SDL_BlitSurface(boutonTourSuivant, NULL, screen, &posButton);
    }

    SDL_Flip(screen);
  }
  // Liberation
  SDL_FreeSurface(boutonTourSuivant);
  TTF_CloseFont(font);
  SDL_FreeSurface(boutonMenu);
  SDL_FreeSurface(case1);
  SDL_FreeSurface(case2);
  SDL_FreeSurface(texte);
  if (*continuer == 0)
  {
    *continuer = 1;
  }
  return t;
}
