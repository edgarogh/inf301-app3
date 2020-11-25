#include "arbres.h"
#include <stdio.h>

/**
 * Créé des flèches Dot pour un arbre donné
 * 
 * @returns le nom du nœud Dot créé
 */
char* arbre_vers_edges(arbre a, FILE* out) {
  if (est_carac(a)) {
    char* g = arbre_vers_edges(a->gauche, out);
    char* d = arbre_vers_edges(a->droit, out);
    if (g != NULL) fprintf(out, "%s -> %s [label=non]\n", a->valeur, g);
    if (d != NULL) fprintf(out, "%s -> %s [label=oui]\n", a->valeur, d);
  }

  return a->valeur;
}

void arbre_vers_dot(char* title, arbre a, FILE* out) {
  fprintf(out, "digraph \"%s\" {\n", title);
  arbre_vers_edges(a, out);
  fprintf(out, "}\n");
}

// Cette section est activée lorsque make fabrique l'exécutable "dotcv"
// Si elle reste désactivée, on peut se servir de ce fichier comme d'un
// paquetage indépendant
#ifdef DOT_CONVERT_MAIN
#include <stdio.h>
#include <stdlib.h>

void help(char* exe_name) {
  fprintf(stderr, "Utilisation:\n  %s <chemin/vers/arbre.test> [chemin/vers/graphe.dot]\n\nnote: la sortie par défaut est stdout\n", exe_name);
  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc < 2 || argc > 3) help(argv[0]);

  FILE* in = fopen(argv[1], "r");

  FILE* out = stdout;
  if (argc == 3) {
    out = fopen(argv[2], "w");
  }

  if (in == NULL || out == NULL) {
    fprintf(stderr, "Impossible d'ouvrir un fichier. Arrêt");
    exit(2);
  }

  arbre a = lire_arbre(in);

  arbre_vers_dot(argv[1], a, out);

  fclose(in);
  fclose(out); // Ne pose aucun problème quand `out == stdout`
}
#endif
