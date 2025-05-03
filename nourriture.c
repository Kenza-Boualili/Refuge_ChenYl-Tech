// nourriture.c
#include <stdio.h>
#include <time.h>
#include "animal.h"
#include "utils.h"      // Pour comparerStr
#include "retourmenu.h" // Contient demanderRetourMenu

#define ROUGE_VIF    "\033[38;5;196m"
#define JAUNE        "\033[38;5;226m"
#define VERT_TITRE   "\033[38;5;82m"
#define BLEU_CHIEN   "\033[38;5;33m"
#define VIOLET_CHAT  "\033[38;5;61m"
#define ORANGE_HAMSTER "\033[38;5;208m"
#define ROSE_AUTRUCHE "\033[38;5;214m"
#define VERT_TOTAL   "\033[38;5;40m"
#define RESET        "\033[0m"

// Fonction helper pour calculer longueur chaîne sans string.h
size_t longueurChaineNourriture(const char *chaine) {
    size_t len = 0;
    while(chaine[len] != '\0' && chaine[len] != '\n' && chaine[len] != '\r') {
        len++;
    }
    return len;
}


void afficherNourriture() {
    printf(VERT_TITRE "\n=== Calcul des Besoins Quotidiens en Nourriture ===\n" RESET);

    FILE *f = fopen("animaux/animaux.txt", "r");
    if (!f) {
        printf(ROUGE_VIF "❌ Erreur: Fichier animaux.txt introuvable ou inaccessible.\n" RESET);
        // Pas de pause ici
        return;
    }

    // <<< Vérification si l'utilisateur veut annuler >>>
    if (demanderRetourMenu()) {
        fclose(f);
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int annee_actuelle = tm.tm_year + 1900;

    Animal a;
    float total_qte = 0;
    float qte_chien = 0;
    float qte_chat = 0;
    float qte_hamster = 0;
    float qte_autruche = 0;

    char especeLue[50];
    char commentaireLu[TAILLE_COMM];

    char ligne[512];
    while(fgets(ligne, sizeof(ligne), f)) {
        int champsLus = sscanf(ligne, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                              &a.id, a.nom, especeLue, &a.annee_naissance,
                              &a.poids, commentaireLu);

         if (champsLus >= 5) {
             int age = annee_actuelle - a.annee_naissance;
             float qte_animal = 0;

            if (compareStr(especeLue, "chien")) {
                qte_animal = (age < 2) ? 0.5f : (a.poids * 0.1f);
                qte_chien += qte_animal;
            } else if (compareStr(especeLue, "chat")) {
                qte_animal = (age < 2) ? 0.5f : (a.poids * 0.1f);
                qte_chat += qte_animal;
            } else if (compareStr(especeLue, "hamster")) {
                qte_animal = 0.02f;
                qte_hamster += qte_animal;
            } else if (compareStr(especeLue, "autruche")) {
                qte_animal = 2.5f;
                qte_autruche += qte_animal;
            } else {
                printf(JAUNE "⚠️ Espèce non reconnue pour calcul nourriture: %s (Animal ID: %d)\n" RESET, especeLue, a.id);
            }
            total_qte += qte_animal;
         } else {
             size_t len_ligne = longueurChaineNourriture(ligne); // Utilise notre fonction longueur
             if (len_ligne > 0) {
                 printf(JAUNE "⚠️ Ligne mal formatée ignorée pour calcul nourriture : %s" RESET, ligne);
             }
         }
    }

    fclose(f);

    printf("\n" VERT_TITRE "Répartition des croquettes quotidiennes nécessaires :\n" RESET);
    if (qte_chien > 0) printf(BLEU_CHIEN "→ Chien     : %.2f kg 🐕\n" RESET, qte_chien);
    if (qte_chat > 0) printf(VIOLET_CHAT "→ Chat      : %.2f kg 🐱\n" RESET, qte_chat);
    if (qte_hamster > 0) printf(ORANGE_HAMSTER "→ Hamster   : %.2f kg 🐹\n" RESET, qte_hamster);
    if (qte_autruche > 0) printf(ROSE_AUTRUCHE "→ Autruche  : %.2f kg 🦩\n" RESET, qte_autruche);

    printf("\n" VERT_TOTAL "Total général : %.2f kg 🏁\n" RESET, total_qte);

    // PAS D'APPEL A pauseOuRetourMenu() ICI

} // Fin de la fonction afficherNourriture