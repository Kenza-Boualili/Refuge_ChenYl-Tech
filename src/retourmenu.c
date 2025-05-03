// retourmenu.c (Version finale propre avec fgets)
#include <stdio.h>       // Pour printf, fgets, stdin
#include "retourmenu.h"  // Contient la déclaration de demanderRetourMenu
#include "utils.h"       // Pour nettoyerBuffer (même si non utilisé ici)

#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

// SEULEMENT LA DÉFINITION DE demanderRetourMenu ICI
int demanderRetourMenu() {
    char buffer[10];

    printf("\n" YELLOW "Appuyez sur 'm' + Entrée pour retourner au menu, ou juste Entrée pour continuer... " RESET);

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        // Gérer erreur lecture
        return 0;
    }

    // Retourne 1 SEULEMENT si l'entrée est 'm' ou 'M' suivi de newline/null
    if ((buffer[0] == 'm' || buffer[0] == 'M') &&
        (buffer[1] == '\n' || (buffer[1] == '\r' && buffer[2] == '\n') || buffer[1] == '\0') ) {
         return 1; // OUI, retourner au menu
    }

    // Toute autre entrée retourne 0 (continuer)
    return 0;
}

// *** IL NE DOIT Y AVOIR RIEN D'AUTRE DANS CE FICHIER !!! ***