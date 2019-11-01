#include "../headers/structure.h"


//mise au jeu , suivre=memesomme , relance= mindouble de la memesomme, coucher=etat a 1
void miseJeu (JoueurPoker *j, CentrePlateau* p){
  int choix =0; //1=suivre; 2=relance; 3= se coucher
  int a=0;
  while(a==0){
  printf("Votre choix 1=suivre; 2=relance; 3= se coucher 4=tapis\n");
  scanf("%d",&choix );
switch (choix){
  case 1: //Suivre
    if (j->argent >= p->miseD){
    suivre(j,p);
    a=1;
    }
      break;
   case 2: //relance
   if (j->argent >= (p->miseD*2)){
    relancer(j,p);
    a=1;
   }
    break;
    case 3: // se coucher
      j->etat= 1;
      a=1;
    break;
    case 4://tapis
      if (j->argent >= p->miseD){
      tapis(j,p);
      a=1;
    }
      break;
  }
  }
}

void suivre (JoueurPoker *j, CentrePlateau *p){
    j->argent-=p->miseD;
    p->mise+=p->miseD;
}

void relancer(JoueurPoker *j, CentrePlateau *p){
  int choix2=0;
  int choix3=0;
  int miseA=p->miseD*2;
  while (choix3!=1){
      printf("Votre argent : %d\n",j->argent);
      printf("mise actuelle : %d\n",miseA);
      printf("Votre choix 1=+10; 2=+5; 3= s*2; 4=reset\n");
      scanf("%d",&choix2 );
      switch (choix2){
        case 1:
          if(j->argent>=miseA+10){
              miseA+=10;
          }
        break;
        case 2:
          if(j->argent>=miseA+5){
              miseA+=5;
          }
        break;
        case 3:
          if(j->argent>=miseA*2){
              miseA*=2;
          }
        break;
        case 4:
            miseA=p->miseD*2;
        break;
      }
    printf("1 pour valider mise 0= continuer a  monter la mise\n" );
    scanf("%d",&choix3);
    }
    j->argent-=miseA;
    p->mise+=miseA;
    p->miseD=miseA;
}

void tapis (JoueurPoker *j, CentrePlateau *p){
      p->miseD=j->argent;
      p->mise+=j->argent;
      j->argent-=j->argent;
}
