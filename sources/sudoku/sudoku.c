#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "../../headers/global/shortcuts.h"
#include "../../headers/global/structure.h"
#include "../../headers/sudoku/sudoku.h"
#include "../../headers/sudoku/initGrilleSudoku.h"
#include "../../headers/sudoku/detectionSudoku.h"
#include "../../headers/global/constantes.h"
#include "../../headers/global/interface.h"

int affichageSudoku(SDL_Surface *screen)
{
  // Variables
  int continuer = 1;
  SDL_Event event;
  Coord c;
  int choix = 0;

  //tableau de profil
  tabJP jp;
  tabP p;

  // Images
  SDL_Surface *reglesImage = NULL;
  SDL_Surface *hoverFacile = NULL;
  SDL_Surface *hoverMoyen = NULL;
  SDL_Surface *hoverDifficile = NULL;
  SDL_Surface *hoverDemoniaque = NULL;
  SDL_Surface *nextButton = NULL;
  SDL_Surface *nextButtonHover = NULL;
  SDL_Surface *menuBouton = NULL;
  SDL_Surface *menuBoutonHover = NULL;

  reglesImage = IMG_Load("assets/sudoku/difficulteSudoku.jpg");
  hoverFacile = IMG_Load("assets/sudoku/facileButton.png");
  hoverMoyen = IMG_Load("assets/sudoku/moyenButton.png");
  hoverDifficile = IMG_Load("assets/sudoku/difficileButton.png");
  hoverDemoniaque = IMG_Load("assets/sudoku/demoniaqueButton.png");
  nextButton = IMG_Load("assets/sudoku/nextButton.png");
  nextButtonHover = IMG_Load("assets/sudoku/nextButtonHover.png");
  menuBouton = IMG_Load("assets/sudoku/menuBouton.png");
  menuBoutonHover = IMG_Load("assets/sudoku/menuBoutonHover.png");

  // Positions
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect posFacileButton = newRect(80, 489, 76, 339);
  SDL_Rect posMoyenButton = newRect(775, 489, 76, 324);
  SDL_Rect posDifficileButton = newRect(51, 593, 68, 435);
  SDL_Rect posDemoniaqueButton = newRect(642, 595, 68, 590);
  SDL_Rect posNextButton = newRect(479, 278, 99, 278);
  SDL_Rect posMenuBouton = newRect(25, 25, 200, 200);

  // Boucle principale
  while (continuer == 1)
  {
    // Affichage des parametres
    SDL_BlitSurface(reglesImage, NULL, screen, &fullscreen);
    SDL_BlitSurface(menuBouton, NULL, screen, &posMenuBouton);
    if (choix)
      SDL_BlitSurface(nextButton, NULL, screen, &fullscreen);
    // Recuperation de la position de la souris
    c.x = event.button.x;
    c.y = event.button.y;
    // Detection boutons onHover
    if (posInclusion(c.x, c.y, posFacileButton) || (choix == 1))
    {
      SDL_BlitSurface(hoverFacile, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posMoyenButton) || (choix == 2))
    {
      SDL_BlitSurface(hoverMoyen, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posDifficileButton) || (choix == 3))
    {
      SDL_BlitSurface(hoverDifficile, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posDemoniaqueButton) || (choix == 4))
    {
      SDL_BlitSurface(hoverDemoniaque, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posNextButton) && (choix))
    {
      SDL_BlitSurface(nextButtonHover, NULL, screen, &fullscreen);
    }
    if (posInclusion(c.x, c.y, posMenuBouton))
    {
      SDL_BlitSurface(menuBoutonHover, NULL, screen, &posMenuBouton);
    }
    // Boucle principale
    while (SDL_PollEvent(&event))
    {
      // Detection des entrees
      switch (event.type)
      {
      // Si on clique sur la croix, ca se ferme
      case SDL_QUIT:
        continuer = 0;
        break;
      // Detection du clic de la souris
      case SDL_MOUSEBUTTONDOWN:
        if (posInclusion(c.x, c.y, posFacileButton))
        {
          choix = 1;
        }
        if (posInclusion(c.x, c.y, posMoyenButton))
        {
          choix = 2;
        }
        if (posInclusion(c.x, c.y, posDifficileButton))
        {
          choix = 3;
        }
        if (posInclusion(c.x, c.y, posDemoniaqueButton))
        {
          choix = 4;
        }
        if (posInclusion(c.x, c.y, posNextButton) && choix)
        {
          // On lance le jeu
          continuer = playSudoku(screen, choix - 1, time(NULL), jp, p);
        }
        if (posInclusion(c.x, c.y, posMenuBouton))
        {
          continuer = 2;
        }
      }
    }
    // On actualise l'ecran
    SDL_Flip(screen);
  }
  // On libere la memoire
  SDL_FreeSurface(reglesImage);
  SDL_FreeSurface(hoverFacile);
  SDL_FreeSurface(hoverMoyen);
  SDL_FreeSurface(hoverDifficile);
  SDL_FreeSurface(hoverDemoniaque);
  SDL_FreeSurface(nextButton);
  SDL_FreeSurface(nextButtonHover);
  SDL_FreeSurface(menuBouton);
  SDL_FreeSurface(menuBoutonHover);
  // On retourne continuer pour le reste des fonctions
  return continuer;
}

int playSudoku(SDL_Surface *screen, int difficulte, time_t temps,tabJP jp, tabP p)
{
  // Variables
  JoueurSudoku J;
  Coord c;
  Coord onClicked;
  char a;
  int b;
  char d;
  int newNum = 0;
  int nouveau = 0;
  int continuer = 1;
  char timerText[20];
  Coord cTab;
  int c_fini = 0;
  int current_time = 0;
  SDL_Event event;

  // Surfaces
  SDL_Surface *ecranVictoire = NULL;
  SDL_Surface *imageDeFond = NULL;
  SDL_Surface *caseHover = NULL;
  SDL_Surface *menuBouton = NULL;
  SDL_Surface *menuBoutonHover = NULL;
  SDL_Surface *newNumArea = NULL;
  SDL_Surface *niveauAffichage = NULL;
  SDL_Surface *timerSurface = NULL;
  ecranVictoire = IMG_Load("assets/sudoku/fin.png");
  imageDeFond = IMG_Load("assets/sudoku/grilleVide.jpg");
  caseHover = IMG_Load("assets/sudoku/numeros/caseHover.png");
  menuBouton = IMG_Load("assets/sudoku/menuBouton.png");
  menuBoutonHover = IMG_Load("assets/sudoku/menuBoutonHover.png");
  newNumArea = IMG_Load("assets/sudoku/newNumber.png");

  //Sons
  Mix_Music *ok;
  Mix_Music *non;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  ok = Mix_LoadMUS("assets/sounds/ok-sudoku.wav");
  non = Mix_LoadMUS("assets/sounds/non-.wav");
  int sonOkDejaJoue = 0;
  int sonNonDejaJoue = 0;

  // il faut random le numero dans la fonction, selon la difficulte
  int niveau = 0;
  switch (difficulte)
  {
  case 0:
    niveau = intAlea(4);
    break;
  case 1:
    niveau = 4 + intAlea(4);
    break;
  case 2:
    niveau = 8 + intAlea(4);
    break;
  case 3:
    niveau = 12 + intAlea(2);
    break;
  default:
    break;
  }
  grilleSudokuBrute g = initGrilleSudoku(niveau);

  // Chiffres dans les trois couleurs possibles
  SDL_Surface *nbBlancs[9];
  SDL_Surface *nbVerts[9];
  SDL_Surface *nbRouges[9];

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      a = g.gsb[i * 9 + j];
      J.i.tab[j][i] = atoi(&a);
      J.g.tab[j][i] = atoi(&a);
      a = g.gss[i * 9 + j];
      J.s.tab[j][i] = atoi(&a);
    }
  }

  nbBlancs[0] = IMG_Load("assets/sudoku/numeros/base/1.png");
  nbBlancs[1] = IMG_Load("assets/sudoku/numeros/base/2.png");
  nbBlancs[2] = IMG_Load("assets/sudoku/numeros/base/3.png");
  nbBlancs[3] = IMG_Load("assets/sudoku/numeros/base/4.png");
  nbBlancs[4] = IMG_Load("assets/sudoku/numeros/base/5.png");
  nbBlancs[5] = IMG_Load("assets/sudoku/numeros/base/6.png");
  nbBlancs[6] = IMG_Load("assets/sudoku/numeros/base/7.png");
  nbBlancs[7] = IMG_Load("assets/sudoku/numeros/base/8.png");
  nbBlancs[8] = IMG_Load("assets/sudoku/numeros/base/9.png");

  nbVerts[0] = IMG_Load("assets/sudoku/numeros/valide/1.png");
  nbVerts[1] = IMG_Load("assets/sudoku/numeros/valide/2.png");
  nbVerts[2] = IMG_Load("assets/sudoku/numeros/valide/3.png");
  nbVerts[3] = IMG_Load("assets/sudoku/numeros/valide/4.png");
  nbVerts[4] = IMG_Load("assets/sudoku/numeros/valide/5.png");
  nbVerts[5] = IMG_Load("assets/sudoku/numeros/valide/6.png");
  nbVerts[6] = IMG_Load("assets/sudoku/numeros/valide/7.png");
  nbVerts[7] = IMG_Load("assets/sudoku/numeros/valide/8.png");
  nbVerts[8] = IMG_Load("assets/sudoku/numeros/valide/9.png");

  nbRouges[0] = IMG_Load("assets/sudoku/numeros/invalide/1.png");
  nbRouges[1] = IMG_Load("assets/sudoku/numeros/invalide/2.png");
  nbRouges[2] = IMG_Load("assets/sudoku/numeros/invalide/3.png");
  nbRouges[3] = IMG_Load("assets/sudoku/numeros/invalide/4.png");
  nbRouges[4] = IMG_Load("assets/sudoku/numeros/invalide/5.png");
  nbRouges[5] = IMG_Load("assets/sudoku/numeros/invalide/6.png");
  nbRouges[6] = IMG_Load("assets/sudoku/numeros/invalide/7.png");
  nbRouges[7] = IMG_Load("assets/sudoku/numeros/invalide/8.png");
  nbRouges[8] = IMG_Load("assets/sudoku/numeros/invalide/9.png");

  // Couleurs
  SDL_Color blanc = {255, 255, 255};
  SDL_Color orange = {255, 136, 0};

  // Polices
  TTF_Font *font = NULL;
  TTF_Font *font2 = NULL;
  font = TTF_OpenFont(FONT_UBUNTU, 30);
  font2 = TTF_OpenFont(FONT_UBUNTU, 50);

  // Positions
  SDL_Rect posMenuBouton = newRect(25, 25, 200, 200);
  SDL_Rect zoneTextNiveau = newRect(580, 50, 0, 0);
  char textNiveauAffichage[50];
  SDL_Rect positionsNumeros[9][9];
  SDL_Rect positionsNewNumberArea[3][3];
  SDL_Rect fullscreen = newRect(0, 0, 720, 1280);
  SDL_Rect temp = newRect(0, 0, 0, 0);
  SDL_Rect temp2 = newRect(0, 0, 0, 0);
  SDL_Rect timerPos = newRect(1100, 50, 0, 0);

  sprintf(textNiveauAffichage, "Grille %d", niveau + 1);
  niveauAffichage = creerTexte(screen, textNiveauAffichage, blanc, font);

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      positionsNumeros[i][j] = newRect(372 + (56 + 4) * i, 92 + (56 + 4) * j, 56, 56);
    }
  }

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      positionsNewNumberArea[i][j] = newRect(1000 + (56 + 4) * i, 272 + (56 + 4) * j, 56, 56);
    }
  }

  while (continuer == 1)
  {
    // Le temps avance sauf si c'est fini
    if (!c_fini)
      current_time = time(NULL) - temps;
    sprintf(timerText, "%ld", current_time);
    timerSurface = creerTexte(screen, timerText, orange, font2);

    SDL_PollEvent(&event);
    // Recuperation de la position du curseur
    c.x = event.button.x;
    c.y = event.button.y;

    // On affiche la grille vide ainsi que l'interface
    SDL_BlitSurface(imageDeFond, NULL, screen, &fullscreen);
    SDL_BlitSurface(menuBouton, NULL, screen, &posMenuBouton);
    SDL_BlitSurface(niveauAffichage, NULL, screen, &zoneTextNiveau);
    SDL_BlitSurface(timerSurface, NULL, screen, &timerPos);
    SDL_FreeSurface(timerSurface);
    // Si on hover une case, on affiche l'image Hover
    for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        temp = newPos(positionsNumeros[i][j]);
        temp.w = 60;
        temp.h = 60;
        if (posInclusion(c.x, c.y, temp))
        {
          SDL_BlitSurface(caseHover, NULL, screen, &temp);
        }
      }
    }

    // Affichage des chiffres
    for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        if (verification(J))
        {
          // Le chiffre est de base
          if (J.i.tab[i][j])
          {
            SDL_BlitSurface(nbBlancs[J.i.tab[i][j] - 1], NULL, screen, &positionsNumeros[i][j]);
          }
          else if (J.g.tab[i][j])
          {
            cTab.x = i;
            cTab.y = j;
            // Le chiffre est coherent
            if (detection(cTab, J))
            {
              //Le son va se jouer une fois lors de la première case réussie mais après non
              if(sonOkDejaJoue == 0)
              {
                Mix_PlayMusic(ok, 1);
                sonOkDejaJoue = 1;
              }
              SDL_BlitSurface(nbVerts[J.g.tab[i][j] - 1], NULL, screen, &positionsNumeros[i][j]);
            }
            // Le chiffre n'est pas coherent
            else
            {
              //Idem pour celui-ci
              if(sonNonDejaJoue == 0)
              {
                Mix_PlayMusic(non, 1);
                sonNonDejaJoue = 1;
              }
              SDL_BlitSurface(nbRouges[J.g.tab[i][j] - 1], NULL, screen, &positionsNumeros[i][j]);
            }


          }
        }
        else
        {
          c_fini = 1;
          SDL_BlitSurface(nbBlancs[J.g.tab[i][j] - 1], NULL, screen, &positionsNumeros[i][j]);
        }
      }
    }

    // Affichage de l'inteface pour saisir un nouveau numero (la grille a droite)
    if (newNum)
    {
      SDL_BlitSurface(newNumArea, NULL, screen, &fullscreen);
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          if (posInclusion(c.x, c.y, positionsNewNumberArea[i][j]))
          {
            temp = newPos(positionsNewNumberArea[i][j]);
            SDL_BlitSurface(caseHover, NULL, screen, &temp);
          }
        }
      }
      // On garde en memoire la case cliquee pour qu'elle reste hovered
      temp2 = newPos(positionsNumeros[onClicked.x][onClicked.y]);
      if (!c_fini)
        SDL_BlitSurface(caseHover, NULL, screen, &temp2);
    }

    switch (event.type)
    {
    // On clique sur la croix
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_KEYDOWN:
      // Raccourci pour finir le sudoku, on appuis sur une touche
      c_fini = 1;
      break;

    case SDL_MOUSEBUTTONDOWN:
      // Si on clique sur le menu
      if (posInclusion(c.x, c.y, posMenuBouton))
      {
        continuer = 2;
      }
      // Si on clique sur une nouvelle case, ca affichage l'interface voulue
      if (!c_fini)
      {
        for (int i = 0; i < 9; i++)
        {
          for (int j = 0; j < 9; j++)
          {
            if (posInclusion(c.x, c.y, positionsNumeros[i][j]))
            {
              if (J.i.tab[i][j] == 0)
              {
                // On garde en memoire la case, et on passe newNum a 1 pour afficher l'interface
                onClicked.x = i;
                onClicked.y = j;
                newNum = 1;
              }
            }
            if (newNum)
            {
              // On parcours pour savoir quelle case est cliquee
              for (int i = 0; i < 3; i++)
              {
                for (int j = 0; j < 3; j++)
                {
                  if (posInclusion(c.x, c.y, positionsNewNumberArea[i][j]))
                  {
                    nouveau = (i + j * 3) + 1;
                    J.g.tab[onClicked.x][onClicked.y] = nouveau;
                    newNum = 0;
                  }
                }
              }
            }
          }
        }
      }
    }
    // Si on hover le bouton ..
    if (posInclusion(c.x, c.y, posMenuBouton))
    {
      SDL_BlitSurface(menuBoutonHover, NULL, screen, &posMenuBouton);
    }
    // Affichage de l'ecran de victoire
    if (c_fini)
      //scoreSud( current_time,jp,difficulte);
      SDL_BlitSurface(ecranVictoire, NULL, screen, &fullscreen);

    // Actulisation de l'ecran
    SDL_Flip(screen);
  }
  // Liberation memoire
  SDL_FreeSurface(ecranVictoire);
  SDL_FreeSurface(imageDeFond);
  SDL_FreeSurface(caseHover);
  SDL_FreeSurface(menuBouton);
  SDL_FreeSurface(menuBoutonHover);
  SDL_FreeSurface(niveauAffichage);
  SDL_FreeSurface(newNumArea);
  Mix_FreeMusic(ok);
  Mix_FreeMusic(non);
  for (int i = 0; i < 9; i++)
  {
    SDL_FreeSurface(nbBlancs[i]);
    SDL_FreeSurface(nbVerts[i]);
    SDL_FreeSurface(nbRouges[i]);
  }
  TTF_CloseFont(font);
  TTF_CloseFont(font2);
  return continuer;
}

// Permet de formater une case pour l'affichage du hover
SDL_Rect newPos(SDL_Rect oldPos)
{
  return newRect(oldPos.x - 4, oldPos.y - 4, 64, 64);
}

//appel de fonction fait au niveau de c_fini
void scoreSud(int current_time,tabJP jp, int difficulte,tabP p){
  int tempsFacile =600; //temps max pour difficulte facileButton = 10min
  int tempsMoyen  =900; //meme chose pour moyen = 15min
  int tempsDifficile  =2700 ;// difficile 45min
  int tempsDemoniaque = 3600; // demoniaque 1h
  int score=0;
  if (current_time<tempsFacile && difficulte==0) {
    score = score + 40;//score normal pour facile
    if (current_time<0.75*tempsFacile){
      score=score+30;// attribution d'un bonus si nous somme en dessous de 75% du temps
    }
    if (current_time>tempsFacile){
      score=score-((int)((current_time-tempsFacile)/60))*5; //penalité si on depasse
    }
  }
  if (current_time<tempsMoyen && difficulte==1) {
    score = score + 50;//score normal pour moyen
    if (current_time<0.75*tempsMoyen){
      score=score+30;// attribution d'un bonus si nous somme en dessous de 75% du temps
    }
    if (current_time>tempsMoyen){
      score=score-((int)((current_time-tempsMoyen)/60))*5; //penalité si on depasse
    }
  }
  if (current_time<tempsDifficile && difficulte==2) {
    score = score + 60;//score normal pour difficile
    if (current_time<0.75*tempsDifficile){
      score=score+30;// attribution d'un bonus si nous somme en dessous de 75% du temps
    }
    if (current_time>tempsDifficile){
      score=score-((int)((current_time-tempsDifficile)/60))*5; //penalité si on depasse
    }
  }
  if (current_time<tempsDemoniaque && difficulte==3) {
    score = score + 70;//score normal pour demoniaque
    if (current_time<0.75*tempsDemoniaque){
      score=score+30;// attribution d'un bonus si nous somme en dessous de 75% du temps
    }
    if (current_time>tempsDemoniaque){
      score=score-((int)((current_time-tempsDemoniaque)/60))*5; //penalité si on depasse
    }
  }
  score=score/100;
  //mettre score dans jp[0].scoreSudoku et ensuite save le score dans p[0].scoreSudoku

}
