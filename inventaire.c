// inventaire.c
#include <stdio.h>
#include <stdlib.h>     // Pour qsort (si utilisé)
#include "animal.h"
#include "utils.h"      // Pour comparerStr
#include "retourmenu.h" // Contient demanderRetourMenu

#define PINK    "\033[35m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

struct EspeceCount {
    const char *nom;
    int count;
};

// Fonction helper pour calculer longueur chaîne sans string.h
size_t longueurChaineInventaire(const char *chaine) {
    size_t len = 0;
    while(chaine[len] != '\0' && chaine[len] != '\n' && chaine[len] != '\r') {
        len++;
    }
    return len;
}

void afficherInventaire() {
    printf("\n" GREEN "≡ Inventaire du Refuge ≡\n" RESET);

    FILE *f = fopen("animaux/animaux.txt", "r");
    if (!f) {
        printf(PINK "❌ Erreur: Fichier animaux.txt introuvable ou inaccessible.\n" RESET);
        // Pas de pause ici
        return;
    }

    // <<< Vérification si l'utilisateur veut annuler >>>
     if (demanderRetourMenu()) {
        fclose(f);
        return;
    }

    int total_animaux = 0;
    int nb_chien = 0;
    int nb_chat = 0;
    int nb_hamster = 0;
    int nb_autruche = 0;
    int nb_inconnu = 0;

    char ligne[512];
    char especeLue[50];
    int idLu;

    while(fgets(ligne, sizeof(ligne), f)) {
         if (sscanf(ligne, "%d;%*49[^;];%49[^;];", &idLu, especeLue) == 2) {
             total_animaux++;
            if (compareStr(especeLue, "chien")) nb_chien++;
            else if (compareStr(especeLue, "chat")) nb_chat++;
            else if (compareStr(especeLue, "hamster")) nb_hamster++;
            else if (compareStr(especeLue, "autruche")) nb_autruche++;
            else nb_inconnu++;
         } else {
             size_t len_ligne = longueurChaineInventaire(ligne); // Utilise notre fonction longueur
              if (len_ligne > 0) {
                  printf(PINK "⚠️ Ligne mal formatée ignorée pour inventaire : %s" RESET, ligne);
              }
         }
    }
    fclose(f);

    struct EspeceCount counts[] = {
        {"Chien", nb_chien},
        {"Chat", nb_chat},
        {"Hamster", nb_hamster},
        {"Autruche", nb_autruche},
    };
    int num_especes_connues = sizeof(counts) / sizeof(counts[0]);

    // Tri à bulles (inchangé)
    for (int i = 0; i < num_especes_connues - 1; i++) {
        for (int j = 0; j < num_especes_connues - 1 - i; j++) {
            if (counts[j].count < counts[j + 1].count) {
                struct EspeceCount tmp = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tmp;
            }
        }
    }

    printf(PINK "Total animaux enregistrés : %d\n" RESET, total_animaux);
    printf(GREEN "-----------------------------\n" RESET);
    for (int i = 0; i < num_especes_connues; i++) {
        if (counts[i].count > 0) {
            const char *emoji = "";
            if (compareStr(counts[i].nom, "Chien")) emoji = "🐕";
            else if (compareStr(counts[i].nom, "Chat")) emoji = "🐈";
            else if (compareStr(counts[i].nom, "Hamster")) emoji = "🐹";
            else if (compareStr(counts[i].nom, "Autruche")) emoji = "🦩";
            printf(GREEN "→ " PINK "%-10s" RESET " : %d %s\n", counts[i].nom, counts[i].count, emoji);
        }
    }
     if (nb_inconnu > 0) {
         printf(GREEN "→ " PINK "%-10s" RESET " : %d %s\n", "Autres", nb_inconnu, "❓");
     }
    printf(GREEN "-----------------------------\n" RESET);


    // PAS D'APPEL A pauseOuRetourMenu() ICI

} // Fin de la fonction afficherInventaire