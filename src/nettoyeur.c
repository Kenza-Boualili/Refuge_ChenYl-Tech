#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "../include/comparer.h"
#include "../include/utils.h"
#include "../include/animal.h"
#include "../include/retourmenu.h"
#include "../include/nourriture.h"  

#define REINITIALISER     "\033[0m"
#define ROUGE_ERREUR      "\033[1;31m"
#define VERT_TITRE        "\033[38;5;82m"

#define CHEMIN_COPIE "data/animaux/animaux_copie.txt"
#define CHEMIN_NETTOYE "data/animaux/animaux.txt"

void nettoyerFichierAnimaux() {
    printf("\033[38;5;82m\n=== Nettoyage depuis la copie du fichier ===\n\033[0m");

    FILE *fichierEntree = fopen(CHEMIN_COPIE, "r");
    FILE *fichierSortie = fopen(CHEMIN_NETTOYE, "w");

    if (!fichierEntree || !fichierSortie) {
        printf("\033[1;31mErreur : impossible d’ouvrir les fichiers.\033[0m\n");
        return;
    }

    char c;
    char mot[64];
    int index = 0;
    int champ = 0;

    while ((c = fgetc(fichierEntree)) != EOF) {
        if (c == ';' || c == '\n') {
            mot[index] = '\0';

            // Majuscules seulement pour nom et espèce (champs 1 et 2)
            if (champ == 1 || champ == 2) {
                if (mot[0] >= 'a' && mot[0] <= 'z') {
                    mot[0] = mot[0] - 32;
                }
                int i = 1;
                while (mot[i] != '\0') {
                    if (mot[i] >= 'A' && mot[i] <= 'Z') {
                        mot[i] = mot[i] + 32;
                    }
                    i++;
                }
            }

            // Écriture
            int i = 0;
while (mot[i] != '\0') {
    fprintf(fichierSortie, "%c", mot[i]);
    i++;
}

if (c == ';') {
    fprintf(fichierSortie, ";");
    champ++;
} else if (c == '\n') {
    fprintf(fichierSortie, "\n");
    champ = 0;
}


            index = 0;
        } else {
            if (index < 63) {
                mot[index] = c;
                index++;
            }
        }
    }

    fclose(fichierEntree);
    fclose(fichierSortie);

    printf("\033[38;5;82mLe fichier a été nettoyé et enregistré dans animaux.txt !\n\033[0m");
}

