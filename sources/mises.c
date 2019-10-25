#include "../headers/structure.h"


//mise au jeu , suivre=memesomme , relance= mindouble de la memesomme, coucher=etat a 1
void miseJeu (JoueurPoker *j, CentrePlateau* p){
  int choix =0; //1=suivre; 2=relance; 3= se coucher
  printf("Votre choix 1=suivre; 2=relance; 3= se coucher 4=tapis\n");
  scanf("%d",&choix );
switch (choix){
  case 1: //Suivre
    suivre(j,p);
      break;
   case 2: //relance
    relancer(j,p);
    break;
    case 3: // se coucher
      j->etat= 1;
    break;
    case 4://tapis
      tapis(j,p);
      break;
  }
}

void suivre (JoueurPoker *j, CentrePlateau *p){
  if (j->etat==0){
    if (j->argent >= p->mise) {
      j->argent-=p->mise;
      p->mise+=p->mise;
    }
    else {
      j->etat=1;
    }
  }
}

void relancer(JoueurPoker *j, CentrePlateau *p){
  int choix2=0;
  int choix3=0;
  while (choix3!=1){
    if (j->etat==0) {
      printf("Votre choix 1=+10; 2=+5; 3= s*2; 4=defaut\n");
      scanf("%d \n",&choix2 );
      switch (choix2){
        case 1:
        if (j->argent >= ((p->mise*2)+10)) {
          j->argent -= ((p->mise*2)+10);
          p->mise += ((p->mise*2)+10);
          }
          else {
            j->etat=1;
          }
        break;
        case 2:
        if (j->argent >= ((p->mise*2)+5)) {
          j->argent -= ((p->mise*2)+5);
          p->mise += ((p->mise*2)+5);
          }
          else {
            j->etat=1;
          }
        break;
        case 3:
        if (j->argent >= (p->mise*4)) {
          j->argent -= ((p->mise*4));
          p->mise += ((p->mise*4));
        }
        else {
          j->etat=1;
        }
        break;
        case 4:
          if (j->argent >= (p->mise*2)) {
            j->argent -= (p->mise*2);
            p->mise += (p->mise*2);
          }
          else {
            j->etat=1;
          }
        break;
      }
    }
    printf("1 pour valider mise 0= continuer a  monter la mise\n" );
    scanf("%d\n",&choix3);
    }
}

void tapis (JoueurPoker *j, CentrePlateau *p){
  if (j->etat==0){
    if (j->argent >= p->mise) {
      p->mise+=j->argent;
      j->argent-=j->argent;
    }
    else {
      j->etat=1;
    }
  }
}
