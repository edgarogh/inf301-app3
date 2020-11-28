#include "arbresphylo.h"
#include "arbres.h"
#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyse_arbre_rec(arbre racine, int *nb_esp, int *nb_carac) {
  if (racine != NULL) {
    if (est_esp(racine)) {
      *nb_esp += 1;
    }

    else if (est_carac(racine)) {
      *nb_carac += 1;
      analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);
      analyse_arbre_rec(racine->droit, nb_esp, nb_carac);
    }

    else {
      fprintf(stderr, "Nœud invalide");
      exit(1);
    }
  }
}

void analyse_arbre(arbre racine, int *nb_esp, int *nb_carac) {
  *nb_esp = 0;
  *nb_carac = 0;
  analyse_arbre_rec(racine, nb_esp, nb_carac);
}

/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y
 * mettre les caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece(arbre a, char *espece, liste_t *seq) {
  if (a == NULL) {
    return 1;
  }
  if (a->gauche != NULL){
    rechercher_espece(a->gauche, espece, seq);
  }
  else if (a->droit != NULL){
    ajouter_tete(seq, a->valeur);
    /*while (seq->tete->val != a->valeur){
        supprimer_tete(seq);
    }*/
    rechercher_espece(a->droit, espece, seq);
  }
  else {
    if (strcmp(a->valeur, espece) == 0){
        return 0;
        //trouver un moyen de supprimer les éléments en trop de la séquence
    }
    else {
        // remonter dans l'arbre
    }
  }
  return 1;
}

/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece(arbre *a, char *espece, cellule_t *seq) {
  bool e_esp = est_esp(*a);
  bool e_car = est_carac(*a);

  // FIXME conditions à tester
  if (seq == NULL) {

  }
  else if (e_esp) {

  }
  else if (0 == strcmp((*a)->valeur, seq->val)) {

  }
  return 1;
}
