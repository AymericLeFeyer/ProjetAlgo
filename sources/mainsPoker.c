#include "../headers/structure.h"
#include "../headers/mainsPoker.h"



int valeurMain(JoueurPoker jo, CentrePlateau cp) {
  Carte t[5];
  t[0] = jo.hand.carte1;
  t[1] = jo.hand.carte2;
  t[2] = cp.flop;
  t[3] = cp.turn;
  t[4] = cp.river;

  int max = jo.hand.carte1.valeur;
  int current = 0;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        for (int l = 0; l < 5; l++) {
          for (int m = 0; m < 5; m++) {
            if (differents(i, j, k, l, m)) {
              current = valeurMain2(t[i], t[j], t[k], t[l], t[m]);
              if (max < current) max = current;
            }
          }
        }
      }
    }
  }

  return max;
}

int valeurMain2(Carte c1, Carte c2, Carte c3, Carte c4, Carte c5) {
  int a, b, c, d, e;
  a = c1.valeur;
  b = c2.valeur;
  c = c3.valeur;
  d = c4.valeur;
  e = c5.valeur;
  // Retourne la valeur de la main dans cette configuration
  if (memeCouleur(c1, c2, c3, c4, c5)) {
    if (quinte(a, b, c, d, e) == 13) {
      // OMG Trop de chance c'est une QUINTE ROYAL FLUSH
      return 10000;
    }
    else if (quinte(a, b, c, d, e) != 0) {
      // OMG Trop de chance (un peu moins quand meme) c'est une QUINTE FLUSH
      return 8000 + 10 * maxi(a, b, c, d, e);
    }
    else {
      // Dans ce jeu on fait gagner ceux qui n'ont qu'une seule couleur, vive la diversite
      return 5000 + 10 * maxi(a, b, c, d, e) + a;
    }
  }
  if (carre(a, b, c, d)) {
    // Un carre, il est bien droit (comme ses angles xptdr)
    return 7000 + 10 * a;
  }
  if (full(a, b, c, d, e)) {
    // Un full !!
    return 6000 + 10 * a;
  }
  if (quinte(a, b, c, d, e)) {
    // Une quinte pas piauee des hannetons
    return 5000 + 10 * e;
  }

  if (brelan(a, b, c)) {
    // Le bon ptit brelan, l'authentique
    return 3000 + 10 * a;
  }

  if (paire(a, b) && (paire(c, d))) {
    // Une double paire bien sympathique
    return 2000 + 10 * a + c;
  }

  if (paire(a, b)) {
    // Une bien belle petite paire de ... cartes
    return 1000 + 10 * a + c + d + e;
  }
}

int differents(int i, int j, int k, int l, int m) {
  // Retourne 1 si toutes les valeurs sont differentes
  if ((i == j) || (i == k) || (i == l) || (i == m)) return 0;
  if ((j == k) || (j == l) || (j == m)) return 0;
  if ((k == l) || (k == m)) return 0;
  if (l == m) return 0;
  return 1;
}

int maxi(int a, int b, int c, int d, int e) {
  int max = a;
  if (b > max) max = b;
  if (c > max) max = c;
  if (d > max) max = d;
  if (e > max) max = e;
  return max;
}

int memeCouleur(Carte c1, Carte c2, Carte c3, Carte c4, Carte c5) {
  return ((c1.couleur == c2.couleur) && (c2.couleur == c3.couleur) && (c3.couleur == c4.couleur));
}

int quinte(int a, int b, int c, int d, int e) {
  if (a + 1 == b) {
    if (b + 1 == c) {
      if (c + 1 == d) {
        if (d + 1 == e) {
          return e;
        }
      }
    }
  }
  return 0;
}

int carre(int a, int b, int c, int d) {
  if ((a == b) && (a == c) && (a == d)) {
    return a; // a et b font partis du carre
  }
  else return 0;
}

int full(int a, int b, int c, int d, int e) {
  // Un full est compose d'un brelan et d'une paire differente du brelan
  if ((brelan(a, b, c)) && paire(d, e)) {
    return a;
  }
}

int brelan(int a, int b, int c) {
  if ((a == b) && (a == c)) return a;
  return 0;
}

int paire(int a, int b) {
  if (a == b) return a;
  return 0;
}

int testMains() {
  JoueurPoker j;
  CentrePlateau cp;
  j.hand.carte1 = newCarte(1, 13);
  j.hand.carte2 = newCarte(2, 13);
  cp.flop = newCarte(3, 8);
  cp.turn = newCarte(4, 7);
  cp.river = newCarte(1, 11);

  return valeurMain(j, cp);
}
