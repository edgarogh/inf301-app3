#ifndef _LISTES_H
#define _LISTES_H

#include "arbres.h"

typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */

typedef char *string;

struct cellule {
  string val;
  struct cellule *suivant;
  int hauteur;
};

typedef struct cellule cellule_t;

struct liste {
  cellule_t *tete;
  cellule_t *dernier;
};

typedef struct liste liste_t;



struct cellule_noeud {
  noeud *nd;
  int hauteur;
  struct cellule_noeud *suivant;
};

typedef struct cellule_noeud cellule_n;

struct liste_noeud {
  cellule_n *tete;
};

typedef struct liste_noeud liste_n;



/* cree une nouvelle liste, initialement vide */
void init_liste_vide(liste_t *L);

/* Ajouter une nouvelle cellule contenant c
 * en tête de la liste L.
 * Si l'ajout est réussi, le résultat est 0,
 * et 1 sinon (échec de l'ajout)
 */

int ajouter_fin(liste_t *L, string c, int h);

int ajouter_tete(liste_t *L, string c);

void supprimer_tete(liste_t *L);

void init_liste_noeud_vide(liste_n *L);

int ajouter_fin_noeud(liste_n *L, noeud *n, int h);

noeud *supprimer_tete_noeud(liste_n *L, int *h);

#endif /* _LISTES_H */
