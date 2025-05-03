// retourmenu.c (Nettoyé)
#include <stdio.h>
#include "retourmenu.h" // Contient maintenant SEULEMENT demanderRetourMenu
#include "utils.h"

#define YELLOW "\033[93m"
#define RESET "\033[0m"

// Fonction pour la vérification AU DÉBUT des autres fonctions
int demanderRetourMenu() {
    char choix;
    printf("\n" YELLOW "Appuyez sur 'm' pour retourner au menu, ou une autre touche pour continuer l'action... " RESET);

    if (scanf(" %c", &choix) != 1) {
         nettoyerBuffer();
         return 0; // Ne pas retourner en cas d'erreur
    }
    nettoyerBuffer();

    if (choix == 'm' || choix == 'M') {
        return 1; // OUI, retourner au menu
    }

    return 0; // NON, continuer l'action
}

// La fonction pauseOuRetourMenu() a été supprimée d'ici.