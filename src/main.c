#include <stdio.h>
#include "ajouterAnimal.h"
#include "affichage.h"
#include "rechercherAnimaux.h"
#include "nettoyeur.h"
#include "adopterAnimal.h"  
#include "nourriture.h"
#include "inventaire.h"   
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
            case 3: 
                afficherInventaire();
                break;
            case 4:
                afficherNourriture();
                break;
            case 5: 
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