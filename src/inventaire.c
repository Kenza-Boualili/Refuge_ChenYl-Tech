#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "animal.h"
#include "utils.h"
#include "retourmenu.h"
#include "comparer.h"

#define PINK        "\033[1;35m"
#define GREEN       "\033[1;32m"
#define CYAN        "\033[1;36m"
#define YELLOW      "\033[1;33m"
#define RED         "\033[1;31m"
#define BLUE        "\033[1;34m"
#define WHITE       "\033[1;37m"
#define YELLOW_WARN "\033[33m"
#define RESET       "\033[0m"

struct EspeceCountResum {
    const char *nom;
    int count;
};

static int calculerAgeInventaire(int annee_naissance) {
    if (annee_naissance <= 0) return -2;
    time_t maintenant = time(NULL);
    struct tm *tm = localtime(&maintenant);
    if (tm == NULL) return -1;
    int annee_actuelle = tm->tm_year + 1900;
    if (annee_naissance > annee_actuelle || annee_naissance < 1900) return -2;
    return annee_actuelle - annee_naissance;
}

static int comparerAnimauxParEspece(const void *p1, const void *p2) {
    const Animal *a1 = (const Animal *)p1;
    const Animal *a2 = (const Animal *)p2;

    if (a1->espece < a2->espece) return -1;
    if (a1->espece > a2->espece) return 1;
    if (a1->id < a2->id) return -1;
    if (a1->id > a2->id) return 1;

    return 0;
}

static int comparerComptesResum(const void *a, const void *b) {
    const struct EspeceCountResum *ca = (const struct EspeceCountResum *)a;
    const struct EspeceCountResum *cb = (const struct EspeceCountResum *)b;
    return cb->count - ca->count;
}

void afficherInventaire() {
    printf("\n" GREEN "=== Inventaire Détaillé par Espèce ===\n" RESET);

    FILE *f = fopen("data/animaux/animaux.txt", "r");
    if (!f) {
        printf(RED "❌ Erreur fichier '%s'.\n" RESET, "data/animaux/animaux.txt");
        return;
    }

    if (demanderRetourMenu()) {
        fclose(f);
        return;
    }

    Animal refuge[MAX_ANIMAUX];
    int nb_animaux = 0;
    char ligne_lue[512];
    char buffer_espece[50];
    char buffer_commentaire[TAILLE_COMM];
    int ligne_num = 0;

    printf("\nLecture...\n");
    while (fgets(ligne_lue, sizeof(ligne_lue), f) && nb_animaux < MAX_ANIMAUX) {
        ligne_num++;
        buffer_commentaire[0] = '\0';

        int champsLus = sscanf(
            ligne_lue, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
            &refuge[nb_animaux].id,
            refuge[nb_animaux].nom,
            buffer_espece,
            &refuge[nb_animaux].annee_naissance,
            &refuge[nb_animaux].poids,
            buffer_commentaire
        );

        if (champsLus >= 5) {
            refuge[nb_animaux].espece = strToEspece(buffer_espece);
            buffer_commentaire[sizeof(buffer_commentaire) - 1] = '\0';
            snprintf(refuge[nb_animaux].commentaire, TAILLE_COMM, "%s", buffer_commentaire);
            enleverNewline(refuge[nb_animaux].commentaire, TAILLE_COMM);
            nb_animaux++;
        } else if (longueurChaine(ligne_lue) > 0) {
            printf(YELLOW_WARN "⚠️ L%d mal formatée.\n" RESET, ligne_num);
        }
    }

    if (!feof(f) && nb_animaux == MAX_ANIMAUX) {
        printf(YELLOW_WARN "\nAttention: Limite %d animaux.\n" RESET, MAX_ANIMAUX);
        while (fgets(ligne_lue, sizeof(ligne_lue), f));
    }

    fclose(f);

    if (nb_animaux <= 0) {
        printf(YELLOW_WARN "\nRefuge vide.\n" RESET);
        return;
    }

    printf("Tri...\n");
    qsort(refuge, nb_animaux, sizeof(Animal), comparerAnimauxParEspece);

    printf("\n" GREEN "--- Liste Animaux par Espèce ---\n" RESET);

    int nb_chien = 0, nb_chat = 0, nb_hamster = 0, nb_autruche = 0, nb_inconnu = 0;
    int premier_groupe = 1;
    Espece espece_precedente = refuge[0].espece;

    for (int i = 0; i < nb_animaux; i++) {
        Animal *a = &refuge[i];

        if (premier_groupe || a->espece != espece_precedente) {
            if (!premier_groupe) printf("\n");
            printf(BLUE "--- %ss ---\n" RESET, especeToStr(a->espece));
            espece_precedente = a->espece;
            premier_groupe = 0;
        }

        switch (a->espece) {
            case CHIEN:    nb_chien++; break;
            case CHAT:     nb_chat++; break;
            case HAMSTER:  nb_hamster++; break;
            case AUTRUCHE: nb_autruche++; break;
            default:       nb_inconnu++; break;
        }

        int age = calculerAgeInventaire(a->annee_naissance);

        printf(GREEN "---\n" RESET);
        printf(YELLOW " ID : %d\n" RESET, a->id);
        printf(PINK   " Nom : %s\n" RESET, a->nom);

        if (age == -1)      printf(CYAN " Âge : Err\n" RESET);
        else if (age == -2) printf(CYAN " Âge : Inv\n" RESET);
        else                printf(CYAN " Âge : %d ans\n" RESET, age);

        printf(RED   " Poids : %.2f kg\n" RESET, a->poids);
        printf(WHITE " Commentaire: %s\n" RESET, a->commentaire[0] == '\0' ? "Aucun" : a->commentaire);
    }

    printf(GREEN "-------------------------------------\n" RESET);
    printf(PINK "\n--- Résumé ---\n" RESET);

    struct EspeceCountResum counts_resum[] = {
        {"Chien", nb_chien},
        {"Chat", nb_chat},
        {"Hamster", nb_hamster},
        {"Autruche", nb_autruche}
    };

    int num_especes = sizeof(counts_resum) / sizeof(counts_resum[0]);
    qsort(counts_resum, num_especes, sizeof(struct EspeceCountResum), comparerComptesResum);

    for (int i = 0; i < num_especes; i++) {
        if (counts_resum[i].count > 0) {
            const char *emoji = "";

            if (compareStr(counts_resum[i].nom, "Chien"))        emoji = "🐕";
            else if (compareStr(counts_resum[i].nom, "Chat"))    emoji = "🐈";
            else if (compareStr(counts_resum[i].nom, "Hamster")) emoji = "🐹";
            else if (compareStr(counts_resum[i].nom, "Autruche"))emoji = "🦩";

            printf(GREEN "→ " PINK "%-10s" RESET " : %d %s\n", counts_resum[i].nom, counts_resum[i].count, emoji);
        }
    }

    if (nb_inconnu > 0) {
        printf(GREEN "→ " PINK "%-10s" RESET " : %d %s\n", "Autres", nb_inconnu, "❓");
    }

    printf(GREEN "-----------------------------\n" RESET);
    printf(PINK "Total général : %d animaux.\n" RESET, nb_animaux);
    printf(GREEN "-----------------------------\n" RESET);
}
