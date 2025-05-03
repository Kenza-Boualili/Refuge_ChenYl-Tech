#include "animal.h"
#include <stdio.h>


int stringsEgaux(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        char ca = a[i];
        char cb = b[i];

        // Convertir en minuscule
        if (ca >= 'A' && ca <= 'Z') ca += 32;
        if (cb >= 'A' && cb <= 'Z') cb += 32;

        if (ca != cb)
            return 0;

        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

Espece strToEspece(const char* str) {
    if (stringsEgaux(str, "Chien")) return CHIEN;
    if (stringsEgaux(str, "Chat")) return CHAT;
    if (stringsEgaux(str, "Hamster")) return HAMSTER;
    if (stringsEgaux(str, "Autruche")) return AUTRUCHE;
    return -1;
}


const char* especeToStr(Espece e) {
    switch (e) {
        case CHIEN: return "Chien";
        case CHAT: return "Chat";
        case HAMSTER: return "Hamster";
        case AUTRUCHE: return "Autruche";
        default: return "Inconnu";
    }
}



Espece choisirEspece() {
    int c;
    char input;

    while (1) {
        printf("Choisissez une espèce :\n");
        printf("1. Chien\n2. Chat\n3. Hamster\n4. Autruche\nVotre choix : ");

        // Lire le premier caractère non-blanc
        if (scanf(" %c", &input) != 1) {
            // Si échec (ex: EOF), vider le buffer et recommencer
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        // Vérifier si le caractère est entre '1' et '4'
        if (input >= '1' && input <= '4') {
            // Vérifier que le caractère suivant est un '\n'
            if (getchar() == '\n') {
                return (Espece)(input - '1'); // Conversion en enum
            } else {
                printf("Erreur : Entrez UN SEUL chiffre.\n");
                while ((c = getchar()) != '\n' && c != EOF); // Vider le surplus
            }
        } else {
            printf("Erreur : Chiffre entre 1 et 4 requis.\n");
        }

        // Vider le buffer en cas d'erreur
        while ((c = getchar()) != '\n' && c != EOF);
    }
}