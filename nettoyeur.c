#include <stdio.h>
#include "nettoyeur.h"
#include "comparer.h"  // Ajout pour utiliser la vraie fonction comparer()

int especeValide(const char* espece) {
    return comparer(espece, "Chien") ||
           comparer(espece, "Chat") ||
           comparer(espece, "Hamster") ||
           comparer(espece, "Autruche");
}

void nettoyerFichierAnimaux() {
    FILE *f = fopen("animaux/animaux.txt", "r");
    if (!f) {
        printf("Fichier animaux.txt introuvable.\n");
        return;
    }

    FILE *backup = fopen("animaux/animaux_backup.txt", "w");
    FILE *temp = fopen("animaux/animaux_temp.txt", "w");

    if (!backup || !temp) {
        printf("Erreur d'ouverture des fichiers temporaires.\n");
        fclose(f);
        return;
    }

    char ligne[512];
    while (fgets(ligne, sizeof(ligne), f)) {
        fputs(ligne, backup);

        char id[10], nom[50], espece[30], annee[10], poids[20], commentaire[256];
        int nb = sscanf(ligne, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
                        id, nom, espece, annee, poids, commentaire);

        if (nb == 6 && especeValide(espece)) {
            fputs(ligne, temp);
        } else {
            printf("[IGNORÉ] Ligne ignorée (espèce invalide ou format incorrect):\n%s", ligne);
        }
    }

    fclose(f);
    fclose(backup);
    fclose(temp);

    remove("animaux/animaux.txt");
    rename("animaux/animaux_temp.txt", "animaux/animaux.txt");

    printf("\n Nettoyage terminé. Ancien fichier sauvegardé dans animaux/animaux_backup.txt\n");
}
