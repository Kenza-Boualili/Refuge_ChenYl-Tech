// utils.h (Modifié)
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h> // Ajout pour size_t

int compareStr(const char *a, const char *b);
void nettoyerBuffer();
void enleverNewline(char *chaine, size_t taille_max); // <-- AJOUTER CETTE LIGNE

#endif