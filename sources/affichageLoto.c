#include <SDL/SDL_ttf.h>
#include "../headers/structure.h"
#include "../headers/affichageLoto.h"
#include "../headers/interface.h"
#include "../headers/shortcuts.h"
#include "../headers/constantes.h"
#include "../headers/loto.h"

void afficheGrilleLoto(CaseLoto t[9][3], SDL_Surface *screen, int numJoueur, TTF_Font *font, SDL_Surface *texte, int punition[4])
{
  int x = 0, y = 0;
  if (numJoueur == 2 || numJoueur == 4)
  {
    x = 735;
  }
  if (numJoueur == 3 || numJoueur == 4)
  {
    y = 469;
  }
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  SDL_Color noir = {0, 0, 0, 0};
  int i, j;
  char valeur[10];
  SDL_Rect rectTexte = newRect(x + 50, y + 3, 0, 0);
  if (numJoueur == 1)
  {
    texte = IMG_Load("assets/loto/J1.png");
  }
  if (numJoueur == 2)
  {
    texte = IMG_Load("assets/loto/J2.png");
  }
  if (numJoueur == 3)
  {
    texte = IMG_Load("assets/loto/J3.png");
  }
  if (numJoueur == 4)
  {
    texte = IMG_Load("assets/loto/J4.png");
  }
  SDL_BlitSurface(texte, NULL, screen, &rectTexte);
  SDL_FreeSurface(texte);
  if (punition[numJoueur - 1] > 0)
  {
    texte = IMG_Load("assets/loto/puni.png");
    SDL_BlitSurface(texte, NULL, screen, &rectTexte);
    SDL_FreeSurface(texte);
  }
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (t[i][j].val != -1)
      {
        sprintf(valeur, "%d", t[i][j].val);
        texte = TTF_RenderText_Solid(font, valeur, noir);
        rectTexte.x = x + 49 * (i + 1) + 10;
        rectTexte.y = y + 50 * (j) + 64;
        SDL_BlitSurface(texte, NULL, screen, &rectTexte);
        SDL_FreeSurface(texte);
        if (t[i][j].jeton == true)
        {
          texte = IMG_Load("assets/loto/jeton.png");
          rectTexte.x = x + 49 * (i + 1) + 1;
          rectTexte.y = y + 50 * (j) + 49;
          SDL_BlitSurface(texte, NULL, screen, &rectTexte);
          SDL_FreeSurface(texte);
        }
      }
      else
      {
        if (t[i][j].val == -1)
        {
          rectTexte.x = x + 49 * (i + 1) + 1;
          rectTexte.y = y + 50 * (j) + 49;
          if (numJoueur == 1)
          {
            texte = IMG_Load("assets/loto/r.png");
          }
          if (numJoueur == 2)
          {
            texte = IMG_Load("assets/loto/b.png");
          }
          if (numJoueur == 3)
          {
            texte = IMG_Load("assets/loto/o.png");
          }
          if (numJoueur == 4)
          {
            texte = IMG_Load("assets/loto/v.png");
          }
          SDL_BlitSurface(texte, NULL, screen, &rectTexte);
          SDL_FreeSurface(texte);
        }
      }
    }
  }
  TTF_CloseFont(font);
}

void afficherNombreLoto(SDL_Surface *screen, int nombre, TTF_Font *font, SDL_Surface *texte)
{
  font = TTF_OpenFont(FONT_UBUNTU, 80);
  SDL_Color noir = {0, 0, 0, 0};
  SDL_Rect rectTexte = newRect(565, 305, 0, 0);
  char valeur[3];
  sprintf(valeur, "%d", nombre);
  texte = TTF_RenderText_Solid(font, valeur, noir);
  SDL_BlitSurface(texte, NULL, screen, &rectTexte);
  SDL_FreeSurface(texte);
  TTF_CloseFont(font);
}

void afficherJeuLoto(SDL_Surface *screen, TTF_Font *font, SDL_Surface *texte, int nombre, int nbJoueurs, CaseLoto g1[9][3], CaseLoto g2[9][3], CaseLoto g3[9][3], CaseLoto g4[9][3], int punition[4])
{
  afficherNombreLoto(screen, nombre, font, texte);
  afficheGrilleLoto(g1, screen, 1, font, texte, punition);
  if (nbJoueurs >= 2)
  {
    afficheGrilleLoto(g2, screen, 2, font, texte, punition);
  }
  if (nbJoueurs >= 3)
  {
    afficheGrilleLoto(g3, screen, 3, font, texte, punition);
  }
  if (nbJoueurs == 4)
  {
    afficheGrilleLoto(g4, screen, 4, font, texte, punition);
  }
}

//gére le menu de choix de joueur du loto
int menuChoixJoueur(SDL_Surface *screen)
{
  int continuer = 1;
  SDL_Event event;
  Coord clic;
  //Affiche l'image du menu de choix
  SDL_Surface *choix = NULL;
  choix = IMG_Load("assets/Loto/choixJoueurLoto.png");
  SDL_Rect choixNbJoueur = newRect(0, 0, 1280, 720);
  //bouton 1 joueur
  SDL_Rect un = newRect(148, 113, 112, 232);
  //bouton 2 Joueurs
  SDL_Rect deux = newRect(900, 113, 112, 232);
  //bouton 3 joueurs
  SDL_Rect trois = newRect(148, 455, 112, 232);
  //bouton 4 joueurs
  SDL_Rect quatre = newRect(900, 455, 112, 232);
  //bouton menu
  SDL_Rect menu = newRect(552, 546, 84, 149);
  // hover choix joueurs
  SDL_Surface *hoverChoixJoueur = NULL;
  hoverChoixJoueur = IMG_Load("assets/loto/hoverJoueurs.png");
  // hover menu
  SDL_Surface *hoverMenu = NULL;
  hoverMenu = IMG_Load("assets/loto/hoverMenu.png");
  SDL_Rect fullZoneMenu = newRect(508, 495, 210, 250);

  while (continuer == 1)
  {
    SDL_BlitSurface(choix, NULL, screen, &choixNbJoueur);

    //evenements
    clic.x = event.button.x;
    clic.y = event.button.y;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;

        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          //conditions des clics
          if (posInclusion(clic.x, clic.y, un))
          {
            continuer = afficherLoto(screen, 1);
          }
          if (posInclusion(clic.x, clic.y, deux))
          {
            continuer = afficherLoto(screen, 2);
          }
          if (posInclusion(clic.x, clic.y, trois))
          {
            continuer = afficherLoto(screen, 3);
          }
          if (posInclusion(clic.x, clic.y, quatre))
          {
            continuer = afficherLoto(screen, 4);
          }
          if (posInclusion(clic.x, clic.y, menu))
          {
            continuer = 2;
          }
        }
        break;
      }
    }
    if (posInclusion(clic.x, clic.y, un))
    {
      SDL_BlitSurface(hoverChoixJoueur, NULL, screen, &un);
    }
    if (posInclusion(clic.x, clic.y, deux))
    {
      SDL_BlitSurface(hoverChoixJoueur, NULL, screen, &deux);
    }
    if (posInclusion(clic.x, clic.y, trois))
    {
      SDL_BlitSurface(hoverChoixJoueur, NULL, screen, &trois);
    }
    if (posInclusion(clic.x, clic.y, quatre))
    {
      SDL_BlitSurface(hoverChoixJoueur, NULL, screen, &quatre);
    }
    if (posInclusion(clic.x, clic.y, menu))
    {
      SDL_BlitSurface(hoverMenu, NULL, screen, &fullZoneMenu);
    }
    SDL_Flip(screen);
  }
  //free les surfaces
  SDL_FreeSurface(choix);
  SDL_FreeSurface(hoverChoixJoueur);
  SDL_FreeSurface(hoverMenu);
  return continuer;
}

//victoire loto
int victoireLoto(SDL_Surface *screen, int gagnant)
{
  int continuer = 1;
  SDL_Event event;
  Coord clic;
  //victoire 1
  SDL_Surface *vic1 = NULL;
  vic1 = IMG_Load("assets/Loto/victoirej1.png");
  SDL_Rect victoire = newRect(0, 0, 1280, 720);
  //victoire 2
  SDL_Surface *vic2 = NULL;
  vic2 = IMG_Load("assets/Loto/victoirej2.png");
  //victoire 3
  SDL_Surface *vic3 = NULL;
  vic3 = IMG_Load("assets/Loto/victoirej3.png");
  //victoire 4
  SDL_Surface *vic4 = NULL;
  vic4 = IMG_Load("assets/Loto/victoirej4.png");

  while (continuer == 1)
  {
    if (gagnant == 1)
    {
      SDL_BlitSurface(vic1, NULL, screen, &victoire);
    }
    else
    {
      if (gagnant == 2)
      {
        SDL_BlitSurface(vic2, NULL, screen, &victoire);
      }
      else
      {
        if (gagnant == 3)
        {
          SDL_BlitSurface(vic3, NULL, screen, &victoire);
        }
        else
        {
          SDL_BlitSurface(vic4, NULL, screen, &victoire);
        }
      }
    }

    SDL_Flip(screen);
    //evenements
    clic.x = event.button.x;
    clic.y = event.button.y;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        continuer = 0;

        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          //conditions des clics
          if (posInclusion(clic.x, clic.y, victoire))
          {
            continuer = 2;
          }
        }
        break;
      }
    }
  }
  //free surfaces
  SDL_FreeSurface(vic1);
  SDL_FreeSurface(vic2);
  SDL_FreeSurface(vic3);
  SDL_FreeSurface(vic4);
  return continuer;
}
