#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void nettoyerTampon();
void enleverSautLigne(char *chaine, size_t taille_max);
size_t longueurChaine(const char *chaine);
int extraireChamps(char *ligne, Animal *animal, char *especeTemp, char *commentaireTemp);


#endif
