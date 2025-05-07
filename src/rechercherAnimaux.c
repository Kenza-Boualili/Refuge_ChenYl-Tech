#include <stdio.h>
#include <stdlib.h>
#include <time.h>       

#include "../include/animal.h"     
#include "../include/comparer.h"   
#include "../include/utils.h"     
#include "../include/affichage.h"  


#ifndef REINITIALISER 
#define REINITIALISER       "\033[0m"
#define ROUGE_GRAS          "\033[1;31m"
#define VERT_GRAS           "\033[1;32m"
#define JAUNE_GRAS          "\033[1;33m"
#define BLEU_GRAS           "\033[1;34m"
#define CYAN_GRAS           "\033[1;36m"
#define MAUVE_GRAS          "\033[1;35m"
#define BLANC_GRAS          "\033[1;37m"
#endif

#define CHEMIN_FICHIER_ANIMAUX "data/animaux/animaux.txt"

// Calcule l’âge à partir de l’année de naissance
static int calculerAge(int annee_naissance) {
    if (annee_naissance <= 0) return -2;

    time_t maintenant = time(NULL);
    struct tm *tm_info = localtime(&maintenant);
    if (!tm_info) return -1;

    int annee_actuelle = tm_info->tm_year + 1900;
    if (annee_naissance > annee_actuelle || annee_naissance < 1950) return -2;

    return annee_actuelle - annee_naissance;
}

void rechercherAnimaux() {
    FILE *fichier = NULL;
    int choix;
    char tampon[512];
    Animal animal;
    char espece_temp[50];
    char commentaire_temp[TAILLE_COMM];

    while (1) {
        printf("\n" CYAN_GRAS "--- 🔍 Mode de Recherche ---\n" REINITIALISER);
        printf(BLANC_GRAS "1. Par ID 🆔\n" REINITIALISER);
        printf(MAUVE_GRAS "2. Par Nom 📛\n" REINITIALISER);
        printf(JAUNE_GRAS "3. Par Catégorie d’âge ⏳\n" REINITIALISER);
        printf(JAUNE_GRAS "➡️ Tapez 'm' pour retourner au menu principal.\n" REINITIALISER);
        printf(BLEU_GRAS "Votre choix : " REINITIALISER);

        if (!fgets(tampon, sizeof(tampon), stdin)) return;
        enleverSautLigne(tampon, sizeof(tampon));

        if ((tampon[0] == 'm' || tampon[0] == 'M') && tampon[1] == '\0') return;

        if (sscanf(tampon, "%d", &choix) != 1 || choix < 1 || choix > 3) {
            printf(ROUGE_GRAS "❌ Choix invalide. Entrez 1, 2, 3 ou 'm'.\n" REINITIALISER);
            continue;
        }

        fichier = fopen(CHEMIN_FICHIER_ANIMAUX, "r");
        if (!fichier) {
            printf(ROUGE_GRAS "\n❌ Erreur : impossible d’ouvrir le fichier.\n" REINITIALISER);
            continue;
        }

        int trouve = 0;

        switch (choix) {
            case 1: {
                printf(BLEU_GRAS "\nRecherche par ID 🆔\n" REINITIALISER);
                printf(JAUNE_GRAS "➡️ Entrez l’ID ('r' retour, 'm' menu) : " REINITIALISER);
                if (!fgets(tampon, sizeof(tampon), stdin)) { fclose(fichier); return; }
                enleverSautLigne(tampon, sizeof(tampon));

                if ((tampon[0] == 'm' || tampon[0] == 'M') && tampon[1] == '\0') { fclose(fichier); return; }
                if ((tampon[0] == 'r' || tampon[0] == 'R') && tampon[1] == '\0') { fclose(fichier); continue; }

                int idRecherche;
                if (sscanf(tampon, "%d", &idRecherche) != 1 || idRecherche <= 0) {
                    printf(ROUGE_GRAS "❌ ID invalide.\n" REINITIALISER);
                    fclose(fichier);
                    continue;
                }

                while (fgets(tampon, sizeof(tampon), fichier)) {
                    commentaire_temp[0] = '\0';
                    int lus = sscanf(tampon, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                                     &animal.id, animal.nom, espece_temp,
                                     &animal.annee_naissance, &animal.poids, commentaire_temp);

                    if (lus >= 5 && animal.id == idRecherche) {
                        animal.espece = chaineVersEspece(espece_temp);
                        snprintf(animal.commentaire, TAILLE_COMM, "%s", commentaire_temp);
                        enleverSautLigne(animal.commentaire, TAILLE_COMM);
                        int age = calculerAge(animal.annee_naissance);
                        afficherResultat(&animal, age);
                        trouve = 1;
                        break;
                    }
                }

                if (!trouve) {
                    printf(JAUNE_GRAS "❓ ID %d non trouvé.\n" REINITIALISER, idRecherche);
                }
                break;
            }

            case 2: {
                printf(BLEU_GRAS "\nRecherche par Nom 📛\n" REINITIALISER);
                printf(JAUNE_GRAS "➡️ Nom recherché ('r' retour, 'm' menu) : " REINITIALISER);
                if (!fgets(tampon, sizeof(tampon), stdin)) { fclose(fichier); return; }
                enleverSautLigne(tampon, sizeof(tampon));

                if ((tampon[0] == 'm' || tampon[0] == 'M') && tampon[1] == '\0') { fclose(fichier); return; }
                if ((tampon[0] == 'r' || tampon[0] == 'R') && tampon[1] == '\0') { fclose(fichier); continue; }

                if (tampon[0] == '\0') {
                    printf(ROUGE_GRAS "❌ Nom vide.\n" REINITIALISER);
                    fclose(fichier); continue;
                }

                char nomRecherche[TAILLE_NOM];
                snprintf(nomRecherche, sizeof(nomRecherche), "%.*s", (int)(TAILLE_NOM - 1), tampon);

                while (fgets(tampon, sizeof(tampon), fichier)) {
                    commentaire_temp[0] = '\0';
                    int lus = sscanf(tampon, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                                     &animal.id, animal.nom, espece_temp,
                                     &animal.annee_naissance, &animal.poids, commentaire_temp);

                    if (lus >= 5 && comparer(animal.nom, nomRecherche)) {
                        animal.espece = chaineVersEspece(espece_temp);
                        snprintf(animal.commentaire, TAILLE_COMM, "%s", commentaire_temp);
                        enleverSautLigne(animal.commentaire, TAILLE_COMM);
                        int age = calculerAge(animal.annee_naissance);
                        afficherResultat(&animal, age);
                        trouve++;
                    }
                }

                if (trouve == 0)
                    printf(JAUNE_GRAS "❓ Aucun animal nommé '%s' trouvé.\n" REINITIALISER, nomRecherche);
                else
                    printf(VERT_GRAS "%d correspondance(s) trouvée(s).\n" REINITIALISER, trouve);
                break;
            }

            case 3: {
                printf(BLEU_GRAS "\nRecherche par Catégorie d'âge ⏳\n" REINITIALISER);
                printf(CYAN_GRAS  "1. Jeune (< 2 ans)\n" REINITIALISER);
                printf(VERT_GRAS  "2. Adulte (2–10 ans)\n" REINITIALISER);
                printf(MAUVE_GRAS "3. Senior (> 10 ans)\n" REINITIALISER);
                printf(JAUNE_GRAS "➡️ Catégorie : " REINITIALISER);
                if (!fgets(tampon, sizeof(tampon), stdin)) { fclose(fichier); return; }
                enleverSautLigne(tampon, sizeof(tampon));

                if ((tampon[0] == 'm' || tampon[0] == 'M') && tampon[1] == '\0') { fclose(fichier); return; }
                if ((tampon[0] == 'r' || tampon[0] == 'R') && tampon[1] == '\0') { fclose(fichier); continue; }

                int cat;
                if (sscanf(tampon, "%d", &cat) != 1 || cat < 1 || cat > 3) {
                    printf(ROUGE_GRAS "❌ Catégorie invalide.\n" REINITIALISER);
                    fclose(fichier); continue;
                }

                while (fgets(tampon, sizeof(tampon), fichier)) {
                    commentaire_temp[0] = '\0';
                    int lus = sscanf(tampon, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                                     &animal.id, animal.nom, espece_temp,
                                     &animal.annee_naissance, &animal.poids, commentaire_temp);

                    if (lus >= 5) {
                        int age = calculerAge(animal.annee_naissance);
                        int correspond = 0;
                        if ((cat == 1 && age < 2) ||
                            (cat == 2 && age >= 2 && age <= 10) ||
                            (cat == 3 && age > 10)) {
                            correspond = 1;
                        }

                        if (correspond) {
                            animal.espece = chaineVersEspece(espece_temp);
                            snprintf(animal.commentaire, TAILLE_COMM, "%s", commentaire_temp);
                            enleverSautLigne(animal.commentaire, TAILLE_COMM);
                            afficherResultat(&animal, age);
                            trouve++;
                        }
                    }
                }

                if (trouve == 0)
                    printf(JAUNE_GRAS "❓ Aucun animal trouvé dans cette catégorie.\n" REINITIALISER);
                else
                    printf(VERT_GRAS "%d animal(aux) trouvé(s) dans la catégorie.\n" REINITIALISER, trouve);
                break;
            }
        }

        fclose(fichier);
        printf(JAUNE_GRAS "\nAppuyez sur Entrée pour revenir au menu..." REINITIALISER);
        nettoyerTampon();
    }
}

