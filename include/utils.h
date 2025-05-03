// include/utils.h (Corrigé)
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h> // Pour size_t

int compareStr(const char *a, const char *b);
void nettoyerBuffer();
void enleverNewline(char *chaine, size_t taille_max);
size_t longueurChaine(const char *chaine); // <-- AJOUTÉE

#endif