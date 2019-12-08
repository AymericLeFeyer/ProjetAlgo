#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../headers/structure.h"
#include "../headers/pioche.h"
#include "../headers/tourPartie.h"
#include "../headers/mainsPoker.h"
#include "../headers/shortcuts.h"
#include "../headers/poker.h"

//lance une partie de poker en textuel
void poker()
{
  srand(time(NULL));
  tabJP jp;
  JoueurPoker joueurs[5];
  CentrePlateau centre;
  int nbJoueurs = 2;
  int miseDepart = 5;
  int nbTours = 2;
  int argentDepart = 50;
  printf("nombre de joueurs ? ");
  scanf("%d", &nbJoueurs);
  printf("mise de depart ? ");
  scanf("%d", &miseDepart);
  printf("nombre de manches ? ");
  scanf("%d", &nbTours);
  printf("jetons au depart pour les joueurs ? ");
  scanf("%d", &argentDepart);
  //tourPartie(centre, joueurs,nbJoueurs,nbTours,argentDepart,miseDepart);
}

// poker en graphique
int affichagePoker(SDL_Surface *screen)
{
  // variables pour la boucle principale
  SDL_Event event;
  int continuer = 1;

  // Images
  SDL_Surface *rulesBoard = NULL;
  SDL_Surface *greenSelection = NULL;
  SDL_Surface *whiteSelection = NULL;
  SDL_Surface *buttonSelection = NULL;

  rulesBoard = IMG_Load("assets/poker/regles/rulesBoard.jpg");
  greenSelection = IMG_Load("assets/poker/regles/greenSelection.png");
  whiteSelection = IMG_Load("assets/poker/regles/whiteSelection.png");
  buttonSelection = IMG_Load("assets/poker/regles/nextSelection.png");

  // Positions
  SDL_Rect posRulesBoard = newRect(0, 0, 720, 1280);

  SDL_Rect posNextButton = newRect(1110, 25, 125, 150);
  SDL_Rect posMenuButton = newRect(25, 25, 125, 150);

  // Differents choix
  choixRegles choix[4][4];

  // Choix nombre de joueurs
  choix[0][0].pos = newRect(56, 185, 70, 250);
  choix[0][0].valeur = 2;
  choix[0][1].pos = newRect(362, 185, 70, 250);
  choix[0][1].valeur = 3;
  choix[0][2].pos = newRect(668, 185, 70, 250);
  choix[0][2].valeur = 4;
  choix[0][3].pos = newRect(974, 185, 70, 250);
  choix[0][3].valeur = 5;

  // Choix nombre de manches
  choix[1][0].pos = newRect(56, 325, 70, 250);
  choix[1][0].valeur = 1;
  choix[1][1].pos = newRect(362, 325, 70, 250);
  choix[1][1].valeur = 2;
  choix[1][2].pos = newRect(668, 325, 70, 250);
  choix[1][2].valeur = 3;
  choix[1][3].pos = newRect(974, 325, 70, 250);
  choix[1][3].valeur = 4;

  // Choix nombre de joueur
  choix[2][0].pos = newRect(56, 475, 70, 250);
  choix[2][0].valeur = 2;
  choix[2][1].pos = newRect(362, 475, 70, 250);
  choix[2][1].valeur = 5;
  choix[2][2].pos = newRect(668, 475, 70, 250);
  choix[2][2].valeur = 10;
  choix[2][3].pos = newRect(974, 475, 70, 250);
  choix[2][3].valeur = 20;

  // Choix nombre de joueur
  choix[3][0].pos = newRect(56, 625, 70, 250);
  choix[3][0].valeur = 20;
  choix[3][1].pos = newRect(362, 625, 70, 250);
  choix[3][1].valeur = 50;
  choix[3][2].pos = newRect(668, 625, 70, 250);
  choix[3][2].valeur = 100;
  choix[3][3].pos = newRect(974, 625, 70, 250);
  choix[3][3].valeur = 200;

  srand(time(NULL));
  JoueurPoker joueurs[5];
  CentrePlateau centre;
  int nbJoueurs = 5, miseDepart = 5, nbTours = 3, argentDepart = 50;
  Coord c;

  while (continuer == 1)
  {
    // Affichage du fond
    SDL_BlitSurface(rulesBoard, NULL, screen, &posRulesBoard);

    // On affiche les cases vertes
    for (int i = 0; i < 4; i++)
    {
      if (choix[0][i].valeur == nbJoueurs)
        SDL_BlitSurface(greenSelection, NULL, screen, &choix[0][i].pos);
      if (choix[1][i].valeur == nbTours)
        SDL_BlitSurface(greenSelection, NULL, screen, &choix[1][i].pos);
      if (choix[2][i].valeur == miseDepart)
        SDL_BlitSurface(greenSelection, NULL, screen, &choix[2][i].pos);
      if (choix[3][i].valeur == argentDepart)
        SDL_BlitSurface(greenSelection, NULL, screen, &choix[3][i].pos);
    }

    c.x = event.button.x;
    c.y = event.button.y;

    // On regarde l'event
    SDL_PollEvent(&event);

    // En fonction de l'event, on fait des actions
    switch (event.type)
    {
    // Si on clique sur la croix, on ferme la fenêtre
    case SDL_QUIT:
      continuer = 0;
      break;
    // Gestion du clic
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT)
      {
        // Changements des regles
        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            if (posInclusion(c.x, c.y, choix[i][j].pos) && continuer == 1)
            {
              switch (i)
              {
              case 0:
                nbJoueurs = choix[i][j].valeur;
                break;
              case 1:
                nbTours = choix[i][j].valeur;
                break;
              case 2:
                miseDepart = choix[i][j].valeur;
                break;
              case 3:
                argentDepart = choix[i][j].valeur;
                break;
              default:
                break;
              }
            }
          }
        }
        // Retour au menu
        if (posInclusion(c.x, c.y, posMenuButton) && continuer == 1)
        {
          continuer = 2;
        }
        // Commencer la partie
        if (posInclusion(c.x, c.y, posNextButton) && continuer == 1)
        {
          continuer = tourPartie(screen, centre, joueurs, nbJoueurs, nbTours, argentDepart, miseDepart);
        }
      }
    }

    // Affichages des cases blanches
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (posInclusion(c.x, c.y, choix[i][j].pos))
          SDL_BlitSurface(whiteSelection, NULL, screen, &choix[i][j].pos);
      }
    }
    if (posInclusion(c.x, c.y, posMenuButton))
      SDL_BlitSurface(buttonSelection, NULL, screen, &posMenuButton);
    if (posInclusion(c.x, c.y, posNextButton))
      SDL_BlitSurface(buttonSelection, NULL, screen, &posNextButton);

    SDL_Flip(screen);
  }
  // Liberation
  SDL_FreeSurface(rulesBoard);
  SDL_FreeSurface(greenSelection);
  SDL_FreeSurface(whiteSelection);
  SDL_FreeSurface(buttonSelection);
  return continuer;
}

void afficherCarte(SDL_Surface *screen, Carte c, SDL_Rect pos)
{
  if (c.visible)
  {
    SDL_BlitSurface(c.skin, NULL, screen, &pos);
  }
  else
  {
    SDL_BlitSurface(c.dos, NULL, screen, &pos);
  }
}
