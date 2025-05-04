// main.c (Modifié pour inverser options 3 et 5)
#include <stdio.h>
#include "ajouterAnimal.h"
#include "affichage.h"
#include "rechercherAnimaux.h"
#include "nettoyeur.h"
#include "adopterAnimal.h"  // Header nécessaire pour adopterAnimal()
#include "nourriture.h"
#include "inventaire.h"     // Header nécessaire pour afficherInventaire()
#include "utils.h"

#define RED "\033[91m"
#define RESET "\033[0m"

int main() {
    nettoyerFichierAnimaux();

    int choix;

    do {
        afficherMenu(); // Affiche le nouveau menu

        if (scanf("%d", &choix) != 1) {
            printf(RED "Erreur : Veuillez entrer un numéro valide.\n" RESET);
            nettoyerBuffer();
            choix = 0;
            continue;
        }
        nettoyerBuffer();

        switch (choix) {
            case 1:
                ajouterAnimal();
                break;
            case 2:
                rechercherAnimaux();
                break;
            case 3: // Choix 3 appelle maintenant l'inventaire
                afficherInventaire();
                break;
            case 4:
                afficherNourriture();
                break;
            case 5: // Choix 5 appelle maintenant l'adoption
                adopterAnimal();
                break;
            case 6:
                printf(" Au revoir ! 👋\n");
                break;
            default:
                printf(RED " Choix invalide !\n" RESET);
        }

    } while (choix != 6);

    return 0;
}