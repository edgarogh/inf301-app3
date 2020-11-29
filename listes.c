#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fichier à compléter au besoin */

void init_liste_vide(liste_t *L) {
  L->tete = NULL;
}

int ajouter_fin(liste_t *L, string c) {
  cellule_t *cellule = malloc(sizeof(cellule_t));
  cellule->val = c;
  if (L->tete == NULL){
    L->tete = cellule;
    return 0;
  }
  cellule_t *second = L->tete;
  while(second->suivant != NULL){
    second = second->suivant;
  }
  second->suivant = cellule;
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
