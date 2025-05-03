// src/utils.c (Corrigé)
#include "utils.h"
#include <stdio.h>

void nettoyerBuffer() { /* ... (inchangé) ... */
    int c; while ((c = getchar()) != '\n' && c != EOF);
}
int compareStr(const char* a, const char* b) { /* ... (inchangé) ... */
    int i = 0; while (a[i] && b[i]) { char ca = (a[i]>='A'&&a[i]<='Z')?a[i]+32:a[i]; char cb = (b[i]>='A'&&b[i]<='Z')?b[i]+32:b[i]; if (ca != cb) return 0; i++; } return a[i]=='\0' && b[i]=='\0';
}
void enleverNewline(char *chaine, size_t taille_max) { /* ... (inchangé) ... */
    size_t i = 0; while (i < taille_max && chaine[i] != '\0' && chaine[i] != '\n' && chaine[i] != '\r') i++;
    if (i < taille_max) chaine[i] = '\0'; else if (taille_max > 0) chaine[taille_max - 1] = '\0';
}

// --- AJOUT DE CETTE FONCTION ---
/**
 * @brief Calcule la longueur d'une chaîne (nombre de caractères avant \0).
 * Ne compte PAS \n ou \r dans la longueur utile pour certaines vérifications.
 * @param chaine La chaîne de caractères.
 * @return size_t La longueur.
 */
size_t longueurChaine(const char *chaine) {
    size_t len = 0;
    if (chaine == NULL) return 0; // Sécurité
    while(chaine[len] != '\0' && chaine[len] != '\n' && chaine[len] != '\r') {
        len++;
    }
    return len;
}
// --- FIN AJOUT ---