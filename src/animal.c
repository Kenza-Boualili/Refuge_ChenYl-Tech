#include "animal.h"
#include <stdio.h>

// Compare deux chaînes sans tenir compte de la casse
int chainesEgales(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        char ca = a[i];
        char cb = b[i];

        // Convertir en minuscule
        if (ca >= 'A' && ca <= 'Z') {
            ca += 32;
        }
        if (cb >= 'A' && cb <= 'Z') {
            cb += 32;
        }

        if (ca != cb) {
            return 0;
        }

        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

Espece chaineVersEspece(const char* str) {
    if (chainesEgales(str, "Chien")) {
        return CHIEN;
    }
    if (chainesEgales(str, "Chat")) {
        return CHAT;
    }
    if (chainesEgales(str, "Hamster")) {
        return HAMSTER;
    }
    if (chainesEgales(str, "Autruche")) {
        return AUTRUCHE;
    }
    return -1;
}

const char* especeVersChaine(Espece e) {
    switch (e) {
        case CHIEN: {
            return "Chien";
        }
        case CHAT: {
            return "Chat";
        }
        case HAMSTER: {
            return "Hamster";
        }
        case AUTRUCHE: {
            return "Autruche";
        }
        default: {
            return "Inconnu";
        }
    }
}


Espece choisirEspece() {
    int c;
    char saisie;

    while (1) {
        printf("Choisissez une espèce :\n");
        printf("1. Chien\n2. Chat\n3. Hamster\n4. Autruche\nVotre choix : ");

        if (scanf(" %c", &saisie) != 1) {
            
            while ((c = getchar()) != '\n' && c != EOF) {
                
            }
            continue;
        }

        
        if (saisie >= '1' && saisie <= '4') {
            
            if (getchar() == '\n') {
                return (Espece)(saisie - '1'); 
            } else {
                printf("Erreur : Entrez UN SEUL chiffre.\n");
                while ((c = getchar()) != '\n' && c != EOF) {
                    
                }
            }
        } else {
            printf("Erreur : chiffre entre 1 et 4 requis.\n");
        }

        
        while ((c = getchar()) != '\n' && c != EOF) {
            
        }
    }
} 
