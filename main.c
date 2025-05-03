// main.c (Version finale confirmée)
#include <stdio.h>
#include "ajouterAnimal.h"
#include "affichage.h"
#include "rechercherAnimaux.h"
#include "nettoyeur.h"
#include "adopterAnimal.h"
#include "nourriture.h"
#include "inventaire.h"
#include "utils.h"      // Nécessaire pour nettoyerBuffer

#define RED "\033[91m"
#define RESET "\033[0m"

int main() {
    nettoyerFichierAnimaux(); // Nettoyage au démarrage

    int choix;

    do {
        afficherMenu(); // Affiche le menu principal

        // Lecture et validation du choix principal
        if (scanf("%d", &choix) != 1) {
            printf(RED "Erreur : Veuillez entrer un numéro valide.\n" RESET);
            nettoyerBuffer(); // Vider buffer
            choix = 0;        // Réinitialiser choix pour éviter sortie si ancienne valeur était 6
            continue;         // Revenir directement à l'affichage du menu
        }
        nettoyerBuffer(); // Vider buffer après lecture réussie

        // Exécuter l'action choisie
        switch (choix) {
            case 1:
                ajouterAnimal(); // ajouterAnimal gère ses propres demandes de retour menu
                break;
            case 2:
                rechercherAnimaux(); // rechercherAnimaux gère ses propres demandes
                break;
            case 3:
                adopterAnimal(); // adopterAnimal gère ses propres demandes
                break;
            case 4:
                afficherNourriture(); // afficherNourriture gère ses propres demandes
                break;
            case 5:
                afficherInventaire(); // afficherInventaire gère ses propres demandes
                break;
            case 6:
                printf(" Au revoir ! 👋\n"); // Message de sortie
                break; // Sort de la boucle while
            default:
                printf(RED " Choix invalide !\n" RESET);
                // Pas d'action spécifique, la boucle va se répéter et réafficher le menu
        }

    } while (choix != 6); // Continuer tant que l'utilisateur ne choisit pas de quitter

    return 0;
}