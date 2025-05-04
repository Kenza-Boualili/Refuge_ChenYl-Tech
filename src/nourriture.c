#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "comparer.h"

// Définition des couleurs
#define RESET         "\033[0m"
#define BLEU_CHIEN     "\033[34m"
#define VIOLET_CHAT    "\033[35m"
#define ORANGE_HAMSTER "\033[33m"
#define ROSE_AUTRUCHE  "\033[95m"
#define VERT_TOTAL     "\033[32m"

#define FILE_PATH "../data/animaux.txt"
 

// Découpe une ligne en champs séparés par ';'
int split_line(char *line, char *champs[], int max_champs) {
    int i = 0;
    char *p = line;

    while (*p && i < max_champs) {
        champs[i++] = p;
        while (*p && *p != ';' && *p != '\n') p++;
        if (*p == ';') {
            *p = '\0';
            p++;
        } else if (*p == '\n') {
            *p = '\0';
            break;
        }
    }

    return i;
}

void afficherNourriture() {
    FILE *f = fopen(FILE_PATH, "r");
    if (!f) {
        perror("Erreur ouverture du fichier des animaux");
        return;
    }

    float qte_chien = 0, qte_chat = 0, qte_hamster = 0, qte_autruche = 0;
    char ligne[256];
    char *champs[6]; // ID, nom, type, annee, poids, statut

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int annee_actuelle = t->tm_year + 1900;

    while (fgets(ligne, sizeof(ligne), f)) {
        int nb = split_line(ligne, champs, 6);
        if (nb < 5) continue;

        char *type = champs[2];
        int annee = atoi(champs[3]);
        float poids = atof(champs[4]);
        int age = annee_actuelle - annee;

        if (comparer(type, "hamster")) {
            qte_hamster += 0.020;
        } else if (comparer(type, "autruche")) {
            qte_autruche += 2.5;
        } else if (comparer(type, "chien")) {
            qte_chien += (age < 2) ? 0.5 : 0.10 * poids;
        } else if (comparer(type, "chat")) {
            qte_chat += (age < 2) ? 0.5 : 0.10 * poids;
        }
    }

    fclose(f);

    printf("\n→ Quantité de nourriture quotidienne requise :\n");

    if (qte_chien > 0)     printf(BLEU_CHIEN    "→ Chien : %.2f kg 🐕\n"     RESET, qte_chien);
    if (qte_chat > 0)      printf(VIOLET_CHAT   "→ Chat : %.2f kg 🐱\n"      RESET, qte_chat);
    if (qte_hamster > 0)   printf(ORANGE_HAMSTER"→ Hamster : %.2f kg 🐹\n"   RESET, qte_hamster);
    if (qte_autruche > 0)  printf(ROSE_AUTRUCHE "→ Autruche : %.2f kg 🦩\n"  RESET, qte_autruche);

    float total = qte_chien + qte_chat + qte_hamster + qte_autruche;
    printf("\n" VERT_TOTAL "Total : %.2f kg 🏁\n" RESET "\n", total);
}




