#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "../../headers/global/structure.h"
#include "../../headers/global/shortcuts.h"
#include "../../headers/global/constantes.h"
#include "../../headers/batailleNavale/batailleNavale.h"
#include "../../headers/global/interface.h"
#include "../../headers/batailleNavale/placementBateaux.h"
#include "../../headers/batailleNavale/tourBatailleNavale.h"

//Touché coulé raté bataille Navale
// Renvoie 1 si on continue de jouer, 0 sinon
int aToiDeJouer(SDL_Surface *screen, JoueurBatailleNavale *j1, JoueurBatailleNavale *j2)
{
  // Case cible
  SDL_Surface *caseCible = NULL;
  caseCible = IMG_Load("assets/batailleNavale/case3.jpg");
  SDL_Rect posCaseCible = newRect(0, 0, 0, 0);
  // Images Bateaux allies et ennemis
  SDL_Surface *bateauAlliesSurface = NULL;
  bateauAlliesSurface = IMG_Load("assets/batailleNavale/bateauxAllies.png");
  SDL_Rect posBateauxAllies = newRect(10, 40, 100, 300);
  SDL_Surface *bateauEnnemisSurface = NULL;
  bateauEnnemisSurface = IMG_Load("assets/batailleNavale/bateauxEnnemis.png");
  SDL_Rect posBateauxEnnemis = newRect(WIDTH_GAME - 310, 40, 100, 300);
  // Les deux types de cases (couleurs différentes)
  SDL_Surface *case1 = NULL;
  SDL_Surface *case2 = NULL;
  case1 = IMG_Load("assets/batailleNavale/case1.jpg");
  case2 = IMG_Load("assets/batailleNavale/case2.jpg");
  // Les deux types de croix
  SDL_Surface *touche = NULL;
  SDL_Surface *rate = NULL;
  touche = IMG_Load("assets/batailleNavale/touche.png");
  rate = IMG_Load("assets/batailleNavale/rate.png");
  SDL_Rect posCroix = newRect(0, 0, 64, 64);
  // Police pour les textes, couleurs
  TTF_Font *font = NULL;
  TTF_Font *fontVictoire = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  fontVictoire = TTF_OpenFont(FONT_UBUNTU, 36);
  SDL_Color noir = {0, 0, 0, 0};
  SDL_Surface *texte = NULL;
  // Bouton changement de tour
  SDL_Surface *boutonTourSuivant = NULL;
  boutonTourSuivant = IMG_Load("assets/batailleNavale/tourSuivant.png");
  SDL_Rect posButton = newRect(WIDTH_GAME - 300 - 10, HEIGHT_GAME - 200 - 10, 200, 300);
  // Bouton bouton
  SDL_Surface *boutonMenu = NULL;
  boutonMenu = IMG_Load("assets/batailleNavale/boutonMenu.png");
  SDL_Rect posBoutonMenu = newRect(10, HEIGHT_GAME - 100 - 10, 100, 150);
  // Variables importantes
  Coord clic; // clic utilisateur
  SDL_Event event;
  int continuer = 4;  // boucle principale
  int indexA, indexB; // pour simplifier la ligne 117/119
  int valeurTCR;      // valeur de la fonction, car on en a besoin 2 fois
  bool aJoue = false; // bool qui dit si le joueur a deja joue

  // Sons
  Mix_Music *ploc;
  Mix_Music *touche2;
  Mix_Music *coule;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  ploc = Mix_LoadMUS("assets/sounds/ploc.wav");
  touche2 = Mix_LoadMUS("assets/sounds/touché.wav");
  coule = Mix_LoadMUS("assets/sounds/coule2.wav");

  // Pour debug des variables
  char debugText[50];
  SDL_Surface *debugSurface;
  SDL_Rect debugRect = newRect(0, 0, 0, 0);

  // Numero du tour en cours

  char nbTour[15];
  SDL_Surface *nbTourSuface;
  SDL_Rect nbTourRect = newRect(320, 0, 0, 0);
  sprintf(nbTour, "Tour : %d", nbCaseNonVide(j1->infos) + 1);
  nbTourSuface = creerTexte(screen, nbTour, noir, font);
  bool c_fini = false;

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

  // Afficher le texte correspondant au Joueur
  switch (j1->joueur)
  {
  case 1:
    texte = creerTexte(screen, "Au tour du joueur 1", noir, font);
    break;
  case 2:
    texte = creerTexte(screen, "Au tour du joueur 2", noir, font);
    break;
  }
  SDL_Rect posTexte = newRect(500, 0, 0, 0);

  while (continuer == 4)
  {
    // On affiche le fond blanc
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    // Debug zone
    sprintf(debugText, "%d\n%d\%d\n%d\n%d", j2->tab[0].pv, j2->tab[1].pv, j2->tab[2].pv, j2->tab[3].pv, j2->tab[4].pv);
    //debugSurface = creerTexte(screen, debugText, noir, font);
    // SDL_BlitSurface(debugSurface, NULL, screen, &debugRect);

    // Affichage du nombre de tour
    SDL_BlitSurface(nbTourSuface, NULL, screen, &nbTourRect);
    // Affichage des bateaux (sur le cote)
    SDL_BlitSurface(bateauAlliesSurface, NULL, screen, &posBateauxAllies);

    SDL_BlitSurface(bateauEnnemisSurface, NULL, screen, &posBateauxEnnemis);

    SDL_BlitSurface(boutonMenu, NULL, screen, &posBoutonMenu);
    afficherBateauxSurLeCote(screen, *j1, *j2);

    // Affichage du bouton si on a joue
    if (aJoue && (nbBateauxVivant(*j2) > 0))
    {
      SDL_BlitSurface(boutonTourSuivant, NULL, screen, &posButton);
    }

    afficherGrille(screen, case1, case2, positionCases);

    SDL_BlitSurface(texte, NULL, screen, &posTexte);

    clic.x = event.button.x;
    clic.y = event.button.y;

    // Surligner la case pointee
    if (posInclusion(clic.x, clic.y, positionGrille))
    {
      posCaseCible.x = clic.x - clic.x % 64;
      posCaseCible.y = clic.y - (clic.y - 40) % 64;

      ciblerCase(screen, caseCible, posCaseCible);
    }

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;

        break;
      case SDL_MOUSEBUTTONDOWN:
        indexA = (clic.x - 320) / 64;
        indexB = (clic.y - 40) / 64;
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          if (posInclusion(clic.x, clic.y, posBoutonMenu))
          {
            continuer = 2;
          }

          if (!aJoue)
          {
            if (posInclusion(clic.x, clic.y, positionGrille))
            {
              valeurTCR = tcr(indexA, indexB, j2, j1);
              if (valeurTCR != 0)
              {
                if (valeurTCR == 1) Mix_PlayMusic(touche2, 1);
                if (valeurTCR == 2) Mix_PlayMusic(ploc, 1);
                j1->infos.tab[indexA][indexB] = valeurTCR;
                aJoue = true;
              }
            }
          }

          else
          {
            if ((posInclusion(clic.x, clic.y, posButton) && (nbBateauxVivant(*j2) > 0)))
            {
              continuer = 1;
            }
          }
        }
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
        }
        break;
      }
    }
    // Affichage des bateaux coules
    for (int a = 0; a < 5; a++)
    {
      if (j2->tab[a].pv == 0)
      {
        switch (j2->tab[a].direction)
        {
        case 1:
          SDL_BlitSurface(j2->tab[a].nord, NULL, screen, &j2->tab[a].r);
          break;
        case 2:
          SDL_BlitSurface(j2->tab[a].west, NULL, screen, &j2->tab[a].r);
          break;
        case 3:
          SDL_BlitSurface(j2->tab[a].sud, NULL, screen, &j2->tab[a].r);
          break;
        case 4:
          SDL_BlitSurface(j2->tab[a].est, NULL, screen, &j2->tab[a].r);
          break;
        default:
          break;
        }
      }
    }
    // Affichage des coups
    for (int a = 0; a < 10; a++)
    {
      for (int b = 0; b < 10; b++)
      {
        posCroix.x = (a * 64 + 320);
        posCroix.y = (b * 64 + 40);
        switch (j1->infos.tab[a][b])
        {
        case 0:
          break;
        case 1:
          SDL_BlitSurface(touche, NULL, screen, &posCroix);
          break;
        case 2:
          SDL_BlitSurface(rate, NULL, screen, &posCroix);
          break;
        defaut:
          break;
        }
      }
    }

    // Affichage des ecrans de victoire
    if (nbBateauxVivant(*j2) == 0)
    {
      continuer = 3;
      //   SDL_BlitSurface(victoire2, NULL, screen, &posVictoire2);
      //   sprintf(strCoups, "%d", nbCaseNonVide(j2->infos));
      //   sprintf(strPrecision, "%d%%", (int) (100 * ((float) ((float) 17 / (float) nbCaseNonVide(j2->infos)))));
      //   nbCoupsVictoire = creerTexte(screen, strCoups, noir, fontVictoire);
      //   precisionVictoire = creerTexte(screen, strPrecision, noir, fontVictoire);
      //   SDL_BlitSurface(nbCoupsVictoire, NULL, screen, &nbCoupsVictoireRect);
      //   SDL_BlitSurface(precisionVictoire, NULL, screen, &precisionVictoireRect);
      //   c_fini = true;
    }
    else if (nbBateauxVivant(*j1) == 0)
    {
      continuer = 3;
      //   SDL_BlitSurface(victoire1, NULL, screen, &posVictoire1);
      //   sprintf(strCoups, "%d", nbCaseNonVide(j1->infos));
      //   sprintf(strPrecision, "%d%%", (int) (100 * ((float) ((float) 17 / (float) nbCaseNonVide(j2->infos)))));
      //   nbCoupsVictoire = creerTexte(screen, strCoups, noir, fontVictoire);
      //   precisionVictoire = creerTexte(screen, strPrecision, noir, fontVictoire);
      //   SDL_BlitSurface(nbCoupsVictoire, NULL, screen, &nbCoupsVictoireRect);
      //   SDL_BlitSurface(precisionVictoire, NULL, screen, &precisionVictoireRect);
      //   c_fini = true;
    }

    SDL_Flip(screen);
  }
  // Liberation
  SDL_FreeSurface(caseCible);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(bateauEnnemisSurface);
  SDL_FreeSurface(bateauAlliesSurface);
  SDL_FreeSurface(case1);
  SDL_FreeSurface(case2);
  SDL_FreeSurface(touche);
  SDL_FreeSurface(rate);
  SDL_FreeSurface(boutonTourSuivant);
  SDL_FreeSurface(boutonMenu);
  TTF_CloseFont(font);
  TTF_CloseFont(fontVictoire);
  Mix_FreeMusic(ploc);
  Mix_FreeMusic(touche2);
  Mix_FreeMusic(coule);
  return continuer;
}

//retourne 1 ou 2 si c'est possible, 0 si c'est pas possible
int tcr(int x, int y, JoueurBatailleNavale *victime, JoueurBatailleNavale *attaquant)
{ //rajouter une grille dans joueur comme ils ont chacun leurs grille
  //si il n'y a pas de bateau :            //le joueur c le joueur adverse, celui qu'on attaque
  switch (victime->g.tab[x][y])
  {
  // Si on retourne 0, le coup est invalide
  case 0:
    // Il n'y a rien dans cette case
    if (attaquant->infos.tab[x][y] == 2)
    {
      // Dans ce cas, le joueur avait deja essaye, c'est toujours rate
      return 0;
    }
    return 2;
    break;
  case 10:
    // On touche le bateau 1
    if (attaquant->infos.tab[x][y] == 1)
    {
      // Dans ce cas, le joueur avait deja essaye, c'est toujours touche
      return 0;
    }
    victime->tab[0].pv--;
    return 1;
    break;
  case 11:
    // On touche le bateau 1
    if (attaquant->infos.tab[x][y] == 1)
    {
      // Dans ce cas, le joueur avait deja essaye, c'est toujours touche
      return 0;
    }
    victime->tab[1].pv--;
    return 1;
    break;
  case 12:
    // On touche le bateau 1
    if (attaquant->infos.tab[x][y] == 1)
    {
      // Dans ce cas, le joueur avait deja essaye, c'est toujours touche
      return 0;
    }
    victime->tab[2].pv--;
    return 1;
    break;
  case 13:
    // On touche le bateau 1
    if (attaquant->infos.tab[x][y] == 1)
    {
      // Dans ce cas, le joueur avait deja essaye, c'est toujours touche
      return 0;
    }
    victime->tab[3].pv--;
    return 1;
    break;
  case 14:
    // On touche le bateau 1
    if (attaquant->infos.tab[x][y] == 1)
    {
      // Dans ce cas, le joueur avait deja essaye, c'est toujours touche
      return 0;
    }
    victime->tab[4].pv--;
    return 1;
    break;
  default:
    return 0;
    break;
  }
}
