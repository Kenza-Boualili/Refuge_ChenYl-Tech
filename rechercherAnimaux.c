#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "animal.h"
#include "comparer.h"

// Fonction pour calculer l'âge de l'animal
static int calculerAge(int annee_naissance) {
    time_t maintenant = time(NULL);
    struct tm *tm = localtime(&maintenant);
    return tm->tm_year + 1900 - annee_naissance;
}

// Fonction pour afficher le choix du type d'âge avec des couleurs
static int menuTypeAge() {
    printf("\n\033[1;35mType d'âge :\033[0m\n"); // Texte violet
    printf("1. Jeune \033[1;32m(<2 ans)\033[0m 🐶\n");  // Vert avec emoji
    printf("2. Adulte \033[1;33m(2 à 10 ans)\033[0m 🦁\n"); // Jaune avec emoji
    printf("3. Sénior \033[1;31m(>10 ans)\033[0m 🦓\n");  // Rouge avec emoji
    printf("4. Âge exact \033[1;34m(entrer un âge)\033[0m 🎯\n");  // Bleu avec emoji
    printf("\033[1;36mChoix : \033[0m");

    int choix;
    scanf("%d", &choix);
    return choix;
}

// Fonction pour afficher un résultat trouvé 
static void afficherResultat(const Animal *a, int age) {
    printf("\n\033[1;34m=== Animal trouvé ===\033[0m\n");  // Titre bleu
    printf("\033[1;33mID\033[0m: %d\n", a->id);  // ID en jaune
    printf("\033[1;35mNom\033[0m: %s\n", a->nom);  // Nom en violet
    printf("\033[1;32mEspèce\033[0m: %s 🐾\n", especeToStr(a->espece));  // Espèce en vert avec emoji
    printf("\033[1;36mÂge\033[0m: %d ans 🎂\n", age);  // Âge en bleu avec emoji
    printf("\033[1;31mPoids\033[0m: %.2f kg ⚖️\n", a->poids);  // Poids en rouge avec emoji
    printf("\033[1;37mCommentaire\033[0m: %s\n", a->commentaire);  // Commentaire en blanc
}

void rechercherAnimaux() {
    FILE *f = fopen("animaux/animaux.txt", "r");
    if (!f) {
        printf("\033[1;31mAucun animal enregistré !\033[0m\n");  // Message d'erreur rouge
        return;
    }

    printf("\n\033[1;36m=== Mode de recherche ===\033[0m\n");  // Mode de recherche en bleu
    printf("1. Par ID 🔍\n");  // ID avec emoji
    printf("2. Par nom 📛\n");  // Nom avec emoji
    printf("3. Par âge 🕒\n");  // Âge avec emoji
    printf("\033[1;36mChoix : \033[0m");

    int choix;
    scanf("%d", &choix);

    Animal a;
    int trouve = 0;
    char buffer[256];

    switch (choix) {
        case 1: {
            int idRecherche;
            printf("\033[1;33mID à rechercher : \033[0m");
            scanf("%d", &idRecherche);

            while (fscanf(f, "%d;%49[^;];%14[^;];%d;%f;%255[^\n]",
                          &a.id, a.nom, buffer, &a.annee_naissance,
                          &a.poids, a.commentaire) == 6) {
                a.espece = strToEspece(buffer);

                if (a.id == idRecherche) {
                    afficherResultat(&a, calculerAge(a.annee_naissance));
                    trouve = 1;
                    break; // Un seul résultat attendu
                }
            }
            break;
        }

        case 2: {
            char nomRecherche[50];
            printf("\033[1;33mNom à rechercher : \033[0m");
            scanf("%49s", nomRecherche);

            while (fscanf(f, "%d;%49[^;];%14[^;];%d;%f;%255[^\n]",
                          &a.id, a.nom, buffer, &a.annee_naissance,
                          &a.poids, a.commentaire) == 6) {
                a.espece = strToEspece(buffer);

                if (comparer(a.nom, nomRecherche)) {
                    afficherResultat(&a, calculerAge(a.annee_naissance));
                    trouve = 1;
                }
            }
            break;
        }

        case 3: {
            int typeAge = menuTypeAge();
            int ageRecherche = 0;

            if (typeAge == 4) { // Si l'option est "Âge exact"
                printf("\033[1;33mÂge exact : \033[0m");
                scanf("%d", &ageRecherche);
            }

            while (fscanf(f, "%d;%49[^;];%14[^;];%d;%f;%255[^\n]",
                          &a.id, a.nom, buffer, &a.annee_naissance,
                          &a.poids, a.commentaire) == 6) {
                a.espece = strToEspece(buffer);
                int age = calculerAge(a.annee_naissance);

                // Vérifier le type d'âge sélectionné
                if ((typeAge == 1 && age < 2) ||  // Jeune
                    (typeAge == 2 && age >= 2 && age <= 10) ||  // Adulte
                    (typeAge == 3 && age > 10) ||  // Sénior
                    (typeAge == 4 && age == ageRecherche)) {  // Âge exact

                    afficherResultat(&a, age);
                    trouve = 1;
                }
            }
            break;
        }

        default:
            printf("\033[1;31mOption invalide !\033[0m\n");  // Message d'erreur rouge
            break;
    }

    if (!trouve) {
        printf("\033[1;31mAucun résultat trouvé.\033[0m\n");  // Message d'erreur rouge
    }

    fclose(f);
}