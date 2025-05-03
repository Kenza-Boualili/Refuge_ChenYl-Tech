#include <stdio.h>

// Définition des couleurs directement ici
#define RESET         "\033[0m"
#define BLEU_CHIEN     "\033[34m"
#define VIOLET_CHAT    "\033[35m"
#define ORANGE_HAMSTER "\033[33m"
#define ROSE_AUTRUCHE  "\033[95m"
#define VERT_TOTAL     "\033[32m"

// Exemple de fonction avec indentation corrigée
void afficherNourriture(float qte_chien, float qte_chat, float qte_hamster, float qte_autruche) {
    float total_qte = qte_chien + qte_chat + qte_hamster + qte_autruche;

    if (qte_chien > 0)
        printf(BLEU_CHIEN "→ Chien : %.2f kg 🐕\n" RESET, qte_chien);

    if (qte_chat > 0)
        printf(VIOLET_CHAT "→ Chat : %.2f kg 🐱\n" RESET, qte_chat);

    if (qte_hamster > 0)
        printf(ORANGE_HAMSTER "→ Hamster : %.2f kg 🐹\n" RESET, qte_hamster);

    if (qte_autruche > 0)
        printf(ROSE_AUTRUCHE "→ Autruche : %.2f kg 🦩\n" RESET, qte_autruche);

    printf("\n" VERT_TOTAL "Total : %.2f kg 🏁\n" RESET, total_qte);
}

