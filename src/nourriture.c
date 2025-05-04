#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include "comparer.h"

#define RESET         "\033[0m"
#define BLEU_CHIEN    "\033[34m"
#define VIOLET_CHAT   "\033[35m"
#define ORANGE_HAMSTER "\033[33m"
#define ROSE_AUTRUCHE "\033[95m"
#define VERT_TOTAL    "\033[32m"
#define FILE_PATH "data/animaux.txt"

int split_line(char *line, char *champs[], int max_champs) {
    int i = 0;
    char *p = line;

    while (*p && i < max_champs) {
        champs[i++] = p;
        while (*p && *p != ';' && *p != '\n') p++;
        if (*p == ';' || *p == '\n') {
            *p = '\0';
            p++;
        }
    }
    return i;
}

void afficherNourriture() {
    // Création de l'arborescence si nécessaire
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        if (mkdir("data", 0755)) {
            perror("Erreur création dossier data");
            return;
        }
    }
    
    // Création fichier vide si inexistant
    FILE *init = fopen(FILE_PATH, "a");
    if (init) fclose(init);

    // Debug : chemin absolu
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\n[Debug] Chemin fichier : %s/%s\n", cwd, FILE_PATH);

    FILE *f = fopen(FILE_PATH, "r");
    if (!f) {
        printf("\n🔴 ERREUR : Fichier introuvable dans :\n%s/data/\n", cwd);
        printf("Vérifiez que :\n");
        printf("- Le fichier existe bien\n");
        printf("- Il a les permissions de lecture\n");
        printf("- Il contient des données valides\n");
        return;
    }

    float qte_chien = 0, qte_chat = 0, qte_hamster = 0, qte_autruche = 0;
    char ligne[256];
    int ligne_num = 1;
    time_t now = time(NULL);
    int annee_actuelle = localtime(&now)->tm_year + 1900;

    printf("\n=== Analyse du fichier ===\n");
    
    while (fgets(ligne, sizeof(ligne), f)) {
        char *champs[6];
        int nb = split_line(ligne, champs, 6);
        
        // Debug ligne par ligne
        printf("Ligne %d : %s", ligne_num, ligne);
        
        if (nb < 5) {
            printf("⚠️ Champs insuffisants (%d/5 requis)\n", nb);
            ligne_num++;
            continue;
        }

        // Extraction données
        char *type = champs[2];
        int annee;
        float poids;
        
        if (sscanf(champs[3], "%d", &annee) != 1) {
            printf("⚠️ Année invalide : %s\n", champs[3]);
            continue;
        }
        
        if (sscanf(champs[4], "%f", &poids) != 1) {
            printf("⚠️ Poids invalide : %s\n", champs[4]);
            continue;
        }

        int age = annee_actuelle - annee;
        printf("✅ Type: %-8s | Âge: %2d | Poids: %5.2f\n", type, age, poids);

        // Calcul nourriture
        if (comparer(type, "hamster")) {
            qte_hamster += 0.02;
        } else if (comparer(type, "autruche")) {
            qte_autruche += 2.5;
        } else if (comparer(type, "chien")) {
            qte_chien += (age < 2) ? 0.5 : 0.1 * poids;
        } else if (comparer(type, "chat")) {
            qte_chat += (age < 2) ? 0.5 : 0.1 * poids;
        }
        
        ligne_num++;
    }
    fclose(f);

    // Affichage résultats
    printf("\n=== Résultats ===\n");
    if (qte_chien > 0)     printf(BLEU_CHIEN    "→ Chien : %6.2f kg 🐕\n" RESET, qte_chien);
    if (qte_chat > 0)      printf(VIOLET_CHAT   "→ Chat : %6.2f kg 🐈\n" RESET, qte_chat);
    if (qte_hamster > 0)   printf(ORANGE_HAMSTER"→ Hamster : %4.2f kg 🐹\n" RESET, qte_hamster);
    if (qte_autruche > 0)  printf(ROSE_AUTRUCHE "→ Autruche : %4.2f kg 🦩\n" RESET, qte_autruche);
    
    float total = qte_chien + qte_chat + qte_hamster + qte_autruche;
    printf(VERT_TOTAL "\nTotal : %.2f kg 🌍\n" RESET, total);
}

// Exemple d'utilisation
/*
int main() {
    afficherNourriture();
    return 0;
}
*/


 




