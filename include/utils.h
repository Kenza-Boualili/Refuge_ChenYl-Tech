#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include "animal.h"


void nettoyerTampon();
void enleverSautLigne(char *chaine, int taille_max);
size_t longueurChaine(const char *chaine);
void nettoyerLigne(char *ligne);
int extraireChamps(char *ligne, Animal *animal, char *especeTemp, char *commentaireTemp);
void copierTexte(char *destination, const char *source, size_t max_size);



#endif
