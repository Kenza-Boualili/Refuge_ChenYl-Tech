#include <stdio.h>
#include "animal.h"
#include "utils.h"

#define PINK    "\033[35m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

void afficherInventaire() {
    FILE *f = fopen("animaux/animaux.txt", "r");
    if (!f) {
        printf(PINK "✖ Erreur ouverture du fichier.\n" RESET);
        return;
    }

    int total = 0;
    int nb_chien = 0, nb_chat = 0, nb_hamster = 0, nb_autruche = 0;
    Animal a;
    char espece[50];

    while (fscanf(f, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]\n",
                  &a.id, a.nom, espece, &a.annee_naissance, &a.poids, a.commentaire) == 6) {
        total++;

        if (compareStr(espece, "chien")) nb_chien++;
        else if (compareStr(espece, "chat")) nb_chat++;
        else if (compareStr(espece, "hamster")) nb_hamster++;
        else if (compareStr(espece, "autruche")) nb_autruche++;
    }
    fclose(f);

    struct EspeceCount {
        const char *nom;
        int count;
    } counts[4] = {
        {"Chien", nb_chien},
        {"Chat", nb_chat},
        {"Hamster", nb_hamster},
        {"Autruche", nb_autruche}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (counts[j].count < counts[j + 1].count) {
                struct EspeceCount tmp = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tmp;
            }
        }
    }

    // Affichage avec couleurs
    printf("\n" GREEN "≡ Inventaire du refuge ≡" RESET "\n");
    printf(PINK "Total animaux : %d\n" RESET, total);
    for (int i = 0; i < 4; i++) {
        if (counts[i].count > 0)
            printf(GREEN "→ " PINK "%s" RESET " : %d\n", counts[i].nom, counts[i].count);
    }
}