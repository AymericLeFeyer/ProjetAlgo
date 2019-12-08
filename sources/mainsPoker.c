#include "../headers/structure.h"
#include "../headers/mainsPoker.h"

int valeurMain(JoueurPoker jo, CentrePlateau cp)
{
  // En fonction des 7 cartes, retourne le nombre de points de la plus grosse combinaison
  Carte t[7];
  t[0] = jo.hand.carte1;
  t[1] = jo.hand.carte2;
  t[2] = cp.flop1;
  t[3] = cp.flop2;
  t[4] = cp.flop3;
  t[5] = cp.turn;
  t[6] = cp.river;

  int max = jo.hand.carte1.valeur;
  int current = 0;

  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      for (int k = 0; k < 7; k++)
      {
        for (int l = 0; l < 7; l++)
        {
          for (int m = 0; m < 7; m++)
          {
            for (int n = 0; n < 7; n++)
            {
              for (int o = 0; o < 7; o++)
              {
                if (differents(i, j, k, l, m, n, o))
                {
                  current = valeurMain2(t[i], t[j], t[k], t[l], t[m], t[n], t[o]);
                  if (max < current)
                    max = current;
                }
              }
            }
          }
        }
      }
    }
  }

  return max;
}

int valeurMain2(Carte c1, Carte c2, Carte c3, Carte c4, Carte c5, Carte c6, Carte c7)
{
  int a, b, c, d, e, f, g;
  a = c1.valeur;
  b = c2.valeur;
  c = c3.valeur;
  d = c4.valeur;
  e = c5.valeur;
  f = c6.valeur;
  g = c7.valeur;
  // Retourne la valeur de la main dans cette configuration
  if (memeCouleur(c1, c2, c3, c4, c5, c6, c7))
  {
    if (quinte(a, b, c, d, e) == 13)
    {
      // OMG Trop de chance c'est une QUINTE ROYAL FLUSH
      return 10000;
    }
    else if (quinte(a, b, c, d, e) != 0)
    {
      // OMG Trop de chance (un peu moins quand meme) c'est une QUINTE FLUSH
      return 8000 + 10 * maxi(a, b, c, d, e, f, g);
    }
    else
    {
      // Dans ce jeu on fait gagner ceux qui n'ont qu'une seule couleur, vive la diversite
      return 5000 + 10 * maxi(a, b, c, d, e, f, g) + a;
    }
  }
  if (carre(a, b, c, d))
  {
    // Un carre, il est bien droit (comme ses angles xptdr)
    return 7000 + 10 * a;
  }
  if (full(a, b, c, d, e))
  {
    // Un full !!
    return 6000 + 10 * a;
  }
  if (quinte(a, b, c, d, e))
  {
    // Une quinte pas piquee des hannetons
    return 5000 + 10 * e;
  }

  if (brelan(a, b, c))
  {
    // Le bon ptit brelan, l'authentique
    return 3000 + 10 * a;
  }

  if (paire(a, b) && (paire(c, d)))
  {
    // Une double paire bien sympathique
    return 2000 + 10 * a + c;
  }

  if (paire(a, b))
  {
    // Une bien belle petite paire de ... cartes
    return 1000 + 10 * a + c + d + e;
  }
}

int differents(int i, int j, int k, int l, int m, int n, int o)
{
  // Retourne 1 si toutes les valeurs sont differentes
  if ((i == j) || (i == k) || (i == l) || (i == m) || (i == n) || (i == o))
    return 0;
  if ((j == k) || (j == l) || (j == m) || (j == n) || (j == o))
    return 0;
  if ((k == l) || (k == m) || (k == n) || (k == o))
    return 0;
  if ((l == m) || (l == n) || (l == o))
    return 0;
  if ((m == n) || (m == o))
    return 0;
  if (n == o)
    return 0;
  return 1;
}

int maxi(int a, int b, int c, int d, int e, int f, int g)
{
  int max = a;
  if (b > max)
    max = b;
  if (c > max)
    max = c;
  if (d > max)
    max = d;
  if (e > max)
    max = e;
  if (f > max)
    max = f;
  if (g > max)
    max = g;
  return max;
}

int memeCouleur(Carte c1, Carte c2, Carte c3, Carte c4, Carte c5, Carte c6, Carte c7)
{
  return ((c1.couleur == c2.couleur) && (c2.couleur == c3.couleur) && (c3.couleur == c4.couleur) && (c4.couleur == c5.couleur) && (c5.couleur == c6.couleur) && (c6.couleur == c7.couleur));
}

int quinte(int a, int b, int c, int d, int e)
{
  if (a + 1 == b)
  {
    if (b + 1 == c)
    {
      if (c + 1 == d)
      {
        if (d + 1 == e)
        {
          return e;
        }
      }
    }
  }
  return 0;
}

int carre(int a, int b, int c, int d)
{
  if ((a == b) && (a == c) && (a == d))
  {
    return a; // a et b font partis du carre
  }
  else
    return 0;
}

int full(int a, int b, int c, int d, int e)
{
  // Un full est compose d'un brelan et d'une paire differente du brelan
  if ((brelan(a, b, c)) && paire(d, e))
  {
    return a;
  }
}

int brelan(int a, int b, int c)
{
  if ((a == b) && (a == c))
    return a;
  return 0;
}

int paire(int a, int b)
{
  if (a == b)
    return a;
  return 0;
}
