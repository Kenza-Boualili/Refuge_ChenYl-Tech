#include <stdio.h>
#include "ajouterAnimal.h"
#include "affichage.h"
#include "rechercherAnimaux.h"
#include "nettoyeur.h"
#include "adopterAnimal.h"
#include "nourriture.h"  // ➕ pour afficherNourriture()
#include "inventaire.h"

int main() {
    // Nettoyage automatique au démarrage
    nettoyerFichierAnimaux();

    int choix;
    do {
        afficherMenu();        // Affiche le menu complet
        scanf("%d", &choix);
        while (getchar() != '\n');  // Vider le buffer clavier

        switch (choix) {
            case 1:
                ajouterAnimal();
                break;
            case 2:
                rechercherAnimaux();
                break;
            case 3:
                adopterAnimal();
                break;
            case 4:
                afficherNourriture();  // ➕ calcul croquettes
                break;
                case 5: afficherInventaire(); break;
            case 6:
                printf(" Au revoir !\n");
                break;
            default:
                printf(" Choix invalide !\n");
        }

    } while (choix != 6);  // Boucle tant que l’utilisateur n’a pas choisi 5 (quitter)

    return 0;
}