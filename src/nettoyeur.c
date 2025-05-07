#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "nettoyeur.h"
#include "comparer.h"
#include "utils.h"

// Vérifie si l'espèce est reconnue parmi les espèces valides
int especeValide(const char* espece) {
    return comparer(espece, "Chien")
        || comparer(espece, "Chat")
        || comparer(espece, "Hamster")
        || comparer(espece, "Autruche");
}

// Nettoie le fichier des animaux en supprimant les lignes invalides
void nettoyerFichierAnimaux() {
    printf("\nNettoyage du fichier des animaux...\n");

    // Création des dossiers si nécessaire
    mkdir("data", 0755);
    mkdir("data/animaux", 0755);

    FILE *f = fopen("data/animaux/animaux.txt", "r");
    if (!f) {
        printf("Fichier '%s' introuvable.\n", "data/animaux/animaux.txt");
        return;
    }

    FILE *backup = fopen("data/animaux/animaux_backup.txt", "w");
    FILE *temp = fopen("data/animaux/animaux_temp.txt", "w");
    if (!backup || !temp) {
        printf("Erreur lors de la création des fichiers temporaires/backup.\n");
        if (f) fclose(f);
        if (backup) fclose(backup);
        if (temp) fclose(temp);
        remove("data/animaux/animaux_backup.txt");
        remove("data/animaux/animaux_temp.txt");
        return;
    }

    char ligne[512];
    int lignes_gardees = 0;
    int lignes_ignorees = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        fputs(ligne, backup);  // Sauvegarde la ligne dans l'autre fichier'
        char id[11], nom[50], espece[30], annee[10], poids[20], commentaire[256];
        commentaire[0] = '\0';

        int nb = sscanf(ligne, "%10[^;];%49[^;];%29[^;];%9[^;];%19[^;];%255[^\n]",
                        id, nom, espece, annee, poids, commentaire);

        if (nb >= 5 && especeValide(espece)) {
            fputs(ligne, temp);
            lignes_gardees++;
        } else if (longueurChaine(ligne) > 0) {
            printf("[Nettoyeur IGNORÉ] %s", ligne);
            if (ligne[longueurChaine(ligne)] != '\n') {
                printf("\n");
            }
            lignes_ignorees++;
        }
    }

    fclose(f);
    fclose(backup);
    fclose(temp);

    // Remplace l'ancien fichier par le nettoyé
    if (remove("data/animaux/animaux.txt") != 0) {
        printf("Erreur lors de la suppression de l'ancien fichier.\n");
    } else if (rename("data/animaux/animaux_temp.txt", "data/animaux/animaux.txt") != 0) {
        printf("Erreur lors du renommage du fichier nettoyé.\n");
    } else {
        printf("Nettoyage terminé : %d ligne(s) gardée(s), %d ignorée(s). Backup créé.\n", lignes_gardees, lignes_ignorees);
    }
}
