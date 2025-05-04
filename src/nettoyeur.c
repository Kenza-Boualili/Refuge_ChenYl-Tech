#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "nettoyeur.h"
#include "comparer.h"
#include "utils.h"

int especeValide(const char* espece) { 
    return comparer(espece,"Chien")||comparer(espece,"Chat")||comparer(espece,"Hamster")||comparer(espece,"Autruche"); 
}

void nettoyerFichierAnimaux() {
    printf("\nNettoyage fichier animaux...\n"); 
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
        printf("Err temp/backup\n");
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
        fputs(ligne, backup);
        char id[11], n[50], e[30], an[10], p[20], c[256];
        c[0] = '\0';
        int nb = sscanf(ligne, "%10[^;];%49[^;];%29[^;];%9[^;];%19[^;];%255[^\n]", id, n, e, an, p, c);

        if (nb >= 5 && especeValide(e)) {
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

    if (remove("data/animaux/animaux.txt") != 0) {
        printf("Err remove\n");
    } else if (rename("data/animaux/animaux_temp.txt", "data/animaux/animaux.txt") != 0) {
        printf("Err rename\n");
    } else {
        printf("Nettoyage OK: %d gardées, %d ignorées. Backup créé.\n", lignes_gardees, lignes_ignorees);
    }
} 
