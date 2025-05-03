// utils.c (Modifié)
#include "utils.h"
#include <stdio.h> // Pour getchar, EOF

void nettoyerBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Comparaison manuelle
int compareStr(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i]) {
        char ca = (a[i] >= 'A' && a[i] <= 'Z') ? a[i] + 32 : a[i]; // minuscule
        char cb = (b[i] >= 'A' && b[i] <= 'Z') ? b[i] + 32 : b[i]; // minuscule
        if (ca != cb) return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0'; // Vrai si les deux finissent en même temps
}

// --- AJOUTER CETTE FONCTION ---
/**
 * @brief Enlève le premier caractère newline ou carriage return trouvé
 * dans une chaîne en le remplaçant par un terminateur nul.
 * Vérifie les bornes pour éviter les dépassements.
 * @param chaine La chaîne de caractères à modifier.
 * @param taille_max La taille maximale du buffer contenant la chaîne.
 */
void enleverNewline(char *chaine, size_t taille_max) {
    size_t i = 0;
    // Cherche newline, carriage return ou fin de chaîne, en respectant la taille max
    while (i < taille_max && chaine[i] != '\0' && chaine[i] != '\n' && chaine[i] != '\r') {
        i++;
    }
    // Si on est encore dans les limites du buffer, on place le terminateur nul
    if (i < taille_max) {
        chaine[i] = '\0';
    } else if (taille_max > 0) {
        // Sécurité: si on a atteint la fin du buffer sans trouver de terminateur,
        // on force le dernier caractère à être nul.
        chaine[taille_max - 1] = '\0';
    }
}
// --- FIN DE LA FONCTION AJOUTÉE ---