#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <SDL/SDL_mixer.h>
#include "../../headers/global/structure.h"
#include "../../headers/global/shortcuts.h"
#include "../../headers/loto/timerLoto.h"
#include "../../headers/loto/loto.h"
#include "../../headers/global/constantes.h"
#include "../../headers/loto/affichageLoto.h"
#include "../../headers/loto/grilleLoto.h"
#include "../../headers/loto/bouleLoto.h"
#include "../../headers/loto/scoreLoto.h"
#include "../../headers/profils/chargement.h"
#include "../../headers/profils/sauvegarde.h"

int afficherLoto(SDL_Surface *screen, int nbJoueurs, tabJP tabProfil)
{
  Mix_Music *boule;
  Mix_Music *ok;
  Mix_Music *non;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  boule = Mix_LoadMUS("assets/sounds/boules.wav");
  ok = Mix_LoadMUS("assets/sounds/ok-loto.wav");
  non = Mix_LoadMUS("assets/sounds/non-.wav");

  srand(time(NULL));
  int gagnant = 0;

  int score[4] = {0, 0, 0, 0};
  int punition[4] = {0, 0, 0, 0};
  int nombrePasse[4] = {0, 0, 0, 0};
  CaseLoto grille1[9][3];
  CaseLoto grille2[9][3];
  CaseLoto grille3[9][3];
  CaseLoto grille4[9][3];
  int totalPunition[4] = {0}; //le nombre de fois qu'une personne a une punition

  int tasBoules[90];
  int tailleTas = initialisationLoto(tasBoules, nbJoueurs, grille1, grille2, grille3, grille4);
  int nombreTire;

  long current_time;
  long temps;
  int newNombre = 1;
  Coord c;

  Uint32 start;
  int continuer = 1;
  SDL_Event event;
  TTF_Font *font = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 70);
  SDL_Color blanc = {0, 0, 0, 0};
  SDL_Rect position = newRect(0, 0, 0, 0);
  SDL_Rect positiontimer = newRect(1010, 336, 0, 0);
  SDL_Rect boutonMenu = newRect(133, 290, 84, 154);
  int tempsmax = 5;
  char timerText[10];
  SDL_Surface *texte = NULL;
  SDL_Surface *tempsRestant;
  SDL_Surface *fond = NULL;
  fond = IMG_Load("assets/Loto/backLoto.png");

  // Hover menu
  SDL_Surface *hoverMenu = NULL;
  hoverMenu = IMG_Load("assets/Loto/hoverMenu.png");
  SDL_Rect fullZoneMenu = newRect(90, 239, 210, 250);
  while (continuer == 1)
  {

    //changement de nombre
    if (newNombre == 1)
    {
      for (int i = 0; i < 4; i++)
      {
        if (punition[i] > 0)
        {
          punition[i]--;
        }
      }
      score[0] = nbJetons(grille1);
      score[1] = nbJetons(grille2);
      score[2] = nbJetons(grille3);
      score[3] = nbJetons(grille4);
      if (nombrePasse[0] + nombrePasse[1] + nombrePasse[2] + nombrePasse[3] >= nbJoueurs * 15 || tailleTas <= 0)
      {
        gagnant = maxJeton(score) + 1;
      }
      for (int i = 0; i < 4; i++)
      {
        if (score[i] >= 15)
        {
          gagnant = i + 1;
        }
      }
      if (tailleTas >= 1 && gagnant == 0)
      {
        Mix_PlayMusic(boule, 1);
        nombreTire = prendreNombre(&tailleTas, tasBoules);
        if (nombreDansGrille(grille1, nombreTire))
        {
          nombrePasse[0]++;
        }
        if (nombreDansGrille(grille2, nombreTire))
        {
          nombrePasse[1]++;
        }
        if (nombreDansGrille(grille3, nombreTire))
        {
          nombrePasse[2]++;
        }
        if (nombreDansGrille(grille4, nombreTire))
        {
          nombrePasse[3]++;
        }
      }
      newNombre = 0;
      temps = time(NULL);
    }

    c.x = event.button.x;
    c.y = event.button.y;

    SDL_PollEvent(&event);

    switch (event.type)
    {
    // Si on clique sur la croix, on ferme la fenêtre
    case SDL_QUIT:
      continuer = 0;
      break;

    //retour au menu
    case SDL_MOUSEBUTTONDOWN:
      boutonMenu = newRect(133, 290, 84, 154);

      if (posInclusion(c.x, c.y, boutonMenu))
      {
        continuer = 2;
      }
      break;

    case SDL_KEYDOWN:
      if (gagnant == 0)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_LCTRL: /* Appui sur la touche ctrl gauche pour le joueur 1 */
          if (punition[0] == 0)
          {
            if (nombreDansGrille(grille1, nombreTire))
            {
              Mix_PlayMusic(ok, 1);
              poserJeton(grille1, nombreTire);
            }
            else
            {
              Mix_PlayMusic(non, 1);
              punition[0] = 2;
              totalPunition[0] = totalPunition[0] + 1;
            }
          }
          break;

        case SDLK_SPACE: /* Appui sur la touche ctrl droite pour le joueur 2 */
          if (punition[1] == 0)
          {
            if (nbJoueurs >= 2)
            {
              if (nombreDansGrille(grille2, nombreTire))
              {
                Mix_PlayMusic(ok, 1);
                poserJeton(grille2, nombreTire);
              }
              else
              {
                Mix_PlayMusic(non, 1);
                punition[1] = 2;
                totalPunition[1] = totalPunition[1] + 1;
              }
            }
          }
          break;
        case SDLK_RCTRL: /* Appui sur la touche ctrl droit pour le joueur 3 */
          if (punition[2] == 0)
          {
            if (nbJoueurs >= 3)
            {
              if (nombreDansGrille(grille3, nombreTire))
              {
                Mix_PlayMusic(ok, 1);
                poserJeton(grille3, nombreTire);
              }
              else
              {
                Mix_PlayMusic(non, 1);
                punition[2] = 2;
                totalPunition[2] = totalPunition[2] + 1;
              }
            }
          }
          break;
        case SDLK_RIGHT: /* Appui sur la touche ctrl droit pour le joueur 4 */
          if (punition[3] == 0)
          {
            if (nbJoueurs == 4)
            {
              if (nombreDansGrille(grille4, nombreTire))
              {
                Mix_PlayMusic(ok, 1);
                poserJeton(grille4, nombreTire);
              }
              else
              {
                Mix_PlayMusic(non, 1);
                punition[3] = 2;
                totalPunition[3] = totalPunition[3] + 1;
              }
            }
          }
          break;
        }
      }
      break;
    }

    current_time = time(NULL) - temps;
    sprintf(timerText, "%ld", tempsmax - current_time);
    SDL_BlitSurface(fond, NULL, screen, &position);
    if (gagnant == 0)
    {
      if (tempsmax - current_time <= 0)
      {
        newNombre = 1;
      }
      font = TTF_OpenFont(FONT_UBUNTU, 70);
      tempsRestant = TTF_RenderText_Solid(font, timerText, blanc);
      SDL_BlitSurface(tempsRestant, NULL, screen, &positiontimer);
      TTF_CloseFont(font);
      SDL_FreeSurface(tempsRestant);
    }
    afficherJeuLoto(screen, font, texte, nombreTire, nbJoueurs, grille1, grille2, grille3, grille4, punition);
    if (posInclusion(c.x, c.y, boutonMenu))
    {
      SDL_BlitSurface(hoverMenu, NULL, screen, &fullZoneMenu);
    }

    //victoire
    if (gagnant != 0)
    {

      continuer = victoireLoto(screen, gagnant);
      //modifit le tableau de profil pour enregistrer les meilleurs scores :
      for (int i = 0; i < nbJoueurs; i++)
      {
        if (i == 0)
        {
          tabProfil[i].scoreLoto = scoreLoto(totalPunition[i], grille1);
        }
        else
        {
          if (i == 1)
          {
            tabProfil[i].scoreLoto = scoreLoto(totalPunition[i], grille2);
          }
          else
          {
            if (i == 2)
            {
              tabProfil[i].scoreLoto = scoreLoto(totalPunition[i], grille3);
            }
            else
            {
              tabProfil[i].scoreLoto = scoreLoto(totalPunition[i], grille4);
            }
          }
        }
      }
      // Sauvegarde si c'est mieux
      tabP p;
      chargementProfils(p);

      for (int i = 0; i < 10; i++)
      {
        for (int j = 0; j < nbJoueurs; j++)
        {
          if (p[i].ID == tabProfil[j].ID)
          {
            if (p[i].scoreLoto < tabProfil[j].scoreLoto)
            {
              p[i].scoreLoto = tabProfil[j].scoreLoto;
            }
          }
        }
      }
      sauvegardeProfils(p);

      /*sprintf(timerText, "Victoire du Joueur %d", gagnant);
      font = TTF_OpenFont(FONT_UBUNTU, 70);
      tempsRestant = TTF_RenderText_Solid(font, timerText, blanc);
      SDL_BlitSurface(tempsRestant, NULL, screen, &position);
      TTF_CloseFont(font);
      SDL_FreeSurface(tempsRestant);*/
    }

    SDL_Flip(screen);
  }
  SDL_FreeSurface(fond);
  SDL_FreeSurface(hoverMenu);
  Mix_FreeMusic(boule);
  Mix_FreeMusic(ok);
  Mix_FreeMusic(non);
  Mix_CloseAudio();
  return continuer;
}
//joueur 1: ctrl g
//joueur 2: espace
//joueur 3: ctrl d
//joueur 4: flèche droite
