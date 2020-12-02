#include "arbresphylo.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    fprintf(stderr, "Aucun argument attendu\n");
    return 1;
  }

  FILE* in = fopen("tests/recherche-AppoLab.test", "r");
  arbre a = lire_arbre(in);

  liste_t carac = { .tete = NULL };
  rechercher_espece(a, "AppoLab", &carac);

  cellule_t* cel = carac.tete;
  while (cel) {
    printf("%s ", cel->val);
    cel = cel->suivant;
  }

  printf("AppoLab\n");
}