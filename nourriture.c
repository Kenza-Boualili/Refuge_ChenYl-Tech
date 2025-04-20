#include <stdio.h>
#include <time.h>
#include "animal.h"
#include "utils.h"

void afficherNourriture() {
    FILE *f = fopen("animaux/animaux.txt", "r");
    if (!f) {
        // Rouge + Emoji erreur
        printf("\033[38;5;196mErreur ouverture du fichier.\033[0m ❌\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int annee_actuelle = tm.tm_year + 1900;

    Animal a;
    float total = 0;
    float croquettes_chien = 0;
    float croquettes_chat = 0;
    float croquettes_hamster = 0;
    float croquettes_autruche = 0;

    char especeLue[50];

    while (fscanf(f, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]\n",
                  &a.id, a.nom, especeLue, &a.annee_naissance,
                  &a.poids, a.commentaire) == 6) {

        int age = annee_actuelle - a.annee_naissance;
        float qte = 0;

        if (compareStr(especeLue, "hamster")) {
            qte = 0.02f;
            croquettes_hamster += qte;
        } else if (compareStr(especeLue, "autruche")) {
            qte = 2.5f;
            croquettes_autruche += qte;
        } else if (compareStr(especeLue, "chien")) {
            qte = (age < 2) ? 0.5f : a.poids * 0.1f;
            croquettes_chien += qte;
        } else if (compareStr(especeLue, "chat")) {
            qte = (age < 2) ? 0.5f : a.poids * 0.1f;
            croquettes_chat += qte;
        } else {
            // Jaune + Emoji attention pour espèce inconnue
            printf("\033[38;5;226m Espèce inconnue : %s\033[0m ⚠️\n", especeLue);
        }

        total += qte;
    }

    fclose(f);

    // ✅ Résumé par espèce :
    printf("\n\033[38;5;82mCroquettes quotidiennes nécessaires :\033[0m\n");
    if (croquettes_chien > 0)     printf("\033[38;5;33m→ Chien     : %.2f kg 🐕\033[0m\n", croquettes_chien);
    if (croquettes_chat > 0)      printf("\033[38;5;61m→ Chat      : %.2f kg 🐱\033[0m\n", croquettes_chat);
    if (croquettes_hamster > 0)   printf("\033[38;5;208m→ Hamster   : %.2f kg 🐹\033[0m\n", croquettes_hamster);
    if (croquettes_autruche > 0)  printf("\033[38;5;214m→ Autruche  : %.2f kg 🦩\033[0m\n", croquettes_autruche);

    // Total
    printf("\n\033[38;5;40m Total : %.2f kg 🏁\033[0m\n", total);
}