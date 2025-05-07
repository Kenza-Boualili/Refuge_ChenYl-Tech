#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "comparer.h"
#include "utils.h"
#include "animal.h"
#include "retourmenu.h"

#define REINITIALISER     "\033[0m"
#define BLEU_CHIEN        "\033[34m"
#define VIOLET_CHAT       "\033[35m"
#define ORANGE_HAMSTER    "\033[33m"
#define ROSE_AUTRUCHE     "\033[95m"
#define VERT_TOTAL        "\033[32m"
#define ROUGE_ERREUR      "\033[1;31m"
#define JAUNE_AVERT       "\033[33m"
#define VERT_TITRE        "\033[38;5;82m"

#define CHEMIN_FICHIER "data/animaux/animaux.txt"

// Découpe une ligne en champs séparés par des virgules
static int decouperLigne(char *ligne, char *champs[], int max_champs) {
    int i = 0;
    char *p = ligne;

    if (!ligne) return 0;

    while (*p && i < max_champs) {
        champs[i++] = p;

        while (*p && *p != ';' && *p != '\n' && *p != '\r') p++;

        if (*p == ';' || *p == '\n' || *p == '\r') {
            *p = '\0';
            p++;
        }
    }

    return i;
}

// Calcule et affiche les besoins quotidiens en nourriture par espèce
void afficherNourriture() {
    printf(VERT_TITRE "\n=== Calcul des Besoins Quotidiens ===\n" REINITIALISER);

    FILE *f = fopen(CHEMIN_FICHIER, "r");

    if (!f) {
        printf(ROUGE_ERREUR "\n🔴 ERREUR : Fichier %s introuvable ou illisible.\n" REINITIALISER, CHEMIN_FICHIER);
        return;
    }

    if (demanderRetourMenu()) {
        fclose(f);
        return;
    }

    // Totaux par espèce
    float qte_chien = 0, qte_chat = 0, qte_hamster = 0, qte_autruche = 0;

    char ligne[256];
    int ligne_num = 0;

    time_t now = time(NULL);
    struct tm tm_info = *localtime(&now);
    int annee_actuelle = tm_info.tm_year + 1900;

    printf("\nAnalyse du fichier %s...\n", CHEMIN_FICHIER);

    while (fgets(ligne, sizeof(ligne), f)) {
        ligne_num++;
        char *champs[6];

        if (longueurChaine(ligne) == 0) continue;

        int nb = decouperLigne(ligne, champs, 6);

        if (nb < 5) {
            printf(JAUNE_AVERT "⚠️ Ligne %d : champs insuffisants (%d/5 requis), ignorée.\n" REINITIALISER, ligne_num, nb);
            continue;
        }

        char *type = champs[2];
        int annee;
        float poids;

        if (sscanf(champs[3], "%d", &annee) != 1 || annee < 1900 || annee > annee_actuelle + 1) {
            printf(JAUNE_AVERT "⚠️ Ligne %d : année invalide ('%s'), ignorée.\n" REINITIALISER, ligne_num, champs[3]);
            continue;
        }

        if (sscanf(champs[4], "%f", &poids) != 1 || poids <= 0) {
            printf(JAUNE_AVERT "⚠️ Ligne %d : poids invalide ou nul ('%s'), ignorée.\n" REINITIALISER, ligne_num, champs[4]);
            continue;
        }

        int age = annee_actuelle - annee;
        if (age < 0) age = 0;

        float qte_animal = 0;

        if (comparer(type, "hamster")) {
            qte_animal = 0.02f;
            qte_hamster += qte_animal;

        } else if (comparer(type, "autruche")) {
            qte_animal = 2.5f;
            qte_autruche += qte_animal;

        } else if (comparer(type, "chien")) {
            qte_animal = (age < 2) ? 0.5f : (0.1f * poids);
            qte_chien += qte_animal;

        } else if (comparer(type, "chat")) {
            qte_animal = (age < 2) ? 0.5f : (0.1f * poids);
            qte_chat += qte_animal;
        }
    }

    fclose(f);
    printf("Analyse terminée.\n");

    printf("\n=== Résultats des Besoins Quotidiens ===\n");

    int nb_especes = 0;

    if (qte_chien > 0) {
        printf(BLEU_CHIEN "→ Chien    : %6.2f kg 🐕\n" REINITIALISER, qte_chien);
        nb_especes++;
    }

    if (qte_chat > 0) {
        printf(VIOLET_CHAT "→ Chat     : %6.2f kg 🐈\n" REINITIALISER, qte_chat);
        nb_especes++;
    }

    if (qte_hamster > 0) {
        printf(ORANGE_HAMSTER "→ Hamster  : %4.2f kg 🐹\n" REINITIALISER, qte_hamster);
        nb_especes++;
    }

    if (qte_autruche > 0) {
        printf(ROSE_AUTRUCHE "→ Autruche : %4.2f kg 🦩\n" REINITIALISER, qte_autruche);
        nb_especes++;
    }

    if (nb_especes == 0) {
        printf(JAUNE_AVERT "Aucune donnée animale valide trouvée pour calculer la nourriture.\n" REINITIALISER);
    } else {
        float total = qte_chien + qte_chat + qte_hamster + qte_autruche;
        printf(VERT_TOTAL "\nTotal : %.2f kg 🌍\n" REINITIALISER, total);
    }
}
