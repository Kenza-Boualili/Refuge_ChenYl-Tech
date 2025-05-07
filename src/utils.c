#include "utils.h"
#include <stdio.h>

void nettoyerTampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void enleverSautLigne(char *chaine, size_t taille_max) {
    size_t i = 0;
    while (i < taille_max && chaine[i] != '\0' &&
           chaine[i] != '\n' && chaine[i] != '\r') {
        i++;
    }
    if (i < taille_max) chaine[i] = '\0';
    else if (taille_max > 0) chaine[taille_max - 1] = '\0';
}

size_t longueurChaine(const char *chaine) {
    size_t len = 0;
    if (chaine == NULL) return 0;
    while (chaine[len] != '\0' && chaine[len] != '\n' && chaine[len] != '\r') {
        len++;
    }
    return len;
}
