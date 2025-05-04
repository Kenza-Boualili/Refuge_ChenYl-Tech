#ifndef UTILS_H               // Si UTILS_H n'est pas défini, 
                              // active le code jusqu'à #endif

#define UTILS_H               // Définit UTILS_H pour empêcher 
                              // l'inclusion multiple du fichier

#include <stddef.h>           // Inclusion de la bibliothèque standard pour size_t (représenter les tailles/mémoire)

int compareStr(const char *a, const char *b); // Compare deux chaînes 

void nettoyerBuffer();         // Nettoie le buffer d'entrée 
                               // Utile après un scanf() pour éviter les erreurs

void enleverNewline(char *chaine, size_t taille_max); // Enlève le caractère '\n' d'une chaîne :
                                                      // - "chaine" : chaîne à modifier
                                                      // - "taille_max" : taille maximale 

size_t longueurChaine(const char *chaine); // Calcule la longueur d'une chaîne :
                                           // - Equivalent de strlen() (sauf que nous on utilise pas string)
                                           // - Retourne un size_t (non négatif)

#endif                        // Fin de la protection d'inclusion multiple