#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "animal.h"
#include "comparer.h"
#include "retourmenu.h"
#include "utils.h"
#include "affichage.h"

#define RED_BOLD    "\033[1;31m"
#define YELLOW_BOLD "\033[1;33m"
#define BLUE_BOLD   "\033[1;34m"
#define CYAN_BOLD   "\033[1;36m"
#define GREEN_BOLD  "\033[1;32m"
#define PINK        "\033[1;35m"
#define GREEN       "\033[1;32m"
#define CYAN        "\033[1;36m"
#define YELLOW      "\033[1;33m"
#define RED         "\033[1;31m"
#define WHITE       "\033[1;37m"
#define RESET       "\033[0m"

static int calculerAge(int annee_naissance) {
    if (annee_naissance <= 0) { 
        return -2; 
    }
    time_t maintenant = time(NULL);
    struct tm *tm = localtime(&maintenant);
    if (tm == NULL) { 
        return -1;
     }
    int annee_actuelle = tm->tm_year + 1900;
    if (annee_naissance > annee_actuelle || annee_naissance < 1900) {
         return -2;
         }
    return annee_actuelle - annee_naissance;
}



void rechercherAnimaux() {
    FILE *f = NULL;
    int choix_mode;
    char input_buffer[256];
    Animal a;
    char buffer_espece[50];
    char buffer_commentaire[TAILLE_COMM];
    char ligne_lue[512];
    int age_calcule;

    while (1) {
        f = fopen("data/animaux/animaux.txt", "r");
        if (!f) {
            printf(RED_BOLD "❌ Fichier '%s' introuvable.\n" RESET, "data/animaux/animaux.txt");
            return;
        }

        printf("\n" CYAN_BOLD "=== Mode recherche ===\n" RESET);
        printf("1. ID\n2. Nom\n3. Âge\n'm' menu.\n");
        printf(CYAN_BOLD "Choix : " RESET);

        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
            fclose(f);
            return;
        }

        enleverNewline(input_buffer, sizeof(input_buffer));

        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
            fclose(f);
            return;
        }

        if (sscanf(input_buffer, "%d", &choix_mode) != 1 || choix_mode < 1 || choix_mode > 3) {
            printf(RED_BOLD "Choix invalide.\n" RESET);
            printf(YELLOW_BOLD "(Rappel: 'm' menu.)\n" RESET);
            fclose(f);
            continue;
        }

        int trouve = 0;
        int action_terminee = 0;

        switch (choix_mode) {
            case 1: { // Recherche par ID
                printf(YELLOW_BOLD "ID ('r' retour, 'm' menu) : " RESET);

                if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
                    fclose(f);
                    return;
                }

                enleverNewline(input_buffer, sizeof(input_buffer));

                if (input_buffer[0] == 'm') {
                    fclose(f);
                    return;
                }

                if (input_buffer[0] == 'r') {
                    fclose(f);
                    continue;
                }

                int idRecherche;
                if (sscanf(input_buffer, "%d", &idRecherche) != 1 || idRecherche <= 0) {
                    printf(RED_BOLD "ID invalide.\n" RESET);
                    printf(YELLOW_BOLD "('r' retour, 'm' menu.)\n" RESET);
                    fclose(f);
                    continue;
                }

                rewind(f);
                while (fgets(ligne_lue, sizeof(ligne_lue), f)) {
                    buffer_commentaire[0] = '\0';

                    if (sscanf(ligne_lue, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                               &a.id, a.nom, buffer_espece,
                               &a.annee_naissance, &a.poids, buffer_commentaire) >= 5) {

                        if (a.id == idRecherche) {
                            a.espece = strToEspece(buffer_espece);
                            buffer_commentaire[sizeof(buffer_commentaire)-1] = '\0';
                            snprintf(a.commentaire, TAILLE_COMM, "%s", buffer_commentaire);
                            enleverNewline(a.commentaire, TAILLE_COMM);

                            age_calcule = calculerAge(a.annee_naissance);
                            afficherResultat(&a, age_calcule);
                            trouve = 1;
                            break;
                        }
                    }
                }

                if (!trouve) {
                    printf(YELLOW_BOLD "ID %d non trouvé.\n" RESET, idRecherche);
                }

                action_terminee = 1;
                break;
            }

            case 2: { // Recherche par nom
                printf(YELLOW_BOLD "Nom ('r' retour, 'm' menu) : " RESET);

                if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
                    fclose(f);
                    return;
                }

                enleverNewline(input_buffer, sizeof(input_buffer));

                if (input_buffer[0] == 'm') {
                    fclose(f);
                    return;
                }

                if (input_buffer[0] == 'r') {
                    fclose(f);
                    continue;
                }

                if (input_buffer[0] == '\0') {
                    printf(RED_BOLD "Nom vide.\n" RESET);
                    printf(YELLOW_BOLD "('r' retour, 'm' menu.)\n" RESET);
                    fclose(f);
                    continue;
                }

                char nomRecherche[TAILLE_NOM];
                snprintf(nomRecherche, sizeof(nomRecherche), "%.*s", (int)(sizeof(nomRecherche) - 1), input_buffer);

                rewind(f);
                while (fgets(ligne_lue, sizeof(ligne_lue), f)) {
                    buffer_commentaire[0] = '\0';

                    if (sscanf(ligne_lue, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                               &a.id, a.nom, buffer_espece,
                               &a.annee_naissance, &a.poids, buffer_commentaire) >= 5) {

                        if (comparer(a.nom, nomRecherche)) {
                            a.espece = strToEspece(buffer_espece);
                            buffer_commentaire[sizeof(buffer_commentaire)-1] = '\0';
                            snprintf(a.commentaire, TAILLE_COMM, "%s", buffer_commentaire);
                            enleverNewline(a.commentaire, TAILLE_COMM);

                            age_calcule = calculerAge(a.annee_naissance);
                            afficherResultat(&a, age_calcule);
                            trouve = 1;
                        }
                    }
                }

                if (!trouve) {
                    printf(YELLOW_BOLD "Nom '%s' non trouvé.\n" RESET, nomRecherche);
                    if (longueurChaine(nomRecherche) <= 2) {
                        printf(YELLOW_BOLD "(Rappel: 'r' retour, 'm' menu.)\n" RESET);
                    }
                }

                action_terminee = 1;
                break;
            }

            case 3: { // Recherche par âge
                int typeAge = menuTypeAge();

                if (typeAge == -1) {
                    fclose(f);
                    return;
                }

                if (typeAge == 0) {
                    fclose(f);
                    continue;
                }

                int ageRecherche = 0;
                if (typeAge == 4) {
                    printf(YELLOW_BOLD "Âge exact ('r' retour, 'm' menu) : " RESET);

                    if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
                        fclose(f);
                        return;
                    }

                    enleverNewline(input_buffer, sizeof(input_buffer));

                    if (input_buffer[0] == 'm') {
                        fclose(f);
                        return;
                    }

                    if (input_buffer[0] == 'r') {
                        fclose(f);
                        continue;
                    }

                    if (sscanf(input_buffer, "%d", &ageRecherche) != 1 || ageRecherche < 0) {
                        printf(RED_BOLD "Age invalide.\n" RESET);
                        printf(YELLOW_BOLD "('r' retour, 'm' menu.)\n" RESET);
                        fclose(f);
                        continue;
                    }
                }

                rewind(f);
                while (fgets(ligne_lue, sizeof(ligne_lue), f)) {
                    buffer_commentaire[0] = '\0';

                    if (sscanf(ligne_lue, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                               &a.id, a.nom, buffer_espece,
                               &a.annee_naissance, &a.poids, buffer_commentaire) >= 5) {

                        age_calcule = calculerAge(a.annee_naissance);
                        if (age_calcule >= 0) {
                            int correspond = (
                                (typeAge == 1 && age_calcule < 2) ||
                                (typeAge == 2 && age_calcule >= 2 && age_calcule <= 10) ||
                                (typeAge == 3 && age_calcule > 10) ||
                                (typeAge == 4 && age_calcule == ageRecherche)
                            );

                            if (correspond) {
                                a.espece = strToEspece(buffer_espece);
                                buffer_commentaire[sizeof(buffer_commentaire)-1] = '\0';
                                snprintf(a.commentaire, TAILLE_COMM, "%s", buffer_commentaire);
                                enleverNewline(a.commentaire, TAILLE_COMM);

                                afficherResultat(&a, age_calcule);
                                trouve = 1;
                            }
                        }
                    }
                }

                if (!trouve) {
                    printf(YELLOW_BOLD "Aucun trouvé critère âge.\n" RESET);
                    printf(YELLOW_BOLD "(Rappel: 'r' retour, 'm' menu.)\n" RESET);
                }

                action_terminee = 1;
                break;
            }
        } // Fin switch

        fclose(f);

        if (action_terminee) {
            if (trouve) {
                printf("\nAppuyez sur Entrée...");
                nettoyerBuffer();
            }
            return;
        }
    } // Fin while
}
