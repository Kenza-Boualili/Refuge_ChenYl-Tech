#ifndef COMPARER_H
#define COMPARER_H
#include "animal.h"
// Fonction pour comparer deux chaînes de caractères sans tenir compte de la casse
int comparer(const char *s1, const char *s2);

// Fonction pour comparer deux animaux par espèce
int comparerAnimauxParEspece(const void* a1, const void* a2);


#endif // COMPARER_H
