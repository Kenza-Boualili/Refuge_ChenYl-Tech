#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "comparer.h"
#include "utils.h"
#include "animal.h"
#include "retourmenu.h"
#include "nourriture.h"  

#define REINITIALISER     "\033[0m"
#define ROUGE_ERREUR      "\033[1;31m"
#define VERT_TITRE        "\033[38;5;82m"

#define CHEMIN_FICHIER "data/animaux/animaux.txt"


void nettoyerFichierAnimaux() {
    printf(VERT_TITRE "\n=== Nettoyage du fichier animaux ===\n" REINITIALISER);

    FILE *f = fopen(CHEMIN_FICHIER, "w"); 
    if (!f) {
        printf(ROUGE_ERREUR "Erreur : Impossible d’ouvrir le fichier %s\n" REINITIALISER, CHEMIN_FICHIER);
        return;
    }

    fclose(f);
    printf("✅ Le fichier %s a été vidé avec succès.\n", CHEMIN_FICHIER);
}
