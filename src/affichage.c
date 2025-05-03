// affichage.c (Modifié pour inverser options 3 et 5)
#include <stdio.h>
#define PINK    "\033[95m"
#define YELLOW  "\033[93m"
#define CYAN    "\033[96m"
#define RESET   "\033[0m"

void afficherMenu() {
    printf(PINK "╔══════════════════════════════════════╗\n" RESET);
    printf(PINK "║ " CYAN "🏠  Bienvenue au Refuge ChenYl-Tech  " PINK "║\n" RESET);
    printf(PINK "╚══════════════════════════════════════╝\n" RESET);

    printf(YELLOW "1️⃣  Ajouter un animal        🐕 🐈\n" RESET);
    printf(YELLOW "2️⃣  Rechercher des animaux   🔍🐾\n" RESET);
    // Option 3 est maintenant Inventaire
    printf(YELLOW "3️⃣  Inventaire du refuge     📋🐾\n" RESET); 
    printf(YELLOW "4️⃣  Nourriture quotidienne   🍖🧮\n" RESET);
    // Option 5 est maintenant Adopter
    printf(YELLOW "5️⃣  Faire adopter un animal  🏡❤️\n" RESET); 
    printf(YELLOW "6️⃣  Quitter                  ❌👋\n" RESET);

    printf(CYAN "\n👉 Choix : " RESET);
}