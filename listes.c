#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_liste_vide(liste_t *L) {
  L->tete = NULL;
  L->dernier = NULL;
}

/**
 * Ajouter une chaîne de caractères à la fin d'une liste chaînée
 */
int ajouter_fin(liste_t *L, string s, int h) {
  cellule_t *cel = malloc(sizeof(cellule_t));
  cel->val = s;
  cel->suivant = NULL;
  cel->hauteur = h;

  if (L->tete == NULL) {
    L->tete = cel;
    L->dernier = cel;
    return 0;
  }

  L->dernier->suivant = cel;
  L->dernier = L->dernier->suivant;
  return 0;
}

int ajouter_tete(liste_t *L, string c) {
  cellule_t *cellule = malloc(sizeof(cellule_t));
  cellule->val = c;
  cellule_t *second = L->tete;
  L->tete = cellule;
  L->tete->suivant = second;
  return 0;
}

void supprimer_tete(liste_t *L) {
  if (L->tete != NULL){
    cellule_t *cellule = L->tete;
    L->tete = L->tete->suivant;
    free(cellule);
  }
  else {
    printf("Erreur, pile vide");
  }
}

void init_liste_noeud_vide(liste_n *L){
  L->tete = NULL;
}

int ajouter_fin_noeud(liste_n *L, noeud *n, int h){
  cellule_n *cel = malloc(sizeof(cellule_t));
  cel->nd = n;
  cel->suivant = NULL;
  cel->hauteur = h;

  if (L->tete == NULL) {
    L->tete = cel;
    return 0;
  }

  cellule_n *p = L->tete;
  while (p->suivant != NULL){
    p = p->suivant;
  }
  p->suivant = cel;
  return 0;
}

noeud *supprimer_tete_noeud(liste_n *L, int *h){
  if (L->tete != NULL){
    cellule_n *cellule = L->tete;
    noeud *n = cellule->nd;
    *h = cellule->hauteur;
    L->tete = L->tete->suivant;
    free(cellule);
    return n;
  }
  else {
    printf("Erreur, pile vide");
    return NULL;
  }
}
