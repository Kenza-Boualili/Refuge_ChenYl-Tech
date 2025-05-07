#include "utils.h"
#include <stdio.h>

void nettoyerTampon() {
    while (getchar() != '\n'); 
}    
void enleverSautLigne(char *chaine, size_t taille_maximale) {
    for (size_t i = 0; i < taille_maximale && chaine[i] != '\0'; i++) {
        if (chaine[i] == '\n' || chaine[i] == '\r') {
            chaine[i] = '\0';
            return;
        }
    }
    if (taille_maximale > 0) {
        chaine[taille_maximale - 1] = '\0';
    }
}

size_t longueurChaine(const char *chaine) {
    size_t longueur = 0;  
    if (!chaine){
        return 0;
    } 
    while (chaine[longueur] && chaine[longueur] != '\n' && chaine[longueur] != '\r') {
        longueur++;
    }
    return longueur;
}
