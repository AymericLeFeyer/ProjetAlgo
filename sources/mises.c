#include "../headers/structure.h"


//mise au jeu , suivre=memesomme , relance= mindouble de la memesomme, coucher=etat a 1
void miseJeu (JoueurPoker *j, CentrePlateau* p){
  int choix =0; //1=suivre; 2=relance; 3= se coucher
  printf("Votre choix 1=suivre; 2=relance; 3= se coucher 4=tapis\n");
  scanf("%d",&choix );
switch (choix){
  case 1: //Suivre
    if (j->argent >= p->miseD){
    suivre(j,p);
    }
      break;
   case 2: //relance
   if ((j->argent >= ((p->miseD*2)+10)) || (j->argent >= ((p->miseD*2)+5)) || (j->argent >= (p->miseD*4)) || (j->argent >= (p->miseD*2)) )
    relancer(j,p);
    break;
    case 3: // se coucher
      j->etat= 1;
    break;
    case 4://tapis
      if (j->argent >= p->miseD){
      tapis(j,p);
    }
      break;
  }
}

void suivre (JoueurPoker *j, CentrePlateau *p){
    j->argent-=p->miseD;
    p->mise+=p->miseD;
}

void relancer(JoueurPoker *j, CentrePlateau *p){
  int choix2=0;
  int choix3=0;
  while (choix3!=1){
      printf("Votre choix 1=+10; 2=+5; 3= s*2; 4=defaut\n");
      scanf("%d \n",&choix2 );
      switch (choix2){
        case 1:
          j->argent -= ((p->miseD*2)+10);
          p->mise += ((p->miseD*2)+10);
        break;
        case 2:
          j->argent -= ((p->miseD*2)+5);
          p->mise += ((p->miseD*2)+5);
        break;
        case 3:
          j->argent -= ((p->miseD*4));
          p->mise += ((p->miseD*4));
        break;
        case 4:
            j->argent -= (p->miseD*2);
            p->mise += (p->miseD*2);
        break;
      }
    printf("1 pour valider mise 0= continuer a  monter la mise\n" );
    scanf("%d\n",&choix3);
    }
}

void tapis (JoueurPoker *j, CentrePlateau *p){
      p->mise+=j->argent;
      j->argent-=j->argent;
}
