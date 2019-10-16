#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>

#include "../headers/structure.h"
#include "../headers/shortcuts.h"


// Cree un rect rapidement
SDL_Rect newRect(int x, int y, int h, int w) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.h = h;
    r.w = w;
    return r;
}

// Renvoie true si a est totalement inclus dans b, false sinon
bool inclusion(SDL_Rect a, SDL_Rect b) {
  if (!((b.x <= a.x) && (a.x <= b.x + b.w))) {
    return false;
  }
  if (!((b.x <= a.x + a.w) && (a.x + a.w <= b.x + b.w))) {
    return false;
  }
  if (!((b.y <= a.y) && (a.y <= b.y + b.h))) {
    return false;
  }
  if (!((b.y <= a.y + a.h) && (a.y + a.h <= b.y + b.h))) {
    return false;
  }
  return true;
}

// retourne true si la pos est sur le rect, false sinon
bool posInclusion(int x, int y, SDL_Rect b) {
  return inclusion(newRect(x, y, 1, 1), b);
}

// Renvoie true si a est partiellement inclus dans b
bool collision(SDL_Rect a, SDL_Rect b) {
  if ((b.x < a.x) && (a.x < b.x + b.w) && (b.y < a.y) && (a.y < b.y + b.h)) {
    return true;
  }
  if ((b.x < a.x + a.w) && (a.x + a.w < b.x + b.w) && (b.y < a.y) && (a.y < b.y + b.h)) {
    return true;
  }
  if ((b.x < a.x) && (a.x < b.x + b.w) && (b.y < a.y + a.h) && (a.y + a.h < b.y + b.h)) {
    return true;
  }
  if ((b.x < a.x + a.w) && (a.x + a.w < b.x + b.w) && (b.y < a.y + a.h) && (a.y + a.h < b.y + b.h)) {
    return true;
  }
  return false;

}
