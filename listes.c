#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_liste_vide(liste_t *L) {
  L->tete = NULL;
}

/**
 * Ajouter une chaîne de caractères à la fin d'une liste chaînée
 */
int ajouter_fin(liste_t *L, string s) {
  cellule_t *queue = malloc(sizeof(cellule_t));
  queue->val = s;
  queue->suivant = NULL;

  if (L->tete == NULL){
    L->tete = queue;
    return 0;
  }

  cellule_t *c = L->tete;

  while(c->suivant != NULL) {
    c = c->suivant;
  }

  c->suivant = queue;
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
  cellule_t *cellule = L->tete;
  L->tete = L->tete->suivant;
  free(cellule);
}
