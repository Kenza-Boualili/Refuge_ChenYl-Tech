#include <stdio.h>
#include "affichage.h"
#include "animal.h" 
#define PINK    "\033[95m"
#define YELLOW  "\033[93m"
#define CYAN    "\033[96m"
#define RESET   "\033[0m"
void afficherResultat(const Animal *a, int age_calcule) {
    if (!a) return;

    printf("\n--- Résultat ---\n");
    printf("ID         : %d\n", a->id);
    printf("Nom        : %s\n", a->nom);
    printf("Espèce     : %s\n", especeToStr(a->espece));
    printf("Année Naiss: %d\n", a->annee_naissance);
    printf("Poids      : %.2f kg\n", a->poids);
    printf("Âge calculé: %d ans\n", age_calcule);
    printf("Commentaire: %s\n", a->commentaire);
}

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


void afficherMenu() {
    printf(PINK "╔══════════════════════════════════════╗\n" RESET);
    printf(PINK "║ " CYAN "🏠  Bienvenue au Refuge ChenYl-Tech  " PINK "║\n" RESET);
    printf(PINK "╚══════════════════════════════════════╝\n" RESET);

    printf(YELLOW "1️⃣  Ajouter un animal        🐕 🐈\n" RESET);
    printf(YELLOW "2️⃣  Rechercher des animaux   🔍🐾\n" RESET);
    printf(YELLOW "3️⃣  Inventaire du refuge     📋🐾\n" RESET); 
    printf(YELLOW "4️⃣  Nourriture quotidienne   🍖🧮\n" RESET);
    printf(YELLOW "5️⃣  Faire adopter un animal  🏡❤️\n" RESET); 
    printf(YELLOW "6️⃣  Quitter                  ❌👋\n" RESET);

    printf(CYAN "\n👉 Choix : " RESET);
}

