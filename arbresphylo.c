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

    else {
      *nb_carac += 1;
      analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);
      analyse_arbre_rec(racine->droit, nb_esp, nb_carac);
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

bool present_espece(arbre a, char *espece){
  if (a == NULL){
    return false;
  }
  if (strcmp(a->valeur, espece) == 0){
    return true;
  }
  return present_espece(a->gauche, espece) || present_espece(a->droit, espece);
}


int rechercher_espece(arbre a, char *espece, liste_t *seq) {
  if (a == NULL) {
    return 1;
  }
  if (strcmp(a->valeur, espece) == 0){
    return 0;
  }

  if (present_espece(a->gauche, espece)){
    return rechercher_espece(a->gauche, espece, seq);
  }
  else if (present_espece(a->droit, espece)){
    ajouter_fin(seq, a->valeur, 0);
    return rechercher_espece(a->droit, espece, seq);
  }
  return 1;
}

/**
 * Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece(arbre *a, char *espece, cellule_t *seq) {
  assert(a != NULL);

  if (*a == NULL || est_esp(*a)) {
    char* a_espece = (*a == NULL) ? "<inconnue>" : (*a)->valeur;

    if (seq == NULL) {
      fprintf(stderr, "L'espèce à ajouter '%s' est indifférenciable de l'espèce '%s'\n", espece, a_espece);
      return 1;
    } else {
      // Ici, l'arbre (le nœud) est une espèce et il reste 1 ou plus caractères
      // permettant de la différencier de l'espèce à ajouter. On créé
      // itérativement les caractères restants dans `seq` et on ajoute
      // l'`espèce` en feuille.

      noeud* feuille = malloc(sizeof(noeud));
      feuille->valeur = espece;
      feuille->gauche = NULL;
      feuille->droit = NULL;

      noeud* caractere = malloc(sizeof(noeud));
      caractere->valeur = seq->val;
      caractere->gauche = *a;

      cellule_t* reste = seq->suivant;
      noeud* caractereA = caractere;

      while (reste) {
        noeud* caractereN = malloc(sizeof(noeud));
        caractereN->valeur = reste->val;
        caractereN->gauche = NULL;
        caractereN->droit = feuille;
        caractereA->droit = caractereN;
        caractereA = caractereN;

        reste = reste->suivant;
      }

      caractereA->droit = feuille;

      *a = caractere;
      return 0;
    }
  }

  else {
    // Vrai si l'espèce à ajouter possède le caractère du nœud `a`
    bool espece_possede_a
      = (seq != NULL) && (0 == strcmp((*a)->valeur, seq->val));

    if (espece_possede_a) {
      // Si l'espèce possède la caractéristique, on "passe à la suivante"...
      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
    } else {
      // ...alors que si elle ne le possède pas, on reste sur la car. actuelle
      return ajouter_espece(&(*a)->gauche, espece, seq);
    }
  }
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */

  // remplir la liste avec les éléments les plus à droite
  // parcour en largeur en stockant la hauteur de chaque noeud
  // puis supprimer les éléments qui ont la même hauteur que leur suivant

void afficher_par_niveau(arbre racine, FILE* fout) {
  // Remplissage d'une liste chaînée avec tous les noeuds de l'arbre qui ne sont pas des feuilles
  if (racine == NULL || (racine->gauche == NULL && racine->droit == NULL)){
    return;
  }
  int i = 0;
  noeud *n = NULL;
  liste_n file;
  init_liste_noeud_vide(&file);
  liste_n *f = &file;
  liste_t l_cmp, l_parcours;
  init_liste_vide(&l_cmp);
  liste_t *liste_comp = &l_cmp;
  init_liste_vide(&l_parcours);
  liste_t *liste_parcours = &l_parcours;
  ajouter_fin(liste_comp, racine->valeur, i);
  ajouter_fin_noeud(f, racine, i);
  while (f->tete != NULL){
    n = supprimer_tete_noeud(f, &i);
    if (n->gauche != NULL && (n->gauche->gauche != NULL || n->gauche->droit != NULL)){
      ajouter_fin_noeud(f, n->gauche, i+1);
      ajouter_fin(liste_comp, n->gauche->valeur, i+1);
      ajouter_fin(liste_parcours, n->gauche->valeur, i+1);
  
    }
    if (n->droit != NULL && (n->droit->gauche != NULL || n->droit->droit != NULL)){
      ajouter_fin_noeud(f, n->droit, i+1);
      ajouter_fin(liste_comp, n->droit->valeur, i+1);
      ajouter_fin(liste_parcours, n->droit->valeur, i+1);
    }
  }

  // Tri de la liste pour ne garder que les éléments le plus à droite pour chaque niveau
  cellule_t *prec = liste_comp->tete;
  cellule_t *parcours = prec->suivant;
  if (parcours != NULL){
    while (parcours->suivant != NULL){
      if (parcours->hauteur == parcours->suivant->hauteur){
        prec->suivant = parcours->suivant;
        parcours = prec->suivant;
      } else {
        prec = prec->suivant;
        parcours = prec->suivant;
      }
    }
  }

  // Parcours final de l'arbre et affichage des caractéristiques
  fprintf(fout, "%s\n", racine->valeur);
  supprimer_tete(liste_comp);
  while (liste_parcours->tete != NULL){
    fprintf(fout, "%s ", liste_parcours->tete->val);
    if (liste_comp->tete != NULL){
      if (liste_parcours->tete->val == liste_comp->tete->val){
        fprintf(fout, "\n");
        supprimer_tete(liste_comp);
      }
    }
    supprimer_tete(liste_parcours);
  }
}


// Acte 4

int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
