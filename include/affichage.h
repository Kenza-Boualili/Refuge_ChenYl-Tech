#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "animal.h" // pour le type Animal

// Affiche le menu principal
void afficherMenu(void);

// Affiche les détails d'un animal et son âge (réel ou humain)
void afficherResultat(const Animal *a, int age_calcule);

// Menu pour choisir le type d’âge à afficher (réel ou humain)
int menuTypeAge(void);

#endif
