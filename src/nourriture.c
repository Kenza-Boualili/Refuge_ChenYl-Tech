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


#define RESET          "\033[0m"
#define BLEU_CHIEN     "\033[34m"
#define VIOLET_CHAT    "\033[35m"
#define ORANGE_HAMSTER "\033[33m"
#define ROSE_AUTRUCHE  "\033[95m"
#define VERT_TOTAL     "\033[32m"
#define RED_ERROR      "\033[1;31m"
#define YELLOW_WARN    "\033[33m"
#define VERT_TITRE     "\033[38;5;82m"

#define FILE_PATH "data/animaux/animaux.txt"


static int split_line(char *line, char *champs[], int max_champs) {
    int i = 0;
    char *p = line;

    if (!line) return 0;

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


void afficherNourriture() {
    printf(VERT_TITRE "\n=== Calcul Besoins Quotidiens ===\n" RESET);

    FILE *f = fopen(FILE_PATH, "r");

    if (!f) {
        printf(RED_ERROR "\n🔴 ERREUR : Fichier %s introuvable ou illisible.\n" RESET, FILE_PATH);
        return;
    }

    if (demanderRetourMenu()) {
        fclose(f);
        return;
    }

    // Initialisation des totaux par espèce
    float qte_chien = 0, qte_chat = 0, qte_hamster = 0, qte_autruche = 0;

    char ligne[256];
    int ligne_num = 0;

    time_t now = time(NULL);
    struct tm tm_info = *localtime(&now);
    int annee_actuelle = tm_info.tm_year + 1900;

    printf("\nAnalyse du fichier %s...\n", FILE_PATH);

    while (fgets(ligne, sizeof(ligne), f)) {
        ligne_num++;
        char *champs[6];

        if (longueurChaine(ligne) == 0) continue;

        int nb = split_line(ligne, champs, 6);

        if (nb < 5) {
            printf(YELLOW_WARN "⚠️ L%d: Champs insuffisants (%d/5 requis), ligne ignorée.\n" RESET, ligne_num, nb);
            continue;
        }

        
        char *type = champs[2];
        int annee;
        float poids;

        if (sscanf(champs[3], "%d", &annee) != 1 || annee < 1900 || annee > annee_actuelle + 1) {
            printf(YELLOW_WARN "⚠️ L%d: Année invalide ('%s'), ligne ignorée.\n" RESET, ligne_num, champs[3]);
            continue;
        }

        if (sscanf(champs[4], "%f", &poids) != 1 || poids <= 0) {
            printf(YELLOW_WARN "⚠️ L%d: Poids invalide ou nul ('%s'), ligne ignorée.\n" RESET, ligne_num, champs[4]);
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

  
    printf("\n=== Résultats Besoins Quotidiens ===\n");

    int animaux_comptes = 0;

    if (qte_chien > 0) {
        printf(BLEU_CHIEN "→ Chien   : %6.2f kg 🐕\n" RESET, qte_chien);
        animaux_comptes++;
    }

    if (qte_chat > 0) {
        printf(VIOLET_CHAT "→ Chat    : %6.2f kg 🐈\n" RESET, qte_chat);
        animaux_comptes++;
    }

    if (qte_hamster > 0) {
        printf(ORANGE_HAMSTER "→ Hamster : %4.2f kg 🐹\n" RESET, qte_hamster);
        animaux_comptes++;
    }

    if (qte_autruche > 0) {
        printf(ROSE_AUTRUCHE "→ Autruche: %4.2f kg 🦩\n" RESET, qte_autruche);
        animaux_comptes++;
    }

    if (animaux_comptes == 0) {
        printf(YELLOW_WARN "Aucune donnée animale valide trouvée pour calculer la nourriture.\n" RESET);
    } else {
        float total = qte_chien + qte_chat + qte_hamster + qte_autruche;
        printf(VERT_TOTAL "\nTotal : %.2f kg 🌍\n" RESET, total);
    }
}





 




