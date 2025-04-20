#include <stdio.h>
#include <stdlib.h>
#include "animal.h"

void adopterAnimal() {
    FILE *f = fopen("animaux/animaux.txt", "r");
    if (!f) {
        // Rouge (hex #FF0000) + Emoji erreur
        printf("\033[38;5;196mFichier animaux.txt introuvable.\033[0m 🚫\n");  
        return;
    }

    int idRecherche;
    // Bleu clair (hex #00FFFF) pour l'invite
    printf("\033[38;5;45mEntrez l'ID de l'animal à adopter : \033[0m");  
    scanf("%d", &idRecherche);

    FILE *temp = fopen("animaux/animaux_temp.txt", "w");
    if (!temp) {
        // Rouge (hex #FF0000) + Emoji erreur
        printf("\033[38;5;196mErreur lors de la création du fichier temporaire.\033[0m ❌\n");  
        fclose(f);
        return;
    }

    int trouve = 0;
    Animal a;
    char especeStr[20];

    while (fscanf(f, "%d;%49[^;];%14[^;];%d;%f;%255[^\n]",
                  &a.id, a.nom, especeStr, &a.annee_naissance, &a.poids, a.commentaire) == 6) {
        if (a.id == idRecherche) {
            trouve = 1; // Animal trouvé, donc on le saute
        } else {
            fprintf(temp, "%d;%s;%s;%d;%.2f;%s\n", a.id, a.nom, especeStr,
                    a.annee_naissance, a.poids, a.commentaire);
        }
    }

    fclose(f);
    fclose(temp);

    if (trouve) {
        remove("animaux/animaux.txt");
        rename("animaux/animaux_temp.txt", "animaux/animaux.txt");
        // Correction : Ajout de l'argument idRecherche
        printf("\033[38;5;40mL'animal avec l'ID %d a été adopté et retiré du refuge !\033[0m 🐾💖\n", idRecherche);
    } else {
        remove("animaux/animaux_temp.txt");
        // Correction : Ajout de l'argument idRecherche
        printf("\033[38;5;226mAucun animal trouvé avec l'ID %d.\033[0m 🛑\n", idRecherche);
    }
}