#include <stdio.h>
#include "../include/ajouterAnimal.h"
#include "../include/affichage.h"
#include "../include/rechercherAnimaux.h"
#include "../include/nettoyeur.h"
#include "../include/adopterAnimal.h"  
#include "../include/nourriture.h"
#include "../include/inventaire.h"   
#include "../include/utils.h"

#define ROUGE "\033[91m"
#define REINITIALISER "\033[0m"

int main() {
    nettoyerFichierAnimaux();  // Nettoie les données au démarrage

    int choix;

    do {
        afficherMenu(); // Affiche le menu principal

        if (scanf("%d", &choix) != 1) {
            printf(ROUGE "Erreur : veuillez entrer un numéro valide.\n" REINITIALISER);
            nettoyerTampon(); // vide le tampon d’entrée
            choix = 0;
            continue;
        }
        nettoyerTampon();

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
                printf(ROUGE "Choix invalide !\n" REINITIALISER);
        }

    } while (choix != 6);

    return 0;
}

