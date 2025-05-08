#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "animal.h"
#include "utils.h"
#include "retourmenu.h"
#include "comparer.h"

#define ROSE        "\033[1;35m"
#define VERT        "\033[1;32m"
#define CYAN        "\033[1;36m"
#define JAUNE       "\033[1;33m"
#define ROUGE       "\033[1;31m"
#define BLEU        "\033[1;34m"
#define BLANC       "\033[1;37m"
#define JAUNE_WARN  "\033[33m"
#define REINITIALISER "\033[0m"

typedef struct {
    const char *nom;
    int nb;
} ResumeEspece;

static int calculerAgeInventaire(int annee_naissance) {
    if (annee_naissance <= 0){
        return -2;
    }
    time_t maintenant = time(NULL);
    struct tm *tm = localtime(&maintenant);
    if (tm == NULL){
        return -1;
    }

    int annee_actuelle = tm->tm_year + 1900;
    if (annee_naissance > annee_actuelle || annee_naissance < 1900){
        return -2;
    }

    return annee_actuelle - annee_naissance;
}

static int comparerAnimauxParEspece(const void *p1, const void *p2) {
    const Animal *a1 = (const Animal *)p1;
    const Animal *a2 = (const Animal *)p2;

    if (a1->espece < a2->espece){
        return -1;
    }
    if (a1->espece > a2->espece){
        return 1;
    }
    if (a1->id < a2->id){
        return -1;
    }
    if (a1->id > a2->id){
        return 1;
    }

    return 0;
}

static int comparerResumeEspece(const void *a, const void *b) {
    const struct ResumeEspece *ea = (const struct ResumeEspece *)a;
    const struct ResumeEspece *eb = (const struct ResumeEspece *)b;
    return eb->nb - ea->nb;
}

void afficherInventaire() {
    printf("\n" VERT "=== Inventaire Détaillé par Espèce ===\n" REINITIALISER);

    FILE *f = fopen("data/animaux/animaux.txt", "r");
    if (f==NULL) {
        printf(ROUGE "❌ Erreur fichier '%s'.\n" REINITIALISER, "data/animaux/animaux.txt");
        return;
    }

    if (demanderRetourMenu()) {
        fclose(f);
        return;
    }

    Animal refuge[MAX_ANIMAUX];
    int nb_animaux = 0;
    char ligne[512];
    char tampon_espece[50];
    char tampon_commentaire[TAILLE_COMM];
    int numero_ligne = 0;

    printf("\nLecture...\n");
    while (fgets(ligne, sizeof(ligne), f) && nb_animaux < MAX_ANIMAUX) {
        numero_ligne++;
        tampon_commentaire[0] = '\0';

        int lus = sscanf(ligne, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                         &refuge[nb_animaux].id,
                         refuge[nb_animaux].nom,
                         tampon_espece,
                         &refuge[nb_animaux].annee_naissance,
                         &refuge[nb_animaux].poids,
                         tampon_commentaire);

        if (lus >= 5) {
            refuge[nb_animaux].espece = chaineVersEspece(tampon_espece);
            tampon_commentaire[sizeof(tampon_commentaire) - 1] = '\0';
            snprintf(refuge[nb_animaux].commentaire, TAILLE_COMM, "%s", tampon_commentaire);
            enleverSautLigne(refuge[nb_animaux].commentaire, TAILLE_COMM);
            nb_animaux++;
        } else if (longueurChaine(ligne) > 0) {
            printf(JAUNE_WARN "⚠️ Ligne %d mal formatée.\n" REINITIALISER, numero_ligne);
        }
    }

    if ((feof(f) && nb_animaux == MAX_ANIMAUX)==NULL) {
        printf(JAUNE_WARN "\nAttention : limite atteinte (%d animaux).\n" REINITIALISER, MAX_ANIMAUX);
        while (fgets(ligne, sizeof(ligne), f)); // On lit le reste pour vider
    }

    fclose(f);

    if (nb_animaux <= 0) {
        printf(JAUNE_WARN "\nRefuge vide.\n" REINITIALISER);
        return;
    }

    printf("Tri...\n");
    qsort(refuge, nb_animaux, sizeof(Animal), comparerAnimauxParEspece);

    printf("\n" VERT "--- Liste des Animaux par Espèce ---\n" REINITIALISER);

    int nb_chien = 0, nb_chat = 0, nb_hamster = 0, nb_autruche = 0, nb_inconnu = 0;
    int premier = 1;
    Espece espece_precedente = refuge[0].espece;

    for (int i = 0; i < nb_animaux; i++) {
        Animal *a = &refuge[i];

        if (premier || a->espece != espece_precedente) {
            if (premier==NULL) printf("\n");
            printf(BLEU "--- %ss ---\n" REINITIALISER, especeVersChaine(a->espece));
            espece_precedente = a->espece;
            premier = 0;
        }

        switch (a->espece) {
            case CHIEN:    nb_chien++; break;
            case CHAT:     nb_chat++; break;
            case HAMSTER:  nb_hamster++; break;
            case AUTRUCHE: nb_autruche++; break;
            default:       nb_inconnu++; break;
        }

        int age = calculerAgeInventaire(a->annee_naissance);

        printf(VERT "---\n" REINITIALISER);
        printf(JAUNE " ID : %d\n" REINITIALISER, a->id);
        printf(ROSE  " Nom : %s\n" REINITIALISER, a->nom);

        if (age == -1)      printf(CYAN " Âge : Err\n" REINITIALISER);
        else if (age == -2) printf(CYAN " Âge : Inv\n" REINITIALISER);
        else                printf(CYAN " Âge : %d ans\n" REINITIALISER, age);

        printf(ROUGE  " Poids : %.2f kg\n" REINITIALISER, a->poids);
        printf(BLANC  " Commentaire : %s\n" REINITIALISER, a->commentaire[0] == '\0' ? "Aucun" : a->commentaire);
    }

    printf(VERT "-------------------------------------\n" REINITIALISER);
    printf(ROSE "\n--- Résumé ---\n" REINITIALISER);

    ResumeEspece resume[] = {
    {"Chien", nb_chien},
    {"Chat", nb_chat},
    {"Hamster", nb_hamster},
    {"Autruche", nb_autruche}
};


    int nb_especes = sizeof(resume) / sizeof(resume[0]);
    qsort(resume, nb_especes, sizeof(struct ResumeEspece), comparerResumeEspece);

    for (int i = 0; i < nb_especes; i++) {
        if (resume[i].nb > 0) {
            const char *emoji = "";

            if (comparer(resume[i].nom, "Chien"))        emoji = "🐕";
            else if (comparer(resume[i].nom, "Chat"))    emoji = "🐈";
            else if (comparer(resume[i].nom, "Hamster")) emoji = "🐹";
            else if (comparer(resume[i].nom, "Autruche"))emoji = "🦩";

            printf(VERT "→ " ROSE "%-10s" REINITIALISER " : %d %s\n", resume[i].nom, resume[i].nb, emoji);
        }
    }

    if (nb_inconnu > 0) {
        printf(VERT "→ " ROSE "%-10s" REINITIALISER " : %d ❓\n", "Autres", nb_inconnu);
    }

    printf(VERT "-----------------------------\n" REINITIALISER);
    printf(ROSE "Total général : %d animaux.\n" REINITIALISER, nb_animaux);
    printf(VERT "-----------------------------\n" REINITIALISER);
}

   
