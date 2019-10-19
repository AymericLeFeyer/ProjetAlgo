#include "../headers/structure.h"

//retire 5 a l'argent de chaque joueur pour la mise sur le CentrePlateau
void miseTotal(JoueurPoker* j1, JoueurPoker* j2, JoueurPoker* j3, JoueurPoker* j4, JoueurPoker* j5,CentrePlateau* p){
    int somme=0;
    if (j1->etat==0){
      j1->argent -=5;
      somme=somme+5;
    }
    if (j2->etat==0){
      j2->argent-=5;
      somme=somme+5;
    }
    if (j3->etat==0){
      j3->argent-=5;
      somme=somme+5;
    }
    if (j4->etat==0){
      j4->argent-=5;
      somme=somme+5;
    }
    if (j5->etat==0){
      j5->argent-=5;
      somme=somme+5;
    }

    p->mise=somme;
}

//mise au jeu , suivre=memesomme , relance= mindouble de la memesomme, coucher=etat a 1
<<<<<<< HEAD
void miseJeu (JoueurPoker *j, CentrePlateau* p){
  int choix =0; //1=suivre; 2=relance; 3= se coucher
  int choix2=0; //1=+10;2=+5;3=*2;4=defaut (fera *2 par default)
=======
Void miseJeu (JoueurPoker *j, CentrePlateau* p){
  int choix =0; //1=suivre; 2=relance; 3= se coucher
  int choix2=; //1=+10;2=+5;3=*2;4=defaut (fera *2 par default)
>>>>>>> 034fc29561c0525c51901a9f06f65ce8a2177d1b
  scanf("%d Votre choix 1=suivre; 2=relance; 3= se coucher\n",choix );
switch (choix) {
  case 1:
    if (j->argent >= p->mise) {
      j->argent-=p->mise;
      p->mise+=p->mise;
      break;
    }
  case 2:
  if (j->argent >= (p->mise*2)) {
    scanf("%d Votre choix 1=+10; 2=+5; 3= s*2; 4=defaut \n",choix2 );
    switch (choix2) {
      case 1:
      if (j->argent >= ((p->mise*2)+10)) {
        j->argent -= ((p->mise*2)+10);
        p->mise += ((p->mise*2)+10);
      }
    break;
      case 2:
      if (j->argent >= ((p->mise*2)+5)) {
        j->argent -= ((p->mise*2)+5);
        p->mise += ((p->mise*2)+5);
      }
    break;
      case 3:
<<<<<<< HEAD
      if (j->argent >= (p->mise*4)) {
        j->argent -= ((p->mise*4));
        p->mise += ((p->mise*4));
=======
      if (j->argent >= (p->mise*4) {
        j->argent -= ((p->mise*4);
        p->mise += ((p->mise*4);
>>>>>>> 034fc29561c0525c51901a9f06f65ce8a2177d1b
      }
    break;
      case 4:
      if (j->argent >= (p->mise*2)) {
        j->argent -= (p->mise*2);
        p->mise += (p->mise*2);
      }
    break;

  }
  case 3:
  j->etat= 1;
  break;
}

}
<<<<<<< HEAD
}
=======
>>>>>>> 034fc29561c0525c51901a9f06f65ce8a2177d1b
