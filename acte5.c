#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "arbres.h"
#include "arbresphylo.h"
#include "common_tests.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage : %s <nom fichier test>\n", argv[0]);
		return 1;
	}
	char* fichier_test = argv[1];
  affiche_arbre(acte_V(fichier_test));
}
