#include <stdio.h>
#include "affichage.h"
#include "animal.h"

#define ROSE    "\033[95m"
#define JAUNE   "\033[93m"
#define CYAN    "\033[96m"
#define REINITIALISER  "\033[0m"

// Affiche les informations complètes d'un animal donné
void afficherResultat(const Animal *a, int age_calcule) {
    if (a == NULL) {
        return;
    }

    Animal animal = *a;  

    printf("\n--- Résultat ---\n");
    printf("ID          : %d\n", animal.id);
    printf("Nom         : %s\n", animal.nom);
    printf("Espèce      : %s\n", especeVersChaine(animal.espece));
    printf("Année Naiss : %d\n", animal.annee_naissance);
    printf("Poids       : %.2f kg\n", animal.poids);
    printf("Âge calculé : %d ans\n", age_calcule);
    printf("Commentaire : %s\n", animal.commentaire);
}
// Affiche le sous-menu pour choisir le type d’âge à afficher
int menuTypeAge(void) {
    int choix = 0;
    printf("Afficher :\n");
    printf("1. Âge réel\n");
    printf("2. Âge humain\n");
    printf("Votre choix : ");
    if (scanf("%d", &choix) != 1) {
        choix = 1;
    }
    return choix;
}

// Affiche le menu principal
void afficherMenu() {
    printf(ROSE "╔══════════════════════════════════════╗\n" REINITIALISER);
    printf(ROSE "║ " CYAN "🏠  Bienvenue au Refuge ChenYl-Tech  " ROSE "║\n" REINITIALISER);
    printf(ROSE "╚══════════════════════════════════════╝\n" REINITIALISER);

    printf(JAUNE "1️⃣  Ajouter un animal        🐕 🐈\n" REINITIALISER);
    printf(JAUNE "2️⃣  Rechercher des animaux   🔍🐾\n" REINITIALISER);
    printf(JAUNE "3️⃣  Inventaire du refuge     📋🐾\n" REINITIALISER); 
    printf(JAUNE "4️⃣  Nourriture quotidienne   🍖🧮\n" REINITIALISER);
    printf(JAUNE "5️⃣  Faire adopter un animal  🏡❤️\n" REINITIALISER); 
    printf(JAUNE "6️⃣  Quitter                  ❌👋\n" REINITIALISER);

    printf(CYAN "\n👉 Choix : " REINITIALISER);
}

